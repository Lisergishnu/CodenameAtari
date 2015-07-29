/**
 * main.c - Entrada inicial al juego
 * Autor: MBT
 */
#include <stdio.h>
#include "sdl.h"
#include "video.h"
#include "game.h"

AppScene currentAppScene = APPSCENE_MAINMENU;
SDL_Window *window = NULL;
SDL_Surface *surface = NULL;
int isGameRunning = 1;
SDL_Event currentEvent;
int lastTick = 0;
char currentMenuSelection = 0;
// Methods
void
init()
{
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
	    printf( "SDL could not initialize! SDL_Error: %s\n", 
		SDL_GetError() );
		exit(-1);
	}
	 else
	{
		//Create window
		window = SDL_CreateWindow( "Elevator Rescue v0.4",
			SDL_WINDOWPOS_CENTERED, 
			SDL_WINDOWPOS_CENTERED, 
		 320*SCALING_FACTOR, 
		 192*SCALING_FACTOR, 
		 SDL_WINDOW_SHOWN );
		if( window == NULL )
		{
		    printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
		}
		else
		{
			initVideo();
		}
	}
}

void
shutdown()
{
  cleanUpVideo();
  cleanGameLogic();
	//Destroy window
    SDL_DestroyWindow( window );

    //Quit SDL subsystems
    SDL_Quit();
}

int
main(int argc, char *argv[])
{
	init();
	loadAssets();
	while (isGameRunning)
	{
		int thisTick = SDL_GetTicks();
		float dt = (float) (thisTick - lastTick);
		lastTick = thisTick;
		switch (currentAppScene)
		{
			case APPSCENE_INTRO:
				//Handle events on queue
				while( SDL_PollEvent( &currentEvent ) != 0 )
				{
					//User requests quit
					if( currentEvent.type == SDL_QUIT )
					{
						isGameRunning = 0;
					}
				}
				break;
			case APPSCENE_MAINMENU:
        while (SDL_PollEvent( &currentEvent ) != 0)
        {
          if (currentEvent.type == SDL_QUIT)
          {
            isGameRunning = 0;
          }
          else if (currentEvent.type == SDL_KEYDOWN)
          {
            switch(currentEvent.key.keysym.sym)
            {
              case SDLK_RIGHT:
              case SDLK_DOWN:
              case SDLK_LEFT:
              case SDLK_UP:
                currentMenuSelection = (currentMenuSelection == 0) ?1:0;
                break;
              case SDLK_RETURN:
                if (currentMenuSelection == 0)
                {
                  currentAppScene = APPSCENE_GAMEPLAY;
          			initGameLogic();
          		}
                else
                  isGameRunning = 0;
                break;
            }
          }
        }
        renderSplashScreen();
        break;
			case APPSCENE_GAMEPLAY:
				//Handle events on queue
				while( SDL_PollEvent( &currentEvent ) != 0 )
				{
					//User requests quit
					if( currentEvent.type == SDL_QUIT )
					{
						isGameRunning = 0;
					}
				}
				handleGameInput(currentEvent);
				update(dt);
				render();
				break;
			case APPSCENE_GAMEOVER:
				break;
		}
	}
	shutdown();
	return 0;
}
