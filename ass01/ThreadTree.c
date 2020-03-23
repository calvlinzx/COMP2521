// ThreadTree.c ... implementation of Tree-of-Mail-Threads ADT
// Written by John Shepherd, Feb 2019

#include <assert.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>

#include "MMList.h"
#include "MMTree.h"
#include "MailMessage.h"
#include "ThreadTree.h"
/*
#ifndef __unused
#define __unused __attribute__((unused))
#endif
*/
// Representation of ThreadTree's

typedef struct ThreadTreeNode *Link;

typedef struct ThreadTreeNode {
	MailMessage mesg;
	Link next, replies;
} ThreadTreeNode;

typedef struct ThreadTreeRep {
	Link messages;
} ThreadTreeRep;

// Auxiliary data structures and functions

// Add any new data structures and functions here ...

static void doDropThreadTree (Link t);
static void doShowThreadTree (Link t, int level);
static Link newTTNode (MailMessage message);
static Link TTLinkSearch (Link l, char *id);
static void insertNext(Link head, Link node);
// END auxiliary data structures and functions

// create a new empty ThreadTree
ThreadTree newThreadTree (void)
{
	ThreadTreeRep *new = malloc (sizeof *new);
	if (new == NULL) err (EX_OSERR, "couldn't allocate ThreadTree");
	*new = (ThreadTreeRep) { };
	return new;
}

void dropThreadTree (ThreadTree tt)
{
	assert (tt != NULL);
	doDropThreadTree (tt->messages);
}

// free up memory associated with list
static void doDropThreadTree (Link t)
{
	if (t == NULL)
		return;

	for (Link curr = t, next; curr != NULL; curr = next) {
		next = curr->next;
		doDropThreadTree (curr->replies);
		// don't drop curr->mesg, in case referenced elsehwere
		free (curr);
	}
}

void showThreadTree (ThreadTree tt)
{
	assert (tt != NULL);
	doShowThreadTree (tt->messages, 0);
}

// display thread tree as hiearchical list
static void doShowThreadTree (Link t, int level)
{
	if (t == NULL)
		return;
	for (Link curr = t; curr != NULL; curr = curr->next) {
		showMailMessage (curr->mesg, level);
		doShowThreadTree (curr->replies, level + 1);
	}
}

// insert mail message into ThreadTree
// if a reply, insert in appropriate replies list
// whichever list inserted, must be in timestamp-order
ThreadTree ThreadTreeBuild (MMList mesgs, MMTree msgids)
{
    assert(mesgs != NULL);
    assert(MMListIsOrdered(mesgs));
    assert(msgids != NULL);
    
    // initiate the new thread tree
    ThreadTree tt = newThreadTree();
    
    // initiate the root of the thread tree
    MMListStart(mesgs);         
    MailMessage msg = MMListNext(mesgs);
    tt->messages = newTTNode(msg);
    
    // traverse the MMList
    while (!MMListEnd(mesgs)) {
        msg = MMListNext(mesgs); 
        Link curr = newTTNode(msg);
        
        //if current message is replying to no one
        if (MailMessageRepliesTo(msg) == NULL) {
            // insert current to the next field of root
            insertNext(tt->messages, curr);
        }
        //if current message is replying to someone in the Thread Tree
        else {
            char *reply_id = MailMessageRepliesTo(msg);
            
            // find the node in thread tree that current is replying to
            Link search_res ult = TTLinkSearch(tt->messages, reply_id);
            
            //if the result message has no reply
            if (search_result->replies == NULL) {
                //insert current to the replies field of search_result
                search_result->replies = curr;
            }
            //if the result message already has reply
            else {
                //insert current to the next field of search_result
                insertNext(search_result->replies,curr);                  
            }
        }
    }            
    
	return tt;
}

//create new thread tree node
static Link newTTNode (MailMessage message)
{
    Link new = malloc(sizeof(ThreadTreeNode));
    assert(new != NULL);
    new->mesg = message;
    new->next = new->replies = NULL;
    return new;
}

// Return a link in Thread Tree by searching the ID
static Link TTLinkSearch (Link l, char *id)
{
	if (l == NULL) {
		return NULL;
    }
    //if the ID of l is the same as id
	else if (strcmp(MailMessageID(l->mesg), id) == 0) {
        return l;
	}
	else {
	    Link result = NULL;
	    //search the next field of l 
	    if (l->next != NULL) {
	        result = TTLinkSearch(l->next, id);
	        if (result != NULL) {
	            return result;
	        }
	    }
	    //search the replies field of l
	    if (l->replies != NULL) {
	        result = TTLinkSearch(l->replies, id);
	        if (result != NULL) {
	            return result;
	        }
	    } 
	    return result;
	}

}

// insert node to the next field of head 
static void insertNext(Link head, Link node) {
    Link L = head;
    while (L->next != NULL) {
        L = L->next; 
    }    
    L->next = node;
}
