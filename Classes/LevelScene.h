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
	public Scene
{
public:
	static Scene* createScene(bool isClassical);
	bool init() override;
	CREATE_FUNC(LevelScene)

private:
	void initBackground();
	void initScrollView();
	void initButtons();
	void initCoin();
	void initModeLabel(bool isClassic);
	void update(float) override;

	// 用于存放按钮的layer
	Layer* layer = nullptr;

	// 第一张背景图 （做滚动效果需要两张图来拼接） 
	Sprite* backgroundFirst = nullptr;
	Sprite* backgroundSecond = nullptr;
	// 第二张背景图 
	Sprite* foregroundFirst = nullptr;
	Sprite* foregroundSecond = nullptr;

	Theme* theme = Theme::getInstance();
	User* user = User::getInstance();

	// 金币数
	Label* coinText = nullptr;

	// 模式
	bool isClassic = true;

	// 选关Button的位置数组
	pair<int, int> pos[10] =
	{
		{200, 600},
		{420, 510},
		{640, 640},
		{860, 520},
		{1080, 600},
		{1280, 420},
		{1500, 270},
		{1720, 390},
		{1940, 470},
		{2160, 420}
	};
};

#endif
