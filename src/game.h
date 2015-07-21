/**
 * game.h - Procesamiento logica juego
 * Autor: MBT
 */

#ifndef __GAME_H
#define __GAME_H

#include "sdl.h"
#include <stdio.h>

// Game logic defines
// Game space 220x192
#define GAME_GRID_SIZE 4
#define GAME_GRID_WIDTH 55
#define GAME_GRID_HEIGHT 48

// Tama�os definidos en grid sizes
#define SIZE_BASE	4;
#define SIZE_LIFT	6;
#define SIZE_BULLET 1;

#define MAX_MISSILE_COUNT 100

#define WORLD_WIDTH 320
#define WORLD_HEIGHT 192

// Element definitions
typedef
struct _vectors
{
	int x;
	int y;
} Vector;

// Orientaciones generales
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
struct __missile
{
	int isAlive;
	Vector position;
	Orientation orientation;
} Missile;

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
	// Level
	char currentLevel;
	int onScreenMissileCount;
	// Score
	int currentScore;
	int peopleRescued;

	Missile missileList[MAX_MISSILE_COUNT];

	Vector botBase;
	Vector topBase;
	
	Vector liftPosition;
	GameScene currentGameScene;
} GameState;

typedef
struct __base
{
	SDL_Rect drawSpace;
	Vector position;
} Base;

/* Player Stuff */
typedef
struct __lift
{
	int health;

	SDL_Rect drawSpace;

	Orientation orientation;
	Vector position;
} Lift;

// Global variables
GameState currentGameState;
Lift lift;

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

void
initializeMissiles();

void
updatePositions();

#endif //__GAME.H
