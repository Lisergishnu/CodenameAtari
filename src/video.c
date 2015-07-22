#include "video.h"


SDL_Rect bkgRect = {100,0,220,192};
SDL_Rect scoreBannerRect = {0,0,100,192};
SDL_Rect destRect = {0,0,0,0};

void
initVideo()
{
	renderer = SDL_CreateRenderer(window, -1,
      SDL_RENDERER_ACCELERATED);
	 //Initialize renderer color
	SDL_SetRenderDrawColor( renderer, 0x00, 0x00,
      0x00, 0xFF );

	//Initialize PNG loading
	imgFlags = IMG_INIT_PNG;
	if( !( IMG_Init( imgFlags ) & imgFlags ) )
	{
		printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
	}

  //Initialize TTF rendering
  if ( TTF_Init() == -1)
  {
    printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
  }
}

void
loadAssets()
{
	gamebkg = IMG_LoadTexture(renderer,
      "img/fondoJuego.png");
  ASSERT_IMG(gamebkg);
  liftTex = IMG_LoadTexture(renderer,
      "res/sprites/lift.png");
  ASSERT_IMG(liftTex);
  topBaseTex = IMG_LoadTexture(renderer,
      "res/sprites/base1.png");
  ASSERT_IMG(topBaseTex);
  bottomBaseTex = IMG_LoadTexture(renderer,
      "res/sprites/base2.png");
  ASSERT_IMG(bottomBaseTex);
  bulletTex = IMG_LoadTexture(renderer,
      "res/sprites/bala.png");
  ASSERT_IMG(bulletTex);

  font = TTF_OpenFont( "font/game.ttf",8);
}

void
PrintText(
    int x,
    int y,
    char *str)
{
 SDL_Color textColor = {255,255,255,0};
 SDL_Surface* textSurface = TTF_RenderText_Solid(
     font,
     str,
     textColor);
 SDL_Texture* text = SDL_CreateTextureFromSurface(
     renderer, textSurface);
 int textw = textSurface->w;
 int texth = textSurface->h;
 SDL_FreeSurface(textSurface);
 SDL_Rect renderQuad = {x,y,textw,texth};
 SDL_RenderCopy(renderer, text, NULL, &renderQuad);
 SDL_DestroyTexture(text);
}

void
render()
{
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer,
				gamebkg,
				NULL,
				&bkgRect);
  /* Draw lift */
  destRect = lift.drawSpace;
  SDL_RenderCopy(renderer,
      liftTex,
      NULL,
      &destRect);
  /* Draw score */
  char str[15];
  sprintf(str,"%d", currentGameState.currentScore);
  PrintText(20, 20, str);
	SDL_RenderPresent(renderer);
}

void
cleanUpVideo()
{
  TTF_CloseFont(font);
  SDL_DestroyTexture(bulletTex);
  SDL_DestroyTexture(bottomBaseTex);
  SDL_DestroyTexture(topBaseTex);
  SDL_DestroyTexture(liftTex);
	SDL_DestroyTexture(gamebkg);
	SDL_DestroyRenderer(renderer);

  TTF_Quit();
  IMG_Quit();
}
