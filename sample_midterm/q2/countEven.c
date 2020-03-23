/* countEven.c 
   Written by Ashesh Mahidadia, October 2017
*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "BSTree.h"
/* 
    You will submit only this one file.

    Implement the function "countEven" below. Read the exam paper for 
    detailed specification and description of your task.  

    - You can add helper functions in this file, if required.  

    - DO NOT modify code in the file BSTree.h . 
    - DO NOT add "main" function in this file. 
*/
//int countTotal(BSTree t);

int countEven(BSTree t){

	int count = 0;

	// Implement this function, 
	// also change the return value below!
	if (t == NULL) {
	    return count;
	}
	else if (t->left == NULL && t->right == NULL) {
	    return count;
	}
	else {
	    if (t->left == NULL || t->right == NULL) {
	        count = countEven(t->left) + countEven(t->right) + 1;
	    }
	    else {
	        count = countEven(t->left) + countEven(t->right);
	    }
	}
	//int n = countTotal(t) - 1;
	
	return count;

}
/*
int countTotal(BSTree t){


	// Implement this function, 
	// also change the return value below!
	if (t == NULL) {
	    return 0;
	}
	else {
	    //if (t->key % 2 == 0) {
	         return countEven(t->left) + countEven(t->right) + 1;
	    //}
	    //else {
	      //  count = countEven(t->left) + countEven(t->right);
	    //}
	}

}
*/
