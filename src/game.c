#include "game.h"

#define LIFT_STARTING_POS_TOP_X 31
#define LIFT_STARTING_POS_TOP_Y 9
#define LIFT_STARTING_POS_BOT_X 189
#define LIFT_STARTING_POS_BOT_Y 166
#define MISSILE_SPEED 0.05f
#define GAME_SCORE_PER_BLOCK 1.0f
#define GAME_SCORE_PER_LIFE 50
#define GAME_SCORE_PER_POWERUP 50
#define GS_READY_SCREEN_TIMER 2500.0f
#define GAME_MS_PER_LIFT_MOVEMENT 350.0f
#define GAME_MS_PER_MISSILE 10000.0f
#define GAME_MS_PER_STOP 3000.0f
#define GAME_MS_PER_STALL 500.0f
#define GAME_SCORE_PER_PERSON 20
#define GS_SCORING_MS_PER_TICK 50.0f
#define GS_SCORING_MS_BEFORE_NEXT_LEVEL 1000.0f
#define GS_GAMEOVER_MS_BEFORE_MAINMENU 5000.0f

// Global Variables
GameState currentGameState;
Lift lift;
int highScore;
int isNewHighScore;
float startTimer;
char isGoingUphill;
int displayScoring = 0;
extern AppScene currentAppScene;
float missileGenTimer = 0.0f;
float missileFreq = 1.0f;
char liftCurrentlyStalled = 0;

void
initGameLogic()
{
    srand((unsigned int)time(NULL));
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
    currentGameState.peopleRescued = 2 + lvl*0.50;
    currentGameState.onScreenPowerup.isAlive = 0;

    startTimer = 0;
    /*
     * Each level the frequency of missiles
     * increases.
     */
    missileFreq = 4 + 2*lvl;
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
    /*
     * To keep game somewhat unpredictable,
     * only 2 of 3 missiles get launched
     */
    int p = rand() % 3;
    if (p == 2)
        return;

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
    int targetx = (isGoingUphill) ? lift.drawSpace.x :
                  lift.drawSpace.x + 24;
    int targety = (isGoingUphill) ? lift.drawSpace.y :
                  lift.drawSpace.y + 24;
    FVector dirVec;
    dirVec.x = targetx - mis->position.x;
    dirVec.y = targety - mis->position.y;
    mis->angle = atan2(dirVec.y,dirVec.x);
}

void
generatePowerup()
{
    if (currentGameState.onScreenPowerup.isAlive == 1)
        return;

    /*
     * Per call, there is a 5% chance to drop a powerup
     */
    int p = rand() % 50;
    if (p != 0)
        return;

    Powerup *pw = &currentGameState.onScreenPowerup;
    pw->isAlive = 1;

    char pwt = rand() % 2;
    switch (pwt)
        {
        case 0:
            pw->type = PT_REPAIR;
            break;
        case 1:
            pw->type = PT_ULTIMATE;
            break;
        }

    /*
     * We use the same principle as missiles to fire them.
     */
    int side = rand() % 4;
    switch(side)
        {
        case 0:
            pw->position.x = rand() % WORLD_WIDTH/2 + WORLD_WIDTH/2;
            pw->position.y = 0;
            break;
        case 1:
            pw->position.x = 0;
            pw->position.y = rand() % WORLD_HEIGHT/2 + WORLD_HEIGHT/2;
            break;
        case 2:
            pw->position.x = WORLD_WIDTH;
            pw->position.y = rand() % WORLD_HEIGHT/2;
            break;
        case 3:
            pw->position.x = rand() % WORLD_WIDTH/2;
            pw->position.y = WORLD_HEIGHT;
            break;
        }
    /*
     * Calculate angle so we can update the
     * bullet position.
     */
    int targetx = (isGoingUphill) ? lift.drawSpace.x :
                  lift.drawSpace.x + 24;
    int targety = (isGoingUphill) ? lift.drawSpace.y :
                  lift.drawSpace.y + 24;
    FVector dirVec;
    dirVec.x = targetx - pw->position.x;
    dirVec.y = targety - pw->position.y;
    pw->angle = atan2(dirVec.y,dirVec.x);
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
            missileGenTimer += dt;
            if (missileGenTimer > GAME_MS_PER_MISSILE/missileFreq)
                {
                    generateMissiles();
                    generatePowerup();
                    missileGenTimer = 0;
                }
            updatePositions(dt);
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

                    if (lift.health > 0)
                        {
                            if (displayScoring <= 0)
                                displayScoring = GAME_SCORE_PER_LIFE;
                            else
                                {
                                    currentGameState.currentScore += 5;
                                    playSound(AC_SCORING);
                                    displayScoring -= 5;
                                    startTimer = 0;
                                }
                            if (displayScoring <= 0)
                                lift.health -= 1;
                        }
                    else
                        {
                            if (currentGameState.peopleRescued > 0)
                                {
                                    if (displayScoring <= 0)
                                        displayScoring = GAME_SCORE_PER_PERSON;
                                    else
                                        {
                                            currentGameState.currentScore += 5;
                                            playSound(AC_SCORING);
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
            i++)
        {
            currentGameState.missileList[i].isAlive = 0;
            currentGameState.missileList[i].position.x = 0;
            currentGameState.missileList[i].position.y = 0;
        }
}

void
updateLiftPosition(float dt)
{
    /* We need to stall the position until at least
      * one second since our timer resoultion
      * doesn't allow for slow movement.
      * */
    /*
     * We also check here if the lift has arrived
     * at destination. In that case we proceed to
     * the scoring phase.
     */
    /*
     * Also theres the possibility that in each
     * night level, the lift can stop suddenly
     * for some time.
     */
    if (currentGameState.currentLevel % 3 == 0)
        {
            static float liftStopTimer = 0.0f;
            if (liftStopTimer >= GAME_MS_PER_STOP)
                {
                    char prob = rand() % 100;
                    if (prob < currentGameState.currentLevel)
                        {
                            liftCurrentlyStalled = 1;
                            playSound(AC_BREAKDOWN);
                        }
                    liftStopTimer = 0;
                }
            else
                {
                    if (liftCurrentlyStalled &&
                            liftStopTimer >= GAME_MS_PER_STALL*currentGameState.currentLevel)
                        {
                            liftCurrentlyStalled = 0;
                            liftStopTimer = 0;
                        }
                    liftStopTimer += dt;
                }
        }
    static float liftMovementTimer = 0.0f;
    if (liftCurrentlyStalled == 0)
        {
            if (liftMovementTimer >= GAME_MS_PER_LIFT_MOVEMENT)
                {
                    playSound(AC_CLIMB);
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
        }
}

void
updatePositions(float dt)
{
    /* Update lift position */
    updateLiftPosition(dt);
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
                            playSound(AC_HIT);
                        }

                    /* Now check if it has collided with the player rect */
                    if (SDL_HasIntersection(&lift.drawSpace, &mir) == SDL_TRUE)
                        {
                            lift.health -= 1;
                            playSound(AC_LOSS_HEALTH);
                            if (lift.health == 0)   // Game Over!!
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
    /* Now we repeat the process if theres a powerup on the screen */

    Powerup *pwrup = &currentGameState.onScreenPowerup;
    if (pwrup->isAlive == 1)
        {
            pwrup->position.x += cos(pwrup->angle)*MISSILE_SPEED*dt;
            pwrup->position.y += sin(pwrup->angle)*MISSILE_SPEED*dt;

            /*
             * Consider if the current missile has collided
             * with the shield
             */

            SDL_Rect r = getShieldRect();
            SDL_Rect mir;
            mir.x = pwrup->position.x;
            mir.y = pwrup->position.y;
            mir.w = 4;
            mir.h = 4;

            if (SDL_HasIntersection(&r, &mir) == SDL_TRUE)
                {
                    pwrup->isAlive = 0;
                    currentGameState.currentScore += GAME_SCORE_PER_BLOCK;
                    playSound(AC_HIT);
                }

            /* Now check if it has collided with the player rect */
            if (SDL_HasIntersection(&lift.drawSpace, &mir) == SDL_TRUE)
                {
                    playSound(AC_POWERUP);
                    switch (pwrup->type)
                        {
                        case PT_REPAIR:
                            lift.health = 3;
                            break;
                        case PT_ULTIMATE:
                            /* Clear all missiles on screen */
                            for (m = 0;
                                    m < MAX_MISSILE_COUNT;
                                    m++)
                                {
                                    currentGameState.missileList[m].isAlive = 0;
                                }
                            break;
                        }
                    currentGameState.currentScore += GAME_SCORE_PER_POWERUP;
                    pwrup->isAlive = 0;
                }

            /*
             * If missile leaves screen, mark it as dead.
             */

            if ((pwrup->position.x >= WORLD_WIDTH) ||
                    (pwrup->position.x <= 0) ||
                    (pwrup->position.y >= WORLD_HEIGHT) ||
                    (pwrup->position.y <= 0))
                pwrup->isAlive = 0;
        }
}

void
cleanGameLogic()
{
}
