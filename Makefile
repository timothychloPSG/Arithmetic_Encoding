CC = gcc
CFLAGS = -Wall -Wextra -Werror -Wpedantic
OBJECTS1 = test test.o 
OBJECTS = coder.o model.o

.PHONY	:	all 
all :	test

test 	:	test.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $(OBJECTS1) $(OBJECTS) -g

model.o 	:	model.c 
	$(CC) $(CFLAGS) -c model.c

coder.o 	: 	coder.c 
	$(CC) $(CFLAGS) -c coder.c

#EDset.o 	:	EDset.c
#	$(CC) $(CFLAGS) -c EDset.c

.PHONY	:	clean
clean	:	
	rm -f $(OBJECTS1) $(OBJECTS)

#valgrind --leak-check=full [NAME OF EXECUTABLE]