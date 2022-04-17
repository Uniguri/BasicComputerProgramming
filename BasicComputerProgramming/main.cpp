#include <bangtal.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "game.h"

// MainScreen : 1280 x 720
// LeftTop : 0 x 360 ~ 640 x 720
// RightTop : 640 x 360 ~ 1280 x 720
// LeftDown : 0 x 0 ~ 640 x 360
// RightDown : 640 x 0 ~ 1280 x360

const float FPS = 0.01f;
const int BGM_IN_MENU_NUMBER = 2;
const int BGM_IN_GAME_NUMBER = 5;

game Game;

TimerID refresher;
time_t startTime;
SoundID bgmInMenu[BGM_IN_MENU_NUMBER];
SoundID bgmInGame[BGM_IN_GAME_NUMBER];
SoundID nowBGM;
SoundID MC;

bool isWPressed = false, isLeftPressed = false, isRightPressed = false, isUpPressed = false, isDownPressed = false;
bool isOnceStartGame = false, isInGame = false;

int easter_count = 0;

void tcb(TimerID refresher)
{
	if (isWPressed)
		jump(&Game.flappyGame);
	if (isLeftPressed)
		moveLeft(&Game.avoidGame);
	if (isRightPressed)
		moveRight(&Game.avoidGame);
	if (isUpPressed)
		moveUp(&Game.avoidGame);
	if (isDownPressed)
		moveDown(&Game.avoidGame);

	update(&Game);
	refresh(&Game);

	if (doEnd(&Game))
	{
		isWPressed = false, isLeftPressed = false, isRightPressed = false, isUpPressed = false, isDownPressed = false;
		ChangeScene(&Game.endScreen);
		if (Game.isFlappyOn && Game.isJumpingOn && Game.isAvoidingOn)
		{
			char strForMessage[100];
			char temp_str[30];
			unsigned int playTime = time(0) - startTime;
			int i = 0;
			for (time_t temp = playTime / 60; temp != 0; temp /= 60)
				i++;

			sprintf_s(strForMessage, "%s%s%s\ntime: ", Game.isFlappyOn ? "Flappy, " : "", Game.isJumpingOn ? "Jumping, " : "", Game.isAvoidingOn ? "Avoiding" : "");
			switch (i)
			{
			case 0:
				sprintf_s(temp_str, "%us", playTime);
				break;
			case 1:
				sprintf_s(temp_str, "%um %us", playTime / 60, playTime % 60);
				break;
			default:
				sprintf_s(temp_str, "%uh %um %us", playTime / 360, (playTime % 360) / 60, (playTime % 360) % 60);
				break;
			}
			strcat_s(strForMessage, temp_str);
			showMessage(strForMessage);
		}
		stopSound(nowBGM);
	}
	else
	{
		setTimer(refresher, FPS);
		startTimer(refresher);
	}
}

int main()
{
	srand((unsigned int)time(0));
	init(&Game);
	setTimerCallback(tcb);

	refresher = createTimer(FPS);
	bgmInGame[0] = createSound("sound/ingame/1.mp3");
	bgmInGame[1] = createSound("sound/ingame/2.mp3");
	bgmInGame[2] = createSound("sound/ingame/3.mp3");
	bgmInGame[3] = createSound("sound/ingame/4.mp3");
	bgmInGame[4] = createSound("sound/ingame/5.mp3");

	bgmInMenu[0] = createSound("sound/1.mp3");
	bgmInMenu[1] = createSound("sound/2.mp3");

	MC = createSound("sound/MC.mp3");

	//startTimer(t);
	startGame(Game.startScreen.mScene);
	
	DeleteScene(&Game.startScreen);
	DeleteScene(&Game.optionScreen);
	DeleteScene(&Game.endScreen);
}

void StartScreenKeyboardCallback(KeyCode key, KeyState state) {}

void OptionScreenKeyboardCallback(KeyCode key, KeyState state) {}

void GameScreenKeyboardCallback(KeyCode key, KeyState state)
{
	if (state == KeyState::KEY_PRESSED)
	{
		switch (key)
		{
		case KeyCode::KEY_W:
			isWPressed = true;
			break;
		case KeyCode::KEY_Q:
			hold(&Game.flappyGame);
			break;
		case KeyCode::KEY_SPACE:
			if (Game.isSoundOn && !Game.jumpGame.isJumping && Game.jumpGame.canJumping)
			{
				SoundID jump = createSound("sound/jump/jump.mp3");
				playSound(jump);
			}
			jump(&Game.jumpGame);
			break;
		case KeyCode::KEY_UP_ARROW:
			isUpPressed = true;
			break;
		case KeyCode::KEY_DOWN_ARROW:
			isDownPressed = true;
			break;
		case KeyCode::KEY_LEFT_ARROW:
			isLeftPressed = true;
			break;
		case KeyCode::KEY_RIGHT_ARROW:
			isRightPressed = true;
			break;
		case KeyCode::KEY_ESCAPE:
			stopTimer(refresher);
			ChangeScene(&Game.pauseScreen);
			break;
		default:
			break;
		}
	}
	else
	{
		switch (key)
		{
		case KeyCode::KEY_W:
			isWPressed = false;
			break;
		case KeyCode::KEY_Q:
			unhold(&Game.flappyGame);
			break;
		case KeyCode::KEY_UP_ARROW:
			isUpPressed = false;
			break;
		case KeyCode::KEY_DOWN_ARROW:
			isDownPressed = false;
			break;
		case KeyCode::KEY_LEFT_ARROW:
			isLeftPressed = false;
			break;
		case KeyCode::KEY_RIGHT_ARROW:
			isRightPressed = false;
			break;
		default:
			break;
		}
	}
}

void PauseScreenKeyboardCallback(KeyCode key, KeyState state) 
{
	if (key == KeyCode::KEY_ESCAPE && state == KeyState::KEY_PRESSED)
	{
		enterScene(Game.gameScreen);
		startTimer(refresher);
		setKeyboardCallback(GameScreenKeyboardCallback);
		setMouseCallback(GameScreenMouseCallback);
	}
}

void EndScreenKeyboardCallback(KeyCode key, KeyState state) {}



void StartScreenMouseCallback(ObjectID obj, int x, int y, MouseAction action)
{
	if (Game.isSoundOn)
		playSound(MC);
	if (obj == Game.startScreen.mObjs[0])
	{
		// Start
		if (Game.isFlappyOn || Game.isJumpingOn || Game.isAvoidingOn)
		{
			if (!isOnceStartGame)
			{
				isOnceStartGame = true;
				startGame(&Game);
			}
			else
			{
				restartGame(&Game);
			}
			isInGame = true;

			if (Game.isSoundOn)
			{
				stopSound(nowBGM);
				nowBGM = bgmInGame[rand() % BGM_IN_MENU_NUMBER];
				playSound(nowBGM, true);
			}

			startTimer(refresher);
			startTime = time(0);
		}
		else
		{
			showMessage("음.. 그건 너무 쉬울 것 같은데요?");
		}
	}
	else if (obj == Game.startScreen.mObjs[1])
	{
		// Optionwww
		ChangeScene(&Game.optionScreen);
	}
	else if (obj == Game.startScreen.mObjs[2])
	{
		// End
		endGame();
	}
	else if (obj == Game.startScreen.mObjs[3])
	{
		// ?
		showObject(Game.startScreen.mObjs[5]);
	}
	else if (obj == Game.startScreen.mObjs[4])
	{
		// Easter 
		easter_count++;
		if (Game.isSoundOn)
		{
			SoundID e = createSound("sound/click.mp3");
			playSound(e);
		}
		if (easter_count == 5)
		{
			if (Game.isSoundOn)
			{
				stopSound(nowBGM);
				nowBGM = createSound("sound/3.mp3");
				playSound(nowBGM, true);
			}

			setObjectImage(obj, "img/easter_egg_1.png");
		}
	}
	else if (obj == Game.startScreen.mObjs[5])
	{
		// Guide
		hideObject(obj);
	}
}

void OptionScreenMouseCallback(ObjectID obj, int x, int y, MouseAction action)
{
	if (Game.isSoundOn)
		playSound(MC);

	if (obj == Game.optionScreen.mObjs[0])
	{
		// Sound
		if (Game.isSoundOn)
		{
			Game.isSoundOn = false;
			setObjectImage(obj, "img/sound_X.png");
			setObjectImage(Game.pauseScreen.mObjs[0], "img/sound_X.png");
			stopSound(nowBGM);
		}
		else
		{
			Game.isSoundOn = true;
			setObjectImage(obj, "img/sound_O.png");
			setObjectImage(Game.pauseScreen.mObjs[0], "img/sound_O.png");

			srand(rand());
			nowBGM = bgmInMenu[rand() % BGM_IN_MENU_NUMBER];
			playSound(nowBGM, true);
		}
	}
	else if (obj == Game.optionScreen.mObjs[1])
	{
		// Flappy
		if (Game.isFlappyOn)
		{
			Game.isFlappyOn = false;
			setObjectImage(obj, "img/flappy_X.png");
		}
		else
		{
			Game.isFlappyOn = true;
			setObjectImage(obj, "img/flappy_O.png");
		}
	}
	else if (obj == Game.optionScreen.mObjs[2])
	{
		// Jumping
		if (Game.isJumpingOn)
		{
			Game.isJumpingOn = false;
			setObjectImage(obj, "img/jumping_X.png");
		}
		else
		{
			Game.isJumpingOn = true;
			setObjectImage(obj, "img/jumping_O.png");
		}
	}
	else if (obj == Game.optionScreen.mObjs[3])
	{
		// Avoiding
		if (Game.isAvoidingOn)
		{
			Game.isAvoidingOn = false;
			setObjectImage(obj, "img/avoiding_X.png");
		}
		else
		{
			Game.isAvoidingOn = true;
			setObjectImage(obj, "img/avoiding_O.png");
		}
	}
	else if (obj == Game.optionScreen.mObjs[4])
	{
		// Back
		ChangeScene(&Game.startScreen);
	}
}

void GameScreenMouseCallback(ObjectID obj, int x, int y, MouseAction action) {}

void PauseScreenMouseCallback(ObjectID obj, int x, int y, MouseAction action) 
{
	if (Game.isSoundOn)
		playSound(MC);

	if (obj == Game.pauseScreen.mObjs[0])
	{
		// Sound
		if (Game.isSoundOn)
		{
			Game.isSoundOn = false;
			setObjectImage(obj, "img/sound_X.png");
			setObjectImage(Game.pauseScreen.mObjs[0], "img/sound_X.png");
			stopSound(nowBGM);
		}
		else
		{
			Game.isSoundOn = true;
			setObjectImage(obj, "img/sound_O.png");
			setObjectImage(Game.pauseScreen.mObjs[0], "img/sound_O.png");
			nowBGM = bgmInGame[rand() % BGM_IN_GAME_NUMBER];
			playSound(nowBGM, true);
		}
	}
	else if (obj == Game.pauseScreen.mObjs[1])
	{
		// Resume
		enterScene(Game.gameScreen);
		startTimer(refresher);
		setKeyboardCallback(GameScreenKeyboardCallback);
		setMouseCallback(GameScreenMouseCallback);
	}
	else if (obj == Game.pauseScreen.mObjs[2])
	{
		// Menu
		if (Game.isSoundOn)
		{
			srand(rand());
			nowBGM = bgmInMenu[rand() % BGM_IN_MENU_NUMBER];
			playSound(nowBGM, true);
		}

		easter_count = 0;
		setObjectImage(Game.startScreen.mObjs[4], "img/empty.png");
		ChangeScene(&Game.startScreen);
	}
}

void EndScreenMouseCallback(ObjectID obj, int x, int y, MouseAction action)
{
	if (Game.isSoundOn)
		playSound(MC);

	if (obj == Game.endScreen.mObjs[0])
	{
		// Restart
		if (Game.isSoundOn)
		{
			srand(rand());
			nowBGM = bgmInGame[rand() % BGM_IN_GAME_NUMBER];
			playSound(nowBGM, true);
		}

		restartGame(&Game);
		startTimer(refresher);
	}
	else if (obj == Game.endScreen.mObjs[1])
	{
		// Menu
		if (Game.isSoundOn)
		{
			srand(rand());
			nowBGM = bgmInMenu[rand() % BGM_IN_MENU_NUMBER];
			playSound(nowBGM, true);
		}

		easter_count = 0;
		setObjectImage(Game.startScreen.mObjs[4], "img/empty.png");
		ChangeScene(&Game.startScreen);
	}
	else if (obj == Game.endScreen.mObjs[2])
	{
		// End
		endGame();
	}
}
