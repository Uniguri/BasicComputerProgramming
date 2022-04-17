#pragma once

#include <bangtal.h>
#include "Header/scene.h"
#include "flappy.h"
#include "jumping.h"
#include "avoiding.h"

typedef struct _Game
{
	flappy flappyGame;
	jumping jumpGame;
	avoiding avoidGame;

	Scene startScreen;
	Scene optionScreen;
	SceneID gameScreen;
	Scene pauseScreen;
	Scene endScreen;

	bool isSoundOn, isFlappyOn, isJumpingOn, isAvoidingOn;
} game;

void init(game *game);

void startGame(game* game);
void restartGame(game* game);

void update(game* game);
void refresh(game* game);

bool doEnd(game* game);

// implements of below functions are in main.cpp.

void StartScreenKeyboardCallback(KeyCode key, KeyState state);
void OptionScreenKeyboardCallback(KeyCode key, KeyState state);
void GameScreenKeyboardCallback(KeyCode key, KeyState state);
void PauseScreenKeyboardCallback(KeyCode key, KeyState state);
void EndScreenKeyboardCallback(KeyCode key, KeyState state);

void StartScreenMouseCallback(ObjectID obj, int x, int y, MouseAction action);
void OptionScreenMouseCallback(ObjectID obj, int x, int y, MouseAction action);
void GameScreenMouseCallback(ObjectID obj, int x, int y, MouseAction action);
void PauseScreenMouseCallback(ObjectID obj, int x, int y, MouseAction action);
void EndScreenMouseCallback(ObjectID obj, int x, int y, MouseAction action);
