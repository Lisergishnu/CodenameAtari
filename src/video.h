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

SDL_Renderer *renderer;
SDL_Texture *gamebkg;
extern SDL_Window *window;

SDL_Rect bkgRect = {100,0,220,192};

void
initVideo();

void
loadAssets();

void
render();

void
cleanUpVideo();

#endif //__VIDEO_H