# COMP2521 19T1 ... lab 3 code

CC	= 2521 3c

.PHONY: all
all:	bst mkrand mkpref

bst:		bst.o BSTree.o Queue.o
bst.o:		bst.c BSTree.h
BSTree.o:	BSTree.c BSTree.h Queue.h
Queue.o:	Queue.c Queue.h

mkrand:		mkrand.o
mkpref:		mkpref.o

.PHONY: test
test: bst
	(cd tests && ${MAKE})

.PHONY: clean
clean:
	-rm -f bst bst.o BSTree.o Queue.o
	-rm -f mkrand mkrand.o
	-rm -f mkpref mkpref.o
	-rm -f tests/*.observed

.PHONY: give
give: BSTree.c test5.txt test6.txt
	give cs2521 lab03 $^
