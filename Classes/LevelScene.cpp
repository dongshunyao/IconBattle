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
	layer->setContentSize(Size(SCREEN_WIDTH*2, SCREEN_HEIGHT));

	// 设置页面滚动
	initScrollView();

	// 设置选关按钮的位置
	int xPos[10], yPos[10];
	for (int i = 0; i < 10; i++)
	{
		xPos[i] = i * 200 + 200;
		if ((i % 4 == 0) || (i % 3 == 0))
			yPos[i] = 350;
		else 
			yPos[i] = 600;
	}

	// 初始化选关按钮
	for (int i = 0; i < 10; i++)
		initButtons(xPos[i], yPos[i], i, i - 0.5);


	// 画连接按钮的线
	DrawNode* drawNode = DrawNode::create();
	layer->addChild(drawNode, 3);
	for (int i = 0; i < 9; i++)
		drawNode->drawSegment(Point(xPos[i], yPos[i]), Point(xPos[i + 1], yPos[i + 1]), 5, Color4F(1, 1, 1, 0.3));

	// 设置按钮
	new SettingButton(this);

	// 返回按钮
	this->addChild(BackButton::create());

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

	scrollView->addEventListener(CC_CALLBACK_2(LevelScene::scrollViewMoveCallback,this));
}

// 暂时未实现
void LevelScene::scrollViewMoveCallback(Ref* pSender, ui::ScrollView::EventType eventType)
{
	switch (eventType) {
	case ui::ScrollView::EventType::SCROLLING:
		break;
	case ui::ScrollView::EventType::SCROLL_TO_BOTTOM:
		break;
	case ui::ScrollView::EventType::SCROLL_TO_TOP:
		break;
	default:
		break;
	}
}

void LevelScene::initButtons(int x, int y, int level, float delayTime)
{
	auto levelButton = ui::Button::create(theme->levelSceneGameButtonNormal, theme->levelSceneGameButtonSelected,
	                                      theme->levelSceneGameButtonDisabled);

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
	case 6: levelButton->setTitleText("Level 7");
		break;
	case 7: levelButton->setTitleText("Level 8");
		break;
	case 8: levelButton->setTitleText("Level 9");
		break;
	case 9: levelButton->setTitleText("Level 10");
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
			case 6:
			case 7:
			case 8:
			case 9:
			default: break;
			}
		}
	});
	layer->addChild(levelButton);
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
