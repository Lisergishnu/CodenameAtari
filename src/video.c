#include "video.h"


SDL_Rect bkgRect = {100*SCALING_FACTOR,
    0*SCALING_FACTOR,
    220*SCALING_FACTOR,
    192*SCALING_FACTOR};
SDL_Rect scoreBannerRect = {0*SCALING_FACTOR,
    0*SCALING_FACTOR,
    100*SCALING_FACTOR,
    192*SCALING_FACTOR};
SDL_Rect splashScreenRect = {0*SCALING_FACTOR,
    0*SCALING_FACTOR,
    320*SCALING_FACTOR,
    192*SCALING_FACTOR};
SDL_Rect destRect = {0,0,0,0};
SDL_Rect liftShieldDestRect = {0,0,0,0};
SDL_Rect gameOverRect = {60*SCALING_FACTOR,
  87*SCALING_FACTOR,
  200*SCALING_FACTOR,
  40*SCALING_FACTOR};
SDL_Rect hiscoreRect = {85*SCALING_FACTOR,
40*SCALING_FACTOR,
150*SCALING_FACTOR,
30*SCALING_FACTOR};

void
scaleDestRect(SDL_Rect *rect)
{
    rect->x *= SCALING_FACTOR;
    rect->y *= SCALING_FACTOR;
    rect->w *= SCALING_FACTOR;
    rect->h *= SCALING_FACTOR;
}

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
      "res/sprites/liftsheet.png");
  ASSERT_IMG(liftTex);
  topBaseTex = IMG_LoadTexture(renderer,
      "res/sprites/casetatop.png");
  ASSERT_IMG(topBaseTex);
  bottomBaseTex = IMG_LoadTexture(renderer,
      "res/sprites/casetaleft.png");
  ASSERT_IMG(bottomBaseTex);
  bulletTex = IMG_LoadTexture(renderer,
      "res/sprites/bala.png");
  ASSERT_IMG(bulletTex);

  /* Loading shield sides */
  shieldLTex = IMG_LoadTexture(renderer,
      "res/sprites/escudoleft.png");
  ASSERT_IMG(shieldLTex);
  shieldRTex = IMG_LoadTexture(renderer,
      "res/sprites/escudoright.png");
  ASSERT_IMG(shieldRTex);
  shieldTTex = IMG_LoadTexture(renderer,
      "res/sprites/escudotop.png");
  ASSERT_IMG(shieldTTex);
  shieldBTex = IMG_LoadTexture(renderer,
      "res/sprites/escudobot.png");
  ASSERT_IMG(shieldBTex);
  shieldBLTex = IMG_LoadTexture(renderer,
      "res/sprites/escudobotleft.png");
  ASSERT_IMG(shieldBLTex);
  shieldBRTex = IMG_LoadTexture(renderer,
      "res/sprites/escudobotright.png");
  ASSERT_IMG(shieldBRTex);
  shieldTRTex = IMG_LoadTexture(renderer,
      "res/sprites/escudotopright.png");
  ASSERT_IMG(shieldTRTex);
  shieldTLTex = IMG_LoadTexture(renderer,
      "res/sprites/escudotopleft.png");
  ASSERT_IMG(shieldTLTex);

  /*Load the "ready" prompt */
  readyPromptTex = IMG_LoadTexture(renderer,
      "res/sprites/ready.png");
  ASSERT_IMG(readyPromptTex);

  /* Load splash and side bar textures */
  scoreBarTex = IMG_LoadTexture(renderer,
      "img/Scorebarra.png");
  ASSERT_IMG(scoreBarTex);
  splashTex = IMG_LoadTexture(renderer,
      "img/Splash.png");
  ASSERT_IMG(splashTex);

  /* Load selection arrow */
  arrowTex = IMG_LoadTexture(renderer,
      "res/sprites/arrow.png");
  ASSERT_IMG(arrowTex);

  /* Load end game textures */
  gameOverTex = IMG_LoadTexture(renderer,
   "res/sprites/gameover.png");
  ASSERT_IMG(gameOverTex);
  hiscoreTex = IMG_LoadTexture(renderer,
   "res/sprites/hiscore.png");
  ASSERT_IMG(hiscoreTex);

  /* Load rail */
  railTex = IMG_LoadTexture(renderer,
      "img/riel.png");
  ASSERT_IMG(railTex);

  /* Load intro screen */
  introTex = IMG_LoadTexture(renderer,
      "img/enactivo.png");
  ASSERT_IMG(introTex);

  /* Load credit screen */
  creditsTex = IMG_LoadTexture(renderer,
      "img/credits.png");
  ASSERT_IMG(creditsTex);

  font = TTF_OpenFont( "font/Beeb.ttf",16);
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

SDL_Rect
getShieldRect()
{
  return liftShieldDestRect;
}

  void
updateAndRenderShield()
{
  int xPos = lift.drawSpace.x;
  int yPos = lift.drawSpace.y;
  SDL_Texture* currentTex = NULL;
  switch (lift.orientation) {
    case SP_0:
      currentTex = shieldRTex;
      xPos += 36;
      break;
    case SP_45:
      currentTex = shieldTRTex;
      xPos += 22;
      yPos -= 18;
      break;
    case SP_90:
      currentTex = shieldTTex;
      yPos -= 18;
      break;
    case SP_135:
      currentTex = shieldTLTex;
      xPos -= 15;
      yPos -= 18;
      break;
    case SP_180:
      currentTex = shieldLTex;
      xPos -= 15;
      break;
    case SP_225:
      currentTex = shieldBLTex;
      xPos -= 15;
      yPos += 21;
      break;
    case SP_270:
      currentTex = shieldBTex;
      yPos += 36;
      break;
    case SP_315:
      currentTex = shieldBRTex;
      xPos += 21;
      yPos += 21;
      break;
  }

  SDL_QueryTexture(currentTex,
      NULL,
      NULL,
      & liftShieldDestRect.w,
      & liftShieldDestRect.h);

  liftShieldDestRect.x = xPos;
  liftShieldDestRect.y = yPos;

  destRect = liftShieldDestRect;
  destRect.x += 100;
    scaleDestRect(&destRect);
  SDL_RenderCopy(renderer, currentTex, NULL,
      &destRect);

}

void
renderMissiles()
{
  SDL_Rect missileRect;
  int m = 0;
  for( m = 0;
      m < MAX_MISSILE_COUNT;
      m++)
  {
    Missile *mil = &currentGameState.missileList[m];
    if (mil->isAlive == 0)
      continue;

    missileRect.x = (int) (mil->position.x) + 100;
    missileRect.y = (int) mil->position.y;
    missileRect.w = 4;
    missileRect.h = 4;

    scaleDestRect(&missileRect);
    SDL_RenderCopy(renderer,
        bulletTex,
        NULL,
        &missileRect);
  }
}

  void
render()
{
  SDL_RenderClear(renderer);
  /*Draw background, morning, day or night depending
   * on level */
  SDL_Texture* currentBKG;
  switch((currentGameState.currentLevel - 1)%3)
  {
    case 0:
      currentBKG = gamebkgMorningTex;
      break;
    case 1:
      currentBKG = gamebkgDayTex;
      break;
    case 2:
      currentBKG = gamebkgNightTex;
      break;
  }
  SDL_RenderCopy(renderer,
      currentBKG,
      NULL,
      &bkgRect);
  SDL_RenderCopy(renderer,
      railTex,
      NULL,
      &bkgRect);
  /* Draw lift */
  destRect = lift.drawSpace;
  destRect.x += 100;
  SDL_Rect sourceRect = {(3-lift.health)*24,0,24,24};
  scaleDestRect(&destRect);
  SDL_RenderCopy(renderer,
      liftTex,
      &sourceRect,
      &destRect);
  /* Draw top base */
  destRect.x = 100 + currentGameState.topBase.x;
  destRect.y = currentGameState.topBase.y;
  destRect.w = 24;
  destRect.h = 24;
    scaleDestRect(&destRect);
  SDL_RenderCopy(renderer,
      topBaseTex,
      NULL,
      &destRect);
    /* Draw bottom base */
  destRect.x = 100 + currentGameState.botBase.x;
  destRect.y = currentGameState.botBase.y;
  destRect.w = 24;
  destRect.h = 24;
    scaleDestRect(&destRect);
  SDL_RenderCopy(renderer,
      bottomBaseTex,
      NULL,
      &destRect);

  renderMissiles();
  updateAndRenderShield();

  /* Draw score bar at left */
  SDL_RenderCopy(renderer,
      scoreBarTex,
      NULL,
      &scoreBannerRect);
/* Draw score */
  char str[30];
  sprintf(str,"%d",
      currentGameState.currentScore);
  PrintText(55*SCALING_FACTOR, 41*SCALING_FACTOR, str);
  /* Draw current level */
  sprintf(str,"%d",
      currentGameState.currentLevel);
  PrintText(55*SCALING_FACTOR,170*SCALING_FACTOR, str);
  /* Draw current health */
  sprintf(str,"%d",
      lift.health);
  PrintText(55*SCALING_FACTOR,70*SCALING_FACTOR,str);
  /* Draw current people on board */
  sprintf(str,"%d",
      currentGameState.peopleRescued);
  PrintText(55*SCALING_FACTOR,99*SCALING_FACTOR , str);


  /*Render the "ready" prompt if necesary*/
  if (currentGameState.currentGameScene == GS_START)
  {
    destRect.x = 178;
    destRect.y = 88;
    destRect.w = 64;
    destRect.h = 16;
    scaleDestRect(&destRect);
    SDL_RenderCopy(renderer,
        readyPromptTex,
        NULL,
        &destRect);
  }

  /* Render end game images if necesarry */
  if (currentGameState.currentGameScene == GS_GAMEOVER)
  {
    SDL_RenderCopy(renderer,
        gameOverTex, 
        NULL, 
        &gameOverRect);
    if (isNewHighScore)
      SDL_RenderCopy(renderer,
        hiscoreTex, 
        NULL, 
        &hiscoreRect);
  }

  SDL_RenderPresent(renderer);
}

void
renderIntroScene()
{
  SDL_RenderClear(renderer);
  SDL_RenderCopy(renderer,
      introTex,
      NULL,
      &splashScreenRect);
  SDL_RenderPresent(renderer);
}

  void
renderSplashScreen()
{
  SDL_RenderClear(renderer);
  SDL_RenderCopy(renderer,
      splashTex,
      NULL,
      &splashScreenRect);

  /* Render the selection arrow */
  SDL_Rect arrowRect = {80,115,20,21};
  if (currentMenuSelection == 0)
    arrowRect.y = 115;
  else
    arrowRect.y = 139;
  scaleDestRect(&arrowRect);
  SDL_RenderCopy(renderer,
      arrowTex,
      NULL,
      &arrowRect);

  /* Render the hiscore text */
  char str[50];
  sprintf(str,"HI-SCORE: %06d",highScore);
  PrintText(105*SCALING_FACTOR,10*SCALING_FACTOR,str);

  SDL_RenderPresent(renderer);
}

void
renderCredits()
{
  SDL_RenderClear(renderer);
  SDL_RenderCopy(renderer,
      creditsTex,
      NULL,
      &splashScreenRect);
  SDL_RenderPresent(renderer);
}

  void
cleanUpVideo()
{
  TTF_CloseFont(font);
  SDL_DestroyTexture(creditsTex);
  SDL_DestroyTexture(introTex);
  SDL_DestroyTexture(railTex);
  SDL_DestroyTexture(hiscoreTex);
  SDL_DestroyTexture(gameOverTex);
  SDL_DestroyTexture(arrowTex);
  SDL_DestroyTexture(splashTex);
  SDL_DestroyTexture(scoreBarTex);
  SDL_DestroyTexture(readyPromptTex);
  SDL_DestroyTexture(shieldTLTex);
  SDL_DestroyTexture(shieldTRTex);
  SDL_DestroyTexture(shieldBRTex);
  SDL_DestroyTexture(shieldBLTex);
  SDL_DestroyTexture(shieldBTex);
  SDL_DestroyTexture(shieldTTex);
  SDL_DestroyTexture(shieldRTex);
  SDL_DestroyTexture(shieldLTex);
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
