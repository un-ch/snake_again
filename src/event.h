#ifndef EVENT_H
#define EVENT_H

#include "coordinates.h"
#include "round_settings.h"

enum {
	key_escape = 27,
	key_spacebar = 32,
	key_yes = 121,
	key_no = 110
};

enum event_type {
	none_ev,
	bar_collision_ev,
	tar_collision_ev,
	ending_ev,
	win_ev,
	count
};

struct event_ctx {
	struct snake_type *snk;
	struct coordinates_list *tar;
	struct coordinates_list *bar;
	struct coordinates *dir;
	struct round_settings *cfg;
};

void init(struct event_ctx *ctx);
void handle_direction(const int signal, struct event_ctx *ctx);
void handle_event(struct event_ctx *ctx);
int resuming(void);
void cleanup(struct event_ctx *ctx);
void release_mem(struct event_ctx *ctx);

#endif
