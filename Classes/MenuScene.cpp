#include "MenuScene.h"

USING_NS_CC;

Scene* MenuScene::createScene()
{
	return MenuScene::create();
}

bool MenuScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	// 在这里进行初始化，有需要可新加函数，如：initComponents()

	return true;
}
