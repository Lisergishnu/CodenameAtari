#include "video.h"


SDL_Rect bkgRect = {100,0,220,192};
SDL_Rect scoreBannerRect = {0,0,100,192};
SDL_Rect destRect = {0,0,0,0};
SDL_Rect liftShieldDestRect = {0,0,0,0};

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
	gamebkgMorningTex = IMG_LoadTexture(renderer,
      "img/morning.png");
  ASSERT_IMG(gamebkgMorningTex);
  gamebkgDayTex = IMG_LoadTexture(renderer,
      "img/day.png");
  ASSERT_IMG(gamebkgDayTex);
  gamebkgNightTex = IMG_LoadTexture(renderer,
      "img/night.png");
  ASSERT_IMG(gamebkgNightTex);
  liftTex = IMG_LoadTexture(renderer,
      "res/sprites/ascensor.png");
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
  shieldTex = IMG_LoadTexture(renderer,
      "res/sprites/barra.png");
  ASSERT_IMG(shieldTex);

  font = TTF_OpenFont( "font/game.ttf",10);
  if (font == NULL)
    printf("Couldn't load game font!\n");
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
updateAndRenderShield()
{
}

void
render()
{
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer,
				gamebkgDayTex,
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
  sprintf(str,"Score: %d",
      currentGameState.currentScore);
  PrintText(20, 20, str);
  /* Draw current level */
  sprintf(str,"Level: %d",
      currentGameState.currentLevel);
  PrintText(20,50, str);
  /* Draw current health */
  sprintf(str,"Health: %d",
      lift.health);
  PrintText(20,80, str);

  updateAndRenderShield();
	SDL_RenderPresent(renderer);
}

void
cleanUpVideo()
{
  TTF_CloseFont(font);
  SDL_DestroyTexture(shieldTex);
  SDL_DestroyTexture(bulletTex);
  SDL_DestroyTexture(bottomBaseTex);
  SDL_DestroyTexture(topBaseTex);
  SDL_DestroyTexture(liftTex);
	SDL_DestroyTexture(gamebkgNightTex);
  SDL_DestroyTexture(gamebkgDayTex);
  SDL_DestroyTexture(gamebkgMorningTex);
	SDL_DestroyRenderer(renderer);

  TTF_Quit();
  IMG_Quit();
}
