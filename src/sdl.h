/*
 * sdl.h - Permite configurar los includes de SDL2 dependiendo de la plataforma
 * Autor: MBT
 */

#ifndef __SDLHELP_H
#define __SDLHELP_H

#if _WIN32
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#elif __APPLE__
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>
#endif

#endif //__SDLHELP_H
