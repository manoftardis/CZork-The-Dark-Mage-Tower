CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pedantic -g
MAIN = zork
SRC = zork.c object.c player.c room.c door.c utility.c
OBJ = $(SRC:.c=.o)

.PHONY: all clean

all: $(MAIN)

$(MAIN): $(OBJ)
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o *~ $(MAIN)
