//
// (C) Gabriel Hite 2026
//
// This code is licensed under the GNU GPL v3.0
// See COPYING for more information.
//
// DESCRIPTION:
//	The raycasting code and math.
//

#include <SDL2/SDL.h>
#include <math.h>
#include "raycaster.h"
#include "map.h"

static double posX = 3.5, posY = 3.5;       
static double dirX = -1.0, dirY = 0.0;      
static double planeX = 0.0, planeY = 0.66;  

void updatePlayer(double frameTime) {
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    
    // Scale movement and rotation speeds by frameTime for smooth motion
    double moveSpeed = frameTime * 3.0; 
    double rotSpeed = frameTime * 2.0;

    // Move Forward (W or Up Arrow)
    if (state[SDL_SCANCODE_W] || state[SDL_SCANCODE_UP]) {
        if (worldMap[(int)(posY)][(int)(posX + dirX * moveSpeed)] == 0) posX += dirX * moveSpeed;
        if (worldMap[(int)(posY + dirY * moveSpeed)][(int)(posX)] == 0) posY += dirY * moveSpeed;
    }
    // Move Backward (S or Down Arrow)
    if (state[SDL_SCANCODE_S] || state[SDL_SCANCODE_DOWN]) {
        if (worldMap[(int)(posY)][(int)(posX - dirX * moveSpeed)] == 0) posX -= dirX * moveSpeed;
        if (worldMap[(int)(posY - dirY * moveSpeed)][(int)(posX)] == 0) posY -= dirY * moveSpeed;
    }
    // Rotate Right (D or Right Arrow)
    if (state[SDL_SCANCODE_RIGHT] || state[SDL_SCANCODE_D]) {
        double oldDirX = dirX;
        dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
        dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
        double oldPlaneX = planeX;
        planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
        planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
    }
    // Rotate Left (A or Left Arrow)
    if (state[SDL_SCANCODE_LEFT] || state[SDL_SCANCODE_A]) {
        double oldDirX = dirX;
        dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
        dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
        double oldPlaneX = planeX;
        planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
        planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
    }
}

void castRays(SDL_Renderer* renderer) {
    int screenWidth = 640;
    int screenHeight = 480;

    for (int x = 0; x < screenWidth; x++) {
        double cameraX = 2.0 * x / (double)screenWidth - 1.0;
        double rayDirX = dirX + planeX * cameraX;
        double rayDirY = dirY + planeY * cameraX;

        int mapX = (int)posX;
        int mapY = (int)posY;

        double sideDistX, sideDistY;

        double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1.0 / rayDirX);
        double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1.0 / rayDirY);
        double perpWallDist;

        int stepX, stepY;
        int hit = 0;
        int side;

        if (rayDirX < 0) {
            stepX = -1;
            sideDistX = (posX - mapX) * deltaDistX;
        } else {
            stepX = 1;
            sideDistX = (mapX + 1.0 - posX) * deltaDistX;
        }
        if (rayDirY < 0) {
            stepY = -1;
            sideDistY = (posY - mapY) * deltaDistY;
        } else {
            stepY = 1;
            sideDistY = (mapY + 1.0 - posY) * deltaDistY;
        }

        while (hit == 0) {
            if (sideDistX < sideDistY) {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            } else {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            if (worldMap[mapY][mapX] > 0) hit = 1;
        }

        if (side == 0) perpWallDist = (sideDistX - deltaDistX);
        else           perpWallDist = (sideDistY - deltaDistY);

        int lineHeight = (int)(screenHeight / perpWallDist);
        int drawStart = -lineHeight / 2 + screenHeight / 2;
        if (drawStart < 0) drawStart = 0;
        int drawEnd = lineHeight / 2 + screenHeight / 2;
        if (drawEnd >= screenHeight) drawEnd = screenHeight - 1;

        // Look up wall type and get RNG color from map.c palette
        int wallType = worldMap[mapY][mapX];
        int r = 200, g = 200, b = 200;

        if (wallType >= 1 && wallType <= 5) {
            r = wallColors[wallType].r;
            g = wallColors[wallType].g;
            b = wallColors[wallType].b;
        }

        // Apply side shading.
        if (side == 1) {
            r = (int)(r * 0.7);
            g = (int)(g * 0.7);
            b = (int)(b * 0.7);
        }

        SDL_SetRenderDrawColor(renderer, r, g, b, 255);
        SDL_RenderDrawLine(renderer, x, drawStart, x, drawEnd);
    }
}
