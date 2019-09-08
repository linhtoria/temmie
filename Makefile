CC = gcc
OBJS = main.o affects.o
# CFLAGS = -c -O2 -Wall -DDEBUG_LEV
CFLAGS = -c -O2 -Wall
LIB = -lncurses

temmie: $(OBJS)
	$(CC) $(OBJS) $(LIB) -o temmie 
	strip temmie

main.o: main.c

affects.o: affects.c

clean:
	rm -f ./*.o


