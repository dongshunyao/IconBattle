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

	// 设置layer来存放各个按钮
	layer = Layer::create();
	layer->setContentSize(Size(SCREEN_WIDTH * 2, SCREEN_HEIGHT));

	// 设置页面滚动
	initScrollView();

	// 设置选关按钮的位置

#pragma region Level Button Location
	xPos[0] = 200;
	yPos[0] = 600;
	xPos[1] = 420;
	yPos[1] = 510;
	xPos[2] = 640;
	yPos[2] = 640;
	xPos[3] = 860;
	yPos[3] = 520;
	xPos[4] = 1080;
	yPos[4] = 600;
	xPos[5] = 1280;
	yPos[5] = 420;
	xPos[6] = 1500;
	yPos[6] = 270;
	xPos[7] = 1720;
	yPos[7] = 390;
	xPos[8] = 1940;
	yPos[8] = 470;
	xPos[9] = 2160;
	yPos[9] = 420;
	xPos[10] = 2160;
	yPos[10] = 420;


#pragma endregion

	// 初始化选关按钮
	initButtons();


	// 画连接按钮的线


	// 设置按钮
	auto settingButton = SettingButton::create();
	settingButton->setPosition(Point(1050, 850));
	this->addChild(settingButton, 4);

	// 返回按钮
	this->addChild(BackButton::create(), 4);

	return true;
}

void LevelScene::initBackground()
{
	// 第一张背景图 —— 星空
	backgroundFirst = Sprite::create(theme->levelSceneDistantView);
	backgroundFirst->setPosition(Vec2::ZERO);
	backgroundFirst->setAnchorPoint(Vec2::ZERO);
	this->addChild(backgroundFirst);

	backgroundSecond = Sprite::create(theme->levelSceneDistantView);
	backgroundSecond->setPosition(Vec2::ZERO);
	backgroundSecond->setAnchorPoint(Vec2(1, 0));
	this->addChild(backgroundSecond);

	// 第二张背景图 —— 前景的星星
	foregroundFirst = Sprite::create(theme->levelSceneForeground);
	foregroundFirst->setPosition(Vec2::ZERO);
	foregroundFirst->setAnchorPoint(Vec2::ZERO);
	this->addChild(foregroundFirst);

	foregroundSecond = Sprite::create(theme->levelSceneForeground);
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


void LevelScene::initScrollView()
{
	auto scrollView = ui::ScrollView::create();
	scrollView->setPosition(Point(0, 0));
	scrollView->setDirection(ui::ScrollView::Direction::HORIZONTAL);
	scrollView->setScrollBarEnabled(true);
	scrollView->setBounceEnabled(true);
	scrollView->setContentSize(Size(SCREEN_WIDTH, SCREEN_HEIGHT));
	scrollView->setInnerContainerSize(layer->getContentSize());
	scrollView->addChild(layer);
	addChild(scrollView, 3);

	// 暂时未实现
	scrollView->addEventListener([&](Ref* pSender, ui::ScrollView::EventType eventType)
	{
		switch (eventType)
		{
		case ui::ScrollView::EventType::SCROLLING:
			break;
		case ui::ScrollView::EventType::SCROLL_TO_BOTTOM:
			break;
		case ui::ScrollView::EventType::SCROLL_TO_TOP:
			break;
		default:
			break;
		}
	});
}

void LevelScene::initButtons()
{
	ui::Button* levelButton = nullptr;
	drawNode = DrawNode::create();
	layer->addChild(drawNode, 3);

	for (i = 0; i < 10; i++)
	{
		levelButton = ui::Button::create(theme->levelSelectButton + std::to_string(i + 1) + "_normal.png",
		                                 theme->levelSelectButton + std::to_string(i + 1) + "_selected.png",
		                                 theme->levelSelectButton + std::to_string(i + 1) + "_disabled.png");

		levelButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
		{
			if (type == ui::Widget::TouchEventType::ENDED)
			{
				
			// TODO 选关
	
			}
		});

		layer->addChild(levelButton, 4);
		levelButton->setPosition(Point(xPos[i], yPos[i]));
		levelButton->setOpacity(0); //设置透明度为0
		const auto fadeIn = FadeIn::create(1.3f); // 淡入的效果
		const auto delay = DelayTime::create(2*i);
		const auto sequence = Sequence::create(delay, fadeIn, CallFunc::create([&]()
		{
			if (i == 10)
			{
				drawNode->drawSegment(Point(xPos[count], yPos[count]), Point(xPos[count + 1], yPos[count + 1]), 5,
				                      Color4F(1, 1, 1, 0.3));
				count++;
			}
		}), nullptr); // 动作序列

		levelButton->runAction(sequence);
	}
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
