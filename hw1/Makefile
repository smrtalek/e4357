CC = gcc

strcmp: strcmp.o
	$(CC) -Wall -o $@ $^

strcmp.o: strcmp.c
	$(CC) -Wall -c $<

clean:
	rm -rf strcmp.o strcmp
