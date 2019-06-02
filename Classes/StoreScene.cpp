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
	this->addChild(settingButton);

	// 返回按钮
	this->addChild(BackButton::create());

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

	// TODO 统一字体？路径放到头文件orTheme？
	coinText = Label::createWithTTF(to_string(user->getCoin()), "font/marker_felt.ttf", 30);
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
		updateCurrentTheme(theme->jetBrainThemeName);
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
			updateCurrentTheme(theme->adobeThemeName);
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
				// TODO 人民币支付，成功后调用unlockTheme（名字）
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
					// TODO 对话框确认支付，成功后调用下面一行
					unlockTheme(theme->adobeThemeName, 30);
				}
				else
				{
					// TODO 对话框没钱
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
			updateCurrentTheme(theme->officeThemeName);
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
				// TODO 人民币支付，成功后调用unlockTheme（名字）
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
				if (user->getCoin() >= 50)
				{
					// TODO 对话框确认支付，成功后调用下面一行
					unlockTheme(theme->officeThemeName, 50);
				}
				else
				{
					// TODO 对话框没钱
				}
			}
		);
		officeCoinsMenuItem->setPosition(Point(960, 120));
		officeMenu = Menu::create(officeRmbMenuItem, officeCoinsMenuItem, nullptr);
		officeMenu->setPosition(Point(0, 0));
		this->addChild(officeMenu);
	}
}
