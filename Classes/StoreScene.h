#ifndef __STORE_SCENE_H__
#define __STORE_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "MenuScene.h"
#include "Theme.h"

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 900

USING_NS_CC;

class StoreScene final :
	public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	bool init() override;
	CREATE_FUNC(StoreScene)

private:
	Theme* theme = Theme::getInstance();

	void initLabel();
	void initThemeIcon();
	void initButtons();
	void initCoins();

};

#endif
