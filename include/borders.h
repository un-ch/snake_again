#ifndef BORDERS_H_SENTRY
#define BORDERS_H_SENTRY

#include "coordinates.h"

#define TRUE	1
#define FALSE	0

enum { borders_color_pair = 6 };
enum { false_exit_code = 0 };

void
display_borders_with_game_title();

int
is_contact_with_borders(const struct coordinates crd);

#endif
