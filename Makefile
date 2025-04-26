CC 	= gcc

CFLAGS 	= -Wall -ggdb -ansi -pg -O0 -MMD -MP -fdiagnostics-color=never -fno-diagnostics-show-caret -save-temps --verbose
CFLAGS	+= -fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all -fsanitize=float-divide-by-zero
CFLAGS	+= -static-libasan
CFLAGS	+= -fsanitize=float-cast-overflow -fno-sanitize=null -fno-sanitize=alignment
CFLAGS	+= -I

LIBS		= -lncurses

MAIN_BIN	= main

# directories definitions:
BUILD_DIR 	= build
INCLUDE_DIR	= include
SRC_DIR 	= src

CURRENT_TARGET		= $@
FIRST_PREREQUISITE	= $<
ALL_PREREQUISITES	= $^

SRC_FILES = $(SRC_DIR)/screen.c \
	$(SRC_DIR)/string.c	\
	$(SRC_DIR)/display_message.c \
	$(SRC_DIR)/end_program.c \
	$(SRC_DIR)/objects.c \
	$(SRC_DIR)/get_random_number.c \
	$(SRC_DIR)/coordinates.c \
	$(SRC_DIR)/barrier.c \
	$(SRC_DIR)/target.c	\
	$(SRC_DIR)/snake_object.c \
	$(SRC_DIR)/round_settings.c \
	$(SRC_DIR)/handle_direction.c \
	$(SRC_DIR)/continue_game_request.c \
	$(SRC_DIR)/borders.c \
	$(SRC_DIR)/color.c \
	$(SRC_DIR)/dot_background.c \

# set object files to the build directory:
OBJECT_FILES = $(subst \
	$(SRC_DIR), \
	$(BUILD_DIR), \
	$(SRC_FILES:.c=.o))

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDE_DIR)/%.h
	@$(CC) $(CFLAGS)$(INCLUDE_DIR) -c $(FIRST_PREREQUISITE) -o $(CURRENT_TARGET)

# targets:
$(MAIN_BIN): \
	$(SRC_DIR)/$(MAIN_BIN).c \
	$(LIBS) \
	$(OBJECT_FILES)
	@$(CC) $(CFLAGS) $(INCLUDE_DIR) $(ALL_PREREQUISITES) -o \
	$(BUILD_DIR)/$(CURRENT_TARGET)

.PHONY: run valg clean

run: $(MAIN_BIN)
	@./$(BUILD_DIR)/$(MAIN_BIN)

valg:
	@valgrind --tool=memcheck --leak-check=full ./$(BUILD_DIR)/$(MAIN_BIN) 2>VALG_LOG

clean:
	@rm -f	$(BUILD_DIR)/*.o $(BUILD_DIR)/$(MAIN_BIN)
