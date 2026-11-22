//
// (C) Gabriel Hite 2026
//
// This code is licensed under the GNU GPL v3.0
// See COPYING for more information.
//
// DESCRIPTION:
//	Holds the map data.
//

#include "map.h"
#include "rng.h"

// Baked-in map. (Gotta fix that.)
int worldMap[MAP_HEIGHT][MAP_WIDTH] = {
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 2},
    {3, 0, 1, 1, 0, 2, 0, 3},
    {3, 0, 1, 0, 0, 2, 0, 3},
    {4, 0, 4, 0, 0, 0, 0, 4},
    {4, 0, 4, 4, 0, 5, 5, 4},
    {5, 0, 0, 0, 0, 0, 0, 5},
    {1, 5, 5, 5, 5, 5, 5, 1}
};

Color wallColors[6]; 

// So colorful!
void initWallColors() {
    for (int i = 1; i <= 5; i++) {
        wallColors[i].r = rngcall() % 256;
        wallColors[i].g = rngcall() % 256;
        wallColors[i].b = rngcall() % 256;
    }
}
