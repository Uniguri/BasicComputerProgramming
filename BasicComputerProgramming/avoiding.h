#pragma once

#include <bangtal.h>
#include <time.h>
#include <stdlib.h>
#include "Header/scene.h"

#define AVOIDING_MIN_X 645
#define AVOIDING_MIN_Y 0
#define AVOIDING_MAX_X 1280
#define AVOIDING_MAX_Y 720

#define AVOIDING_PLAYER_WIDTH 50
#define AVOIDING_PLAYER_HEIGHT 50
#define AVOIDING_BULLET_WIDTH 11
#define AVOIDING_BULLET_HEIGHT 11

#define AVOIDING_BULLET_NUMBER 10

#define AVOIDING_BULLET_CREATATION_PER_FRAME 20

#define AVOIDING_PLAYER_SPEED 5

typedef struct _DOUBLE_VECTOR
{
	double x;
	double y;
} dVec;

typedef struct _Avoiding
{
	ObjectID player;
	iCoord playerLoc;
	bool isBulletExist[AVOIDING_BULLET_NUMBER];
	ObjectID bullet[AVOIDING_BULLET_NUMBER];
	dVec bulletLoc[AVOIDING_BULLET_NUMBER];
	dVec bulletVec[AVOIDING_BULLET_NUMBER];
	int BulletBounceLimit[AVOIDING_BULLET_NUMBER];
	double divideBulletSpeed;
	int framePerCreation;
} avoiding;

void startGame(avoiding* avoid);
void restartGame(avoiding* avoid);

void update(avoiding* avoid);
void refresh(avoiding* avoid, SceneID screen);

void moveLeft(avoiding* avoid);
void moveRight(avoiding* avoid);
void moveUp(avoiding* avoid);
void moveDown(avoiding* avoid);
bool isCollision(avoiding* avoid);