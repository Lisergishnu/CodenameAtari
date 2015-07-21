/**
 * game.h - Procesamiento logica juego
 * Autor: MBT
 */

#ifndef __GAME_H
#define __GAME_H

// Game logic defines
#define BOTTOM_BASE_X 400
#define BOTTOM_BASE_Y 400
#define TOP_BASE_X 200
#define TOP_BASE_Y 100

#define WORLD_WIDTH 320
#define WORLD_HEIGHT 192

// Element definitions
typedef
struct _vectors
{
	int x;
	int y;
} Vector;

typedef
enum _defPos
{
	SP_0,
	SP_45,
	SP_90,
	SP_135,
	SP_180,
	SP_225,
	SP_270,
	SP_315
} Orientation;

typedef
enum __missile
{
	Vector position;
	Orientation angle;
} Missile

typedef
enum __gamescene
{
	GS_START,
	GS_PLAYING,
	GS_SCORING
} GameScene;

/* The whole game state is contained in this struct */
typedef
struct __gamestates
{
	char currentLevel;
	int currentScore;
	Vector liftPosition;
	Orientation shieldAngle;
	GameScene currentGameScene;
} GameState;

// Global variables
static GameState currentGameState =
{
	1,
	0,
	{ 0,0 },
	SP_0,
	GS_START
};

// Methods

void
initGameLogic();

void
startNewLevel(int lvl);

/* dt in milliseconds */
void
update(float dt);

/* This function will be called whenever there is a event to process in the game world, i.e. user input */
void
handleGameInput(SDL_Event e);

#endif //__GAME.H