/**
 * video.h - Procesamiento video juego
 * Autor: MBT
 */

#ifndef __VIDEO_H
#define __VIDEO_H

#include "sdl.h"
#include "game.h"

#define ASSERT_IMG(x) if(x==NULL) printf("Couldn't load image.\n");

extern GameState currentGameState;
int imgFlags;
/* Game textures */
SDL_Renderer *renderer;
SDL_Texture *gamebkgMorningTex;
SDL_Texture *gamebkgDayTex;
SDL_Texture *gamebkgNightTex;
SDL_Texture *liftTex;
SDL_Texture *topBaseTex;
SDL_Texture *bottomBaseTex;
SDL_Texture *bulletTex;
SDL_Texture *shieldTex;
/* Game font */
TTF_Font *font;

/* Game logic variables */
extern SDL_Window *window;
extern Lift lift;
extern GameState currentGameState;

/* Methods */
void
PrintText(
    int x,
    int y,
    char * str);

void
initVideo();

void
loadAssets();

void
render();

void
cleanUpVideo();

#endif //__VIDEO_H
