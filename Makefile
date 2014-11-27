CC=g++
CFLAGS=-Wall -O2

all:
	$(CC) $(CFLAGS) main.cpp account.cpp -o memo
	touch account.txt
clean:
	rm -rf *.o memo
	rm -rf account.txt
