#ifndef __STORE_SCENE_H__
#define __STORE_SCENE_H__

#include "cocos2d.h"
#include "MenuScene.h"
#include "Theme.h"
#include "User.h"

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 900

USING_NS_CC;
using ui::Button;
using namespace std;

class StoreScene final :
	public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	bool init() override;
	CREATE_FUNC(StoreScene)

private:
	Theme* theme = Theme::getInstance();
	User* user = User::getInstance();
	Label* coinText = nullptr;
	Menu* adobeMenu = nullptr;
	Menu* officeMenu = nullptr;

	void initLabel();
	void initThemeIcon();
	void initJetBrainButtons(bool ownJetBrain);
	void initAdobeButtons(bool ownAdobe);
	void initOfficeButtons(bool ownOffice);
	void initCoins();

	void getAdobe();
	void getOffice();
	void notEnoughCoins();
};

#endif
