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

	auto v = user->getUnlockedThemes();
	const auto ownJetBrain = find(v.begin(), v.end(), theme->jetBrainThemeName);
	const auto ownAdobe = find(v.begin(), v.end(), theme->adobeThemeName);
	const auto ownOffice = find(v.begin(), v.end(), theme->officeThemeName);
	initJetBrainButtons(!(ownJetBrain == v.end()));
	initAdobeButtons(!(ownAdobe == v.end()));
	initOfficeButtons(!(ownOffice == v.end()));

	return true;
}

void StoreScene::initCoins()
{
	auto coinIcon = Sprite::create(theme->storeSceneCoin);
	coinIcon->setPosition(Point(130, 850));
	this->addChild(coinIcon, -1);

	auto coins = user->getCoin();
	coinText = Label::createWithTTF(std::to_string(coins), "font/marker_felt.ttf", 30);
	coinText->setPosition(Point(220, 850));
	this->addChild(coinText, -1);
}

void StoreScene::getAdobe()
{
	user->setCoin(user->getCoin() - 30);
	auto v = user->getUnlockedThemes();
	v.emplace_back(theme->adobeThemeName);
	user->setUnlockedThemes(v);

	coinText->setString(std::to_string(user->getCoin()));
	initAdobeButtons(true);
}

void StoreScene::getOffice()
{
	user->setCoin(user->getCoin() - 50);
	auto v = user->getUnlockedThemes();
	v.emplace_back(theme->officeThemeName);
	user->setUnlockedThemes(v);

	coinText->setString(std::to_string(user->getCoin()));
	initOfficeButtons(true);
}

// TODO 未完成模态对话框提示用户硬币不够
void StoreScene::notEnoughCoins()
{
	// TODO 提示玩家金币不足 模态对话框
}

void StoreScene::initLabel()
{
	auto label = Sprite::create(theme->storeSceneStoreLabel);
	label->setPosition(Point(600, 830));
	this->addChild(label, -1);
}

void StoreScene::initThemeIcon()
{
	auto jetBrainThemeIcon = Sprite::create(theme->storeSceneJetBrainThemeIcon);
	jetBrainThemeIcon->setPosition(Point(240, 500));
	this->addChild(jetBrainThemeIcon, -1);

	auto adobeThemeIcon = Sprite::create(theme->storeSceneAdobeThemeIcon);
	adobeThemeIcon->setPosition(Point(600, 500));
	this->addChild(adobeThemeIcon, -1);

	auto officeThemeIcon = Sprite::create(theme->storeSceneOfficeThemeIcon);
	officeThemeIcon->setPosition(Point(960, 500));
	this->addChild(officeThemeIcon, -1);
}

void StoreScene::initJetBrainButtons(const bool ownJetBrain)
{
	if (ownJetBrain) {
		auto jetBrainChoiceIcon = Button::create(theme->storeSceneChoiceButtonNormal,
			theme->storeSceneChoiceButtonSelected,
			theme->storeSceneChoiceButtonDisabled);
		jetBrainChoiceIcon->addTouchEventListener([&, jetBrainChoiceIcon](Ref* sender, ui::Widget::TouchEventType type)
		{
			theme->setCurrentTheme(theme->jetBrainThemeName);
		});
		jetBrainChoiceIcon->setPosition(Point(240, 150));
		this->addChild(jetBrainChoiceIcon);
	}
}

// TODO 未完成模态对话框、支付功能
void StoreScene::initAdobeButtons(const bool ownAdobe)
{
	if(ownAdobe)
	{
		auto adobeChoiceIcon = Button::create(theme->storeSceneChoiceButtonNormal,
			theme->storeSceneChoiceButtonSelected,
			theme->storeSceneChoiceButtonDisabled);
		adobeChoiceIcon->addTouchEventListener([&, adobeChoiceIcon](Ref* sender, ui::Widget::TouchEventType type)
		{
			theme->setCurrentTheme(theme->adobeThemeName);
		});
		adobeChoiceIcon->setPosition(Point(600, 150));
		this->addChild(adobeChoiceIcon);
	}else
	{
		const auto adobeRmbIconNormal = Sprite::create(theme->storeSceneAdobeRmbButtonNormal);
		const auto adobeRmbIconSelected = Sprite::create(theme->storeSceneAdobeRmbButtonSelected);
		const auto adobeRmbIconDisable = Sprite::create(theme->storeSceneAdobeRmbButtonDisabled);
		auto adobeRmbMenuItem = MenuItemSprite::create(adobeRmbIconNormal, adobeRmbIconSelected, adobeRmbIconDisable, [&](Ref* sender)
		{
			// TODO
		});
		adobeRmbMenuItem->setPosition(Point(600, 220));

		const auto adobeCoinsIconNormal = Sprite::create(theme->storeSceneAdobeCoinsButtonNormal);
		const auto adobeCoinsIconSelected = Sprite::create(theme->storeSceneAdobeCoinsButtonSelected);
		const auto adobeCoinsIconDisable = Sprite::create(theme->storeSceneAdobeCoinsButtonDisabled);
		auto adobeCoinsMenuItem = MenuItemSprite::create(adobeCoinsIconNormal, adobeCoinsIconSelected, adobeCoinsIconDisable, [&](Ref* sender)
		{
			if ((user->getCoin()) > 30) {
				// TODO 模态对话框询问用户
				getAdobe();
				this->removeChild(adobeMenu, true);
			}
			else
				notEnoughCoins();
		});
		adobeCoinsMenuItem->setPosition(Point(600, 120));
		adobeMenu = Menu::create(adobeRmbMenuItem, adobeCoinsMenuItem, nullptr);
		adobeMenu->setPosition(Point(0, 0));
		this->addChild(adobeMenu);
	}
}

void StoreScene::initOfficeButtons(const bool ownOffice)
{
	if(ownOffice)
	{
		auto officesChoiceIcon = Button::create(theme->storeSceneChoiceButtonNormal,
			theme->storeSceneChoiceButtonSelected,
			theme->storeSceneChoiceButtonDisabled);
		officesChoiceIcon->addTouchEventListener([&, officesChoiceIcon](Ref* sender, ui::Widget::TouchEventType type)
		{
			theme->setCurrentTheme(theme->officeThemeName);
		});
		officesChoiceIcon->setPosition(Point(960, 150));
		this->addChild(officesChoiceIcon);
	}else
	{
		const auto officeRmbIconNormal = Sprite::create(theme->storeSceneOfficeRmbButtonNormal);
		const auto officeRmbIconSelected = Sprite::create(theme->storeSceneOfficeRmbButtonSelected);
		const auto officeRmbIconDisable = Sprite::create(theme->storeSceneOfficeRmbButtonDisabled);
		auto officeRmbMenuItem = MenuItemSprite::create(officeRmbIconNormal, officeRmbIconSelected, officeRmbIconDisable, [&](Ref* sender)
		{
			// TODO
		});
		officeRmbMenuItem->setPosition(Point(960, 220));

		const auto officeCoinsIconNormal = Sprite::create(theme->storeSceneAdobeCoinsButtonNormal);
		const auto officeCoinsIconSelected = Sprite::create(theme->storeSceneAdobeCoinsButtonSelected);
		const auto officeCoinsIconDisable = Sprite::create(theme->storeSceneAdobeCoinsButtonDisabled);
		auto officeCoinsMenuItem = MenuItemSprite::create(officeCoinsIconNormal, officeCoinsIconSelected, officeCoinsIconDisable, [&](Ref* sender)
		{
			if ((user->getCoin()) > 50) {
				// TODO 模态对话框询问用户
				getOffice();
				this->removeChild(officeMenu, true);
			}
			else
				notEnoughCoins();
		});
		officeCoinsMenuItem->setPosition(Point(960, 120));
		officeMenu = Menu::create(officeRmbMenuItem, officeCoinsMenuItem, nullptr);
		officeMenu->setPosition(Point(0, 0));
		this->addChild(officeMenu);	
	}

}
