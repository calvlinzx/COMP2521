// getPeaks.c 
// Written by Ashesh Mahidadia, August 2017

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "DLList.h"

static DLList insertNode(DLList L, int v);

/* 
    You will submit only this one file.

    Implement the function "getPeaks" below. Read the exam paper for 
    detailed specification and description of your task.  

    - DO NOT modify code in the file DLList.h . 
    - You can add helper functions in this file.  
    - DO NOT add "main" function in this file. 
    
*/

DLList getPeaks(DLList L){
	DLList peaksL = newDLList();
    if (L->nitems > 2) {
        for (struct DLListNode *n = L->first; n->next->next != NULL; n = n->next) {
            if (n->value > n->next->value && n->next->value > n->next->next->value) {
                peaksL = insertNode(peaksL, n->next->value);  
            }
        }
    }
    
    
	return peaksL;

}

static DLList insertNode(DLList L, int v) {
    struct DLListNode *new = newDLListNode(v);
    
    if (L->first == NULL) {
        L->first = L->last = L->curr = new;
        L->nitems++;
    }
    else {
        L->curr->next = new;
        new->prev = L->curr;
        L->curr = L->last = new;
        L->nitems++;
    }
    return L;
}




