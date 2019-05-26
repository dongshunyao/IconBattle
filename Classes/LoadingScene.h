#ifndef __LOADING_SCENE_H__
#define __LOADING_SCENE_H__

#include "cocos2d.h"
#include "User.h"
#include "Music.h"
#include "Sound.h"
#include "MenuScene.h"
#include "Theme.h"
#include <vector>
#include <string>

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 900

USING_NS_CC;
using std::vector;
using std::string;

class LoadingScene final :
	public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	bool init() override;
	CREATE_FUNC(LoadingScene)

private:
	Sprite* label = nullptr;
	Theme* theme = Theme::getInstance("JetBrain");
	bool loadingFlag = false;

	void loading();
	void jetIcon();
	void startGame(float);
};

#endif
