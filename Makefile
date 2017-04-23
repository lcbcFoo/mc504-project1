# Makefile

CC=clang
CFLAGS=-std=c99 -Wall -pedantic -lncurses -lpthread -g


all:
	$(CC) $(CFLAGS) *.c -o animation

clean:
	rm -rf animation
