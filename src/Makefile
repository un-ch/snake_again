CC	= gcc

CFLAGS	= -Wall -ggdb -ansi -pg -O0 -MMD -MP -fdiagnostics-color=never -fno-diagnostics-show-caret
CFLAGS	+= -fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all -fsanitize=float-divide-by-zero
CFLAGS	+= -static-libasan
CFLAGS	+= -fsanitize=float-cast-overflow -fno-sanitize=null -fno-sanitize=alignment

LIBS	= -lncurses
MAIN_BIN= main

MODULES	= main.o screen.o string.o display_message.o end_program.o objects.o get_random_number.o \
		coordinates.o barrier.o target.o snake_object.o round_settings.o handle_direction.o \
		continue_game_request.o borders.o color.o dot_background.o

DEPS	= $(MODULES:.o=.d)

all: $(MAIN_BIN) tags

%.o:	%.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(MAIN_BIN): $(MODULES)
	@$(CC) $(CFLAGS) $(MODULES) $(LIBS) -o $@

.PHONY: run valg clean

run:	$(MAIN_BIN)
	@./$(MAIN_BIN)

valg:
	@valgrind --tool=memcheck --leak-check=full ./$(BUILD_DIR)/$(MAIN_BIN) 2>VALG_LOG

tags:
	@ctags -R -n --c-kinds=+p --fields=+iaS --extras=+q

clean:
	@rm -f *.o *.i *.d *.s $(MAIN_BIN)

# dependency files:
-include $(DEPS)
