/**
 * video.h - Procesamiento video juego
 * Autor: MBT
 */

#ifndef __VIDEO_H
#define __VIDEO_H

#include "sdl.h"
#include "game.h"

extern GameState currentGameState;
int imgFlags;
SDL_Renderer *renderer;
SDL_Texture *gamebkg;
SDL_Texture *lift;
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
