#ifndef __LOADING_SCENE_H__
#define __LOADING_SCENE_H__

#include "cocos2d.h"

class LoadingScene final :
	public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	bool init() override;

	CREATE_FUNC(LoadingScene);
};

#endif
