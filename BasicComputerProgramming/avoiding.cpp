#include "avoiding.h"

const char* const BULLET_IMG[] = { "img/avoiding/blue_square_bullet.png", "img/avoiding/red_square_bullet.png", "img/avoiding/green_square_bullet.png" };

void startGame(avoiding* avoid)
{
	srand((unsigned int)time(NULL));
	avoid->player = createObject("img/avoiding/player.png");
	
	avoid->playerLoc = { (AVOIDING_MAX_X + AVOIDING_MIN_X) / 2,(AVOIDING_MAX_Y + AVOIDING_MIN_Y) / 2 };
	avoid->framePerCreation = 0;
	avoid->divideBulletSpeed = 200;
	for (int i = 0; i < AVOIDING_BULLET_NUMBER; i++)
	{
		avoid->isBulletExist[i] = false;
		avoid->bullet[i] = createObject("img/avoiding/blue_square_bullet.png");
		avoid->bulletLoc[i] = { 0, 0 };
		avoid->bulletVec[i] = { 0, 0 };
	}
}

void restartGame(avoiding* avoid)
{
	srand((unsigned int)time(NULL));
	avoid->playerLoc = { (AVOIDING_MAX_X + AVOIDING_MIN_X) / 2,(AVOIDING_MAX_Y + AVOIDING_MIN_Y) / 2 };
	hideObject(avoid->player);
	avoid->framePerCreation = 0;
	avoid->divideBulletSpeed = 200;
	for (int i = 0; i < AVOIDING_BULLET_NUMBER; i++)
	{
		hideObject(avoid->bullet[i]);
		avoid->isBulletExist[i] = false;
		avoid->bulletLoc[i] = { 0, 0 };
		avoid->bulletVec[i] = { 0, 0 };
	}
}

void update(avoiding* avoid)
{
	srand(rand() * time(0));
	bool onceCreation = false;

	if (avoid->playerLoc.x < AVOIDING_MIN_X)
		avoid->playerLoc.x = AVOIDING_MIN_X;
	else if (avoid->playerLoc.x + AVOIDING_PLAYER_WIDTH > AVOIDING_MAX_X)
		avoid->playerLoc.x = AVOIDING_MAX_X - AVOIDING_PLAYER_WIDTH;

	if (avoid->playerLoc.y < AVOIDING_MIN_Y)
		avoid->playerLoc.y = AVOIDING_MIN_Y;
	else if (avoid->playerLoc.y + AVOIDING_PLAYER_HEIGHT > AVOIDING_MAX_Y)
		avoid->playerLoc.y = AVOIDING_MAX_Y - AVOIDING_PLAYER_HEIGHT;

	avoid->framePerCreation++;
	for (int i = 0; i < AVOIDING_BULLET_NUMBER; i++)
	{
		if (avoid->isBulletExist[i])
		{
			avoid->bulletLoc[i].x += avoid->bulletVec[i].x;
			avoid->bulletLoc[i].y += avoid->bulletVec[i].y;

			if (avoid->bulletLoc[i].x < AVOIDING_MIN_X
				|| avoid->bulletLoc[i].x  > AVOIDING_MAX_X - AVOIDING_BULLET_WIDTH
				|| avoid->bulletLoc[i].y < AVOIDING_MIN_Y
				|| avoid->bulletLoc[i].y > AVOIDING_MAX_Y - AVOIDING_BULLET_HEIGHT)
			{
				if (avoid->BulletBounceLimit[i] > 0)
				{
					avoid->BulletBounceLimit[i]--;
					avoid->bulletVec[i].x *= -1;
					avoid->bulletVec[i].y *= -1;
				}
				else
					avoid->isBulletExist[i] = false;
			}
		}
		else if (!onceCreation && avoid->framePerCreation >= AVOIDING_BULLET_CREATATION_PER_FRAME)
		{
			onceCreation = true;
			avoid->isBulletExist[i] = true;
			avoid->framePerCreation = 0;
			switch (rand() % 4)
			{
			// Up
			case 0:
				avoid->bulletLoc[i].x = rand() % (AVOIDING_MAX_X - AVOIDING_MIN_X) + AVOIDING_MIN_X;
				avoid->bulletLoc[i].y = AVOIDING_MAX_Y - AVOIDING_BULLET_HEIGHT;
				break;
			// Down
			case 1:
				avoid->bulletLoc[i].x = rand() % (AVOIDING_MAX_X - AVOIDING_MIN_X) + AVOIDING_MIN_X;
				avoid->bulletLoc[i].y = AVOIDING_MIN_Y;
				break;
			// Right
			case 2:
				avoid->bulletLoc[i].x = AVOIDING_MAX_X - AVOIDING_BULLET_WIDTH;
				avoid->bulletLoc[i].y = rand() % (AVOIDING_MAX_Y - AVOIDING_MIN_Y) + AVOIDING_MIN_Y;
				break;
			// Left
			case 3:
				avoid->bulletLoc[i].x = AVOIDING_MIN_X;
				avoid->bulletLoc[i].y = rand() % (AVOIDING_MAX_Y - AVOIDING_MIN_Y) + AVOIDING_MIN_Y;
				break;
			default:
				break;
			}

			srand(rand() * time(0));
			avoid->BulletBounceLimit[i] = rand() % 30 - 10;

			if(avoid->BulletBounceLimit[i] <= 0)
				setObjectImage(avoid->bullet[i], BULLET_IMG[rand() % 2]);
			else
				setObjectImage(avoid->bullet[i], BULLET_IMG[2]);

			srand(rand() * time(0));
			avoid->bulletVec[i].x = (avoid->playerLoc.x - avoid->bulletLoc[i].x) + rand() % (200) - 100;
			avoid->bulletVec[i].x /= rand() % ((int)avoid->divideBulletSpeed / 2) + avoid->divideBulletSpeed / 2;
			avoid->bulletVec[i].y = (avoid->playerLoc.y - avoid->bulletLoc[i].y) + rand() % (200) - 100;
			avoid->bulletVec[i].y /= rand() % ((int)avoid->divideBulletSpeed / 2) + avoid->divideBulletSpeed / 2;
		}
	}
}

void refresh(avoiding* avoid, SceneID screen)
{
	for (int i = 0; i < AVOIDING_BULLET_NUMBER; i++)
	{
		if (avoid->isBulletExist[i])
		{
			showObject(avoid->bullet[i]);
			locateObject(avoid->bullet[i], screen, (int)avoid->bulletLoc[i].x, (int)avoid->bulletLoc[i].y);
		}
		else
			hideObject(avoid->bullet[i]);
	}

	showObject(avoid->player);
	locateObject(avoid->player, screen, avoid->playerLoc.x, avoid->playerLoc.y);
}

void moveLeft(avoiding* avoid)
{
	avoid->playerLoc.x += -AVOIDING_PLAYER_SPEED;
}

void moveRight(avoiding* avoid)
{
	avoid->playerLoc.x += AVOIDING_PLAYER_SPEED;
}

void moveUp(avoiding* avoid)
{
	avoid->playerLoc.y += AVOIDING_PLAYER_SPEED;
}

void moveDown(avoiding* avoid)
{
	avoid->playerLoc.y += -AVOIDING_PLAYER_SPEED;
}

bool isCollision(avoiding* avoid)
{
	for (int i = 0; i < AVOIDING_BULLET_NUMBER; i++)
	{
		if ((avoid->playerLoc.x + 10 < avoid->bulletLoc[i].x + AVOIDING_BULLET_WIDTH && avoid->bulletLoc[i].x + AVOIDING_BULLET_WIDTH < avoid->playerLoc.x + AVOIDING_PLAYER_WIDTH - 10)
			|| (avoid->playerLoc.x + 10 < avoid->bulletLoc[i].x && avoid->bulletLoc[i].x < avoid->playerLoc.x + AVOIDING_PLAYER_WIDTH - 10))
		{
			if ((avoid->playerLoc.y + 10 < avoid->bulletLoc[i].y + AVOIDING_BULLET_HEIGHT && avoid->bulletLoc[i].y + AVOIDING_BULLET_HEIGHT < avoid->playerLoc.y + AVOIDING_PLAYER_HEIGHT - 10)
				|| (avoid->playerLoc.y + 10 < avoid->bulletLoc[i].y && avoid->bulletLoc[i].y < avoid->playerLoc.y + AVOIDING_PLAYER_HEIGHT - 10))
			{
				return true;
			}
		}
	}

	return false;
}
