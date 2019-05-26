#ifndef __LEVEL_SCENE_H__
#define __LEVEL_SCENE_H__

#include "cocos2d.h"
#include "BackButton.h"
#include "SettingButton.h"
#include "MenuScene.h"
#include "Theme.h"

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 900

USING_NS_CC;

class LevelScene final :
	public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	bool init() override;
	CREATE_FUNC(LevelScene)

private:
	void initBackground();
	void initUsername();
	void initButtons(int x, int y, int type, float delayTime);
	void update(float delta) override;


	// 第一张背景图 （做滚动效果需要两张图来拼接） 
	Sprite* background1_1 = nullptr;
	Sprite* background1_2 = nullptr;
	// 第二张背景图 
	Sprite* background2_1 = nullptr;
	Sprite* background2_2 = nullptr;
	Theme* theme = Theme::getInstance("JetBrain");//User::getInstance()->getCurrentTheme());
};

#endif
