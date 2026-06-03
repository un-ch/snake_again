#include <stddef.h>
#include <stdlib.h>
#include <ncurses.h>

#include "event.h"
#include "barrier.h"
#include "borders.h"
#include "coordinates.h"
#include "color.h"
#include "end_program.h"
#include "handle_direction.h"
#include "objects.h"
#include "round_settings.h"
#include "screen.h"
#include "snake_object.h"
#include "string.h"
#include "target.h"

void
handle_event(struct snake_type **snake,
		struct coordinates_list **tar,
		struct coordinates_list **bar,
		struct round_settings *cfg,
		struct coordinates *crd)
{
	display_in_fog_of_war((*snake)->first->coord, *tar, *bar);

	if (border_collision((*snake)->first->coord) ||
	    barrier_collision((*snake)->first->coord, *bar)) {
		game_settings_decrease(cfg);

		if (cfg->round_num < 1) {
			if (resuming()) {
				reset_settings(cfg);
				setup_objects(snake, tar, bar, *cfg, crd);

				/* TODO: better solution should be done: */
				return;

			} else {
				cleanup(snake, tar, bar);
				end(quit);
			}
		}

		setup_objects(snake, tar, bar, *cfg, crd);
	}

	if (target_collision((*snake)->first->coord, tar)) {
		update_after_contact_with_target(snake, cfg);

		if (cfg->current_snake_length > max_snake_length) {
			game_settings_increase(cfg);
			
			if (cfg->round_num > max_round_num) {
				end(win);
			}

			setup_objects(snake, tar, bar, *cfg, crd);
		}
	}
}

static int
get_user_input(void)
{
	int answer;

	while (answer = getch()) {
		switch (answer) {
		case key_yes:
			return 1;
		case key_no:
		case key_escape:
			return 0;
		default:
			break;
		}
	}
}

int
resuming(void)
{
	const char quest[] = "Crash! Would you like to continue the game?";
	int max_y, max_x, rc, len;

	getmaxyx(stdscr, max_y, max_x);
	len = string_length(quest);

	clear_screen();
	move(max_y / 2, (max_x - len - 1) / 2);
	set_color(gray_on_black);
	addstr(quest);

	len = string_length("(y) (n)");

	move((max_y / 2) + 2, (max_x - len - 1) / 2);
	addstr("(y) (n)");

	rc = get_user_input();

	return rc;
}

void
cleanup(struct snake_type **snake,
	struct coordinates_list **tar,
	struct coordinates_list **bar)
{
	if (*snake) {
		delete_coordinate_list(&((*snake)->first));
		(*snake)->last = NULL;
	}

	if (*tar) {
		delete_coordinate_list(tar);
	}

	if (*bar) {
		delete_coordinate_list(bar);
	}
}

void
release_mem(struct snake_type **snake,
		struct coordinates_list **tar,
		struct coordinates_list **bar)
{
	cleanup(snake, tar, bar);

	if ((*snake) != NULL) {
		free((*snake)->last_direction);
		free(*snake);
		(*snake)->last_direction = NULL;
		(*snake) = NULL;
	}
}
