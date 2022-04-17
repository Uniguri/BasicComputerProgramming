#pragma once

#include <bangtal.h>
#include <time.h>
#include <stdlib.h>
#include "Header/scene.h"

#define FLAPPY_MIN_X 0
#define FLAPPY_MIN_Y 365
#define FLAPPY_MAX_X 640
#define FLAPPY_MAX_Y 720

#define FLAPPY_PLAYER_WIDTH 44
#define FLAPPY_PLAYERHEIGHT 31
#define FLAPPY_BARRIER_WIDTH 50
#define FLAPPY_BARRIER_MARGIN 200
#define FLAPPY_EMPTY_WIDTH FLAPPY_BARRIER_WIDTH
#define FLAPPY_EMPTY_HEIGHT 100

#define FLAPPY_PLAYER_X (FLAPPY_MIN_X + 20)
#define FLAPPY_BASIC_VEC_Y -3

#define FLAPPY_BARRIER_SPEED -1

typedef struct _Flappy_Bird
{
	int PlayerY;
	bool isHold;
	ObjectID player;
	int playerImgCount;
	int playerVecY;
	int barrierX[4];
	int barrierSpeedX;
	int emptyY[4];
	ObjectID barrier[4];
	ObjectID empty[4];
	int count;
} flappy;

void startGame(flappy* flappy);
void restartGame(flappy* flappy);

void update(flappy* flappy);
void refresh(flappy* flappy, SceneID screen);

void jump(flappy* flappy);
void hold(flappy* flappy);
void unhold(flappy* flappy);
bool isCollision(flappy* flappy);

void changeCharacter(flappy* flappy);