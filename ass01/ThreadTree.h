// ThreadTree.h ... interface to Tree-of-Mail-Threads ADT
// Written by John Shepherd, Feb 2019

#ifndef THREAD_TREE_H
#define THREAD_TREE_H

#include "MMList.h"
#include "MMTree.h"
#include "MailMessage.h"

// External view of ThreadTree

typedef struct ThreadTreeRep *ThreadTree;

// create a new empty ThreadTree
ThreadTree newThreadTree (void);

// free up memory associated with list
void dropThreadTree (ThreadTree);

// display list as one integer per line on stdout
void showThreadTree (ThreadTree);

// insert mail message in order
// if message is a reply, 3rd arg says what it's a reply to
// ordering based on MailMessageDate
ThreadTree ThreadTreeBuild (MMList, MMTree);

#endif
