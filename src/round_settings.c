#include <stddef.h>
#include <ncurses.h>
#include <stdlib.h>

#include "round_settings.h"
#include "borders.h"
#include "end_program.h"
#include "event.h"
#include "coordinates.h"
#include "display_message.h"
#include "snake_object.h"
#include "target.h"
#include "screen.h"
#include "dot_background.h"

void
init_round_settings(struct round_settings **cfg)
{
	(*cfg) = NULL;
	(*cfg) = malloc(sizeof(struct round_settings));

	if (!(*cfg)) {
		end(malloc_err);
	}

	reset_settings(cfg);
}

void
reset_settings(struct round_settings **cfg)
{
	int max_x, max_y, barrier_amount;

	getmaxyx(stdscr, max_y, max_x);
	barrier_amount = (max_y + max_x) * 3;

	(*cfg)->round_num = 1;
	(*cfg)->current_snake_length = 1;
	(*cfg)->snake_speed = 200;
	(*cfg)->max_barrier_amount = barrier_amount;

	apply_snake_speed((*cfg)->snake_speed);
}

void
game_settings_increase(struct round_settings *cfg)
{
	cfg->round_num += 1;
	cfg->current_snake_length = 1;
	cfg->snake_speed -= 30;
	cfg->max_barrier_amount += 150;

	apply_snake_speed(cfg->snake_speed);
}

void
game_settings_decrease(struct round_settings *cfg)
{
	cfg->round_num -= 1;
	cfg->current_snake_length = 1;
	cfg->snake_speed += 30;
	cfg->max_barrier_amount -= 150;

	apply_snake_speed(cfg->snake_speed);
}
