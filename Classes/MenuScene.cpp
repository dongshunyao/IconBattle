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

	// 添加背景图片
	auto sprite = Sprite::create("/images/menuScene/jetBrainTheme/backgroud.jpg");
	sprite->setPosition(Point(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
	this->addChild(sprite);

	// 用户名
	auto myLabel = Label::createWithTTF("USERNAME:", "/fonts/Marker Felt.ttf", 24);
	myLabel->setColor(Color3B(255, 255, 255));
	myLabel->setPosition(Point(100, 850));
	this->addChild(myLabel);

	auto textField = ui::TextField::create("TQTQL", "/fonts/Marker Felt.ttf", 30);
	textField->setPasswordEnabled(true);
	textField->setColor(Color3B(255, 255, 255));
	textField->setMaxLength(10);

	textField->addClickEventListener([&](Ref* sender) {
		// TODO 修改用户名
	});
	textField->setPosition(Point(250, 850));
	this->addChild(textField);


	// 商店按钮
	auto shopButton = ui::Button::create("/images/menuScene/jetBrainTheme/shop_normal_image.png", "/images/menuScene/jetBrainTheme/shop_selected_image.png", "/images/menuScene/jetBrainTheme/shop_disabled_image.png");
	shopButton->setTitleText("SHOP");
	shopButton->setTitleFontName("/fonts/Marker Felt.ttf");
	shopButton->setTitleFontSize(25);
	shopButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		// 进入商店界面
		if (type == ui::Widget::TouchEventType::ENDED)
			Director::getInstance()->pushScene(StoreScene::createScene());
	});
	shopButton->setPosition(Point(650, 850));
	this->addChild(shopButton);

	// 排名按钮
	auto rankButton = ui::Button::create("/images/menuScene/jetBrainTheme/rank_normal_image.png", "/images/menuScene/jetBrainTheme/rank_selected_image.png", "/images/menuScene/jetBrainTheme/rank_disabled_image.png");
	rankButton->setTitleText("RANK");
	rankButton->setTitleFontName("/fonts/Marker Felt.ttf");
	rankButton->setTitleFontSize(25);
	rankButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		// TODO 排名相关
	});
	rankButton->setPosition(Point(850, 850));
	this->addChild(rankButton);


	// 设置按钮
	auto settingButton = ui::Button::create("/images/menuScene/jetBrainTheme/setting_normal_image.png", "/images/menuScene/jetBrainTheme/setting_selected_image.png", "/images/menuScene/jetBrainTheme/setting_disabled_image.png");
	settingButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		// TODO 设置相关
	});
	settingButton->setPosition(Point(1050, 850));
	this->addChild(settingButton);

	// 返回按钮
	auto backButton = ui::Button::create("/images/menuScene/jetBrainTheme/back_normal_image.png", "/images/menuScene/jetBrainTheme/back_selected_image.png", "/images/menuScene/jetBrainTheme/back_disabled_image.png");
	backButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		// TODO 返回相关
	});
	backButton->setPosition(Point(1150, 850));
	this->addChild(backButton);

	// 选关按钮1
	auto gameButton1 = ui::Button::create("/images/menuScene/jetBrainTheme/game_normal_image.png", "/images/menuScene/jetBrainTheme/game_selected_image.png", "/images/menuScene/jetBrainTheme/game_disabled_image.png");
	gameButton1->setTitleText("Practice-1");
	gameButton1->setTitleFontName("/fonts/Marker Felt.ttf");
	gameButton1->setTitleFontSize(35);
	gameButton1->setTitleColor(Color3B(0, 0, 0));
	gameButton1->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		// TODO 选关按钮1
	});
	gameButton1->setPosition(Point(650, 600));
	this->addChild(gameButton1);

	// 选关按钮2
	auto gameButton2 = ui::Button::create("/images/menuScene/jetBrainTheme/game_normal_image.png", "/images/menuScene/jetBrainTheme/game_selected_image.png", "/images/menuScene/jetBrainTheme/game_disabled_image.png");
	gameButton2->setTitleText("Level-1");
	gameButton2->setTitleFontName("/fonts/Marker Felt.ttf");
	gameButton2->setTitleFontSize(35);
	gameButton2->setTitleColor(Color3B(0, 0, 0));
	gameButton2->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		// TODO 选关按钮2
	});
	gameButton2->setPosition(Point(850, 600));
	this->addChild(gameButton2);

	// 选关按钮3
	auto gameButton3 = ui::Button::create("/images/menuScene/jetBrainTheme/game_normal_image.png", "/images/menuScene/jetBrainTheme/game_selected_image.png", "/images/menuScene/jetBrainTheme/game_disabled_image.png");
	gameButton3->setTitleText("Infinity-1");
	gameButton3->setTitleFontName("/fonts/Marker Felt.ttf");
	gameButton3->setTitleFontSize(35);
	gameButton3->setTitleColor(Color3B(0, 0, 0));
	gameButton3->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		// TODO 选关按钮3
	});
	gameButton3->setPosition(Point(1050, 600));
	this->addChild(gameButton3);

	// 选关按钮4
	auto gameButton4 = ui::Button::create("/images/menuScene/jetBrainTheme/game_normal_image.png", "/images/menuScene/jetBrainTheme/game_selected_image.png", "/images/menuScene/jetBrainTheme/game_disabled_image.png");
	gameButton4->setTitleText("Practice-2");
	gameButton4->setTitleFontName("/fonts/Marker Felt.ttf");
	gameButton4->setTitleFontSize(35);
	gameButton4->setTitleColor(Color3B(0, 0, 0)); 
	gameButton4->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		// TODO 选关按钮4
	});
	gameButton4->setPosition(Point(650, 350));
	this->addChild(gameButton4);

	// 选关按钮5
	auto gameButton5 = ui::Button::create("/images/menuScene/jetBrainTheme/game_normal_image.png", "/images/menuScene/jetBrainTheme/game_selected_image.png", "/images/menuScene/jetBrainTheme/game_disabled_image.png");
	gameButton5->setTitleText("Level-2");
	gameButton5->setTitleFontName("/fonts/Marker Felt.ttf");
	gameButton5->setTitleFontSize(35);
	gameButton5->setTitleColor(Color3B(0, 0, 0)); 
	gameButton5->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		// TODO 选关按钮5
	});
	gameButton5->setPosition(Point(850, 350));
	this->addChild(gameButton5);

	// 选关按钮6
	auto gameButton6 = ui::Button::create("/images/menuScene/jetBrainTheme/game_normal_image.png", "/images/menuScene/jetBrainTheme/game_selected_image.png", "/images/menuScene/jetBrainTheme/game_disabled_image.png");
	gameButton6->setTitleText("Infinity-2");
	gameButton6->setTitleFontName("/fonts/Marker Felt.ttf");
	gameButton6->setTitleFontSize(35);
	gameButton6->setTitleColor(Color3B(0, 0, 0)); 
	gameButton6->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		// TODO 选关按钮6
	});
	gameButton6->setPosition(Point(1050, 350));
	this->addChild(gameButton6);


	// 公告栏
	auto board = Label::createWithTTF("NOTICE", "/fonts/Marker Felt.ttf", 24);
	board->setColor(Color3B(255, 255, 255));
	board->setPosition(Point(80, 55));
	this->addChild(board);

	// 滚动公告
	PannelNews *news = PannelNews::create();
	this->addChild(news);

	return true;
}
