// MailMessage.h ... interface to Mail Message ADT
// Written by John Shepherd, Feb 2019

#ifndef MAIL_MESSAGE_H
#define MAIL_MESSAGE_H

#include <stdio.h>
#include <time.h>

#include "DateTime.h"

// External view of MailMessage

typedef struct MailMessageRep *MailMessage;

// create new Mail Message object
MailMessage newMailMessage (void);

// free up memory associated with mail message
void dropMailMessage (MailMessage);

// read next Mail Message from open file
// return NULL if find EOF instead of message
MailMessage getMailMessage (FILE *);

// display Mail Message on stdout (with indentation)
void showMailMessage (MailMessage, int);

// get ID of mail message
char *MailMessageID (MailMessage);

// get timestamp of mail message
DateTime MailMessageDateTime (MailMessage);

// get in-reply-to field of mail message
char *MailMessageRepliesTo (MailMessage);

#endif
