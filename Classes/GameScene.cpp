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

	initBoard();
	newBlocksDrop();

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

	progressBarScore = Sprite::create(theme->gameSceneProcessBar);
	progressTimer = ProgressTimer::create(progressBarScore);
	progressTimer->setPosition(Point(225, 410));
	progressTimer->setType(ProgressTimer::Type::BAR);
	// 设置竖向变化
	progressTimer->setBarChangeRate(Point(0, 1));
	progressTimer->setMidpoint(Point(0, 0));
	progressTimer->setPercentage(0);
	this->addChild(progressTimer, 2);

	// 分数板
	scoreLabel = Label::createWithTTF("25", "/font/marker_felt.ttf", 32);
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
				hintNumber->setTexture(theme->gameSceneHintNumber + std::to_string(hint) + ".png");

				// 接口测试
				setTotalProgress(10);
				setCurrentProgress(5);
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

			auto e = (EventMouse*)(event);
			// 只按下左键为有效操作
			if (e->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT)
			{
				auto cursorX = e->getCursorX();
				auto cursorY = e->getCursorY();
				log("click %f %f (%d,%d)", cursorX, cursorY, getIndex(Pii(cursorX, cursorY)));

				// TODO: 选中标识动画
				// 还未选中过方块
				if (selectedBlockF.first == -1)
				{
					selectedBlockF = getIndex(Pii(cursorX, cursorY));
				}

					//已经选中一个方块
				else if (selectedBlockF.first != -1 && selectedBlockS.first == -1)
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
								selectedBlockS = {-1, -1};
							}
							break;
						}

					case 0:
						{
							// 不相邻，现选择的方块变为第一块
							if ((selectedBlockF.second - selectedBlockS.second != -1)
								&& (selectedBlockF.second - selectedBlockS.second != 1))
							{
								selectedBlockF = getIndex(Pii(cursorX, cursorY));
								selectedBlockS = {-1, -1};
							}
							break;
						}

						// 不相邻，现选择的方块变为第一块
					default:
						{
							selectedBlockF = getIndex(Pii(cursorX, cursorY));
							selectedBlockS = {-1, -1};
							break;
						}
					}
				}
			}
		};

		// 鼠标弹起
		mouseListener->onMouseUp = [&](Event* event)
		{
			auto e = (EventMouse*)(event);
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

		getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, this);
	}

#pragma endregion
}

Pii GameScene::getPosition(Pii index)
{
	return Pii(550 + 64 * index.second, 230 + 64 * index.first);
}

Pii GameScene::getIndex(Pii pos)
{
	if (pos.first < 520 || pos.first > 520 + 512)return {-1, -1};
	if (pos.second < 210 || pos.second > 210 + 512)return {-1, -1};
	return Pii((pos.second - 200) / 64, (pos.first - 520) / 64);
}

Sprite* GameScene::createSprite(const int picType, Pii pos)
{
	auto block = Sprite::create(BLOCK_N[picType]);
	block->setPosition(Point(pos.first, pos.second));
	block->setScale(0.9f);
	addChild(block);
	return block;
}

vector<pair<Pii, Pii>> GameScene::getKillList()
{
	vector<pair<Pii, Pii>> rtn;
	std::set<Pii> vis;

	//TODO: check cross;
	//TODO: check 6 link;
	//TODO: check 5 link;
	//TODO: check 4 link;

	//check 3 link;
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if ((i > 0 && i < BOARD_SIZE - 1)
				&& (boardInfo[i - 1][j].first == boardInfo[i][j].first && boardInfo[i][j].first == boardInfo[i + 1][j].
					first)
				&& (!vis.count({i - 1, j}) && !vis.count({i, j}) && !vis.count({i + 1, j})))
			{
				rtn.push_back({{i - 1, j}, {-1, -1}});
				vis.insert({i - 1, j});
				rtn.push_back({{i, j}, {-1, -1}});
				vis.insert({i, j});
				rtn.push_back({{i + 1, j}, {-1, -1}});
				vis.insert({i + 1, j});
			}
			if ((j > 0 && j < BOARD_SIZE - 1)
				&& (boardInfo[i][j - 1].first == boardInfo[i][j].first && boardInfo[i][j].first == boardInfo[i][j + 1].
					first)
				&& (!vis.count({i, j - 1}) && !vis.count({i, j}) && !vis.count({i, j + 1})))
			{
				rtn.push_back({{i, j - 1}, {-1, -1}});
				vis.insert({i, j - 1});
				rtn.push_back({{i, j}, {-1, -1}});
				vis.insert({i, j});
				rtn.push_back({{i, j + 1}, {-1, -1}});
				vis.insert({i, j + 1});
			}
		}
	}

	return rtn;
}

void GameScene::trySwap(Pii block1, Pii block2)
{
	selectedBlockF = {-1, -1};
	selectedBlockS = {-1, -1};

	boardLocked = true;
	swap(boardInfo[block1.first][block1.second], boardInfo[block2.first][block2.second]);
	auto tempList = getKillList();
	swap(boardInfo[block1.first][block1.second], boardInfo[block2.first][block2.second]);

	if (!tempList.empty())
	{
		blockSwap(block1, block2);
	}
}

void GameScene::blockSwap(Pii blocka, Pii blockb)
{
	auto posa = getPosition(blocka);
	auto posb = getPosition(blockb);
	Vec2 veta = {static_cast<float>(posa.first), static_cast<float>(posa.second)};
	Vec2 vetb = {static_cast<float>(posb.first), static_cast<float>(posb.second)};

	boardInfo[blocka.first][blocka.second].second->runAction(Sequence::create(
		CCMoveTo::create(0.25, vetb),
		NULL
	));

	boardInfo[blockb.first][blockb.second].second->runAction(Sequence::create(
		CCMoveTo::create(0.25, veta),
		CCCallFunc::create([&]() { animationDoneCallback(); }),
		NULL
	));

	swap(boardInfo[blocka.first][blocka.second], boardInfo[blockb.first][blockb.second]);
}

void GameScene::blockVanish(vector<pair<Pii, Pii>> killList)
{
	for (auto elm : killList)
	{
		Pii pos = elm.first;
		Pii fil = elm.second;
		Sprite* todel = boardInfo[pos.first][pos.second].second;
		todel->runAction(Sequence::create(
			CCScaleTo::create(.3f, .0f),
			CCCallFunc::create([&, todel]() { removeChild(todel); }),
			NULL
		));

		if (fil == Pii(-1, -1))
		{
			boardInfo[pos.first][pos.second] = {-1, nullptr};
			auto ti = BOARD_SIZE;
			while (boardInfo[ti][pos.second].first != -1)
			{
				ti++;
				assert(ti < 2 * BOARD_SIZE);
			}
			int typ = rand() % 6;
			boardInfo[ti][pos.second] = {typ, createSprite(typ, getPosition({ti, pos.second}))};
		}
		else
		{
			//TODO: fill
		}
	}
	runAction(Sequence::createWithTwoActions(DelayTime::create(.3f), CCCallFunc::create([&]() { newBlocksDrop(); })));
}

void GameScene::initBoard()
{
	for (auto i = 0; i < 2 * BOARD_SIZE; i++)
	{
		for (auto j = 0; j < BOARD_SIZE; j++)
		{
			boardInfo[i][j] = {-1, nullptr};
		}
	}
	refreshBoard();
}

void GameScene::refreshBoard()
{
	for (auto i = 0; i < 2 * BOARD_SIZE; i++)
	{
		for (auto j = 0; j < BOARD_SIZE; j++)
		{
			if (boardInfo[i][j].first != -1)
			{
				removeChild(boardInfo[i][j].second);
				boardInfo[i][j].second->release();
			}
			boardInfo[i][j] = {-1, nullptr};
		}
	}
	for (auto i = BOARD_SIZE; i < 2 * BOARD_SIZE; i++)
	{
		for (auto j = 0; j < BOARD_SIZE; j++)
		{
			const auto banx = ((i >= BOARD_SIZE + 2 && boardInfo[i - 1][j].first == boardInfo[i - 2][j].first)
				                   ? (boardInfo[i - 2][j].first)
				                   : (-1));
			const auto bany = ((j >= 2 && boardInfo[i][j - 1].first == boardInfo[i][j - 2].first)
				                   ? (boardInfo[i][j - 2].first)
				                   : (-1));
			auto typ = rand() % 6;
			while (typ == banx || typ == bany)typ = rand() % 6;
			boardInfo[i][j] = {typ, createSprite(typ, getPosition({i, j}))};
		}
	}
}

void GameScene::newBlocksDrop()
{
	for (auto i = 0; i < BOARD_SIZE; i++)
	{
		for (auto j = 0; j < BOARD_SIZE; j++)
		{
			if (boardInfo[i][j].first == -1)
			{
				auto tempi = i;
				while (boardInfo[tempi][j].first == -1)
				{
					tempi++;
					assert(tempi < 2 * BOARD_SIZE);
				}
				auto ep = getPosition({i, j});
				//boardInfo[ti][j].second->runAction(EaseBounceOut::create(CCMoveTo::create(1, ccp(ep.first, ep.second))));
				boardInfo[tempi][j].second->runAction(
					CCEaseOut::create(CCMoveTo::create(0.5, ccp(ep.first, ep.second)), 2.0f));
				swap(boardInfo[i][j], boardInfo[tempi][j]);
			}
		}
	}
	runAction(Sequence::createWithTwoActions(DelayTime::create(0.5),
	                                         CCCallFunc::create([&]() { animationDoneCallback(); })));
}

void GameScene::animationDoneCallback()
{
	auto newList = getKillList();
	if (newList.empty())
	{
		boardLocked = false;
	}
	else
	{
		blockVanish(newList);
	}
}

void GameScene::setTotalProgress(const int total)
{
	totalProgress = total;
}

void GameScene::setCurrentProgress(int progress)
{
	if (progress < 0) { progress = 0; }
	if (progress > totalProgress) { progress = totalProgress; }
	currentProgress = progress;
	scoreLabel->setString(std::to_string(currentProgress));
	const auto processAction = ProgressFromTo::create(0.25, 0, currentProgress/totalProgress*100);
	progressTimer->runAction(processAction);
}


float GameScene::getCurrentProgress() const { return currentProgress; }
float GameScene::getTotalProgress() const { return totalProgress; }
