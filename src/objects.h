#ifndef OBJECTS_H_SENTRY
#define OBJECTS_H_SENTRY

#include "coordinates.h"

enum {
	symbol_target = '+',
	symbol_snake = '+',
	symbol_barrier = '#',
	symbol_blank = ' ',
	symbol_dot = '.'
};

enum object {
	target_obj,
	snake_obj,
	barrier_obj,
	blank_obj,
	dot_obj
};

void show_object_target(const struct coordinates crd);
void show_object_snake(const struct coordinates crd);
void show_object_barrier(const struct coordinates crd);
void show_object_dot_background(const struct coordinates crd);
void hide_object(const struct coordinates crd);
void display_object(enum object obj, const struct coordinates crd);
void display_object_in_fog_of_war(const struct coordinates sn,
				const struct coordinates_list *list,
				void (*func)(struct coordinates));

void
display_in_fog_of_war(const struct coordinates sn,
			const struct coordinates_list *tar,
			const struct coordinates_list *bar,
			const struct coordinates_list *dot);
#endif
