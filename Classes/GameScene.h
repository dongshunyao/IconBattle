#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 900

class GameScene final :
	public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	bool init() override;
	CREATE_FUNC(GameScene)
};

#endif
