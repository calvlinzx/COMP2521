# COMP2521 19T1 ... assignment 1

#
# 3c turns on the following interesting flags (and a few more):
#
#     -Weverything                  turn on every possible warning, except...
#     -Wno-padded                   ... structure padding,
#     -Wno-reserved-id-macro        ... underscores leading macro names,
#     -Wno-gnu                      ... use of GNU extensions,
#     -Wno-c++-compat               ... and C++ ABI compatibility.
#
#     -std=gnu11                    select ISO C11 with GNU extensions.
#     -D_DEFAULT_SOURCE             avoid precise POSIX and irritating
#     -D_BSD_SOURCE                 ISO C compliance; enable all this C
#     -D_SVID_SOURCE                implementation's features.
#     -D_GNU_SOURCE                 expressivity > standards compliance
#
#     -lm                           include the math library
#     -ldl                          include the runtime linker library
#     -rdynamic                     export dynamic symbols
#     -g                            emit debugging symbols
#
#     -fsanitize=address            enable AddressSanitizer
#     -fsanitize=undefined          enable UndefinedBehaviourSanitizer
#     -fno-omit-frame-pointer       leave stack frame pointers in
#     -fno-optimize-sibling-calls   don't try tail-call optimisation
#
CC	 = 2521 3c

.PHONY: all
all:	task1 task2 task3

task1:		task1.o DateTime.o MailMessage.o MMList.o
task1.o:	task1.c DateTime.h MailMessage.h MMList.h

task2:		task2.o DateTime.o MailMessage.o MMList.o MMTree.o
task2.o:	task2.c DateTime.h MailMessage.h MMList.h MMTree.h

task3:		task3.o DateTime.o MailMessage.o MMList.o MMTree.o ThreadTree.o
task3.o:	task3.c DateTime.h MailMessage.h MMList.h MMTree.h ThreadTree.h

DateTime.o:	DateTime.c DateTime.h
MailMessage.o:	MailMessage.c MailMessage.h DateTime.h
MMTree.o:	MMTree.c MMTree.h MailMessage.h
MMList.o:	MMList.c MMList.h MailMessage.h
ThreadTree.o:	ThreadTree.c ThreadTree.h MailMessage.h MMList.h MMTree.h

.PHONY: check
check: task1 task2 task3
	./check

.PHONY: clean
clean:
	-rm -f task1 task1.o
	-rm -f task2 task2.o
	-rm -f task3 task3.o
	-rm -f DateTime.o MailMessage.o MMTree.o MMList.o ThreadTree.o
	-rm -f tests/*.out
