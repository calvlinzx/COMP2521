// MMList.c ... implementation of List-of-Mail-Messages ADT
// Written by John Shepherd, Feb 2019

#include <assert.h>
#include <err.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>

#include "MMList.h"
#include "MailMessage.h"

// data structures representing MMList

typedef struct MMListNode *Link;

typedef struct MMListNode {
	MailMessage data; // message associated with this list item
	Link next;		  // pointer to node containing next element
} MMListNode;

typedef struct MMListRep {
	Link first; // node containing first value
	Link last;  // node containing last value
	Link curr;  // current node (for iteration)
} MMListRep;

static Link newMMListNode (MailMessage mesg);


// create a new empty MMList
MMList newMMList (void)
{
	MMListRep *new = malloc (sizeof *new);
	if (new == NULL) err (EX_OSERR, "couldn't allocate MMList");
	*new = (MMListRep) { };
	return new;
}

// free up memory associated with list
// note: does not remove Mail Messages
void dropMMList (MMList L)
{
	assert (L != NULL);
	Link curr = L->first;
	while (curr != NULL) {
		Link next = curr->next;
		free (curr);
		curr = next;
	}
	free (L);
}

// display list as one integer per line on stdout
void showMMList (MMList L)
{
	assert (L != NULL);
	for (Link curr = L->first; curr != NULL; curr = curr->next)
		showMailMessage (curr->data, 0);
}

// insert mail message in order
// ordering based on MailMessageDateTime
void MMListInsert (MMList L, MailMessage mesg)
{
	// You need to change the following and
	// implement this function
	assert(L != NULL);
	assert(MMListIsOrdered(L));
	assert(mesg != NULL);
	
	// create new MMList node
	Link new = newMMListNode(mesg);
	
	// get the time of the new message
	DateTime newDate = MailMessageDateTime(mesg);
	
	// if L is empty
	if (L->first == NULL) {
	    L->first = L->last = L->curr = new;
	}
	// if the time of new message is ahead of the first's
    else if (!DateTimeAfter(newDate, MailMessageDateTime(L->first->data))) {
	    new->next = L->first;
	    L->first = L->curr = new;
	}
	// if the time of the new message is after the last's
	else if(DateTimeAfter(newDate, MailMessageDateTime(L->last->data))) {
	    L->last->next = new;
	    L->last = L->curr = new;
	    new->next = NULL;
	}
	// if the time of the new message is in the middle
	else {
	    Link curr = L->first;
	    Link prev;
	    while (curr->next != NULL) {	    
	        prev = curr;
	        curr = curr->next;
	        // find the messages that are before and after the new message 
	        if (DateTimeAfter(newDate,MailMessageDateTime(prev->data))
	        && !DateTimeAfter(newDate,MailMessageDateTime(curr->data))) {
	            prev->next = new;
	            new->next = curr;
	            break;    
	        }
	    }
	}
}

// create a new MMListNode for mail message
// (this function is used only within the ADT)
static Link newMMListNode (MailMessage mesg)
{
	Link new = malloc (sizeof *new);
	if (new == NULL) err (EX_OSERR, "couldn't allocate MMList node");
	*new = (MMListNode) { .data = mesg };
	return new;
}

// check whether a list is ordered (by MailMessageDate)
bool MMListIsOrdered (MMList L)
{
	DateTime prevDate = NULL;
	for (Link n = L->first; n != NULL; n = n->next) {
		DateTime currDate = MailMessageDateTime (n->data);
		if (prevDate != NULL && DateTimeAfter (prevDate, currDate))
			return false;
		prevDate = currDate;
	}
	return true;
}

// start scan of an MMList
void MMListStart (MMList L)
{
	assert (L != NULL);
	L->curr = L->first;
}

// get next item during scan of an MMList
MailMessage MMListNext (MMList L)
{
	assert (L != NULL);
	if (L->curr == NULL)
		// this is probably an error
		return NULL;

	MailMessage mesg = L->curr->data;
	L->curr = L->curr->next;
	return mesg;
}

// check whether MMList scan is complete
bool MMListEnd (MMList L)
{
	assert (L != NULL);
	return (L->curr == NULL);
}
