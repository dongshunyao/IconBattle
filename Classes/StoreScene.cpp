#include "StoreScene.h"

Scene* StoreScene::createScene()
{
	return StoreScene::create();
}

bool StoreScene::init()
{
	if (!Scene::init()) return false;

	// 设置按钮
	auto settingButton = SettingButton::create();
	settingButton->setPosition(Point(1050, 850));
	this->addChild(settingButton, 2);

	// 返回按钮
	auto* backButton = Button::create(theme->backButtonNormal, theme->backButtonSelected,
	                                  theme->backButtonDisabled);

	backButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		//返回到上一个场景
		if (type == ui::Widget::TouchEventType::ENDED) Director::getInstance()->replaceScene(
			TransitionSlideInB::create(1.0f, MenuScene::create()));
	});
	backButton->setPosition(Point(1150, 850));
	this->addChild(backButton, 2);

	// 背景图
	auto background = Sprite::create(theme->storeSceneBackground);
	background->setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	this->addChild(background);

	// 标题
	auto label = Sprite::create(theme->storeSceneStoreLabel);
	label->setPosition(Point(600, 830));
	this->addChild(label);

	// 硬币显示
	initCoin();

	// 主题大图
	initThemeIcon();

	initButton();

	return true;
}

void StoreScene::initCoin()
{
	auto coinIcon = Sprite::create(theme->storeSceneCoin);
	coinIcon->setPosition(Point(130, 850));
	this->addChild(coinIcon);

	coinText = Label::createWithTTF(to_string(user->getCoin()), theme->markerFeltFont, 30);
	coinText->setPosition(Point(220, 850));
	this->addChild(coinText);
}

void StoreScene::initThemeIcon()
{
	auto jetBrainThemeIcon = Sprite::create(theme->storeSceneJetBrainThemeIcon);
	jetBrainThemeIcon->setPosition(Point(240, 500));
	this->addChild(jetBrainThemeIcon);

	auto adobeThemeIcon = Sprite::create(theme->storeSceneAdobeThemeIcon);
	adobeThemeIcon->setPosition(Point(600, 500));
	this->addChild(adobeThemeIcon);

	auto officeThemeIcon = Sprite::create(theme->storeSceneOfficeThemeIcon);
	officeThemeIcon->setPosition(Point(960, 500));
	this->addChild(officeThemeIcon);
}

void StoreScene::initButton()
{
	// jetBrain 默认已经有了
	jetBrainSelectButton = createSelectButton();
	jetBrainSelectButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			updateCurrentTheme(theme->jetBrainThemeName);
			Director::getInstance()->replaceScene(StoreScene::createScene());
			Music::getInstance()->change(theme->backgroundMusic);
		}
	});
	jetBrainSelectButton->setPosition(Point(240, 150));
	this->addChild(jetBrainSelectButton);


	for (const auto& it : user->getUnlockedThemes())
	{
		if (it == theme->adobeThemeName) createAdobeButton(true);
		else if (it == theme->officeThemeName) createOfficeButtons(true);
	}
	if (adobeSelectButton == nullptr) createAdobeButton(false);
	if (officeSelectButton == nullptr) createOfficeButtons(false);

	updateCurrentTheme(theme->getCurrentThemeName());
}

void StoreScene::updateCurrentTheme(const string& themeName) const
{
	if (jetBrainSelectButton != nullptr) jetBrainSelectButton->setEnabled(true);
	if (adobeSelectButton != nullptr) adobeSelectButton->setEnabled(true);
	if (officeSelectButton != nullptr) officeSelectButton->setEnabled(true);

	if (themeName == theme->jetBrainThemeName)
	{
		jetBrainSelectButton->setEnabled(false);
		theme->setCurrentTheme(theme->jetBrainThemeName);
	}

	if (themeName == theme->adobeThemeName)
	{
		adobeSelectButton->setEnabled(false);
		theme->setCurrentTheme(theme->adobeThemeName);
	}

	if (themeName == theme->officeThemeName)
	{
		officeSelectButton->setEnabled(false);
		theme->setCurrentTheme(theme->officeThemeName);
	}

	user->update();
}

void StoreScene::unlockTheme(const string& themeName, const int coin)
{
	user->setCoin(user->getCoin() - coin);
	coinText->setString(to_string(user->getCoin()));

	unlockTheme(themeName);
}

void StoreScene::unlockTheme(const string& themeName)
{
	auto v = user->getUnlockedThemes();
	v.emplace_back(themeName);
	user->setUnlockedThemes(v);

	if (themeName == theme->adobeThemeName) createAdobeButton(true);
	if (themeName == theme->officeThemeName) createOfficeButtons(true);
}

Button* StoreScene::createSelectButton() const
{
	return Button::create(theme->storeSceneChoiceButtonNormal,
	                      theme->storeSceneChoiceButtonSelected,
	                      theme->storeSceneChoiceButtonDisabled);
}

void StoreScene::createAdobeButton(const bool unlocked)
{
	if (adobeSelectButton != nullptr)
	{
		removeChild(adobeSelectButton);
		adobeSelectButton = nullptr;
	}

	if (adobeMenu != nullptr)
	{
		removeChild(adobeMenu);
		adobeMenu = nullptr;
	}

	if (unlocked)
	{
		adobeSelectButton = createSelectButton();
		adobeSelectButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
		{
			if (type == Widget::TouchEventType::ENDED)
			{
				updateCurrentTheme(theme->adobeThemeName);
				Director::getInstance()->replaceScene(StoreScene::createScene());
				Music::getInstance()->change(theme->backgroundMusic);
			}
		});
		adobeSelectButton->setPosition(Point(600, 150));
		this->addChild(adobeSelectButton);
	}
	else
	{
		auto adobeRmbMenuItem = MenuItemSprite::create
		(
			Sprite::create(theme->storeSceneAdobeRmbButtonNormal),
			Sprite::create(theme->storeSceneAdobeRmbButtonSelected),
			Sprite::create(theme->storeSceneAdobeRmbButtonDisabled),
			[&](Ref* sender)
			{
				cashPay();
			}
		);
		adobeRmbMenuItem->setPosition(Point(600, 220));

		auto adobeCoinsMenuItem = MenuItemSprite::create
		(
			Sprite::create(theme->storeSceneAdobeCoinsButtonNormal),
			Sprite::create(theme->storeSceneAdobeCoinsButtonSelected),
			Sprite::create(theme->storeSceneAdobeCoinsButtonDisabled),
			[&](Ref* sender)
			{
				if (user->getCoin() >= 30)
				{
					successfulPay(false, 30, theme->adobeThemeName);
				}
				else
				{
					failedPay();
				}
			}
		);
		adobeCoinsMenuItem->setPosition(Point(600, 120));
		adobeMenu = Menu::create(adobeRmbMenuItem, adobeCoinsMenuItem, nullptr);
		adobeMenu->setPosition(Point(0, 0));
		this->addChild(adobeMenu);
	}
}

void StoreScene::createOfficeButtons(const bool unlocked)
{
	if (officeSelectButton != nullptr)
	{
		removeChild(officeSelectButton);
		officeSelectButton = nullptr;
	}

	if (officeMenu != nullptr)
	{
		removeChild(officeMenu);
		officeMenu = nullptr;
	}

	if (unlocked)
	{
		officeSelectButton = createSelectButton();
		officeSelectButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
		{
			if (type == Widget::TouchEventType::ENDED)
			{
				updateCurrentTheme(theme->officeThemeName);
				Director::getInstance()->replaceScene(StoreScene::createScene());
				Music::getInstance()->change(theme->backgroundMusic);
			}
		});
		officeSelectButton->setPosition(Point(960, 150));
		this->addChild(officeSelectButton);
	}
	else
	{
		auto officeRmbMenuItem = MenuItemSprite::create
		(
			Sprite::create(theme->storeSceneOfficeRmbButtonNormal),
			Sprite::create(theme->storeSceneOfficeRmbButtonSelected),
			Sprite::create(theme->storeSceneOfficeRmbButtonDisabled),
			[&](Ref* sender)
			{
				cashPay();
			}
		);
		officeRmbMenuItem->setPosition(Point(960, 220));

		auto officeCoinsMenuItem = MenuItemSprite::create
		(
			Sprite::create(theme->storeSceneOfficeCoinsButtonNormal),
			Sprite::create(theme->storeSceneOfficeCoinsButtonSelected),
			Sprite::create(theme->storeSceneOfficeCoinsButtonDisabled),
			[&](Ref* sender)
			{
				if (user->getCoin() >= 60)
				{
					successfulPay(false, 60, theme->officeThemeName);
				}
				else
				{
					failedPay();
				}
			}
		);
		officeCoinsMenuItem->setPosition(Point(960, 120));
		officeMenu = Menu::create(officeRmbMenuItem, officeCoinsMenuItem, nullptr);
		officeMenu->setPosition(Point(0, 0));
		this->addChild(officeMenu);
	}
}

#pragma region Pay
void StoreScene::cashPay()
{
	const auto dialog = Dialog::create(theme->gameSceneDialogBackground, Size(640, 480));
	dialog->setContentText("功能开发中, 敬请期待!", 36, 60, 20);

	dialog->addButton(MenuItemSprite::create(
		Sprite::create(theme->gameSceneYesButtonNormal),
		Sprite::create(theme->gameSceneYesButtonSelected),
		Sprite::create(theme->gameSceneYesButtonNormal),
		[&, dialog](Ref* sender)
		{
			Director::getInstance()->getRunningScene()->removeChild(dialog);
		}));

	this->addChild(dialog, 30);
}

void StoreScene::successfulPay(const bool rmbPay, int coin, const string& themeName)
{
	if (rmbPay) coin /= 10;
	const auto dialog = Dialog::create(theme->gameSceneDialogBackground, Size(640, 480));
	dialog->setContentText("确认购买主题?", 36, 60, 20);

	dialog->addButton(MenuItemSprite::create(
		Sprite::create(theme->gameSceneYesButtonNormal),
		Sprite::create(theme->gameSceneYesButtonSelected),
		Sprite::create(theme->gameSceneYesButtonNormal),
		[&, dialog, coin, themeName](Ref* sender)
		{
			unlockTheme(themeName, coin);
			Director::getInstance()->getRunningScene()->removeChild(dialog);
			auto successPay = Dialog::create(theme->gameSceneDialogBackground, Size(640, 480));
			successPay->setContentText("购买成功, 快去试试新主题吧!", 36, 60, 20);
			successPay->addButton(MenuItemSprite::create(
				Sprite::create(theme->gameSceneYesButtonNormal),
				Sprite::create(theme->gameSceneYesButtonSelected),
				Sprite::create(theme->gameSceneYesButtonNormal),
				[&, successPay](Ref* sender)
				{
					Director::getInstance()->getRunningScene()->removeChild(successPay);
				}));
			this->addChild(successPay);
		}));
	dialog->addButton(MenuItemSprite::create(
		Sprite::create(theme->gameSceneNoButtonNormal),
		Sprite::create(theme->gameSceneNoButtonSelected),
		Sprite::create(theme->gameSceneNoButtonNormal),
		[&, dialog](Ref* sender)
		{
			Director::getInstance()->getRunningScene()->removeChild(dialog);
		}));

	this->addChild(dialog, 30);
}

void StoreScene::failedPay()
{
	const auto dialog = Dialog::create(theme->gameSceneDialogBackground, Size(640, 480));
	dialog->setContentText("金币不足, 主题购买失败!", 36, 60, 20);

	dialog->addButton(MenuItemSprite::create(
		Sprite::create(theme->gameSceneYesButtonNormal),
		Sprite::create(theme->gameSceneYesButtonSelected),
		Sprite::create(theme->gameSceneYesButtonNormal),
		[&, dialog](Ref* sender)
		{
			Director::getInstance()->getRunningScene()->removeChild(dialog);
		}));
	this->addChild(dialog, 30);
}

#pragma endregion
