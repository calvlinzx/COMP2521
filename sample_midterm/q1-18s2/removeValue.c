// removeValue.c 
// Written by Ashesh Mahidadia, August 2017

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "DLList.h"


/* 
    You will submit only this one file.

    Implement the function "removeValue" below. Read the exam paper for 
    detailed specification and description of your task.  

    - DO NOT modify code in the file DLList.h . 
    - You can add helper functions in this file.  
    - DO NOT add "main" function in this file. 
    
*/



void removeValue(DLList L, int value){

    // only 1 item in L
    if (L->nitems == 1) {
        if (L->first->value == value) {
            DLListNode *tmp = L->first;
            free(tmp);
            L->first = L->curr = L->last = NULL;
            L->nitems--;
        }
    }
    else {
        DLListNode *n = L->first;
        while (n != NULL) {
            if (n->value == value) {
                if (n == L->first) {                    
                    L->first = L->curr = n->next;
                    //L->first->prev = NULL;
                    free(n);
                }
                else if (n == L->last) {
                    L->last = L->curr = n->prev;
                    L->last->next = NULL;
                    free(n);
                }
                else{
                    n->prev->next = n->next;
                    n->next->prev = L->curr = n->prev;
                    free(n);
                }
                n = L->curr->next;
                L->nitems--;
            }
            else {
                n = n->next;   
            }
        }
        L->curr = L->first;
    }

	return;
}



