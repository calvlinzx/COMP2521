// Assignment 1, Task 2

#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <sysexits.h>

#include "MMList.h"
#include "MMTree.h"
#include "MailMessage.h"
#include "ThreadTree.h"

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
	MMTree msgIDs = newMMTree ();       // search tree of Message-ID's
	MailMessage msg;                    // current mail message
	while ((msg = getMailMessage (in)) != NULL) {
		MMListInsert (msgList, msg);
		MMTreeInsert (msgIDs, MailMessageID (msg), msg);
	}

	// Build thread tree from msgList and msgIDs
	// Assumes that messages in mgsList are in timestamp order
	ThreadTree threads = ThreadTreeBuild (msgList, msgIDs);

	// Display thread tree
	showThreadTree (threads);

	// Drop data structures.  We must do so carefully, as ThreadTree,
	// MMTree, and MMList can all hold references to a MailMessage, and
	// none of their destructors deallocate MailMessages.
	dropThreadTree (threads);
	dropMMTree (msgIDs);

	MMListStart (msgList);
	while ((msg = MMListNext (msgList)) != NULL)
		dropMailMessage (msg);
	dropMMList (msgList);

	return EXIT_SUCCESS;
}
