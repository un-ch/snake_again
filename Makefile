SRCMODULES =\
	#simple_snake_game.c

OBJMODULES = $(SRCMODULES:.c=.o)
CFLAGS = -g -Wall -ansi -pedantic
%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

simple_snake_game: simple_snake_game.c -lncurses $(OBJMODULES)
	$(CC) $(CFLAGS) $^ -o $@

run: simple_snake_game
	./simple_snake_game

clean:
	rm -f *.o simple_snake_game
