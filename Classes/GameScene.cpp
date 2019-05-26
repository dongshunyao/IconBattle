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

#pragma  region Init GameScene

	// 添加背景图片
	auto sprite = Sprite::create("/image/gamescene/jetbraintheme/background.png");
	sprite->setPosition(Point(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
	this->addChild(sprite);

	// 设置按钮
	this->addChild(SettingButton::create());

	// 返回按钮
	this->addChild(BackButton::create());

	// 剩余步数Label
	auto remainStep = Label::createWithTTF("20", "/font/marker_felt.ttf", 48);
	// glow effect is TTF only, specify the glow color desired.
	remainStep->enableGlow(Color4B::YELLOW);
	remainStep->setPosition(225, 660);
	this->addChild(remainStep);

	// 当前关卡数背景图片
	auto levelSprite = Sprite::create("/image/gamescene/jetbraintheme/level_sprite.png");
	levelSprite->setScale(1);
	levelSprite->setPosition(225, 580);
	this->addChild(levelSprite, 0);

	auto level = Label::createWithTTF("4", "/font/marker_felt.ttf", 24);
	level->setPosition(225, 580);
	this->addChild(level, 1);

	// 添加积分条灰色背景
	auto processBar = Sprite::create("/image/gamescene/jetbraintheme/process_bar.png");
	processBar->setScale(1.5);
	processBar->setPosition(Point(225, 390));
	this->addChild(processBar, 1);

	const auto processBarScore = Sprite::create("/image/gamescene/jetbraintheme/process_bar_score.png");
	processBar->setScale(0.5);
	auto processTimer = ProgressTimer::create(processBarScore);
	processTimer->setPosition(Point(225, 390));
	processTimer->setType(ProgressTimer::Type::BAR);
	// 设置竖向变化
	processTimer->setBarChangeRate(Point(0, 1));
	processTimer->setMidpoint(Point(0, 0));
	processTimer->setPercentage(0);
	this->addChild(processTimer, 2);

	// 积分条测试动作
	const auto processAction = ProgressFromTo::create(5, 0, 100);
	const auto repeatAction = RepeatForever::create(processAction);
	processTimer->runAction(repeatAction);
	// 分数板
	auto scoreLabel = Label::createWithTTF("25", "/font/marker_felt.ttf", 32);
	scoreLabel->setPosition(225, 240);
	this->addChild(scoreLabel);

	// 默认初始提示剩余次数为3
	auto hint = 3;
	auto hintNumber = Sprite::createWithTexture(
		Director::getInstance()->getTextureCache()->addImage(
			"/image/gamescene/jetbraintheme/hint" + std::to_string(hint) + ".png"));
	hintNumber->setPosition(340, 520);
	this->addChild(hintNumber, 2);

	// 提示按钮
	auto hintButton = ui::Button::create("/image/gamescene/jetbraintheme/hint_button_normal.png",
	                                     "/image/gamescene/jetbraintheme/hint_button_selected.png",
	                                     "/image/gamescene/jetbraintheme/hint_button.png_disabled");
	hintButton->setPosition(Point(375, 540));
	hintButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			if (hint > 0)
			{
				hint--;
				// TODO:动态更新hintNumber图片
			}
		}
	});
	this->addChild(hintButton, 1);


#pragma endregion

	return true;
}
