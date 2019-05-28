#include "GameScene.h"
#include "User.h"


Scene* GameScene::createScene()
{
	return GameScene::create();
}

bool GameScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	initComponents();

	return true;
}

void GameScene::initComponents()
{
#pragma  region Init GameScene

	// 添加背景图片
	auto sprite = Sprite::create(theme->gameSceneBackground);
	sprite->setPosition(Point(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
	this->addChild(sprite);

	// 设置按钮
	auto settingButton = SettingButton::create();
	settingButton->setPosition(Point(1050, 850));
	this->addChild(settingButton);

	// 返回按钮
	this->addChild(BackButton::create());

	// 剩余步数Label
	auto levelSprite = Sprite::create(theme->gameSceneLevelSpriteBackground);
	levelSprite->setScale(1.5);
	levelSprite->setPosition(225, 630);
	this->addChild(levelSprite, 0);
	auto remainStep = Label::createWithTTF("20", "/font/marker_felt.ttf", 48);
	// glow effect is TTF only, specify the glow color desired.
	remainStep->enableGlow(Color4B::YELLOW);
	remainStep->setPosition(225, 625);
	this->addChild(remainStep);

	// 添加积分条灰色背景
	auto processBar = Sprite::create(theme->gameSceneGreyProcessBar);
	processBar->setPosition(Point(225, 410));
	this->addChild(processBar, 1);

	processBarScore = Sprite::create(theme->gameSceneProcessBar);
	auto processTimer = ProgressTimer::create(processBarScore);
	processTimer->setPosition(Point(225, 410));
	processTimer->setType(ProgressTimer::Type::BAR);
	// 设置竖向变化
	processTimer->setBarChangeRate(Point(0, 1));
	processTimer->setMidpoint(Point(0, 0));
	processTimer->setPercentage(0);
	this->addChild(processTimer, 2);

	// 积分条测试动作
	const auto processAction = ProgressFromTo::create(5, 0, 100);
	const auto repeatAction = RepeatForever::create(processAction);
	processTimer->runAction(repeatAction);
	// 分数板
	auto scoreLabel = Label::createWithTTF("25", "/font/marker_felt.ttf", 32);
	scoreLabel->setPosition(225, 240);
	this->addChild(scoreLabel);

	// 默认初始提示剩余次数为3
	hintNumber = Sprite::createWithTexture(
		Director::getInstance()->getTextureCache()->addImage(
			theme->gameSceneHintNumber + std::to_string(hint)
			+ ".png"));
	hintNumber->setPosition(340, 520);
	this->addChild(hintNumber, 2);

	// 提示按钮
	auto hintButton = ui::Button::create(theme->gameSceneHintButtonNormal, theme->gameSceneHintButtonSelected,
	                                     theme->gameSceneHintButtonDisabled);
	hintButton->setPosition(Point(375, 540));
	hintButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			if (hint > 0)
			{
				hint--;
				// TODO:动态更新hintNumber图片
				hintNumber->setTexture(theme->gameSceneHintNumber + std::to_string(hint) + ".png");
			}
		}
	});
	this->addChild(hintButton, 1);


#pragma endregion

#pragma  region addMouseListener
	{
		auto mouseListener = EventListenerMouse::create();
		// 鼠标按下
		mouseListener->onMouseDown = [&](Event* event)
		{
			if (boardLocked)return;

			const auto e = dynamic_cast<EventMouse*>(event);
			// 只按下左键为有效操作
			if (e->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT)
			{
				auto cursorX = e->getCursorX();
				auto cursorY = e->getCursorY();

				// TODO: 选中标识动画
				// 还未选中过方块
				if (selectedBlockF.first == -1)
					selectedBlockF = getIndex(Pii(cursorX, cursorY));
				//已经选中一个方块
				else if(selectedBlockF.first != -1 && selectedBlockS.first == -1)
				{
					selectedBlockS = getIndex(Pii(cursorX, cursorY));
					// 判断第二方块是否相邻
					switch (selectedBlockS.first - selectedBlockF.first)
					{
					case 1: case -1:
						{
							// 不相邻，现选择的方块变为第一块
							if (selectedBlockF.second != selectedBlockS.second)
							{
								selectedBlockF = getIndex(Pii(cursorX, cursorY));
								selectedBlockS = { -1,-1 };
							}
							break;
						}
						
					case 0:
						{
							// 不相邻，现选择的方块变为第一块
							if ((selectedBlockF.second - selectedBlockS.second != -1)
								|| (selectedBlockF.second - selectedBlockS.second != 1))
							{
								selectedBlockF = getIndex(Pii(cursorX, cursorY));
								selectedBlockS = { -1,-1 };
							}
							break;
						}

					// 不相邻，现选择的方块变为第一块
					default:
						{
							selectedBlockF = getIndex(Pii(cursorX, cursorY));
							selectedBlockS = { -1,-1 };
							break;
						}
					}
				}
			}

		};

		// 鼠标弹起
		mouseListener->onMouseUp = [&](Event* event)
		{
			const auto e = dynamic_cast<EventMouse*>(event);
			// 只左键弹起有效
			if (e->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT)
			{
				// 已经选中两块则尝试交换，否则不进行操作
				if (selectedBlockF.first != -1 && selectedBlockS.first != -1)
				{
					trySwap(selectedBlockF, selectedBlockS);
				}
			}
		};
	}

#pragma endregion
}
