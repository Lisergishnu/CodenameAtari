#include "game.h"

#define LIFT_STARTING_POS_TOP_X 31
#define LIFT_STARTING_POS_TOP_Y 9
#define LIFT_STARTING_POS_BOT_X 189
#define LIFT_STARTING_POS_BOT_Y 166
#define MISSILE_SPEED 0.05f
#define GAME_SCORE_PER_BLOCK 1.0f
#define GS_READY_SCREEN_TIMER 2500.0f
#define GAME_MS_PER_LIFT_MOVEMENT 250.0f
#define GAME_SCORE_PER_PERSON 20
#define GS_SCORING_MS_PER_TICK 50.0f
#define GS_SCORING_MS_BEFORE_NEXT_LEVEL 1000.0f
#define GS_GAMEOVER_MS_BEFORE_MAINMENU 5000.0f

float startTimer;
char isGoingUphill;
int levelMissileProbThreshold;
int displayScoring = 0;
extern AppScene currentAppScene;

void
initGameLogic()
{
  srand(time(NULL));
  currentGameState.currentScore = 0;
	startNewLevel(1);
}

void
startNewLevel(int lvl)
{
	currentGameState.currentLevel = lvl;
	currentGameState.topBase.x = 24;
	currentGameState.topBase.y = 6;
	currentGameState.botBase.x = 196;
	currentGameState.botBase.y = 168;
	currentGameState.onScreenMissileCount = 10;
  currentGameState.currentGameScene = GS_START;
  currentGameState.peopleRescued = 2 + lvl*0.34;

  startTimer = 0;
  /*
   * As levels are from increasing dificulty
   * the probability of having a missile
   * launched at the player also increases
   *
   * Value ranges from 0 to 99. If >= 100
   * missles always launch.
   */
  levelMissileProbThreshold = 10 + 20*lvl;

	initializeMissiles();

  if (lvl%2 == 1)
  {
    isGoingUphill = 1;
    lift.drawSpace.x = LIFT_STARTING_POS_BOT_X;
    lift.drawSpace.y = LIFT_STARTING_POS_BOT_Y;
    lift.orientation = SP_180;
  }
  else
  {
    isGoingUphill = 0;
    lift.drawSpace.x = LIFT_STARTING_POS_TOP_X;
    lift.drawSpace.y = LIFT_STARTING_POS_TOP_Y;
    lift.orientation = SP_0;
  }
  lift.health = 3;
  lift.drawSpace.h = 24;
  lift.drawSpace.w = 24;
	lift.position.x = lift.drawSpace.x;
	lift.position.y = lift.drawSpace.y;

  isNewHighScore = 0;

	printf("Nivel Cargado: %d\n", lvl);
}

  void
generateMissiles()
{
  if (currentGameState.onScreenMissileCount <
      MAX_MISSILE_COUNT)
  {
    int chance = rand() % 10000;
    if (chance <= levelMissileProbThreshold)
    {
      int m = 0;
      while (currentGameState.missileList[m].isAlive == 1)
        m++;
      if (m >= MAX_MISSILE_COUNT)
        return;
      Missile *mis = &currentGameState.missileList[m];
      mis->isAlive = 1;
      /* First we select randomly one side of
       * the screen to appear in.
       *
       *     0
       *   =====
       * 1 |   | 2
       *   =====
       *     3
       *
       *  We only use the corners of the screen.
       */
      int side = rand() % 4;
      switch(side)
      {
        case 0:
          mis->position.x = rand() % WORLD_WIDTH/2 + WORLD_WIDTH/2;
          mis->position.y = 0;
          break;
        case 1:
          mis->position.x = 0;
          mis->position.y = rand() % WORLD_HEIGHT/2 + WORLD_HEIGHT/2;
          break;
        case 2:
          mis->position.x = WORLD_WIDTH;
          mis->position.y = rand() % WORLD_HEIGHT/2;
          break;
        case 3:
          mis->position.x = rand() % WORLD_WIDTH/2;
          mis->position.y = WORLD_HEIGHT;
          break;
      }
      /*
       * Calculate angle so we can update the
       * bullet position.
       */
      int targetx = lift.drawSpace.x;
      int targety = lift.drawSpace.y;
      FVector dirVec;
      dirVec.x = targetx - mis->position.x;
      dirVec.y = targety - mis->position.y;
      mis->angle = atan2(dirVec.y,dirVec.x);
    }
  }
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
      generateMissiles();
      updatePositions(dt);
      //checkCollitions
      //assignDamages
      //assignScores
      break;
    case GS_SCORING:
      /*
       * The idea is to show the score adding up
       * slowly as the people rescued decrease.
       * Then we wait a little before begining
       * the next level.
       */
      startTimer += dt;
      if (startTimer > GS_SCORING_MS_PER_TICK)
      {
        if (currentGameState.peopleRescued > 0)
        {
          if (displayScoring <= 0)
            displayScoring = GAME_SCORE_PER_PERSON;
          else
          {
            currentGameState.currentScore += 5;
            displayScoring -= 5;
            startTimer = 0;
          }
          if (displayScoring <= 0)
            currentGameState.peopleRescued -= 1;
        }
        else
        {
          if (startTimer > GS_SCORING_MS_BEFORE_NEXT_LEVEL)
          {
            startNewLevel(currentGameState.currentLevel + 1);
          }
        }
      }
      break;
      case GS_GAMEOVER:
      startTimer += dt;
      if (startTimer > GS_GAMEOVER_MS_BEFORE_MAINMENU)
      {
        currentAppScene = APPSCENE_MAINMENU;
        startTimer = 0;
      }
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
	for(i=0;
      i<MAX_MISSILE_COUNT;
      i++){
		currentGameState.missileList[i].isAlive = 0;
		currentGameState.missileList[i].position.x = 0;
		currentGameState.missileList[i].position.y = 0;
	}
}

void
updatePositions(float dt)
{
  /* Update lift position */
  /* We need to stall the position until at least
   * one second since our timer resoultion
   * doesn't allow for slow movement.
   * */
  /*
   * We also check here if the lift has arrived
   * at destination. In that case we proceed to
   * the scoring phase.
   */
  static float liftMovementTimer = 0.0f;
  if (liftMovementTimer >= GAME_MS_PER_LIFT_MOVEMENT)
  {
    if (isGoingUphill)
    {
      lift.drawSpace.x -= 1;
    }
    else
    {
      lift.drawSpace.x += 1;
    }

    lift.drawSpace.y = lift.drawSpace.x*0.9937 -
      21.8038;
    liftMovementTimer = 0.0f;
    if ((isGoingUphill &&
          lift.drawSpace.x <= LIFT_STARTING_POS_TOP_X &&
          lift.drawSpace.y <= LIFT_STARTING_POS_TOP_Y) ||
        (!isGoingUphill &&
         lift.drawSpace.x >= LIFT_STARTING_POS_BOT_X &&
         lift.drawSpace.y >= LIFT_STARTING_POS_BOT_Y))
    {
      currentGameState.currentGameScene = GS_SCORING;
      startTimer = 0;
    }
  }
  else
  {
    liftMovementTimer += dt;
  }
  /* Update missile positions */
  int m;
  for (m = 0;
      m < MAX_MISSILE_COUNT;
      m++)
  {
    Missile *mi = &currentGameState.missileList[m];
    if (mi->isAlive == 1)
    {
      mi->position.x += cos(mi->angle)*MISSILE_SPEED*dt;
      mi->position.y += sin(mi->angle)*MISSILE_SPEED*dt;

      /* 
       * Consider if the current missile has collided
       * with the shield
       */

      SDL_Rect r = getShieldRect();
      SDL_Rect mir;
      mir.x = mi->position.x;
      mir.y = mi->position.y;
      mir.w = 4;
      mir.h = 4;

      if (SDL_HasIntersection(&r, &mir) == SDL_TRUE)
      {
        mi->isAlive = 0;
        currentGameState.currentScore += GAME_SCORE_PER_BLOCK;
      }       

      /* Now check if it has collided with the player rect */
      if (SDL_HasIntersection(&lift.drawSpace, &mir) == SDL_TRUE)
      {
        lift.health -= 1;
        if (lift.health == 0) // Game Over!!
        {
          currentGameState.currentGameScene = GS_GAMEOVER;
          if (highScore < currentGameState.currentScore)
          {
            highScore = currentGameState.currentScore;
            isNewHighScore = 1;
          }
          startTimer = 0;
        }
        mi->isAlive = 0;
      }

      /*
       * If missile leaves screen, mark it as dead.
       */

      if ((mi->position.x >= WORLD_WIDTH) ||
          (mi->position.x <= 0) ||
          (mi->position.y >= WORLD_HEIGHT) ||
          (mi->position.y <= 0))
        mi->isAlive = 0;
    }
  }
}

  void
cleanGameLogic()
{
}
