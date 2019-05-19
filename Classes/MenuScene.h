#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "StoreScene.h"
#include "PannelNews.h"


#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 900

class MenuScene final :
	public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	bool init() override;
	CREATE_FUNC(MenuScene)
};

#endif
