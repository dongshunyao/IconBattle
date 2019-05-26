#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "BackButton.h"
#include "SettingButton.h"
#include "Theme.h"

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 900

USING_NS_CC;

class GameScene final :
	public cocos2d::Scene
{
public:

	static cocos2d::Scene* createScene();
	bool init() override;
	CREATE_FUNC(GameScene)

private:
	int hint = 3;
	Theme* theme = Theme::getInstance();
	Sprite* hintNumber = nullptr;
	Sprite* processBarScore = nullptr;
};

#endif
