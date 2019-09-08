CC = gcc
OBJS = main.o
# CFLAGS = -c -O2 -Wall -DDEBUG_LEV
CFLAGS = -c -O2 -Wall
LIB = -lncurses

main.o: main.c

clean:
	rm -f ./*.o


