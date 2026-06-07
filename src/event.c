#include <stddef.h>
#include <stdlib.h>
#include <ncurses.h>

#include "event.h"
#include "barrier.h"
#include "borders.h"
#include "coordinates.h"
#include "color.h"
#include "end_program.h"
#include "objects.h"
#include "round_settings.h"
#include "screen.h"
#include "snake_object.h"
#include "string.h"
#include "target.h"

void
init(struct event_ctx *ctx)
{
	init_screen();
	init_snake_object(&ctx->snk);
	init_direction(&ctx->dir);
	init_round_settings(&ctx->cfg);
}

static void
on_none(struct event_ctx *ctx)
{

}

static void
on_resuming(struct event_ctx *ctx)
{
	reset_settings(&ctx->cfg);
	setup_objects(ctx);
}

static void
on_barrier_collision(struct event_ctx *ctx)
{
	game_settings_decrease(ctx->cfg);

	if (ctx->cfg->round_num > 0) {
		setup_objects(ctx);
		return;
	}

	if (resuming()) {
		on_resuming(ctx);
		return;
	}

	cleanup(ctx);
	end(quit);
}

static void
on_target_collision(struct event_ctx *ctx)
{
	update_after_contact_with_target(ctx);

	if (ctx->cfg->current_snake_length > target_snake_length) {
		game_settings_increase(ctx->cfg);

		if (ctx->cfg->round_num > max_round_num) {
			end(win);
		}

		setup_objects(ctx);
	}
}

static void
on_ending(struct event_ctx *ctx)
{

}

static void
on_win(struct event_ctx *ctx)
{

}

static enum event_type
define_event(struct event_ctx *ctx)
{
	const struct coordinates *head = &ctx->snk->first->coord;
	enum event_type rc = none_ev;

	if (border_collision(head) || barrier_collision(head, ctx->bar)) {
		rc = bar_collision_ev;
	}

	if (target_collision(head, &ctx->tar)) {
		rc = tar_collision_ev;
	}

	return rc;
}

void
handle_direction(const int signal,
		struct event_ctx *ctx)
{
	switch (signal) {
	case key_spacebar:
		ctx->dir->x = 0;
		ctx->dir->y = 0;
		break;
	case KEY_UP:
		ctx->dir->x = 0;
		ctx->dir->y = -1;
		break;
	case KEY_DOWN:
		ctx->dir->x = 0;
		ctx->dir->y = 1;
		break;
	case KEY_LEFT:
		ctx->dir->x = -1;
		ctx->dir->y = 0;
		break;
	case KEY_RIGHT:
		ctx->dir->x = 1;
		ctx->dir->y = 0;
		break;
	case ERR:
		move_snake_object(ctx->snk, ctx->dir);
		break;
	}
}

void
handle_event(struct event_ctx *ctx)
{
	enum event_type event = define_event(ctx);

	display_in_fog_of_war(ctx);

	switch (event) {
	case none_ev:
		on_none(ctx);
		break;
	case bar_collision_ev:
		on_barrier_collision(ctx);
		break;
	case tar_collision_ev:
		on_target_collision(ctx);
		break;
	case ending_ev:
		on_ending(ctx);
		break;
	case win_ev:
		on_win(ctx);
		break;
	default:
		break;
	}
}

static int
get_user_input(void)
{
	int answer;

	for (;;) {
		answer = getch();

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

	return 0;
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
cleanup(struct event_ctx *ctx)
{
	if (!ctx) {
		return;
	}

	if (ctx->snk) {
		delete_coordinate_list(&ctx->snk->first);
		ctx->snk->last = NULL;
	}

	if (ctx->tar) {
		delete_coordinate_list(&ctx->tar);
	}

	if (ctx->bar) {
		delete_coordinate_list(&ctx->bar);
	}
}

void
release_mem(struct event_ctx *ctx)
{
	if ((!ctx) || (!ctx->snk)) {
		return;
	}

	cleanup(ctx);
	free(ctx->snk->last_direction);
	free(ctx->snk);
	ctx->snk->last_direction = NULL;
	ctx->snk = NULL;
}
