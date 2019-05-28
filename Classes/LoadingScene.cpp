#include "LoadingScene.h"

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
	auto sprite = Sprite::create(theme->loadingSceneBackground);
	sprite->setPosition(Point(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
	this->addChild(sprite, -1);

	// 添加游戏名称
	label = Sprite::create(theme->loadingSceneLabelTitle);
	label->setPosition(Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
	this->addChild(label, 0);

	jetIcon();

	// 用于加载的子线程
	std::thread loadingThread(&LoadingScene::loading, this);
	loadingThread.detach();

	// 定时器，每2.5秒检测是否可以开始游戏
	schedule(schedule_selector(LoadingScene::startGame), 2.5);

	return true;
}

void LoadingScene::loading()
{
	// 初始化背景音乐
	vector<string> musicPath;
	musicPath.emplace_back(theme->backgroundMusic);
	Music::getInstance()->loading(musicPath);

	// 初始化音效
	Sound::getInstance();

	loadingFlag = true;
}

void LoadingScene::startGame(float)
{
	if (!loadingFlag) return;
	else unschedule(schedule_selector(LoadingScene::startGame));

	Music::getInstance()->play(theme->backgroundMusic);

	// 将游戏名称向上移动
	const auto moveTo = MoveTo::create(1, Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 50));
	label->runAction(moveTo);

	// 按任意键开始游戏
	auto ready = Sprite::create(theme->loadingSceneLabelPress);
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

// 喷射图标动画实现
void LoadingScene::jetIcon()
{
	// 循环初始化Icon精灵和动作
	for (auto i = 0; i < 10; i++)
	{
		const auto icon = Sprite::create(theme->iconSet + std::to_string(i) + ".png");
		icon->setPosition(SCREEN_WIDTH / 2, 0 - icon->getContentSize().height);
		icon->setScale(1);
		this->addChild(icon, -1, i); // 渲染时 z-order 值大的节点对象会后绘制，值小的节点对象先绘制。
		// 创建一个Action来使得精灵从某一位置喷出，并通过数学表达式实现喷泉造型
		const auto jumpRight = JumpBy::create(i, Point(SCREEN_WIDTH / 4 + 30 * i, 0 - icon->getContentSize().height),
		                                      60 * i + 300, 1);
		const auto jumpLeft = JumpBy::create(i, Point(-(SCREEN_WIDTH / 4 + 30 * i), 0 - icon->getContentSize().height),
		                                     60 * i + 270, 1);

		const auto move = MoveTo::create(1.5, Vec2(SCREEN_WIDTH / 2, 0 - icon->getContentSize().height));
		// 实现精灵的移动过程中Icon放大
		const auto scale = ScaleTo::create(i, 2);
		const auto scaleReverse = ScaleTo::create(i, 1);
		const auto delay = DelayTime::create(0.25 * i * i);
		// 根据计数器判断精灵抛出的方向
		const auto spawn = Spawn::create(i % 2 == 0 ? jumpRight : jumpLeft, delay, scale, delay->clone(), nullptr);
		// 同时运行多个动作
		const auto sequence = Sequence::create(delay, spawn, delay, move, delay, scaleReverse, delay, nullptr); // 动作序列
		icon->runAction(RepeatForever::create(sequence)); // 实现重复跳跃
	}
}
