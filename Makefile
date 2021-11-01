
CC			=	gcc
CFLAGS		=	-Wall -g -I

# directories definitions:
BUILD_DIR	=	build
INCLUDE_DIR	=	include
SRC_DIR		=	src

SRC_FILES	=	$(SRC_DIR)/screen.c \
				$(SRC_DIR)/string.c \
				$(SRC_DIR)/display_message.c \
				$(SRC_DIR)/end_program.c \
				$(SRC_DIR)/objects.c \
				$(SRC_DIR)/get_random_number.c \
				$(SRC_DIR)/coordinate.c

# set object files to the build directory:
OBJECT_FILES=	$(subst \
				$(SRC_DIR), \
				$(BUILD_DIR), \
				$(SRC_FILES:.c=.o))

HEADER_FILES=	$(wildcard $(INCLUDE_DIR)/*.h)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDE_DIR)/%.h
	@$(CC) $(CFLAGS)$(INCLUDE_DIR) -c $< -o $@

# targets:
simple_snake_game: $(SRC_DIR)/simple_snake_game.c -lncurses \
	$(OBJECT_FILES)
	@$(CC) $(CFLAGS) $(INCLUDE_DIR) $^ -o $(BUILD_DIR)/$@

.PHONY: run
run: simple_snake_game
	@./$(BUILD_DIR)/simple_snake_game

.PHONY: clean
clean:
	@rm -f	$(BUILD_DIR)/*.o $(BUILD_DIR)/simple_snake_game

.PHONY: delete_files
delete_files:
	@rm -f	$(BUILD_DIR)/* $(SRC_DIR)/* $(INCLUDE_DIR)/*
