#include "LevelScene.h"

Scene* LevelScene::createScene()
{
	return LevelScene::create();
}

bool LevelScene::init()
{
	if (!Scene::init()) return false;

	// 背景设置
	initBackground();

	// 用户名设置
	initUsername();

	// 设置选关按钮的位置
	int xPos[6], yPos[6];
	for (int i = 0; i < 6; i++)
	{
		xPos[i] = i * 150 + 200;
		if (i % 2 == 0)
			yPos[i] = 300;
		else
			yPos[i] = 600;
	}

	// 初始化选关按钮
	for (int i = 0; i < 6; i++)
		initButtons(xPos[i], yPos[i], i, i - 0.4);

	// 画连接按钮的线
	DrawNode* drawNode = DrawNode::create();
	addChild(drawNode, 3);
	for (int i = 0; i < 5; i++)
		drawNode->drawSegment(Point(xPos[i], yPos[i]), Point(xPos[i + 1], yPos[i + 1]), 5, Color4F(1, 1, 1, 0.3));

	// 设置按钮
	this->addChild(SettingButton::create());

	// 返回按钮
	this->addChild(BackButton::create());

	return true;
}

void LevelScene::initBackground()
{
	// 第一张背景图 —— 星空
	backgroundFirst = Sprite::create("/image/levelscene/jetbraintheme/far.png");
	backgroundFirst->setPosition(Vec2::ZERO);
	backgroundFirst->setAnchorPoint(Vec2::ZERO);
	this->addChild(backgroundFirst);

	backgroundSecond = Sprite::create("/image/levelscene/jetbraintheme/far.png");
	backgroundSecond->setPosition(Vec2::ZERO);
	backgroundSecond->setAnchorPoint(Vec2(1, 0));
	this->addChild(backgroundSecond);

	// 第二张背景图 —— 前景的星星
	foregroundFirst = Sprite::create("/image/levelscene/jetbraintheme/front.png");
	foregroundFirst->setPosition(Vec2::ZERO);
	foregroundFirst->setAnchorPoint(Vec2::ZERO);
	this->addChild(foregroundFirst);

	foregroundSecond = Sprite::create("/image/levelscene/jetbraintheme/front.png");
	foregroundSecond->setPosition(Vec2::ZERO);
	foregroundSecond->setAnchorPoint(Vec2(1, 0));
	this->addChild(foregroundSecond);

	scheduleUpdate();

	// // 视差滚动
	// // ParallaxNode * parallaxNode = ParallaxNode::create();
	// // addChild(parallaxNode, 0);
	//
	// // //近景
	// // parallaxNode->addChild(spFront, 3, Vec2(4.8f, 0), Vec2(spFront->getContentSize().width*0.5, spFront->getContentSize().height*0.5));
	// // //中景
	// // parallaxNode->addChild(spMiddle, 2, Vec2(1.6f, 0), Vec2(spMiddle->getContentSize().width*0.5, spMiddle->getContentSize().height*0.5 + spFront->getContentSize().height*0.5));
	// // //远景
	// // parallaxNode->addChild(spFar, 1, Vec2(0.5f, 0), Vec2(spFar->getContentSize().width*0.5, spFar->getContentSize().height*0.5 + spFront->getContentSize().height*0.5 + spMiddle->getContentSize().height*0.5));
	//
	// // 创建动作序列
	// ActionInterval* go = MoveBy::create(8, Vec2(-100, 0));
	// ActionInterval* goBack = go->reverse();
	// Action* seq = Sequence::create(go, goBack, NULL);
	//
	// //parallaxNode->runAction((RepeatForever::create(dynamic_cast<ActionInterval*>(seq))));
}

void LevelScene::initUsername()
{
	auto usernameLabel = Label::createWithTTF("USERNAME:", "/font/marker_felt.ttf", 24);
	usernameLabel->setColor(Color3B(255, 255, 255));
	usernameLabel->setPosition(Point(100, 850));
	this->addChild(usernameLabel);

	// TODO 获取 设置用户名
	auto usernameText = ui::TextField::create("TQTQL", "/font/marker_felt.ttf", 30);
	usernameText->setPasswordEnabled(true);
	usernameText->setColor(Color3B(255, 255, 255));
	usernameText->setMaxLength(10);

	usernameText->addClickEventListener([&](Ref* sender)
	{
		// TODO 修改用户名
	});
	usernameText->setPosition(Point(250, 850));
	this->addChild(usernameText);
}

void LevelScene::initButtons(int x, int y, int level, float delayTime)
{
	auto levelButton = ui::Button::create("/image/levelscene/jetbraintheme/game_normal.png",
	                                      "/image/levelscene/jetbraintheme/game_selected.png",
	                                      "/image/levelscene/jetbraintheme/game_disabled.png");

	switch (level)
	{
	case 0: levelButton->setTitleText("Level 1");
		break;
	case 1: levelButton->setTitleText("Level 2");
		break;
	case 2: levelButton->setTitleText("Level 3");
		break;
	case 3: levelButton->setTitleText("Level 4");
		break;
	case 4: levelButton->setTitleText("Level 5");
		break;
	case 5: levelButton->setTitleText("Level 6");
		break;
	default: break;
	}

	levelButton->setTitleFontName("/font/marker_felt.ttf");
	levelButton->setTitleFontSize(30);
	levelButton->setTitleColor(Color3B(0, 0, 0));
	levelButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			switch (level)
			{
				// TODO 选关
			case 0:
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
			default: break;
			}
		}
	});
	addChild(levelButton, 4);
	levelButton->setPosition(Point(x, y));
	levelButton->setOpacity(0); //设置透明度为0
	const auto fadeIn = FadeIn::create(1.3f); // 淡入的效果
	const auto delay = DelayTime::create(delayTime);
	const auto sequence = Sequence::create(delay, fadeIn, nullptr); // 动作序列
	levelButton->runAction(sequence);
}

void LevelScene::update(float delta)
{
	backgroundFirst->setPositionX(backgroundFirst->getPositionX() + 1);
	backgroundSecond->setPositionX(backgroundSecond->getPositionX() + 1);

	foregroundFirst->setPositionX(backgroundFirst->getPositionX() + 1);
	foregroundSecond->setPositionX(backgroundSecond->getPositionX() + 1);

	if (backgroundFirst->getPositionX() >= SCREEN_WIDTH)
	{
		backgroundFirst->setPositionX(0);
		backgroundSecond->setPositionX(0);
	}

	if (foregroundFirst->getPositionX() >= SCREEN_WIDTH)
	{
		foregroundFirst->setPositionX(0);
		foregroundSecond->setPositionX(0);
	}
}
