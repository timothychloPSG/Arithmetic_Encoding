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
OBJECTS2 = IOtester IOtester.o 

.PHONY	:	all
all	:	coder.o model.o AR.o IOtester.o IOtester  #test.o test

#test	:
#	$(CC) $(CFLAGS) -o $(OBJECTS1) $(OBJECTS) -lm

IOtester:	
	$(CC) $(CFLAGS) -o $(OBJECTS2) $(OBJECTS) -lm

IOtester.o 	:	IOtester.c
	$(CC) $(CFLAGS) -c IOtester.c

test.o 	:	test.c
	$(CC) $(CFLAGS) -c test.c 

model.o 	:	model.c
	$(CC) $(CFLAGS) -c model.c

coder.o 	: 	coder.c
	$(CC) $(CFLAGS) -c coder.c

AR.o 	:	AR.c
	$(CC) $(CFLAGS) -c AR.c

.PHONY	:	clean
clean	:       
	rm -f $(OBJECTS1) $(OBJECTS) IOtester.o IOtester

#valgrind --leak-check=full [NAME OF EXECUTABLE]
