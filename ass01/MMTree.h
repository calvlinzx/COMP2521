// MMTree.h ... interface to Mail Message search tree ADT
// Written by John Shepherd, Feb 2019

#ifndef MMTREE_H
#define MMTREE_H

#include "MailMessage.h"

// external view of MMTree

typedef struct MMTreeRep *MMTree;

// create an empty MMTree
MMTree newMMTree (void);

// free memory associated with MMTree
void dropMMTree (MMTree);

// display a MMTree (sideways)
void showMMTree (MMTree);

// insert a new message into a MMTree
// message is indexed by a string ID
MMTree MMTreeInsert (MMTree, char *, MailMessage);

// check wheth  er a message with ID is in a MMTree
MailMessage MMTreeFind (MMTree, char *);

#endif
