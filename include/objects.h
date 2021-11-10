#ifndef OBJECTS_H_SENTRY
#define OBJECTS_H_SENTRY

#include "coordinates.h"

enum { symbol_target = '+' };
enum { symbol_snake = '+' };
enum { symbol_barrier_plus = '#' };
enum { symbol_blank = ' ' };

void 
show_object_target(const struct coordinates crd);

void 
show_object_snake(const struct coordinates crd);

void 
show_object_barrier(const struct coordinates crd);

void
hide_object(const struct coordinates crd);

#endif
