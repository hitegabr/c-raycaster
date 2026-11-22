//
// (C) Gabriel Hite 2026
//
// This code is licensed under the GNU GPL v3.0
// See COPYING for more information.
//
// DESCRIPTION:
//	Header file for raycaster.c
//

#ifndef RAYCASTER_H
#define RAYCASTER_H

#include <SDL2/SDL.h>

void updatePlayer(double frameTime);
void castRays(SDL_Renderer* renderer);

#endif
