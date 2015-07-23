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
	currentGameState.topBase.x = 1;
	currentGameState.topBase.y = 35;
	currentGameState.botBase.x = 196;
	currentGameState.botBase.y = 168;
	currentGameState.onScreenMissileCount = 10;

	initializeMissiles();

	
	lift.health = 5;
	lift.drawSpace.x = 107;
	lift.drawSpace.y = 108;
  lift.drawSpace.h = 24;
  lift.drawSpace.w = 24;
	lift.orientation = SP_180;
	lift.position.x = 107;
	lift.position.y = 108;



	printf("Nivel Cargado: %d", lvl);
}

void
update(float dt)
{
	updatePositions();
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
initializeMissiles()
{
	int i;
	for(i=0; i<currentGameState.onScreenMissileCount;i++){
		currentGameState.missileList[i].isAlive = 0;
		currentGameState.missileList[i].position.x = 0;
		currentGameState.missileList[i].position.y = 0;
		currentGameState.missileList[i].orientation = SP_0;
	}
}

void
updatePositions()
{
	/*for(int i=0; i<currentGameState.onScreenMissileCount;i++){
		switch(currentGameState.missileList[i].orientation){
		case SP_0:
			//currentGameState.missileList[i].position.x += SIZE_BULLET*GAME_GRID_SIZE;
			//currentGameState.missileList[i].position.y = 0;
			break;
		case SP_45:
			break;
		case SP_90:
			break;
		case SP_135:
			break;
		case SP_180:
			break;
		case SP_225:
			break;
		case SP_270:
			break;
		case SP_315:
			break;
		default:
			break;
		}
	}*/
}

void
cleanGameLogic()
{
}
