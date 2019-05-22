#include "GameScene.h"
#include "SettingButton.h"


Scene* GameScene::createScene()
{
	return GameScene::create();
}

bool GameScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	// 在这里进行初始化，有需要可新加函数，如：initComponents()


	// 添加背景图片
	auto sprite = Sprite::create("/image/gamescene/jetbraintheme/background.png");
	sprite->setPosition(Point(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
	this->addChild(sprite);

	// 设置按钮
	this->addChild(SettingButton::create());

	// 返回按钮
	this->addChild(BackButton::create());

	auto remainStep = Label::createWithTTF("20", "/font/marker_felt.ttf", 48);

	// glow effect is TTF only, specify the glow color desired.
	remainStep->enableGlow(Color4B::YELLOW);
	remainStep->setPosition(225, 670);
	this->addChild(remainStep);

	auto levelSprite = Sprite::create("/image/gamescene/jetbraintheme/level_sprite.png");
	levelSprite->setScale(1);
	levelSprite->setPosition(225, 600);
	this->addChild(levelSprite, 0);

	auto level = Label::createWithTTF("4", "/font/marker_felt.ttf", 24);
	level->setPosition(225, 600);
	this->addChild(level,1);

	return true;
}
