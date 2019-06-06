#ifndef __STORE_SCENE_H__
#define __STORE_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "MenuScene.h"
#include "Theme.h"
#include "User.h"

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 900

USING_NS_CC;
using ui::Button;
using std::to_string;

class StoreScene final :
	public Scene
{
public:
	static Scene* createScene();
	bool init() override;
	CREATE_FUNC(StoreScene)

private:
	Theme* theme = Theme::getInstance();
	User* user = User::getInstance();
	void initCoin();
	void initThemeIcon();

	Label* coinText = nullptr;

	void updateCurrentTheme(const string& themeName) const;
	void unlockTheme(const string& themeName, int coin);
	void unlockTheme(const string& themeName);

	void cashPay();
	void successfulPay(bool rmbPay,int coin, const string& themeName);
	void failedPay();

	void initButton();
	Button* createSelectButton() const;

	Button* jetBrainSelectButton = nullptr;

	Menu* adobeMenu = nullptr;
	Button* adobeSelectButton = nullptr;

	Menu* officeMenu = nullptr;
	Button* officeSelectButton = nullptr;

	void createAdobeButton(bool unlocked);
	void createOfficeButtons(bool unlocked);
};

#endif
