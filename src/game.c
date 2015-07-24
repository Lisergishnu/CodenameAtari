#include "game.h"

#define LIFT_STARTING_POS_TOP_X 4
#define LIFT_STARTING_POS_TOP_Y 36
#define LIFT_STARTING_POS_BOT_X 189
#define LIFT_STARTING_POS_BOT_Y 166
#define LIFT_SPEED .001f
#define GS_READY_SCREEN_TIMER 3000.0f

float startTimer;
char isGoingUphill;


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
  currentGameState.currentGameScene = GS_START;

  startTimer = 0;

	initializeMissiles();

  if (lvl%2 == 1)
  {
    isGoingUphill = 1;
    lift.drawSpace.x = LIFT_STARTING_POS_BOT_X;
    lift.drawSpace.y = LIFT_STARTING_POS_BOT_Y;
  }
  else
  {
    isGoingUphill = 0;
    lift.drawSpace.x = LIFT_STARTING_POS_TOP_X;
    lift.drawSpace.y = LIFT_STARTING_POS_TOP_Y;
  }
  lift.health = 5;
  lift.drawSpace.h = 24;
  lift.drawSpace.w = 24;
	lift.orientation = SP_180;
	lift.position.x = lift.drawSpace.x;
	lift.position.y = lift.drawSpace.y;

	printf("Nivel Cargado: %d", lvl);
}

  void
update(float dt)
{
  switch(currentGameState.currentGameScene)
  {
    case GS_START:
      startTimer +=dt;
      if (startTimer > GS_READY_SCREEN_TIMER)
      {
        currentGameState.currentGameScene =
          GS_PLAYING;
      }
      break;
    case GS_PLAYING:
      updatePositions(dt);
      //checkCollitions
      //assignDamages
      //assignScores
      break;
    case GS_SCORING:
      break;
  }
}

/* This function will be called
 * whenever there is a event to
 * process in the game world, i.e. user input */
  void
handleGameInput(SDL_Event e)
{
  static char inputXDir = 1; /* 1 der, -1 izq, 0 centro */
  static char inputYDir = 0; /* 1 up, -1 down, 0 centro */

  switch(e.type)
  {
    case SDL_KEYDOWN:
      switch( e.key.keysym.sym )
      {
        case SDLK_LEFT:
          inputXDir = -1;
          break;
        case SDLK_RIGHT:
          inputXDir = 1;
          break;
        case SDLK_UP:
          inputYDir = 1;
          break;
        case SDLK_DOWN:
          inputYDir = -1;
          break;
        default:
          break;
      }
      break;
    case SDL_KEYUP:
      switch( e.key.keysym.sym )
      {
        case SDLK_LEFT:
          if (inputXDir == -1)
            inputXDir = 0;
          break;
        case SDLK_RIGHT:
          if (inputXDir == 1)
            inputXDir = 0;
          break;
        case SDLK_UP:
          if (inputYDir == 1)
            inputYDir = 0;
          break;
        case SDLK_DOWN:
          if (inputYDir == -1)
            inputYDir = 0;
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
  /* Translate direction "vector"
   * into Orientation */
  if (inputXDir == 1)
  {
    if (inputYDir == 1)
      lift.orientation = SP_45;
    else if (inputYDir == 0)
      lift.orientation = SP_0;
    else
      lift.orientation = SP_315;
  }
  else if (inputXDir == 0)
  {
    if (inputYDir == 1)
      lift.orientation = SP_90;
    else if (inputYDir == -1)
      lift.orientation = SP_270;
  }
  else if (inputXDir == -1)
  {
    if (inputYDir == 1)
      lift.orientation = SP_135;
    else if (inputYDir == 0)
      lift.orientation = SP_180;
    else
      lift.orientation = SP_225;
  }

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
updatePositions(float dt)
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

  /* Update lift position */
  /* We need to stall the position until at least
   * one second since our timer resoultion
   * doesn't allow for slow movement.
   * */
  static float liftMovementTimer = 0.0f;
  if (liftMovementTimer >= 1000.0f)
  {
  if (isGoingUphill)
  {
    lift.drawSpace.x -= LIFT_SPEED;
  }
  else
  {
    lift.drawSpace.x += LIFT_SPEED;
  }

  lift.drawSpace.y = lift.drawSpace.x*0.7027 +
                        33.1892;
  liftMovementTimer = 0.0f;
  }
  else
  {
    liftMovementTimer += dt;
  }
}

void
cleanGameLogic()
{
}
