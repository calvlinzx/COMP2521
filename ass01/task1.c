// Assignment 1, Task 1

#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <sysexits.h>

#include "MMList.h"
#include "MailMessage.h"

int main (int argc, char *argv[])
{
	// Process command line args
	if (argc != 2)
		errx (EX_USAGE, "usage: %s <mailbox>", argv[0]);
	char *mailbox = argv[1];

	// Open input file
	FILE *in;                           // input file handle
	if ((in = fopen (mailbox, "r")) == NULL)
		err (EX_DATAERR, "can't open %s", mailbox);

	// Read messages and store in MMList and MMTree
	MMList msgList = newMMList ();      // list of all messages read
	MailMessage msg;                    // current mail message
	while ((msg = getMailMessage (in)) != NULL) {
		MMListInsert (msgList, msg);
	}

	printf ("\n=== List ===\n");
	showMMList (msgList);

	// Drop data structures.  We must do so carefully, as ThreadTree,
	// MMTree, and MMList can all hold references to a MailMessage, and
	// none of their destructors deallocate MailMessages.

	MMListStart (msgList);
	while ((msg = MMListNext (msgList)) != NULL)
		dropMailMessage (msg);
	dropMMList (msgList);

	return EXIT_SUCCESS;
}
