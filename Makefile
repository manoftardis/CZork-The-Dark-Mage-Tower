CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pedantic -g
MAIN = zork
INCS = object.h player.h room.h door.h utility.h
SRC = zork.c object.c player.c room.c door.c

.PHONY: prep all clean

all: $(MAIN)

$(MAIN): $(SRC)
	$(CC) $(CFLAGS) $(INCS) -o $(MAIN) $(SRC)

clean:
	$(RM) *.o *~ $(MAIN)
