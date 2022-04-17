#pragma once

#include <bangtal.h>
#include <time.h>
#include <stdlib.h>
#include "Header/scene.h"

#define JUMPING_MIN_X 0
#define JUMPING_MIN_Y 0
#define JUMPING_MAX_X 640
#define JUMPING_MAX_Y 355

#define JUMPING_BASIC_VEC_Y -10
#define JUMPING_JUMP_VEC_Y 15

#define JUMPING_BARRIER_WIDTH 50
#define JUMPING_BARRIER_HEIGHT 50
#define JUMPING_PLAYER_WIDTH 41
#define JUMPING_PLAYER_HEIGHT 54
#define JUMPING_BARRIER_MIN_MARGIN 300
#define JUMPING_PLAYER_X (JUMPING_MIN_X + 20)

#define JUMPING_BARRIER_SPEED -5

typedef struct _Jump_Box
{
	int PlayerY;
	int playerImgCount;
	ObjectID player;
	int playerVecY;
	int barrierX[8];
	int barrierSpeedX;
	ObjectID barrier[8];
	bool isJumping;
	bool canJumping;
	int count;
} jumping;

void startGame(jumping* jumping);
void restartGame(jumping* jumping);

void update(jumping* jumping);
void refresh(jumping* jumping, SceneID screen);

void jump(jumping* jumping);
bool isCollision(jumping* jumping);

void changeCharacter(jumping* jumping);