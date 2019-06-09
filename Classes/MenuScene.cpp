#include "MenuScene.h"

Scene* MenuScene::createScene()
{
	return MenuScene::create();
}

bool MenuScene::init()
{
	if (!Scene::init()) return false;

	// 添加背景图片
	auto sprite = Sprite::create(theme->menuSceneBackground);
	sprite->setPosition(Point(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
	this->addChild(sprite);

	initUsername();
	// TODO 调整上方位置按钮
	initStoreButton();
	initRankButton();
	initGameButton();
	initPlate();
	if(Theme::getInstance()->getCurrentThemeName() == "AdobeTheme")
	initPainter();

	// 初始化金币
	initCoin();

	// 设置按钮
	auto settingButton = SettingButton::create();
	settingButton->setPosition(Point(1150, 850));
	this->addChild(settingButton);

	// 滚动公告
	const auto news = NewsBoard::create();
	this->addChild(news);

	if (User::getInstance()->isNewUser())
	{
		// TODO 新手显示教程
	}
	return true;
}

void MenuScene::initUsername()
{
	auto userIcon = Sprite::create(theme->menuSceneUserIcon);
	userIcon->setPosition(Point(60, 850));
	this->addChild(userIcon);

	auto userText = ui::TextField::create("", theme->semiBoldFont, 30);

	auto editIcon = ui::Button::create(theme->menuSceneEditIcon,
	                                   theme->menuSceneEditIcon,
	                                   theme->menuSceneEditIcon);

	// 动态确定用户名位置
	userText->setString(User::getInstance()->getUserName());
	userText->setMaxLengthEnabled(true);
	userText->setMaxLength(7);
	userText->setCursorEnabled(true);
	userText->addEventListener([&, userText, editIcon](Ref* sender, ui::TextField::EventType type)
	{
		static string temp;

		userText->setPosition(Point(userText->getContentSize().width / 2 + 100, 850));
		editIcon->setPosition(Point(userText->getPosition().x + userText->getContentSize().width / 2 + 30, 850));

		if (type == ui::TextField::EventType::ATTACH_WITH_IME)
		{
			temp = userText->getString();
			userText->setString("");
		}

		if (type == ui::TextField::EventType::DETACH_WITH_IME)
		{
			if (userText->getString().empty()) userText->setString(temp);
			else User::getInstance()->setUserName(userText->getString());
		}

		userText->setPosition(Point(userText->getContentSize().width / 2 + 100, 850));
		editIcon->setPosition(Point(userText->getPosition().x + userText->getContentSize().width / 2 + 30, 850));
	});
	userText->setPosition(Point(userText->getContentSize().width / 2 + 100, 850));
	this->addChild(userText);

	editIcon->setPosition(Point(userText->getPosition().x + userText->getContentSize().width / 2 + 30, 850));
	editIcon->addClickEventListener([&, userText](Ref* sender) { userText->attachWithIME(); });
	this->addChild(editIcon);
}

void MenuScene::initStoreButton()
{
	auto storeButton = ui::Button::create(theme->menuSceneStoreButtonNormal,
	                                      theme->menuSceneStoreButtonSelected,
	                                      theme->menuSceneStoreButtonDisabled);
	storeButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		// 进入商店界面
		if (type == ui::Widget::TouchEventType::ENDED)
			Director::getInstance()->pushScene(
				TransitionSlideInT::create(1.0f, StoreScene::createScene()));
	});
	storeButton->setPosition(Point(680, 850));
	this->addChild(storeButton);
}

void MenuScene::initRankButton()
{
	auto rankButton = ui::Button::create(theme->menuSceneRankButtonNormal,
	                                     theme->menuSceneRankButtonSelected,
	                                     theme->menuSceneRankButtonDisabled);
	rankButton->addTouchEventListener([&, rankButton](Ref* sender, ui::Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			const auto dialog = Dialog::create(theme->menuSceneRankListBackground, Size(500, 600));

			dialog->addListView(true, true, true);
			dialog->setTitle("经典挑战排行", 50);
			dialog->addButton(MenuItemSprite::create(Sprite::create(theme->gameSceneYesButtonNormal),
			                                         Sprite::create(theme->gameSceneYesButtonSelected),
			                                         Sprite::create(theme->gameSceneYesButtonNormal),
			                                         [&, dialog, rankButton](Ref* sender)
			                                         {
				                                         Director::getInstance()
					                                         ->getRunningScene()->removeChild(dialog);
			                                         }
			));
			this->addChild(dialog, 20);
		}
	});
	rankButton->setPosition(Point(750, 850));
	this->addChild(rankButton);
}

void MenuScene::initCoin()
{
	auto coinIcon = Sprite::create(theme->storeSceneCoin);
	coinIcon->setPosition(Point(550, 850));
	this->addChild(coinIcon, 4);

	coinText = Label::createWithTTF(to_string(user->getCoin()), theme->markerFeltFont, 30);
	coinText->setPosition(Point(620, 850));
	this->addChild(coinText);
}

void MenuScene::initGameButton()
{
	// 经典练习
	classicPractice = ui::Button::create(theme->menuScenePracticeButtonNormal,
	                                     theme->menuScenePracticeButtonSelected,
	                                     theme->menuScenePracticeButtonDisabled);
	classicPractice->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		if (type == ui::Widget::TouchEventType::ENDED) GameSceneController::getInstance()->startPracticeGame(true);
	});
	classicPractice->setPosition(Vec2(105, 40));

	// 经典闯关
	classicLevel = ui::Button::create(theme->menuSceneLevelButtonNormal,
	                                  theme->menuSceneLevelButtonSelected,
	                                  theme->menuSceneLevelButtonDisabled);
	classicLevel->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		if (type == ui::Widget::TouchEventType::ENDED)
			Director::getInstance()->replaceScene(TransitionFade::create(1.0f, LevelScene::createScene(true)));
	});
	classicLevel->setPosition(Vec2(275, 40));

	// 经典挑战
	classicChallenge = ui::Button::create(theme->menuSceneChallengeButtonNormal,
	                                      theme->menuSceneChallengeButtonSelected,
	                                      theme->menuSceneChallengeButtonDisabled);
	classicChallenge->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			if (User::getInstance()->getUnlockedClassicalLevel() != 10)
			{
				// TODO 弹出对话框
				// "完成经典闯关模式后再来挑战吧!";
			}
			else GameSceneController::getInstance()->startChallengeGame(true);
		}
	});
	classicChallenge->setPosition(Vec2(445, 40));

	// 加强练习
	enhancedPractice = ui::Button::create(theme->menuScenePracticeButtonNormal,
	                                      theme->menuScenePracticeButtonSelected,
	                                      theme->menuScenePracticeButtonDisabled);
	enhancedPractice->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		if (type == ui::Widget::TouchEventType::ENDED)
			GameSceneController::getInstance()->startPracticeGame(false);
	});
	enhancedPractice->setPosition(Vec2(105, 40));

	// 加强闯关
	enhancedLevel = ui::Button::create(theme->menuSceneLevelButtonNormal,
	                                   theme->menuSceneLevelButtonSelected,
	                                   theme->menuSceneLevelButtonDisabled);
	enhancedLevel->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		if (type == ui::Widget::TouchEventType::ENDED)
			Director::getInstance()->replaceScene(TransitionFade::create(1.0f, LevelScene::createScene(false)));
	});
	enhancedLevel->setPosition(Vec2(275, 40));

	// 加强挑战
	enhancedChallenge = ui::Button::create(theme->menuSceneChallengeButtonNormal,
	                                       theme->menuSceneChallengeButtonSelected,
	                                       theme->menuSceneChallengeButtonDisabled);
	enhancedChallenge->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			if (User::getInstance()->getUnlockedPlusLevel() != 10)
			{
				// TODO 弹出对话框
				// "完成进阶闯关模式后再来挑战吧!";
			}
			else GameSceneController::getInstance()->startChallengeGame(false);
		}
	});
	enhancedChallenge->setPosition(Vec2(445, 40));
}

void MenuScene::initPlate()
{
	//经典模式
	auto classicPlate = Sprite::create(theme->menuSceneClassicPlate);
	classicPlate->setPosition(Point(800, 600));
	addChild(classicPlate);

	auto classicLabel = Sprite::create(theme->menuSceneClassicLabel);
	classicLabel->setPosition(Vec2(275, 125));

	classicListView = ListView::create();
	classicListView->setDirection(ScrollView::Direction::VERTICAL);
	classicListView->setBounceEnabled(true);
	classicListView->setBackGroundImageScale9Enabled(true);
	classicListView->setAnchorPoint(Point(0.5f, 0.5f));
	classicListView->setContentSize(Size(550, 250));
	classicListView->setPosition(Point(800, 600));
	classicListView->setScrollBarEnabled(false);

	auto classicLabelLayout = Layout::create();
	classicLabelLayout->setContentSize(Size(550, 250));
	classicLabelLayout->addChild(classicLabel);

	auto classicButtonsLayout = Layout::create();
	classicButtonsLayout->setContentSize(Size(550, 80));
	classicButtonsLayout->addChild(classicPractice);
	classicButtonsLayout->addChild(classicLevel);
	classicButtonsLayout->addChild(classicChallenge);

	classicListView->pushBackCustomItem(classicLabelLayout);
	classicListView->pushBackCustomItem(classicButtonsLayout);

	//加强模式
	auto enhancedPlate = Sprite::create(theme->menuSceneEnhancedPlate);
	enhancedPlate->setPosition(Point(800, 280));
	addChild(enhancedPlate);

	auto enhancedLabel = Sprite::create(theme->menuSceneEnhancedLabel);
	enhancedLabel->setPosition(Vec2(275, 125));

	enhancedListView = ListView::create();
	enhancedListView->setDirection(ScrollView::Direction::VERTICAL);
	enhancedListView->setBounceEnabled(true);
	enhancedListView->setBackGroundImageScale9Enabled(true);
	enhancedListView->setAnchorPoint(Point(0.5f, 0.5f));
	enhancedListView->setContentSize(Size(550, 250));
	enhancedListView->setPosition(Point(800, 280));
	enhancedListView->setScrollBarEnabled(false);

	auto enhancedLabelLayout = Layout::create();
	enhancedLabelLayout->setContentSize(Size(550, 250));
	enhancedLabelLayout->addChild(enhancedLabel);

	auto enhancedButtonsLayout = Layout::create();
	enhancedButtonsLayout->setContentSize(Size(550, 80));
	enhancedButtonsLayout->addChild(enhancedPractice);
	enhancedButtonsLayout->addChild(enhancedLevel);
	enhancedButtonsLayout->addChild(enhancedChallenge);

	enhancedListView->pushBackCustomItem(enhancedLabelLayout);
	enhancedListView->pushBackCustomItem(enhancedButtonsLayout);

	//添加鼠标事件侦听
	auto listenerMouse = EventListenerMouse::create();
	listenerMouse->setEnabled(true);
	listenerMouse->onMouseMove = [&](EventMouse* event)
	{
		EventMouse* e = (EventMouse*)event;

		if (!classicMoveOut && e->getCursorX() > 600 && e->getCursorX() < 1100 && e->getCursorY() > 450 && e->
			getCursorY() < 750)
		{
			classicListView->scrollToPercentVertical(100, 0.5, true);
			classicMoveOut = true;
		}
		if (!enhancedMoveOut && e->getCursorX() > 600 && e->getCursorX() < 1100 && e->getCursorY() > 100 && e->
			getCursorY() < 400)
		{
			enhancedListView->scrollToPercentVertical(100, 0.5, true);
			enhancedMoveOut = true;
		}
		if (classicMoveOut && (e->getCursorX() < 600 || e->getCursorX() > 1100 || e->getCursorY() < 450 || e->
			getCursorY() > 750))
		{
			classicListView->scrollToPercentVertical(0, 0.5, true);
			classicMoveOut = false;
		}
		if (enhancedMoveOut && (e->getCursorX() < 600 || e->getCursorX() > 1100 || e->getCursorY() < 100 || e->
			getCursorY() > 400))
		{
			enhancedListView->scrollToPercentVertical(0, 0.5, true);
			enhancedMoveOut = false;
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerMouse, this);

	addChild(classicListView);
	addChild(enhancedListView);
}

void MenuScene::initPainter()
{
	do
	{

		streakSprite = Sprite::create("/image/menuscene/adobetheme/star.png");
		this->addChild(streakSprite);

		//开启多点触摸    
		auto listener = EventListenerTouchAllAtOnce::create();
		listener->onTouchesBegan = CC_CALLBACK_2(MenuScene::onTouchesBegan, this);
		listener->onTouchesMoved = CC_CALLBACK_2(MenuScene::onTouchesMoved, this);
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
		streak = MotionStreak::create(5, 3, 32, Color3B::WHITE, "/image/menuscene/adobetheme/color_action.png");
		this->addChild(streak,22);
	}
	while (false);
}

void MenuScene::onTouchesBegan(const std::vector<Touch *>& touches, cocos2d::Event* event) const
{
	// 获取触摸点位置

	const auto pos = touches[0]->getLocation();


	// 设置位置

	streakSprite->setPosition(pos);

	streak->setPosition(streakSprite->getPosition());


	// 删除所有活动条带段

	streak->reset();
}

// 触摸移动 ：移动star和streak的位置

void MenuScene::onTouchesMoved(const std::vector<Touch *>& touches, cocos2d::Event* event) const

{
	//根据触摸位置，画线

	const auto touchLocation = touches[0]->getLocation();

	if (touchLocation.x < 450 && touchLocation.y > 100 && touchLocation.y < 800)
		streak->setPosition(touchLocation);
}
