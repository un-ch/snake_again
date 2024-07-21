CC 		= gcc
CFLAGS 	= -Wall -I
LIBS 	= -lncurses

PRJ_TITLE = another_snake_game

# directories definitions:
BUILD_DIR 	= build
INCLUDE_DIR = include
SRC_DIR 	= src

CURRENT_TARGET 		= $@
FIRST_PREREQUISITE 	= $<
ALL_PREREQUISITES 	= $^

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

HEADER_FILES = $(wildcard $(INCLUDE_DIR)/*.h)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDE_DIR)/%.h
	@$(CC) $(CFLAGS)$(INCLUDE_DIR) -c $(FIRST_PREREQUISITE) -o $(CURRENT_TARGET)

# targets:
$(PRJ_TITLE): \
	$(SRC_DIR)/$(PRJ_TITLE).c \
	$(LIBS) \
	$(OBJECT_FILES)
	@$(CC) $(CFLAGS) $(INCLUDE_DIR) $(ALL_PREREQUISITES) -o \
	$(BUILD_DIR)/$(CURRENT_TARGET)

.PHONY: run
run: $(PRJ_TITLE)
	@./$(BUILD_DIR)/$(PRJ_TITLE)

ifneq (clean, $(MAKECMDGOALS))
-include deps.mk
endif

deps.mk: $(SRC_FILES)
	$(CC) -MM $(ALL_PREREQUISITES) > $(CURRENT_TARGET)

.PHONY: clean
clean:
	@rm -f	$(BUILD_DIR)/*.o $(BUILD_DIR)/$(PRJ_TITLE)
