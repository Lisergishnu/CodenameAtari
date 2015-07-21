#include "video.h"

void
initVideo()
{
	renderer = SDL_CreateRenderer(window,
	-1,
	SDL_RENDERER_ACCELERATED);
}

void
loadAssets()
{
	img = IMG_LoadTexture(renderer, "img/fondoJuego.png");
}

void
render()
{
	SDL_RenderClean(renderer);
	SDL_RenderCopy(renderer,
				gamebkg,
				NULL,
				bkgRect);
	SDL_RenderPresent(renderer);
}

void
cleanUpVideo()
{
	SDL_DestroyTexture(gamebkg);
	SDL_DestroyRenderer(renderer);
}