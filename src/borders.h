#ifndef BORDERS_H
#define BORDERS_H

#include <stdbool.h>

#include "coordinates.h"

static const char game_title[] = "Snake Again";

void
display_borders_with_game_title(void);

bool
is_contact_with_borders(const struct coordinates crd);

#endif
