#ifndef __LOADING_SCENE_H__
#define __LOADING_SCENE_H__

#include "cocos2d.h"

class LoadingScene final :
	public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void readyToStart();
	void startGame(cocos2d::Event* ev);
	CREATE_FUNC(LoadingScene);

private:
	cocos2d::Sprite *label;
};

#endif
