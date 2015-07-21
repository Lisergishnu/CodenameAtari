/**
 * main.c - Entrada inicial al juego
 * Autor: MBT
 */
#include <stdio.h>
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
AppScene currentScene = APPSCENE_INTRO;

// Methods
void
init()
{
}

void
shutdown()
{
}

int
main(int argc, char *argv[])
{
	init();
	while (1)
	{
		switch (currentScene)
		{
			case APPSCENE_INTRO:
			case APPSCENE_MAINMENU:
			case APPSCENE_GAMEPLAY:
			case APPSCENE_GAMEOVER:
			break;
		}
	}
	shutdown();
	return 0;
}