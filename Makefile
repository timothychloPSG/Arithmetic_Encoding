CC = gcc
CFLAGS = -Wall -Wextra -Werror -Wpedantic
OBJECTS1 = test test.o
OBJECTS = coder.o model.o

.PHONY	:	all
all	:	coder.o model.o test.o test

test	:
	$(CC) $(CFLAGS) -o $(OBJECTS1) $(OBJECTS) -g
# gcc -Wall -Wextra -Werror -Wpedantic -o coder.o model.o test test.o -g

test.o 	:	test.c
	$(CC) $(CFLAGS) -c test.c 

model.o 	:	model.c
	$(CC) $(CFLAGS) -c model.c

coder.o 	: 	coder.c
	$(CC) $(CFLAGS) -c coder.c

#EDset.o        :       EDset.c
#       $(CC) $(CFLAGS) -c EDset.c

.PHONY	:	clean
clean	:       
	rm -f $(OBJECTS1) $(OBJECTS)

#valgrind --leak-check=full [NAME OF EXECUTABLE]
