//
// (C) Gabriel Hite 2026
//
// This code is licensed under the GNU GPL v3.0
// See COPYING for more information.
//
// DESCRIPTION:
//	Header file for map.c
//

#ifndef MAP_H
#define MAP_H

#define MAP_WIDTH 8
#define MAP_HEIGHT 8

extern int worldMap[MAP_HEIGHT][MAP_WIDTH];

typedef struct {
    int r, g, b;
} Color;

extern Color wallColors[6];

void initWallColors(void);

#endif
