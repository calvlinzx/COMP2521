// MMList.h ... interface to Lists-of-Mail-Messages ADT
// Written by John Shepherd, Feb 2019

#ifndef MMLIST_H
#define MMLIST_H

#include <stdbool.h>
#include "MailMessage.h"

// External view of MMList

typedef struct MMListRep *MMList;

// create a new empty MMList
MMList newMMList (void);

// free up memory associated with list
void dropMMList (MMList);

// display list as one integer per line on stdout
void showMMList (MMList);

// insert mail message in order
// ordering based on MailMessageDate
void MMListInsert (MMList, MailMessage);

// check whether a list is ordered (by MailMessageDate)
bool MMListIsOrdered (MMList);

// start scan of an MMList
void MMListStart (MMList);

// get next item during scan of an MMList
MailMessage MMListNext (MMList);

// check whether MMList scan is complete
bool MMListEnd (MMList);

#endif
