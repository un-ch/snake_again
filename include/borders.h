#ifndef BORDERS_H_SENTRY
#define BORDERS_H_SENTRY

#include "coordinates.h"

enum { borders_color_pair = 6 };
enum { true_exit_code = 1 };
enum { false_exit_code = 0 };

void
display_borders();

int
is_contact_with_borders(const struct coordinates crd);

#endif
