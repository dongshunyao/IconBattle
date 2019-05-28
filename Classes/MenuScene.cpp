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
	initStoreButton();
	initRankButton();
	initGameButton();

	// 设置按钮
	new SettingButton(this);

	// 滚动公告
	const auto news = NewsBoard::create();
	this->addChild(news);

	return true;
}

void MenuScene::initUsername()
{
	auto userIcon = Sprite::create(theme->menuSceneUserIcon);
	userIcon->setPosition(Point(60, 850));
	this->addChild(userIcon);

	auto editIcon = ui::Button::create(theme->menuSceneEditIcon,
									theme->menuSceneEditIcon,
									theme->menuSceneEditIcon);
	editIcon->setPosition(Point(300, 850));
	editIcon->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			//TODO 修改用户名
		}
	});
	this->addChild(editIcon);

	auto usernameText = ui::TextField::create(User::getInstance()->getUserName(), "/font/marker_felt.ttf", 30);
	usernameText->setPasswordEnabled(true);
	usernameText->setColor(Color3B(255, 255, 255));
	usernameText->setMaxLength(10);

	usernameText->addClickEventListener([&](Ref* sender)
	{
		// TODO 修改用户名+加个图标
	});
	usernameText->setPosition(Point(180, 850));
	this->addChild(usernameText);
}

void MenuScene::initStoreButton()
{
	auto storeButton = ui::Button::create(theme->menuSceneStoreButtonNormal,
	                                      theme->menuSceneStoreButtonSelected,
	                                      theme->menuSceneStoreButtonDisabled);
	storeButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		// 进入商店界面
		if (type == ui::Widget::TouchEventType::ENDED) Director::getInstance()->pushScene(StoreScene::createScene());
	});
	storeButton->setPosition(Point(550, 850));
	this->addChild(storeButton);
}

void MenuScene::initRankButton()
{
	auto rankButton = ui::Button::create(theme->menuSceneRankButtonNormal,
	                                     theme->menuSceneRankButtonSelected,
	                                     theme->menuSceneRankButtonDisabled);
	rankButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		// TODO 排名相关
	});
	rankButton->setPosition(Point(750, 850));
	this->addChild(rankButton);
}

void MenuScene::initGameButton()
{
	// 选关按钮1
	auto gameButton1 = ui::Button::create(theme->menuSceneGameButtonNormal,
	                                      theme->menuSceneGameButtonSelected,
	                                      theme->menuSceneGameButtonDisabled);
	gameButton1->setTitleText("Practice-1");
	gameButton1->setTitleFontName("/font/marker_felt.ttf");
	gameButton1->setTitleFontSize(35);
	gameButton1->setTitleColor(Color3B(0, 0, 0));
	gameButton1->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		// TODO 选关按钮1
		if (type == ui::Widget::TouchEventType::ENDED) Director::getInstance()->pushScene(GameScene::createScene());
	});
	gameButton1->setPosition(Point(650, 600));

	this->addChild(gameButton1);

	// 选关按钮2
	auto gameButton2 = ui::Button::create(theme->menuSceneGameButtonNormal,
	                                      theme->menuSceneGameButtonSelected,
	                                      theme->menuSceneGameButtonDisabled);
	gameButton2->setTitleText("Level-1");
	gameButton2->setTitleFontName("/font/marker_felt.ttf");
	gameButton2->setTitleFontSize(35);
	gameButton2->setTitleColor(Color3B(0, 0, 0));
	gameButton2->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		// TODO 选关按钮2
		if (type == ui::Widget::TouchEventType::ENDED) Director::getInstance()->pushScene(LevelScene::createScene());
	});
	gameButton2->setPosition(Point(850, 600));
	this->addChild(gameButton2);

	// 选关按钮3
	auto gameButton3 = ui::Button::create(theme->menuSceneGameButtonNormal,
	                                      theme->menuSceneGameButtonSelected,
	                                      theme->menuSceneGameButtonDisabled);
	gameButton3->setTitleText("Infinity-1");
	gameButton3->setTitleFontName("/font/marker_felt.ttf");
	gameButton3->setTitleFontSize(35);
	gameButton3->setTitleColor(Color3B(0, 0, 0));
	gameButton3->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		// TODO 选关按钮3
	});
	gameButton3->setPosition(Point(1050, 600));
	this->addChild(gameButton3);

	// 选关按钮4
	auto gameButton4 = ui::Button::create(theme->menuSceneGameButtonNormal,
	                                      theme->menuSceneGameButtonSelected,
	                                      theme->menuSceneGameButtonDisabled);
	gameButton4->setTitleText("Practice-2");
	gameButton4->setTitleFontName("/font/marker_felt.ttf");
	gameButton4->setTitleFontSize(35);
	gameButton4->setTitleColor(Color3B(0, 0, 0));
	gameButton4->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		// TODO 选关按钮4
	});
	gameButton4->setPosition(Point(650, 350));
	this->addChild(gameButton4);

	// 选关按钮5
	auto gameButton5 = ui::Button::create(theme->menuSceneGameButtonNormal,
	                                      theme->menuSceneGameButtonSelected,
	                                      theme->menuSceneGameButtonDisabled);
	gameButton5->setTitleText("Level-2");
	gameButton5->setTitleFontName("/font/marker_felt.ttf");
	gameButton5->setTitleFontSize(35);
	gameButton5->setTitleColor(Color3B(0, 0, 0));
	gameButton5->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		// TODO 选关按钮5
	});
	gameButton5->setPosition(Point(850, 350));
	this->addChild(gameButton5);

	// 选关按钮6
	auto gameButton6 = ui::Button::create(theme->menuSceneGameButtonNormal,
	                                      theme->menuSceneGameButtonSelected,
	                                      theme->menuSceneGameButtonDisabled);
	gameButton6->setTitleText("Infinity-1");
	gameButton6->setTitleFontName("/font/marker_felt.ttf");
	gameButton6->setTitleFontSize(35);
	gameButton6->setTitleColor(Color3B(0, 0, 0));
	gameButton6->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		// TODO 选关按钮6
	});
	gameButton6->setPosition(Point(1050, 350));
	this->addChild(gameButton6);
}
