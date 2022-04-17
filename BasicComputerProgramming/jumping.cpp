#include "jumping.h"

const char* const JUMPING_PLAYER_IMG[] = { "img/jumping/player1.png", "img/jumping/player2.png", "img/jumping/player3.png",
											"img/jumping/player4.png" , "img/jumping/player5.png" ,"img/jumping/player6.png",
											"img/jumping/player7.png" ,"img/jumping/player8.png" };

const char* const JUMPING_BARRIER_IMG[] = { "img/jumping/barrier1.png", "img/jumping/barrier2.png", "img/jumping/barrier3.png" };

void startGame(jumping* jumping)
{
	srand((unsigned int)time(0));

	jumping->PlayerY = JUMPING_MIN_Y;
	jumping->playerVecY = JUMPING_BASIC_VEC_Y;
	jumping->barrierSpeedX = JUMPING_BARRIER_SPEED;
	jumping->playerImgCount = 0;
	jumping->player = createObject(JUMPING_PLAYER_IMG[jumping->playerImgCount]);
	jumping->isJumping = false;
	jumping->canJumping = true;
	
	for (int i = 0; i < 8; i++)
	{
		jumping->barrier[i] = createObject(JUMPING_BARRIER_IMG[rand()%3]);
		srand(rand() * time(0));
		jumping->barrierX[i] = JUMPING_BARRIER_WIDTH + JUMPING_BARRIER_MIN_MARGIN*(i+3) + 100 * (rand() % 3+2);
		
	}
}

void restartGame(jumping* jumping)
{
	jumping->PlayerY = JUMPING_MIN_Y;
	jumping->playerVecY = JUMPING_BASIC_VEC_Y;
	jumping->barrierSpeedX = JUMPING_BARRIER_SPEED;
	jumping->playerImgCount = 0;
	jumping->isJumping = false;
	jumping->canJumping = true;
	hideObject(jumping->player);
	for (int i = 0; i < 8; i++)
	{
		srand(rand() * time(0));
		jumping->barrierX[i] = JUMPING_BARRIER_WIDTH + JUMPING_BARRIER_MIN_MARGIN * (i + 3) + 100 * (rand() % 3 + 2);
		hideObject(jumping->barrier[i]);
	}
}

void update(jumping* jumping)
{
	srand(rand() * time(0));

	// Move Player
	jumping->PlayerY += jumping->playerVecY;
	if (jumping->PlayerY < JUMPING_MIN_Y)
	{
		jumping->PlayerY = JUMPING_MIN_Y;
		jumping->canJumping = true;
	}
	if (jumping->PlayerY + JUMPING_PLAYER_HEIGHT > JUMPING_MAX_Y)
		jumping->PlayerY = JUMPING_MAX_Y - JUMPING_PLAYER_HEIGHT;

	//Move Barriers
	for (int i = 0; i < 8; i++)
	{
		jumping->barrierX[i] += jumping->barrierSpeedX;
		if (jumping->barrierX[i] + JUMPING_BARRIER_WIDTH < JUMPING_MIN_X)
		{
			if (i == 0)
				jumping->barrierX[i] = jumping->barrierX[7] + JUMPING_BARRIER_WIDTH + JUMPING_BARRIER_MIN_MARGIN * (rand() % 3 + 1);
			else
				jumping->barrierX[i] = jumping->barrierX[i - 1] + JUMPING_BARRIER_WIDTH + JUMPING_BARRIER_MIN_MARGIN * (rand() % 3 + 1);

			setObjectImage(jumping->barrier[i], JUMPING_BARRIER_IMG[rand() % 3]);
		}
	}

	// Change Vector
	if (jumping->isJumping)
	{
		if (jumping->playerVecY < JUMPING_JUMP_VEC_Y)
			jumping->playerVecY += (JUMPING_JUMP_VEC_Y / 10) + (JUMPING_JUMP_VEC_Y % 10);
		else
		{
			jumping->playerVecY = JUMPING_JUMP_VEC_Y;
			jumping->isJumping = false;
		}
	}
	else
	{
		if (jumping->playerVecY > JUMPING_BASIC_VEC_Y)
			jumping->playerVecY += (JUMPING_BASIC_VEC_Y / 10) + (JUMPING_BASIC_VEC_Y % 10);
		else if (jumping->playerVecY < JUMPING_BASIC_VEC_Y)
			jumping->playerVecY = JUMPING_BASIC_VEC_Y;
		else if(jumping->PlayerY == JUMPING_MIN_Y)
			jumping->canJumping = true;
	}
}

void refresh(jumping* jumping, SceneID screen)
{
	for (int i = 0; i < 8; i++)
	{
		if (jumping->barrierX[i] + JUMPING_BARRIER_WIDTH < JUMPING_MAX_X && jumping->barrierX[i] + JUMPING_BARRIER_WIDTH > JUMPING_MIN_X)
		{
			showObject(jumping->barrier[i]);
			locateObject(jumping->barrier[i], screen, jumping->barrierX[i], JUMPING_MIN_Y);
		}
		else
			hideObject(jumping->barrier[i]);
	}

	showObject(jumping->player);
	locateObject(jumping->player, screen, JUMPING_PLAYER_X, jumping->PlayerY);
}

void jump(jumping* jumping)
{
	srand((unsigned int)time(NULL));
	if (!jumping->isJumping && jumping->canJumping)
	{
		jumping->isJumping = true;
		jumping->canJumping = false;
	}
}

bool isCollision(jumping* jumping)
{
	for (int i = 0; i < 8; i++)
	{
		if (JUMPING_PLAYER_X + JUMPING_PLAYER_WIDTH >= jumping->barrierX[i] + 10 && JUMPING_PLAYER_X + JUMPING_PLAYER_WIDTH <= jumping->barrierX[i] + JUMPING_BARRIER_WIDTH - 10
			|| JUMPING_PLAYER_X >= jumping->barrierX[i] && JUMPING_PLAYER_X + 10 <= jumping->barrierX[i] + JUMPING_BARRIER_WIDTH - 10) 
		{
			if (jumping->PlayerY < JUMPING_BARRIER_HEIGHT - 5)
				return true;
		}
	}

	return false;
}

void changeCharacter(jumping* jumping)
{
	jumping->count++;
	if (jumping->count == 5)
	{
		if (++jumping->playerImgCount >= 8)
		{
			jumping->playerImgCount = 0;
		}
		setObjectImage(jumping->player, JUMPING_PLAYER_IMG[jumping->playerImgCount]);

		jumping->count = 0;
	}
}
