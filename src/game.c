#include "game.h"



void
initGameLogic()
{
	startNewLevel(1);
}

void
startNewLevel(int lvl)
{
	currentGameState.currentLevel = lvl;
	currentGameState.topBase.x = 100;
	currentGameState.topBase.y = 100;
	currentGameState.botBase.x = 1;
	currentGameState.botBase.y = 1;
	currentGameState.onScreenMissileCount = 10;

	initializeMissiles(currentGameState.onScreenMissileCount, currentGameState.missileList);

	
	lift.health = 5;
	lift.drawSpace.x = 24;
	lift.drawSpace.y = 24;
	lift.orientation = SP_0;



	printf("Nivel Cargado: %d", lvl);
}

void
update(float dt)
{
	//updatePositions
	//checkCollitions
	//assignDamages
	//assignScores
}

/* This function will be called whenever there is a event to process in the game world, i.e. user input */
void
handleGameInput(SDL_Event e)
{

}

void
initializeMissiles(int amount, Missile *missiles)
{
	for(int i=0; i<amount;i++){
		missiles[i].isAlive = 0;
		missiles[i].position.x = 0;
		missiles[i].position.y = 0;
		missiles[i].angle = SP_0;
	}
}