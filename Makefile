CC			= gcc
EXECUTABLE	= dequeue-tests.exe
SRC			= ./src/

all: tests.o dequeue.o
	$(CC) -o $(EXECUTABLE) tests.o dequeue.o

tests.o: tests.c
	$(CC) -c tests.c

dequeue.o: $(SRC)dequeue.c
	$(CC) -c $(SRC)dequeue.c

run:
	$(EXECUTABLE)

clean:
	del $(EXECUTABLE) *.o