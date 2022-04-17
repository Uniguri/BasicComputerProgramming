#include "flappy.h"

const char* const FLAPPY_PLAYER_IMG[] = { "img/flappy/bird1.png", "img/flappy/bird2.png" };

void startGame(flappy* flappy)
{
	srand((unsigned int)time(0));
	
	flappy->player = createObject("img/flappy/bird1.png");
	flappy->playerImgCount = 0;
	flappy->count = 0;

	flappy->PlayerY = (FLAPPY_MAX_Y + FLAPPY_MIN_Y) / 2;
	flappy->isHold = false;
	flappy->playerVecY = FLAPPY_BASIC_VEC_Y;
	flappy->barrierSpeedX = FLAPPY_BARRIER_SPEED;

	for (int i = 0; i < 4; i++)
	{
		flappy->empty[i] = createObject("img/flappy/empty.png");
		flappy->barrier[i] = createObject("img/flappy/barrier.png");

		srand((unsigned int)rand() * time(0));
		flappy->emptyY[i] = rand() % (FLAPPY_MAX_Y - FLAPPY_EMPTY_HEIGHT - FLAPPY_MIN_Y) + FLAPPY_MIN_Y;
		flappy->barrierX[i] = FLAPPY_PLAYER_X + (i + 1) * FLAPPY_BARRIER_MARGIN + i * FLAPPY_BARRIER_WIDTH;
	}
}

void restartGame(flappy* flappy)
{
	flappy->playerImgCount = 0;
	flappy->count = 0;

	flappy->PlayerY = (FLAPPY_MAX_Y + FLAPPY_MIN_Y) / 2;
	flappy->isHold = false;
	flappy->playerVecY = FLAPPY_BASIC_VEC_Y;
	flappy->barrierSpeedX = FLAPPY_BARRIER_SPEED;

	for (int i = 0; i < 4; i++)
	{
		srand((unsigned int)rand() * time(0));
		flappy->emptyY[i] = rand() % (FLAPPY_MAX_Y - FLAPPY_EMPTY_HEIGHT - FLAPPY_MIN_Y) + FLAPPY_MIN_Y;
		flappy->barrierX[i] = FLAPPY_PLAYER_X + (i + 1) * FLAPPY_BARRIER_MARGIN + i * FLAPPY_BARRIER_WIDTH;

		hideObject(flappy->empty[i]);
		hideObject(flappy->barrier[i]);
	}

	hideObject(flappy->player);
}

void update(flappy* flappy)
{
	srand((unsigned int)rand() * time(0));

	// Move Player
	if(!flappy->isHold)
		flappy->PlayerY += flappy->playerVecY;
	if (flappy->PlayerY < FLAPPY_MIN_Y)
		flappy->PlayerY = FLAPPY_MIN_Y;
	else if (flappy->PlayerY + FLAPPY_PLAYERHEIGHT > FLAPPY_MAX_Y)
		flappy->PlayerY = FLAPPY_MAX_Y - FLAPPY_PLAYERHEIGHT;

	//Move Barriers
	for (int i = 0; i < 4; i++)
	{
		flappy->barrierX[i] += flappy->barrierSpeedX;
		if (flappy->barrierX[i] + FLAPPY_BARRIER_WIDTH < FLAPPY_MIN_X)
		{
			if (i == 0)
				flappy->barrierX[i] = flappy->barrierX[3] + FLAPPY_BARRIER_WIDTH + FLAPPY_BARRIER_MARGIN;
			else
				flappy->barrierX[i] = flappy->barrierX[i-1] + FLAPPY_BARRIER_WIDTH + FLAPPY_BARRIER_MARGIN;

			flappy->emptyY[i] = rand() % (FLAPPY_MAX_Y - FLAPPY_EMPTY_HEIGHT - FLAPPY_MIN_Y) + FLAPPY_MIN_Y;
		}
	}

	// Decrese Vector
	if (flappy->playerVecY > FLAPPY_BASIC_VEC_Y)
		flappy->playerVecY += FLAPPY_BASIC_VEC_Y;
	else if (flappy->playerVecY < FLAPPY_BASIC_VEC_Y)
		flappy->playerVecY = FLAPPY_BASIC_VEC_Y;
}

void refresh(flappy* flappy, SceneID screen)
{
	for (int i = 0; i < 4; i++)
	{
		locateObject(flappy->barrier[i], screen, flappy->barrierX[i], FLAPPY_MIN_Y);
		locateObject(flappy->empty[i], screen, flappy->barrierX[i], FLAPPY_MIN_Y);

		locateObject(flappy->barrier[i], screen, -FLAPPY_BARRIER_WIDTH, FLAPPY_MIN_Y);
		locateObject(flappy->empty[i], screen, -FLAPPY_BARRIER_WIDTH, FLAPPY_MIN_Y);

		if (flappy->barrierX[i] + FLAPPY_BARRIER_WIDTH < FLAPPY_MAX_X)
		{
			showObject(flappy->empty[i]);
			showObject(flappy->barrier[i]);

			locateObject(flappy->barrier[i], screen, flappy->barrierX[i], FLAPPY_MIN_Y);
			locateObject(flappy->empty[i], screen, flappy->barrierX[i], flappy->emptyY[i]);
		}
	}

	showObject(flappy->player);
	locateObject(flappy->player, screen, FLAPPY_PLAYER_X, flappy->PlayerY);
}

void jump(flappy* flappy)
{
	srand((unsigned int)time(NULL));
	if(!flappy->isHold)
		flappy->playerVecY = 5;
}

void hold(flappy* flappy)
{
	flappy->isHold = true;
	flappy->barrierSpeedX = -2;
}

void unhold(flappy* flappy)
{
	flappy->isHold = false;
	flappy->barrierSpeedX = FLAPPY_BARRIER_SPEED;
}

bool isCollision(flappy* flappy)
{
	// Barrier Check
	for (int i = 0; i < 4; i++)
	{
		if (FLAPPY_PLAYER_X + FLAPPY_PLAYER_WIDTH >= flappy->barrierX[i] && FLAPPY_PLAYER_X + FLAPPY_PLAYER_WIDTH <= flappy->barrierX[i] + FLAPPY_BARRIER_WIDTH
			|| FLAPPY_PLAYER_X >= flappy->barrierX[i] && FLAPPY_PLAYER_X <= flappy->barrierX[i] + FLAPPY_BARRIER_WIDTH)
		{
			if (!(flappy->PlayerY >= flappy->emptyY[i] - 5 && flappy->PlayerY + FLAPPY_PLAYERHEIGHT <= flappy->emptyY[i] + FLAPPY_EMPTY_HEIGHT + 5))
				return true;
		}
	}

	return false;
}

void changeCharacter(flappy* flappy)
{
	flappy->count++;
	if (flappy->count == 5)
	{
		if (++flappy->playerImgCount >= 2)
		{
			flappy->playerImgCount = 0;
		}
		setObjectImage(flappy->player, FLAPPY_PLAYER_IMG[flappy->playerImgCount]);

		flappy->count = 0;
	}
}
