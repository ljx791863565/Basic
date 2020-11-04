CC = gcc
CFLAGS = -O2 -Wall -I .
LIB = -lpthread

ser: tiny.c csapp.o rio.o 
	$(CC) $(CFLAGS) -o ser tiny.c csapp.o rio.o $(LIB)
rio.o: rio.c
	$(CC) $(CFLAGS) -c rio.c -o rio.o
csapp.o: csapp.c  
	$(CC) $(CFLAGS) -c csapp.c  -o csapp.o $(LIB)
clean:
	rm -f *.o ser *~
