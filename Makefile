CC=g++
CFLAGS=-Wall

all:
	$(CC) $(CFLAGS) main.cpp account.cpp -o memo
	touch account.txt
clean:
	rm -rf *.o memo
	rm -rf *.txt
