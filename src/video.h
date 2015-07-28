/**
 * video.h - Procesamiento video juego
 * Autor: MBT
 */

#ifndef __VIDEO_H
#define __VIDEO_H

#include "sdl.h"
#include "game.h"

#define SCALING_FACTOR 2
#define ASSERT_IMG(x) if(x==NULL) printf("Couldn't load image: %s.\n", #x);

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
SDL_Texture *shieldLTex;
SDL_Texture *shieldRTex;
SDL_Texture *shieldTTex;
SDL_Texture *shieldBTex;
SDL_Texture *shieldBLTex;
SDL_Texture *shieldBRTex;
SDL_Texture *shieldTLTex;
SDL_Texture *shieldTRTex;
SDL_Texture *scoreBarTex;
SDL_Texture *splashTex;
SDL_Texture *readyPromptTex;
SDL_Texture *arrowTex;
/* Game font */
TTF_Font *font;

/* Game logic variables */
extern SDL_Window *window;
extern Lift lift;
extern GameState currentGameState;
extern char currentMenuSelection;

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
renderSplashScreen();

void
render();

void
cleanUpVideo();

#endif //__VIDEO_H
