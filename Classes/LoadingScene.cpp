#include "LoadingScene.h"

USING_NS_CC;

Scene* LoadingScene::createScene()
{
	return LoadingScene::create();
}

bool LoadingScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	// 在这里进行初始化，有需要可新加函数，如：initComponents()

	return true;
}
