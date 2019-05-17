#include "LoadingScene.h"
#include "Music.h"

Scene* LoadingScene::createScene()
{
	auto scene = LoadingScene::create();

	// 创建一个带有背景颜色的layer
	Layer* layerCLayer = LayerColor::create(Color4B(0, 0, 0, 0), SCREEN_WIDTH, SCREEN_HEIGHT);
	layerCLayer->setIgnoreAnchorPointForPosition(false);
	layerCLayer->setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	scene->addChild(layerCLayer);

	return scene;
}

bool LoadingScene::init()
{
	if (!Scene::init()) return false;


	// 添加背景图片
	auto sprite = Sprite::create("/images/loadingScene/jetBrainTheme/scene_sta.png");
	sprite->setPosition(Point(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
	this->addChild(sprite);

	// 添加游戏名称
	label = Sprite::create("/images/loadingScene/jetBrainTheme/label1.png");
	label->setPosition(Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
	this->addChild(label, 0);

	// 用于加载的子线程
	std::thread loadingThread(&LoadingScene::loading, this);
	loadingThread.detach();

	// 定时器，每2.5秒检测是否可以开始游戏
	schedule(schedule_selector(LoadingScene::startGame), 2.5);

	//开始播放背景音乐
	auto startMusic = new Music;
	startMusic->loading();

	return true;
}


void LoadingScene::loading()
{
	// TODO 加载一切

	loadingFlag = true;
}

void LoadingScene::startGame(float)
{
	if (!loadingFlag) return;
	else unschedule(schedule_selector(LoadingScene::startGame));

	// 将游戏名称向上移动
	const auto moveTo = MoveTo::create(1, Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 50));
	label->runAction(moveTo);

	// 按任意键开始游戏
	auto ready = Sprite::create("/images/loadingScene/jetBrainTheme/label2.png");
	ready->setPosition(Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 50));
	ready->setOpacity(0); //设置透明度为0
	this->addChild(ready);
	// 淡入的效果
	const auto fadeIn = FadeIn::create(3.0f);
	ready->runAction(fadeIn);

	// 鼠标监听器
	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseDown = [](Event* event)
	{
		Director::getInstance()->replaceScene(MenuScene::createScene());
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
}
