#include "StoreScene.h"

Scene* StoreScene::createScene()
{
	return StoreScene::create();
}

bool StoreScene::init()
{
	if (!Scene::init()) return false;

	// TODO 替换设置按钮
	auto settingButton = SettingButton::create();
	settingButton->setPosition(Point(1050, 850));
	this->addChild(settingButton);

	// 返回按钮
	this->addChild(BackButton::create());

	initCoins();
	initLabel();
	initThemeIcon();
	initButtons();

	return true;
}

void StoreScene::initCoins()
{
	auto coinIcon = Sprite::create(theme->storeSceneCoin);
	coinIcon->setPosition(Point(130, 850));
	this->addChild(coinIcon, -1);

	// TODO 待更改
	auto coinText = Label::createWithTTF("30", "font/marker_felt.ttf", 30);
	coinText->setPosition(Point(220, 850));
	this->addChild(coinText, -1);
}

void StoreScene::initLabel()
{
	auto label = Sprite::create(theme->storeSceneStoreLabel);
	label->setPosition(Point(600, 800));
	this->addChild(label, -1);
}

void StoreScene::initThemeIcon()
{
	auto jetBrainThemeIcon = Sprite::create(theme->storeSceneJetBrainThemeIcon);
	jetBrainThemeIcon->setPosition(Point(240, 450));
	this->addChild(jetBrainThemeIcon, -1);

	auto adobeThemeIcon = Sprite::create(theme->storeSceneAdobeThemeIcon);
	adobeThemeIcon->setPosition(Point(600, 450));
	this->addChild(adobeThemeIcon, -1);

	auto officeThemeIcon = Sprite::create(theme->storeSceneOfficeThemeIcon);
	officeThemeIcon->setPosition(Point(960, 450));
	this->addChild(officeThemeIcon, -1);
}

void StoreScene::initButtons()
{
	// TODO 选择按钮 已选择按钮 动态换按钮或图片
	auto choiceIcon = ui::Button::create(theme->storeSceneChoiceButtonNormal,
	                                     theme->storeSceneChoiceButtonSelected,
	                                     theme->storeSceneChoiceButtonDisabled);
	choiceIcon->addTouchEventListener([&, choiceIcon](Ref* sender, ui::Widget::TouchEventType type)
	{
		// TODO
	});
	choiceIcon->setPosition(Point(240, 120));
	this->addChild(choiceIcon);

	// Adobe按钮
	auto adobeCoinIcon = ui::Button::create(theme->storeSceneAdobeCoinsButtonNormal,
	                                        theme->storeSceneAdobeCoinsButtonSelected,
	                                        theme->storeSceneAdobeCoinsButtonDisabled);
	adobeCoinIcon->addTouchEventListener([&,adobeCoinIcon](Ref* sender, ui::Widget::TouchEventType type)
	{
		// TODO
	});
	adobeCoinIcon->setPosition(Point(600, 120));
	this->addChild(adobeCoinIcon);

	// Office按钮
	auto officeCoinIcon = ui::Button::create(theme->storeSceneOfficeCoinsButtonNormal,
	                                         theme->storeSceneOfficeCoinsButtonSelected,
	                                         theme->storeSceneOfficeCoinsButtonDisabled);
	officeCoinIcon->addTouchEventListener([&,officeCoinIcon](Ref* sender, ui::Widget::TouchEventType type)
	{
		// TODO
	});
	officeCoinIcon->setPosition(Point(960, 120));
	this->addChild(officeCoinIcon);
}
