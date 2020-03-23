// MailMessage.c ... implementation of Mail Message ADT
// Written by John Shepherd, Feb 2019

#include <assert.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>

#include "DateTime.h"
#include "MailMessage.h"

// according to RFC5322
#define MAXLINE 1000

// data structures to represent Mail Messages

typedef struct MailMessageRep {
	char *id;	  // "Message-ID:" field (id format)
	char *subject; // "Subject:" field (free text)
	char *from;	// "From:" field (email address)
	DateTime date; // "Date:" field (parsed)
	char *replyTo; // "Reply-To:" field (as for id)
} MailMessageRep;

// create new Mail Message object
MailMessage newMailMessage (void)
{
	MailMessageRep *new = malloc (sizeof *new);
	if (new == NULL) err (EX_OSERR, "couldn't allocate MailMessage");
	*new = (MailMessageRep) { };
	return new;
}

void dropMailMessage (MailMessage msg)
{
	assert (msg != NULL);

	dropDateTime (msg->date);
	free (msg->id);
	free (msg->subject);
	free (msg->from);
	free (msg->replyTo);
	free (msg);
}

// read next Mail Message from open file
// return NULL if find EOF instead of message
MailMessage getMailMessage (FILE *input)
{
	char *status;
	char line[MAXLINE];

	// scan until find start of new message or EOF
	while ((status = fgets (line, MAXLINE, input)) != NULL) {
		// found start of another message
		if (strncmp (line, "From ", 5) == 0)
			break;
	}
	if (status == NULL)
		return NULL; // no more messages

	// make a new empty MailMessage structure
	MailMessage new = newMailMessage ();

	// scan headers, collecting useful data
	// - we compare against the first i chars for the header
	// - we copy from index i+1 to skip the space after the header
	while (fgets (line, MAXLINE, input) != NULL) {
		// strip trailing '\n'
		line[strlen (line) - 1] = '\0';
		// check if it's one of the interesting header fields
		if (strncasecmp (line, "Message-ID:", 11) == 0)
			new->id = strdup (&line[12]);
		else if (strncasecmp (line, "Subject:", 8) == 0)
			new->subject = strdup (&line[9]);
		else if (strncasecmp (line, "From:", 5) == 0)
			new->from = strdup (&line[6]);
		else if (strncasecmp (line, "Date:", 5) == 0)
			new->date = scanDateTime (&line[6]);
		else if (strncasecmp (line, "In-Reply-To:", 12) == 0)
			new->replyTo = strdup (&line[13]);
		else if (strcmp (line, "") == 0)
			break; // end of headers
		else
			/* ignore all other headers */;
	}

	// we MUST have a timestamp for each message
	assert (new->date != NULL);

	// after scanning headers, we stop at the start of message body
	// the message body will be scanned (and skipped) in next call

	return new;
}

// display Mail Message on stdout with indentation
static void indent (int n)
{
	int i;
	for (i = 0; i < n; i++)
		putchar (' ');
}

void showMailMessage (MailMessage mesg, int nsp)
{
	assert (mesg != NULL);
	indent (3 * nsp);
	printf ("/----------\n");
	indent (3 * nsp);
	printf ("| M-ID: %s\n", mesg->id);
	indent (3 * nsp);
	printf ("| Subj: %s\n", mesg->subject);
	indent (3 * nsp);
	printf ("| From: %s\n", mesg->from);
	// no \n for date because ctime gives one
	indent (3 * nsp);
	printf ("| Date: ");
	showDateTime (mesg->date);
	indent (3 * nsp);
	printf ("| Repl: %s\n", mesg->replyTo);
	indent (3 * nsp);
	printf ("\\----------\n");
}

// get ID of mail message
char *MailMessageID (MailMessage mesg)
{
	assert (mesg != NULL);
	return mesg->id;
}

// get timestamp of mail message
DateTime MailMessageDateTime (MailMessage mesg)
{
	assert (mesg != NULL);
	return mesg->date;
}

// get in-reply-to field of mail message
char *MailMessageRepliesTo (MailMessage mesg)
{
	assert (mesg != NULL);
	return mesg->replyTo;
}
