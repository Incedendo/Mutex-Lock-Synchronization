OBJS = LinkList.o queue.o oscp3.o 
CC = gcc
DEBUG = -g
CFLAGS = -I. -pthread -c $(DEBUG)
LFLAGS = $(DEBUG)

oscp3: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o oscp3

testList: testList.o LinkList.o
	$(CC) $(LFLAGS) testList.o LinkList.o -o testList

testQueue: testQueue.o queue.o
	$(CC) $(LFLAGS) testQueue.o queue.o -o testQueue

testList.o: testList.c 
	$(CC) $(CFLAGS) testList.c 

testQueue.o: testQueue.c 
	$(CC) $(CFLAGS) testQueue.c 

LinkList.o: LinkList.h LinkList.c
	$(CC) $(CFLAGS) LinkList.c

queue.o: queue.h queue.c
	$(CC) $(CFLAGS) queue.c

oscp3.o: oscp3.c LinkList.h queue.h
	$(CC) $(CFLAGS) oscp3.c

clean:
	rm oscp3.o
	rm LinkedList.o
	rm queue.o
	rm oscp3
	rm testList.o
	rm testList
	rm testQueue
	rm testQueue.o

