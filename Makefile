###==================================================
#
#
#	12/7/2017
#
#	Makefile
#
#	written by Timothy Lo
#
#
#====================================================


CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c99
OBJECTS = coder.o model.o AR.o
OBJECTS1 = test test.o
OBJECTS2 = ARcoder ARcoder.o 

.PHONY	:	all
all	:	coder.o model.o AR.o ARcoder.o ARcoder

test	:
	$(CC) $(CFLAGS) -o $(OBJECTS1) $(OBJECTS) -lm

test.o 	:	test.c
	$(CC) $(CFLAGS) -c test.c 

ARcoder:	
	$(CC) $(CFLAGS) -o $(OBJECTS2) $(OBJECTS) -lm

ARcoder.o 	:	ARcoder.c
	$(CC) $(CFLAGS) -c ARcoder.c

model.o 	:	model.c
	$(CC) $(CFLAGS) -c model.c

coder.o 	: 	coder.c
	$(CC) $(CFLAGS) -c coder.c

AR.o 	:	AR.c
	$(CC) $(CFLAGS) -c AR.c

.PHONY	:	clean
clean	:       
	rm -f $(OBJECTS2) $(OBJECTS1) $(OBJECTS) 

#valgrind --leak-check=full [NAME OF EXECUTABLE]
