CC = gcc
OBJS = main.o blit.o util.o
# CFLAGS = -c -O2 -Wall -DDEBUG_LEV
CFLAGS = -c -O2 -Wall
LIB = -lncurses

temmie: $(OBJS)
	$(CC) $(OBJS) $(LIB) -o temmie 
	strip temmie

main.o: main.c

blit.o: blit.c

util.o: util.c

clean:
	rm -f ./*.o


