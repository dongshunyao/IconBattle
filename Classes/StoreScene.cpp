#include "StoreScene.h"

Scene* StoreScene::createScene()
{
	return StoreScene::create();
}

bool StoreScene::init()
{
	if (!Scene::init()) return false;

	// TODO 替换设置按钮
	new SettingButton(this,4);

	// 返回按钮
	this->addChild(BackButton::create());

	return true;
}
