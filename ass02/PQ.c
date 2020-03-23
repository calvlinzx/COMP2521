// PQ ADT interface for Ass2 (COMP2521)
#include "PQ.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

static struct PQNode *newNode(ItemPQ element);
static bool sameKey(PQ pq, ItemPQ element);
static void insertPQNode(PQ pq, ItemPQ element);
static void reorder(PQ pq, ItemPQ element);

typedef struct PQNode {
	ItemPQ item;
	struct PQNode *next;
} PQNode;

struct PQRep {
	struct PQNode *first;
};


PQ newPQ() {
	// allocate memory for PQ
	PQ pq = malloc(sizeof(PQ));
	assert(pq != NULL);
	pq->first = NULL;

	return pq;
}

int PQEmpty(PQ pq) {
	if (pq->first != NULL) {
		return 1;
	}

	return 0;
}

void addPQ(PQ pq, ItemPQ element) {
    // check if PQ is valid
	assert(pq != NULL);
    
	// if element is not in PQ
	// insert that element into PQ with ascending value
    if (sameKey(pq, element) == false) {      
        insertPQNode(pq, element);
    }
	// if element is already in PQ
	// update PQ
    else {
        updatePQ(pq, element);
    }
}

ItemPQ dequeuePQ(PQ pq) {
	// check if PQ is valid
	assert(pq != NULL);

	// remove the element with the smallest value
	ItemPQ throwAway = pq->first->item;
	struct PQNode *n = pq->first;
	pq->first = pq->first->next;
	free(n);
	
	return throwAway;
}

void updatePQ(PQ pq, ItemPQ element) {
    // check if PQ is valid
    assert(pq != NULL);

	// if no element in PQ 
	if (pq->first == NULL) {
		return;
	}

	struct PQNode *curr = pq->first;
	struct PQNode *toUpdate;
	// traverse all the elements in PQ
	while (curr != NULL) {
		// find the element with the same key in PQ
		if (curr->item.key == element.key) {
			toUpdate = curr;
			break;
		}
		curr = curr->next;
	}
	// if no element in PQ has the same key
	if (toUpdate == NULL) {
		return;
	}
	// there is element with the same key
	toUpdate->item = element;
	// if only one element in queue
	if (pq->first->next == NULL) {
		return;
	}
	// if the first element is same as toUpdate
	// and element has smaller value than the second element in PQ
	if ((pq->first == toUpdate) && ((element.value) < (pq->first->next->item).value)) {
		return;
	}

	// reorder PQ
	reorder(pq, element);
	return;
}

void  showPQ(PQ pq) {
    assert(pq != NULL);
    
    if (pq->first == NULL) {
        printf("Nothing in PQ");
    }
    for (struct PQNode *n = pq->first; n != NULL; n = n->next) {
        printf("Key:%d , value:%d\n", n->item.key, n->item.value);
    }
}

void  freePQ(PQ pq) {
    struct PQNode *tmp;
    struct PQNode *head = pq->first;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
    free(pq);
}

//--------Helper functions-----------

// create and return a new PQNode
static struct PQNode *newNode(ItemPQ element) {
	struct PQNode *new = malloc(sizeof(struct PQNode));
	assert(new != NULL);
	new->item = element;
	new->next = NULL;
	return new;
}

// return true if the element in PQ has the same key as the element's
static bool sameKey(PQ pq, ItemPQ element) {  
    for (struct PQNode *n = pq->first; n != NULL; n = n->next) {
        if (n->item.key == element.key) {
            return true;
        }
    }
    return false;
}

// insert PQNode into PQ in ascending order of value
static void insertPQNode(PQ pq, ItemPQ element) {
    struct PQNode *new = newNode(element);
        // if nothing in PQ
		if (pq->first == NULL) {
            pq->first = new;
        }
		// if first in PQ has greater value than element's
        else if (pq->first->item.value > element.value) {
            new->next = pq->first;
            pq->first = new;
        }
        else {
            struct PQNode *n = pq->first;
            while (n->next != NULL && n->item.value > element.value){
                n = n->next;
            }
            new->next = n->next;
            n->next = new;
        }
}

// reorder PQ
static void reorder(PQ pq, ItemPQ element) {
	struct PQNode *curr = pq->first;
	struct PQNode *toUpdate;
	struct PQNode *prev;
	
	// if first in PQ has the same key as element's
	if (curr->item.key == element.key) {
	    toUpdate = curr;
	    pq->first = pq->first->next;
	} 
	else {
	    while (curr->next != NULL && (curr->next->item).key != element.key) {
		    curr = curr->next;
	    }
	    prev = curr;
	    toUpdate = curr->next;
	    //connect prev node to update's next
	    prev->next = toUpdate->next;
	}
	
	//add updated node to appropriate pos
	if (element.value <= (pq->first->item).value) {
		toUpdate->next = pq->first;
		pq->first = toUpdate;
		return;
	}
	curr = pq->first;
	while (curr->next != NULL && (curr->next->item).value < element.value) {
		curr = curr->next;
	}
	toUpdate->next = curr->next;
	curr->next = toUpdate;
	return;
}

