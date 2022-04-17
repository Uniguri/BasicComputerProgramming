#pragma once
#include <bangtal.h>
#include <malloc.h>

typedef struct _INT_COORD
{
	int x;
	int y;
} iCoord;

typedef iCoord vector;

typedef struct _CHAR_COORD
{
	char x;
	char y;
} cCoord;

typedef struct _INT_BOX
{
	int leftTop;
	int leftDown;
	int rightTop;
	int rightDown;
} iBox;

enum Direction
{
	LEFT = 0, RIGHT, UP, DOWN
};

typedef struct _SCENE
{
	SceneID mScene;
	size_t mNumberOfObj;
	ObjectID* mObjs;
	KeyboardCallback mKeyBoardCallback;
	MouseCallback mMouseCallback;
} Scene;

void SettingScene(Scene* scene, size_t numberOfObj, KeyboardCallback keyboardCb, MouseCallback mouseCb);
void SetObjectLocation(Scene* scene, ObjectID obj, iCoord coord);
void SetObjectLocation(Scene* scene, ObjectID* obj, iCoord coord);
void ShowAllObject(Scene* scene);
void ChangeScene(Scene* scene);
void DeleteScene(Scene* scene);