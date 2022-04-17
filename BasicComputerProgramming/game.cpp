#include "game.h"

void init(game* game)
{
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, false);

	setMouseCallback(StartScreenMouseCallback);
	setKeyboardCallback(StartScreenKeyboardCallback);

	game->startScreen.mScene = createScene("Start", "img/startmenu.png");
	SettingScene(&game->startScreen, 6, StartScreenKeyboardCallback, StartScreenMouseCallback);
	game->startScreen.mObjs[0] = createObject("img/start.png");
	locateObject(game->startScreen.mObjs[0], game->startScreen.mScene, 566, 720-409);
	game->startScreen.mObjs[1] = createObject("img/option.png");
	locateObject(game->startScreen.mObjs[1], game->startScreen.mScene, 566, 720-500);
	game->startScreen.mObjs[2] = createObject("img/end.png");
	locateObject(game->startScreen.mObjs[2], game->startScreen.mScene, 566, 720 - 591);
	game->startScreen.mObjs[3] = createObject("img/question.png");
	locateObject(game->startScreen.mObjs[3], game->startScreen.mScene, 1191, 720-696);
	game->startScreen.mObjs[4] = createObject("img/empty.png");
	scaleObject(game->startScreen.mObjs[4], 1.82);
	locateObject(game->startScreen.mObjs[4], game->startScreen.mScene, 921, 720 - 250);
	game->startScreen.mObjs[5] = createObject("img/guide.png");
	locateObject(game->startScreen.mObjs[5], game->startScreen.mScene, 0, 0);
	ShowAllObject(&game->startScreen);
	hideObject(game->startScreen.mObjs[5]);

	game->optionScreen.mScene = createScene("option", "img/black.png");
	SettingScene(&game->optionScreen, 5, OptionScreenKeyboardCallback, OptionScreenMouseCallback);
	game->optionScreen.mObjs[0] = createObject("img/sound_X.png");
	scaleObject(game->optionScreen.mObjs[0], 2);
	locateObject(game->optionScreen.mObjs[0], game->optionScreen.mScene, 640-50, 360-50+150);
	game->optionScreen.mObjs[1] = createObject("img/flappy_O.png");
	scaleObject(game->optionScreen.mObjs[1], 2);
	locateObject(game->optionScreen.mObjs[1], game->optionScreen.mScene, 640-50-150, 360-150-50);
	game->optionScreen.mObjs[2] = createObject("img/jumping_O.png");
	scaleObject(game->optionScreen.mObjs[2], 2);
	locateObject(game->optionScreen.mObjs[2], game->optionScreen.mScene, 640-50, 360-150-50);
	game->optionScreen.mObjs[3] = createObject("img/avoiding_O.png");
	scaleObject(game->optionScreen.mObjs[3], 2);
	locateObject(game->optionScreen.mObjs[3], game->optionScreen.mScene, 640-50+150, 360-150-50);
	game->optionScreen.mObjs[4] = createObject("img/back.png");
	locateObject(game->optionScreen.mObjs[4], game->optionScreen.mScene, 1191, 720 - 696);
	ShowAllObject(&game->optionScreen);

	game->gameScreen = createScene("Game", "img/background.png");

	game->pauseScreen.mScene = createScene("Pause", "img/black.png");
	SettingScene(&game->pauseScreen, 3, PauseScreenKeyboardCallback, PauseScreenMouseCallback);
	game->pauseScreen.mObjs[0] = createObject("img/sound_X.png");
	scaleObject(game->pauseScreen.mObjs[0], 2);
	locateObject(game->pauseScreen.mObjs[0], game->pauseScreen.mScene, 640 - 50, 360 - 50 + 150);
	game->pauseScreen.mObjs[1] = createObject("img/resume.png");
	locateObject(game->pauseScreen.mObjs[1], game->pauseScreen.mScene, 566, 720 - 409);
	game->pauseScreen.mObjs[2] = createObject("img/menu.png");
	locateObject(game->pauseScreen.mObjs[2], game->pauseScreen.mScene, 566, 720 - 500);
	ShowAllObject(&game->pauseScreen);

	game->endScreen.mScene = createScene("End", "img/startmenu.png");
	SettingScene(&game->endScreen, 3, EndScreenKeyboardCallback, EndScreenMouseCallback);
	game->endScreen.mObjs[0] = createObject("img/restart.png");
	locateObject(game->endScreen.mObjs[0], game->endScreen.mScene, 566, 720 - 409);
	game->endScreen.mObjs[1] = createObject("img/menu.png");
	locateObject(game->endScreen.mObjs[1], game->endScreen.mScene, 566, 720 - 500);
	game->endScreen.mObjs[2] = createObject("img/end.png");
	locateObject(game->endScreen.mObjs[2], game->endScreen.mScene, 566, 720 - 591);
	ShowAllObject(&game->endScreen);

	game->isSoundOn = false;
	game->isFlappyOn = true;
	game->isJumpingOn = true;
	game->isAvoidingOn = true;
}

void startGame(game* game)
{
	if(game->isFlappyOn)
		startGame(&game->flappyGame);
	if(game->isJumpingOn)
		startGame(&game->jumpGame);
	if(game->isAvoidingOn)
		startGame(&game->avoidGame);

	enterScene(game->gameScreen);
	setKeyboardCallback(GameScreenKeyboardCallback);
	setMouseCallback(GameScreenMouseCallback);
}

void restartGame(game* game)
{
	restartGame(&game->flappyGame);
	restartGame(&game->jumpGame);
	restartGame(&game->avoidGame);

	enterScene(game->gameScreen);
	setKeyboardCallback(GameScreenKeyboardCallback);
	setMouseCallback(GameScreenMouseCallback);
}

void update(game* game)
{
	if (game->isFlappyOn)
		update(&game->flappyGame);
	if (game->isJumpingOn)
		update(&game->jumpGame);
	if (game->isAvoidingOn)
		update(&game->avoidGame);
}

void refresh(game* game)
{
	if (game->isFlappyOn)
		changeCharacter(&game->flappyGame);
	if (game->isJumpingOn)
		changeCharacter(&game->jumpGame);

	if (game->isFlappyOn)
		refresh(&game->flappyGame, game->gameScreen);
	if (game->isJumpingOn)
		refresh(&game->jumpGame, game->gameScreen);
	if (game->isAvoidingOn)
		refresh(&game->avoidGame, game->gameScreen);
}

bool doEnd(game* game)
{
	bool ret = false;
	if (game->isFlappyOn)
	{
		if (isCollision(&game->flappyGame))
		{
			if (game->isSoundOn)
			{
				SoundID hit = createSound("sound/flappy/hit.mp3");
				playSound(hit);
			}
			return true;
		}
		
	}
	if (game->isJumpingOn)
	{
		if (isCollision(&game->jumpGame))
		{
			if (game->isSoundOn)
			{
				SoundID die = createSound("sound/jump/die.mp3");
				playSound(die);
			}
			return true;
		}
	}
	if(game->isAvoidingOn)
		if (isCollision(&game->avoidGame))
		{
			if (game->isSoundOn)
			{
				SoundID die = createSound("sound/avoid/die.mp3");
				playSound(die);
			}
			return true;
		}

	return false;
}
