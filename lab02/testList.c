// testList.c - testing DLList data type
// Written by John Shepherd, March 2013

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "DLList.h"

#define MAX_LINE 10000

static void checkCurrState(DLList L, char *it);
static void showCurrState(DLList L);

int main (void)
{
	DLList myList = getDLList (stdin);
	//putDLList (stdout, myList);
	assert (validDLList (myList));

	// TODO: more tests needed here
    
    //test 1: Insert before current line   
    printf("\n------------Test1:Insert before current line---------\n\n");
    char *it1 = "This is going to be the new first";
    DLListBefore (myList, it1);
    assert (validDLList (myList));
    checkCurrState(myList, it1);
    
    //test 2: Add after current line   
    printf("\n------------Test2:Add after current line-------------\n\n");
    char *it2 = "This is going to be the new second";
    DLListAfter (myList, it2);
    assert (validDLList (myList));
    checkCurrState(myList, it2);
    
    //test 3: Delete current line   
    printf("\n------------Test3:Delete current line-------------\n\n");
    DLListDelete (myList);
    assert (validDLList (myList));
    showCurrState(myList);
    
    //test 4: Delete current line again   
    printf("\n------------Test4:Delete current line again----------\n\n");
    DLListDelete (myList);
    assert (validDLList (myList));
    showCurrState(myList);
    
    //test 5: Add a line after deleting   
    printf("\n------------Test5:Add after current line-------------\n\n");
    char *it5 = "New line for test5!!!";
    DLListAfter (myList, it5);
    assert (validDLList (myList));
    checkCurrState(myList, it5);
        
    //test 6: Add a line after the last line   
    printf("\n------------Test6:Add after last line-------------\n\n");
    DLListMoveTo(myList, MAX_LINE);
    char *it6 = "This is going to be the last (test 6)";
    DLListAfter (myList, it6);
    assert (validDLList (myList));
    checkCurrState(myList, it6);
    
    //test 7: Insert a line before the last line   
    printf("\n------------Test6:Insert before last line------------\n\n");
    char *it7 = "This is going to be the second last (test 7)";
    DLListBefore (myList, it7);
    assert (validDLList (myList));
    checkCurrState(myList, it7);
    
    //test 8: Delete all the lines    
    printf("\n------------Test8: Delete all lines------------------\n\n");
    while (DLListIsEmpty(myList) == false) {
        DLListDelete (myList);
    }
    assert (validDLList (myList));
    showCurrState(myList);
    
    //free the list
	freeDLList (myList);
	return EXIT_SUCCESS;
}

static void checkCurrState(DLList L, char *it) {
    assert(strcmp(it,DLListCurrent(L)) == 0);    
    printf("Show current text:\n");
    putDLList (stdout, L);
    printf("\nNumber of items is: %zu\n", DLListLength(L));
}

static void showCurrState(DLList L) {
    printf("Show current text:\n");
    putDLList (stdout, L);
    printf("\nNumber of items is: %zu\n", DLListLength(L));
    printf("\nCurrent line is: %s\n", DLListCurrent(L));
}
