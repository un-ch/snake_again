#include <stdlib.h>
#include <ncurses.h>

#include "snake_object.h"
#include "coordinates.h"
#include "objects.h"
#include "end_program.h"

void
init_snake_object(struct snake_type **snk)
{
	(*snk) = NULL;
	(*snk) = malloc(sizeof(struct snake_type));

	if (!(*snk)) {
		end(malloc_err);
	}

	(*snk)->first = NULL;
	(*snk)->last = NULL;
	(*snk)->last_direction = NULL;

	(*snk)->last_direction = malloc(sizeof(struct coordinates));

	if (!(*snk)->last_direction) {
		end(malloc_err);
	}
	
	(*snk)->last_direction->x = 0;
	(*snk)->last_direction->y = 0;
}

void
move_snake_object(struct snake_type *snake,
		struct coordinates *direct)
{
	struct coordinates_list *temp = snake->first;
	struct coordinates_list *prev = NULL, *next = NULL;
	struct coordinates prev_coord, next_coord;


	/* for pause: */
	if ((direct->x == 0) && (direct->y == 0)) {
		display_object_list(snake->first, &show_object_snake);
		return;
	}

	display_object_list(snake->first, &hide_object);

	/* opposite direction case: */
	if ((direct->x == -snake->last_direction->x) &&
	    (direct->y == -snake->last_direction->y)) {

		snake->last = snake->first;

		while (temp) {
			next = temp->next;
			temp->next = prev;
			prev = temp;
			temp = next;
		}

		snake->first = prev;

		temp = snake->first;
	}


	/* save the head snake value: */
	prev_coord.x = snake->first->coord.x;
	prev_coord.y = snake->first->coord.y;

	/* update the head snake: */
	snake->first->coord.x += direct->x;
	snake->first->coord.y += direct->y;

	/* TODO: access the second element, be sure if it is exists */
	temp = snake->first->next;

	while (temp) {
		next_coord.x = temp->coord.x;
		next_coord.y = temp->coord.y;

		temp->coord.x = prev_coord.x;
		temp->coord.y = prev_coord.y;

		prev_coord.x = next_coord.x;
		prev_coord.y = next_coord.y;

		temp = temp->next;
	}

	display_object_list(snake->first, &show_object_snake);

	snake->last_direction->x = direct->x;
	snake->last_direction->y = direct->y;
}

void
add_new_snake_element(struct snake_type **snake,
			const struct coordinates crd)
{
	struct coordinates_list *temp = NULL;

	temp = malloc(sizeof(struct coordinates_list));

	if (!temp) {
		end(malloc_err);
	}

	temp->coord.x = crd.x;
	temp->coord.y = crd.y;
	temp->next = NULL;

	if ((*snake)->last) {
		(*snake)->last->next = temp;
		(*snake)->last = temp;
	} else {
		(*snake)->first = (*snake)->last = temp;
	}
}

void
apply_snake_speed(const unsigned int speed)
{
	timeout(speed);
}

void
display_object_list(const struct coordinates_list *list,
			void (*func)(const struct coordinates))
{
	const struct coordinates_list *temp = list;

	while (temp) {
		(*func)(temp->coord);
		temp = temp->next;
	}
}

void
update_after_contact_with_target(struct event_ctx *ctx)
{
	struct coordinates crd;

	crd.x = 1;
	crd.y = 1;

	ctx->cfg->current_snake_length += 1;
	add_new_snake_element(&ctx->snk, crd);
}
