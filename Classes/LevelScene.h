#ifndef __LEVEL_SCENE_H__
#define __LEVEL_SCENE_H__

#include "cocos2d.h"
#include "BackButton.h"
#include "SettingButton.h"
#include "MenuScene.h"
#include "Theme.h"
#include "ui/UIScrollView.h"

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
	void initScrollView();
	void initButtons(int x, int y, int level, float delayTime);
	void update(float delta) override;
	void scrollViewMoveCallback(Ref *pSender, ui::ScrollView::EventType eventType);

	// 用于存放按钮的layer
	Layer* layer = nullptr;

	// 第一张背景图 （做滚动效果需要两张图来拼接） 
	Sprite* backgroundFirst = nullptr;
	Sprite* backgroundSecond = nullptr;
	// 第二张背景图 
	Sprite* foregroundFirst = nullptr;
	Sprite* foregroundSecond = nullptr;

	Theme* theme = Theme::getInstance();

};

#endif
