/**
 * main.c - Entrada inicial al juego
 * Autor: MBT
 */
#include <stdio.h>
#include "sdl.h"
#include "video.h"
#include "game.h"

typedef
enum
appscenes
{
	APPSCENE_INTRO,
	APPSCENE_MAINMENU,
	APPSCENE_GAMEPLAY,
	APPSCENE_GAMEOVER
} AppScene;

// Global Variables
AppScene currentScene = APPSCENE_GAMEPLAY;
SDL_Window *window = NULL;
SDL_Surface *surface = NULL;
int isGameRunning = 1;
SDL_Event currentEvent;
int lastTick = 0;

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
		window = SDL_CreateWindow( "Elevator Rescue",
			SDL_WINDOWPOS_CENTERED, 
			SDL_WINDOWPOS_CENTERED, 
		 WORLD_WIDTH, 
		 WORLD_HEIGHT, 
		 SDL_WINDOW_SHOWN );
		if( window == NULL )
		{
		    printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
		}
		else
		{
			////Get window surface
			//surface = SDL_GetWindowSurface( window );
			//
			////Fill the surface white
			//SDL_FillRect( surface, NULL, SDL_MapRGB( surface->format, 0xFF, 0xFF, 0xFF ) );
			//
			////Update the surface
			//SDL_UpdateWindowSurface( window );
			//
			////Wait two seconds
			//SDL_Delay( 2000 );
			
			initGameLogic();
			initVideo();
		}
	}
}

void
shutdown()
{
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
		switch (currentScene)
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
