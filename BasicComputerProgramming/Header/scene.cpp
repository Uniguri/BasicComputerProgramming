#include "scene.h"

void SettingScene(Scene* scene, size_t numberOfObj, KeyboardCallback keyboardCb, MouseCallback mouseCb)
{
	scene->mNumberOfObj = numberOfObj;
	scene->mObjs = (ObjectID*)malloc(sizeof(ObjectID) * scene->mNumberOfObj);
	scene->mKeyBoardCallback = keyboardCb;
	scene->mMouseCallback = mouseCb;
}

void SetObjectLocation(Scene* scene, ObjectID obj, iCoord coord)
{
	locateObject(obj, scene->mScene, coord.x, coord.y);
}

void SetObjectLocation(Scene* scene, ObjectID* obj, iCoord coord)
{
	locateObject(*obj, scene->mScene, coord.x, coord.y);
}

void ShowAllObject(Scene* scene)
{
	for (int i = 0; i < scene->mNumberOfObj; i++)
	{
		showObject(scene->mObjs[i]);
	}
}

void ChangeScene(Scene* scene)
{
	enterScene(scene->mScene);
	setKeyboardCallback(scene->mKeyBoardCallback);
	setMouseCallback(scene->mMouseCallback);
}

void DeleteScene(Scene* scene)
{
	free(scene->mObjs);
}