#ifndef OBJECTS_H_SENTRY
#define OBJECTS_H_SENTRY

#include "coordinates.h"

enum { symbol_target = '+' };
enum { symbol_snake = '+' };
enum { symbol_barrier_plus = 'x' };
enum { symbol_blank = ' ' };

void 
show_object_target(const struct coordinates coord);

void 
show_object_snake(const struct coordinates coord);

void 
show_object_barrier(const struct coordinates coord);

void
hide_object(const struct coordinates coord);

#endif
