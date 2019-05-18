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
	auto sprite = Sprite::create("/images/loadingScene/jetBrainTheme/scene_sta.png");
	sprite->setPosition(Point(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
	this->addChild(sprite);

	// 添加游戏名称
	label = Sprite::create("/images/loadingScene/jetBrainTheme/label1.png");
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
	// TODO 加载一切

	// 初始化背景音乐
	vector<string> musicPath;
	// TODO 设置默认音乐文件位置
	musicPath.emplace_back("/musics/tryBackgroundMusic.mp3");
	musicPath.emplace_back("/musics/tryBackgroundMusic.mp3");
	Music::getInstance()->loading(musicPath);

	// 初始化音效
	Sound::getInstance();

	loadingFlag = true;
}

void LoadingScene::startGame(float)
{
	if (!loadingFlag) return;
	else unschedule(schedule_selector(LoadingScene::startGame));

	// TODO 设置默认音乐文件位置
	Music::getInstance()->play("/musics/tryBackgroundMusic.mp3");

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

//喷射图标动画实现
void LoadingScene::jetIcon()
{
	const auto dirs = Director::getInstance();

	//图表和Spawn动作数组声明
	Sprite *iconSet[10];
	Spawn *spawnSet[10];

	//循环初始化Icon精灵和动作
	for (auto i = 0; i < 10; i++)
	{
		iconSet[i] = Sprite::create("/images/loadingScene/jetBrainTheme/iconSet/medium/" + std::to_string(i) + ".png");
		iconSet[i]->setPosition(dirs->getVisibleSize().width / 2, 0);
		iconSet[i]->setScale(1);
		this->addChild(iconSet[i]);

		//创建一个Action来使得精灵从某一位置喷出，并通过数学表达式实现喷泉造型（简陋）
		const auto jumpRight = JumpBy::create(3, Point(dirs->getVisibleSize().width/4+30*i, 0-iconSet[i]->getContentSize().height),30 * i+100, 1);
		const auto jumpLeft = JumpBy::create(3, Point(-dirs->getVisibleSize().width/4-30*i, 0-iconSet[i]->getContentSize().height),30 * i+70, 1);

		const auto move = MoveTo::create(1.5,Vec2(dirs->getVisibleSize().width / 2, 0 - iconSet[i]->getContentSize().height));
		//实现精灵的移动过程中Icon放大
		const auto scale = ScaleTo::create(3, 2);

		const auto delay = DelayTime::create(0.25f);

		//根据计数器判断精灵抛出的方向
		if (i % 2 == 0)
		{
			spawnSet[i] = Spawn::create(jumpRight, delay, scale, delay->clone(), nullptr);//同时运行多个动作
			auto sequence = Sequence::create(spawnSet[i], delay, move, delay, nullptr);//动作序列
			iconSet[i]->runAction(RepeatForever::create(sequence));//实现重复跳跃
		}
		else
		{
			spawnSet[i] = Spawn::create(jumpLeft, delay, scale, delay->clone(), nullptr);
			auto sequence = Sequence::create(spawnSet[i], delay, move, delay, nullptr);
			iconSet[i]->runAction(RepeatForever::create(sequence));
		}
	}
}
