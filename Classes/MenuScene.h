#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "StoreScene.h"
#include "GameScene.h"
#include "LevelScene.h"
#include "NewsBoard.h"
#include "SettingButton.h"
#include "Theme.h"
#include "User.h"
#include "GameSceneController.h"
#include "Dialog.h"

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
	void initCoin();
	void initPainter();

	Button* classicPractice = nullptr;
	Button* classicLevel = nullptr;
	Button* classicChallenge = nullptr;
	Button* enhancedPractice = nullptr;
	Button* enhancedLevel = nullptr;
	Button* enhancedChallenge = nullptr;

	// 金币数
	Label* coinText = nullptr;

	ListView* enhancedListView = nullptr;
	ListView* classicListView = nullptr;

	bool classicMoveOut = false;
	bool enhancedMoveOut = false;

	Sprite* streakSprite = nullptr;
	Sprite* drawOnMeLabel = nullptr;
	MotionStreak* streak = nullptr;
	void onTouchesBegan(const std::vector<Touch *> &touches, cocos2d::Event *event) const;
	void onTouchesMoved(const std::vector<Touch *> &touches, cocos2d::Event *event) const;
};

#endif
