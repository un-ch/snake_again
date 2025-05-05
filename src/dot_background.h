#ifndef DOT_BACKGROUND_H_SENTRY
#define DOT_BACKGROUND_H_SENTRY

#include "coordinates.h"

void
display_dot_background();

void
display_dot_background_in_fog_of_war(const struct coordinates snake);

struct coordinates_list *
init_dot_background(void);

#endif
