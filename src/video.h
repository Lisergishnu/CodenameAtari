/**
 * video.h - Procesamiento video juego
 * Autor: MBT
 */

#ifndef __VIDEO_H
#define __VIDEO_H

#include <SDL.h>
#include <SDL_image.h>

#include "game.h"

extern GameState currentGameState;
int imgFlags;
SDL_Renderer *renderer;
SDL_Texture *gamebkg;
extern SDL_Window *window;

void
initVideo();

void
loadAssets();

void
render();

void
cleanUpVideo();

#endif //__VIDEO_H