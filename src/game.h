#ifndef __GAME_H
#define __GAME_H

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
} ShieldPosition;

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
	ShieldPosition shieldAngle;
} GameState;

// Global variables

static GameState currentGameState =
{
	1,
	0,
	{ 0,0 },
	SP_0
};

// Methods

void
initGameLogic();

void
startNewLevel(int lvl);

void
update(float dt);

#endif //__GAME.H