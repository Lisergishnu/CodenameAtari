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
renderIntroScene();

void
renderCredits();

void
render();

void
cleanUpVideo();

SDL_Rect
getShieldRect();

#endif //__VIDEO_H
