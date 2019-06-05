#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "StoreScene.h"
#include "GameScene.h"
#include "LevelScene.h"
#include "NewsBoard.h"
#include "BackButton.h"
#include "SettingButton.h"
#include "Theme.h"
#include "User.h"
#include "GameSceneController.h"

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 900

USING_NS_CC;
using ui::EditBox;

class MenuScene final :
	public Scene
{
public:
	static Scene* createScene();

	bool init() override;
	CREATE_FUNC(MenuScene)

private:
	Theme* theme = Theme::getInstance();
	User* user = User::getInstance();

	void initUsername();
	void initStoreButton();
	void initRankButton();
	void initGameButton();
	void initPlate();

	Button* classicPractice = nullptr;
	Button* classicLevel = nullptr;
	Button* classicChallenge = nullptr;
	Button* enhancedPractice = nullptr;
	Button* enhancedLevel = nullptr;
	Button* enhancedChallenge = nullptr;

	ListView* enhancedListView = nullptr;
	ListView* classicListView = nullptr;

	bool classicMoveOut = false;
	bool enhancedMoveOut = false;
};

#endif
