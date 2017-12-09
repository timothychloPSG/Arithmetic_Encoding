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
OBJECTS1 = test test.o
OBJECTS = coder.o model.o

.PHONY	:	all
all	:	IOtester.o IOtester coder.o model.o test.o test

test	:
	$(CC) $(CFLAGS) -o $(OBJECTS1) $(OBJECTS) -g

IOtester:	
	$(CC) $(CFLAGS) -o IOtester IOtester.o -g

IOtester.o 	:	IOtester.c
	$(CC) $(CFLAGS) -c IOtester.c

test.o 	:	test.c
	$(CC) $(CFLAGS) -c test.c 

model.o 	:	model.c
	$(CC) $(CFLAGS) -c model.c

coder.o 	: 	coder.c
	$(CC) $(CFLAGS) -c coder.c

.PHONY	:	clean
clean	:       
	rm -f $(OBJECTS1) $(OBJECTS) IOtester.o IOtester

#valgrind --leak-check=full [NAME OF EXECUTABLE]
