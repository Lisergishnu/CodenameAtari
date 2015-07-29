/*
 * audio.h - Maneja los efectos de sonido
 * Autor: MBT
 */
#ifndef __AUDIO_H
#define __AUDIO_H

#include "sdl.h"

#define ASSERT_AUDIO(x) if(x==NULL) printf("Couldn't load audio: %s. Reason %s.\n", #x, Mix_GetError());

typedef
enum __audioclip
{
  AC_THEME,
  AC_HIT,
  AC_MENU,
  AC_SCORING
} AudioClip;

void
initAudio();

void
loadAudioClips();

void
playSound(AudioClip clip);

void
cleanupAudio();

#endif //__AUDIO_H
