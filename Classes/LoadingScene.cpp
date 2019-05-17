#include "LoadingScene.h"
#define GAME_SCREEN_WIDTH 1200
#define GAME_SCREEN_HEIGHT 900

USING_NS_CC;

Scene* LoadingScene::createScene()
{
	auto scene = Scene::create();
	auto layer = LoadingScene::create();

	// 创建一个带有背景颜色的layer2 (白色)
	CCLayer *layer2 = CCLayerColor::create(ccc4(0x00, 0x00, 0x00, 0xf0), GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT);
	layer2->ignoreAnchorPointForPosition(false);
	layer2->setPosition(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 2);
	layer2->addChild(layer);
	scene->addChild(layer2, 1, layer2->getTag());

	return scene;
}

bool LoadingScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	// 添加背景图片
	auto sprite = Sprite::create("/images/loadingScene/jetbrainTheme/scene_sta.png");
	sprite->setPosition(Point(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 2));
	this->addChild(sprite);

	// 添加游戏名称
	label = Sprite::create("/images/loadingScene/jetbrainTheme/label1.png");
	label->setPosition(Vec2(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 2));
	this->addChild(label, 0);

	// 加载完成，准备开始游戏
	readyToStart();

	return true;
}


void LoadingScene::readyToStart()
{
	// 将游戏名称向上移动
	auto moveTo = MoveTo::create(1, Vec2(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 2 + 50));
	label->runAction(moveTo);

	// 按任意键开始游戏
	Sprite *ready = Sprite::create("/images/loadingScene/jetbrainTheme/label2.png");
	ready->setPosition(Vec2(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 2 - 50));
	ready->setOpacity(0);	//设置透明度为0
	this->addChild(ready);
	// 淡入的效果
	auto fadeIn = FadeIn::create(3.0f);
	ready->runAction(fadeIn);


	// 鼠标监听器
	auto _mouseListener = EventListenerMouse::create();
	_mouseListener->onMouseDown = CC_CALLBACK_1(LoadingScene::startGame, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);
}

void LoadingScene::startGame(Event* ev)
{
	log("ready to start");
	// 跳转到游戏界面
	// auto scene = GameScene::createScene();
	// CCDirector::sharedDirector()->replaceScene(scene);
}