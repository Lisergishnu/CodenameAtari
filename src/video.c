#include "video.h"


SDL_Rect bkgRect = {100,0,220,192};


void
initVideo()
{
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	
	 //Initialize renderer color
	SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );

	//Initialize PNG loading
	imgFlags = IMG_INIT_PNG;
	if( !( IMG_Init( imgFlags ) & imgFlags ) )
	{
		printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
	}
}

void
loadAssets()
{
	gamebkg = IMG_LoadTexture(renderer, "img/fondoJuego.png");
	if (gamebkg == NULL)
	{
		printf("Couldn´t load image\n");
	}
}

void
render()
{
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer,
				gamebkg,
				NULL,
				&bkgRect);
	SDL_RenderPresent(renderer);
}

void
cleanUpVideo()
{
	SDL_DestroyTexture(gamebkg);
	SDL_DestroyRenderer(renderer);
}