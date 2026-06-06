CC	= gcc
CFLAGS	= -Wall -ggdb -ansi -O0 -MMD -MP -fdiagnostics-color=never -fno-diagnostics-show-caret
LIBS	= -lncurses
MAIN_BIN= snake_again

MODULES	= main.o screen.o string.o display_message.o end_program.o \
	objects.o get_random_number.o coordinates.o barrier.o target.o \
	snake_object.o round_settings.o handle_direction.o borders.o \
	color.o dot_background.o event.o

DEPS	= $(MODULES:.o=.d)

all: tags $(MAIN_BIN)

%.o:	%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(MAIN_BIN): $(MODULES)
	$(CC) $(MODULES) $(LIBS) -o $@

.PHONY: run clean

run:	$(MAIN_BIN)
	@./$(MAIN_BIN)

tags:
	@ctags -R -n --c-kinds=+p --fields=+iaS --extras=+q

valg:
	valgrind -s --tool=memcheck --leak-check=full --track-origins=yes \
	--show-leak-kinds=all --log-file=VALG_LOG ./$(MAIN_BIN)

clean:
	rm -f *.o *.i *.d *.s tags $(MAIN_BIN)

# dependency files:
-include $(DEPS)
