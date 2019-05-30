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
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(
		"/image/gamescene/jetbraintheme/iconset/large/super_gems.plist",
		"/image/gamescene/jetbraintheme/iconset/large/super_gems.png");
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
				judgeResult();
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
				log("click %f %f (%d,%d)", cursorX, cursorY, getIndex(pii(cursorX, cursorY)));

				// TODO: 选中标识动画
				// 还未选中过方块
				if (selectedBlockF.first == -1)
				{
					selectedBlockF = getIndex(pii(cursorX, cursorY));
				}

					//已经选中一个方块
				else if (selectedBlockF.first != -1 && selectedBlockS.first == -1)
				{
					selectedBlockS = getIndex(pii(cursorX, cursorY));
					// 判断第二方块是否相邻
					switch (selectedBlockS.first - selectedBlockF.first)
					{
					case 1: case -1:
						{
							// 不相邻，现选择的方块变为第一块
							if (selectedBlockF.second != selectedBlockS.second)
							{
								selectedBlockF = getIndex(pii(cursorX, cursorY));
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
								selectedBlockF = getIndex(pii(cursorX, cursorY));
								selectedBlockS = {-1, -1};
							}
							break;
						}

						// 不相邻，现选择的方块变为第一块
					default:
						{
							selectedBlockF = getIndex(pii(cursorX, cursorY));
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

pii GameScene::getPosition(pii index)
{
	return pii(550 + 75 * index.second, 200 + 75 * index.first);
}

pii GameScene::getIndex(pii pos)
{
	if (pos.first < 520 || pos.first > 520 + 600)return {-1, -1};
	if (pos.second < 170 || pos.second > 170 + 600)return {-1, -1};
	return pii((pos.second - 170) / 75, (pos.first - 520) / 75);
}

Actor* GameScene::createActor(int typ, int spv, pii pos)
{
	Actor* rtn = Actor::create(typ, spv, pos);
	addChild(rtn);
	return rtn;
}

KillGroupList GameScene::getKillList()
{
	KillGroupList rtn;
	set<pii> vis;

	//TODO: check cross;
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			int ilen = 1, jlen = 1;
			ActorInfoList tCrossActor;
			tCrossActor.push_back(ActorInfo(i, j));
			for (int ip = i + 1; ip < BOARD_SIZE && boardInfo[ip][j].type == boardInfo[i][j].type && !vis.count({ip, j})
			     && boardInfo[ip][j].func != FUNC_SUPER; ip++)
			{
				ilen++;
				tCrossActor.push_back(ActorInfo(ip, j));
			}
			for (int ip = i - 1; ip >= 0 && boardInfo[ip][j].type == boardInfo[i][j].type && !vis.count({ip, j}) &&
			     boardInfo[ip][j].func != FUNC_SUPER; ip--)
			{
				ilen++;
				tCrossActor.push_back(ActorInfo(ip, j));
			}
			for (int jp = j + 1; jp < BOARD_SIZE && boardInfo[i][jp].type == boardInfo[i][j].type && !vis.count({i, jp})
			     && boardInfo[i][jp].func != FUNC_SUPER; jp++)
			{
				jlen++;
				tCrossActor.push_back(ActorInfo(i, jp));
			}
			for (int jp = j - 1; jp >= 0 && boardInfo[i][jp].type == boardInfo[i][j].type && !vis.count({i, jp}) &&
			     boardInfo[i][jp].func != FUNC_SUPER; jp--)
			{
				jlen++;
				tCrossActor.push_back(ActorInfo(i, jp));
			}
			if (ilen == 3 && jlen == 3)
			{
				rtn.push_back({{i, j}, 500, tCrossActor, {ActorInfo(i, j, boardInfo[i][j].type, FUNC_FIRE)}});
			}
			else if (ilen >= 3 && jlen >= 3)
			{
				rtn.push_back({{i, j}, 1000, tCrossActor, {ActorInfo(i, j, boardInfo[i][j].type, FUNC_SUPER)}});
			}
			if (ilen >= 3 && jlen >= 3)
			{
				for (auto elm : tCrossActor)
				{
					vis.insert(elm.pos);
				}
			}
		}
	}

	//TODO: check 6 link;
	//砍了，具体看info

	//TODO: check 5 link;
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if ((i > 1 && i < BOARD_SIZE - 2)
				&& (boardInfo[i - 1][j].type == boardInfo[i][j].type && boardInfo[i][j].type == boardInfo[i + 1][j].type
					&& boardInfo[i][j].type == boardInfo[i + 2][j].type && boardInfo[i][j].type == boardInfo[i - 2][j].
					type)
				&& (boardInfo[i - 1][j].func != FUNC_SUPER && boardInfo[i][j].func != FUNC_SUPER && boardInfo[i + 1][j].
					func != FUNC_SUPER && boardInfo[i + 2][j].func != FUNC_SUPER && boardInfo[i - 2][j].func !=
					FUNC_SUPER)
				&& (!vis.count({i - 1, j}) && !vis.count({i, j}) && !vis.count({i + 1, j}) && !vis.count({i + 2, j}) &&
					!vis.count({i - 2, j})))
			{
				vis.insert({i - 1, j});
				vis.insert({i, j});
				vis.insert({i + 1, j});
				vis.insert({i + 2, j});
				vis.insert({i - 2, j});
				rtn.push_back({
					{i, j}, 200,
					{
						ActorInfo(i - 1, j), ActorInfo(i, j), ActorInfo(i + 1, j), ActorInfo(i + 2, j),
						ActorInfo(i - 2, j)
					},
					{ActorInfo(i, j, boardInfo[i][j].type, FUNC_H_3)}
				});
			}
			if ((j > 1 && j < BOARD_SIZE - 2)
				&& (boardInfo[i][j - 1].type == boardInfo[i][j].type && boardInfo[i][j].type == boardInfo[i][j + 1].type
					&& boardInfo[i][j].type == boardInfo[i][j + 2].type && boardInfo[i][j].type == boardInfo[i][j - 2].
					type)
				&& (boardInfo[i][j - 1].func != FUNC_SUPER && boardInfo[i][j].func != FUNC_SUPER && boardInfo[i][j + 1].
					func != FUNC_SUPER && boardInfo[i][j + 2].func != FUNC_SUPER && boardInfo[i][j - 2].func !=
					FUNC_SUPER)
				&& (!vis.count({i, j - 1}) && !vis.count({i, j}) && !vis.count({i, j + 1}) && !vis.count({i, j + 2}) &&
					!vis.count({i, j - 2})))
			{
				vis.insert({i, j - 1});
				vis.insert({i, j});
				vis.insert({i, j + 1});
				vis.insert({i, j + 2});
				vis.insert({i, j - 2});
				rtn.push_back({
					{i, j}, 200,
					{
						ActorInfo(i, j - 1), ActorInfo(i, j), ActorInfo(i, j + 1), ActorInfo(i, j + 2),
						ActorInfo(i, j - 2)
					},
					{ActorInfo(i, j, boardInfo[i][j].type, FUNC_V_3)}
				});
			}
		}
	}

	//TODO: check 4 link;
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if ((i > 0 && i < BOARD_SIZE - 2)
				&& (boardInfo[i - 1][j].type == boardInfo[i][j].type && boardInfo[i][j].type == boardInfo[i + 1][j].type
					&& boardInfo[i][j].type == boardInfo[i + 2][j].type)
				&& (boardInfo[i - 1][j].func != FUNC_SUPER && boardInfo[i][j].func != FUNC_SUPER && boardInfo[i + 1][j].
					func != FUNC_SUPER && boardInfo[i + 2][j].func != FUNC_SUPER)
				&& (!vis.count({i - 1, j}) && !vis.count({i, j}) && !vis.count({i + 1, j}) && !vis.count({i + 2, j})))
			{
				vis.insert({i - 1, j});
				vis.insert({i, j});
				vis.insert({i + 1, j});
				vis.insert({i + 2, j});
				rtn.push_back({
					{i, j}, 200, {ActorInfo(i - 1, j), ActorInfo(i, j), ActorInfo(i + 1, j), ActorInfo(i + 2, j)},
					{ActorInfo(i, j, boardInfo[i][j].type, FUNC_H_1)}
				});
			}
			if ((j > 0 && j < BOARD_SIZE - 2)
				&& (boardInfo[i][j - 1].type == boardInfo[i][j].type && boardInfo[i][j].type == boardInfo[i][j + 1].type
					&& boardInfo[i][j].type == boardInfo[i][j + 2].type)
				&& (boardInfo[i][j - 1].func != FUNC_SUPER && boardInfo[i][j].func != FUNC_SUPER && boardInfo[i][j + 1].
					func != FUNC_SUPER && boardInfo[i][j + 2].func != FUNC_SUPER)
				&& (!vis.count({i, j - 1}) && !vis.count({i, j}) && !vis.count({i, j + 1}) && !vis.count({i, j + 2})))
			{
				vis.insert({i, j - 1});
				vis.insert({i, j});
				vis.insert({i, j + 1});
				vis.insert({i, j + 2});
				rtn.push_back({
					{i, j}, 200, {ActorInfo(i, j - 1), ActorInfo(i, j), ActorInfo(i, j + 1), ActorInfo(i, j + 2)},
					{ActorInfo(i, j, boardInfo[i][j].type, FUNC_V_1)}
				});
			}
		}
	}

	//check 3 link;
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if ((i > 0 && i < BOARD_SIZE - 1)
				&& (boardInfo[i - 1][j].type == boardInfo[i][j].type && boardInfo[i][j].type == boardInfo[i + 1][j].type
				)
				&& (boardInfo[i - 1][j].func != FUNC_SUPER && boardInfo[i][j].func != FUNC_SUPER && boardInfo[i + 1][j].
					func != FUNC_SUPER)
				&& (!vis.count({i - 1, j}) && !vis.count({i, j}) && !vis.count({i + 1, j})))
			{
				vis.insert({i - 1, j});
				vis.insert({i, j});
				vis.insert({i + 1, j});
				rtn.push_back({{i, j}, 100, {ActorInfo(i - 1, j), ActorInfo(i, j), ActorInfo(i + 1, j)}, {}});
			}
			if ((j > 0 && j < BOARD_SIZE - 1)
				&& (boardInfo[i][j - 1].type == boardInfo[i][j].type && boardInfo[i][j].type == boardInfo[i][j + 1].type
				)
				&& (boardInfo[i][j - 1].func != FUNC_SUPER && boardInfo[i][j].func != FUNC_SUPER && boardInfo[i][j + 1].
					func != FUNC_SUPER)
				&& (!vis.count({i, j - 1}) && !vis.count({i, j}) && !vis.count({i, j + 1})))
			{
				vis.insert({i, j - 1});
				vis.insert({i, j});
				vis.insert({i, j + 1});
				rtn.push_back({{i, j}, 100, {ActorInfo(i, j - 1), ActorInfo(i, j), ActorInfo(i, j + 1)}, {}});
			}
		}
	}

	return rtn;
}

void GameScene::trySwap(pii blocka, pii blockb)
{
	selectedBlockF = {-1, -1};
	selectedBlockS = {-1, -1};

	CCLOG("[LOCK] Try Swap (%d,%d),(%d,%d)", blocka.first, blocka.second, blockb.first, blockb.second);
	boardLocked = true;

	// 如果交换的方块有特效方块
	if (boardInfo[blocka.first][blocka.second].func == FUNC_SUPER && boardInfo[blockb.first][blockb.second].func ==
		FUNC_SUPER)
	{
		pii center = blocka;
		ActorInfoList tCrossActor;
		for (int i = 0; i < BOARD_SIZE; i++)
		{
			for (int j = 0; j < BOARD_SIZE; j++)
			{
				if (boardInfo[i][j].func == FUNC_SUPER) boardInfo[i][j].func = FUNC_NO;
				tCrossActor.push_back(ActorInfo(i, j));
			}
		}
		blockVanish({{center, 5000, tCrossActor, {}}});
		return;
	}
	else if (boardInfo[blocka.first][blocka.second].func == FUNC_SUPER || boardInfo[blocka.first][blocka.second].func ==
		FUNC_SUPER)
	{
		int toDelColor = -1;
		pii center = {-1, -1};
		ActorInfoList tCrossActor;
		if (boardInfo[blocka.first][blocka.second].func == FUNC_SUPER)
		{
			boardInfo[blocka.first][blocka.second].func = -1;
			boardInfo[blocka.first][blocka.second].type = boardInfo[blockb.first][blockb.second].type;
			center = blocka;
			toDelColor = boardInfo[blockb.first][blockb.second].type;
		}
		else
		{
			boardInfo[blockb.first][blockb.second].func = -1;
			boardInfo[blockb.first][blockb.second].type = boardInfo[blocka.first][blocka.second].type;
			center = blockb;
			toDelColor = boardInfo[blocka.first][blocka.second].type;
		}
		for (int i = 0; i < BOARD_SIZE; i++)
		{
			for (int j = 0; j < BOARD_SIZE; j++)
			{
				if (boardInfo[i][j].type == toDelColor && boardInfo[i][j].func != FUNC_SUPER)
				{
					tCrossActor.push_back(ActorInfo(i, j));
				}
			}
		}
		//TODO: anim
		blockVanish({{center, 5000, tCrossActor, {}}});
		return;
	}


	swap(boardInfo[blocka.first][blocka.second], boardInfo[blockb.first][blockb.second]);
	auto rst = getKillList();
	swap(boardInfo[blocka.first][blocka.second], boardInfo[blockb.first][blockb.second]);

	if (rst.empty())
	{
		animationDoneCallback();
	}
	else
	{
		blockSwap(blocka, blockb);
	}
}

void GameScene::blockSwap(pii blocka, pii blockb)
{
	pii posa = getPosition(blocka);
	pii posb = getPosition(blockb);

	boardInfo[blocka.first][blocka.second].actor->moveTo(posb);
	boardInfo[blockb.first][blockb.second].actor->moveTo(posa);

	swap(boardInfo[blocka.first][blocka.second], boardInfo[blockb.first][blockb.second]);

	runAction(Sequence::createWithTwoActions(DelayTime::create(.4f),
	                                         CCCallFunc::create([&]() { animationDoneCallback(); })));
}

// TODO: 粒子特效已经注释掉，待添加
void GameScene::blockVanish(KillGroupList killList)
{
	//移除过程中，检测到的被触发的特殊型宝石暂存于此
	ActorInfoList specialActors;

	//1:移除过程
	for (KillGroup killGroup : killList)
	{
		//1.1展示分数
		//showScore(killGroup.markValue, killGroup.markPoint);
		//1.2移除所有得分块
		for (ActorInfo toDelActorInfo : killGroup.killInfo)
		{
			//delete
			pii pos = toDelActorInfo.pos;
			assert(boardInfo[pos.first][pos.second].type != -1);
			if (boardInfo[pos.first][pos.second].func != -1)
			{
				specialActors.push_back({
					pos, boardInfo[pos.first][pos.second].type, boardInfo[pos.first][pos.second].func
				});
			}
			boardInfo[pos.first][pos.second].actor->selfClose();
			boardInfo[pos.first][pos.second] = blockInfo();
			//placeDropper
			int ti = BOARD_SIZE;
			while (boardInfo[ti][pos.second].type != -1)
			{
				ti++;
				assert(ti < 2 * BOARD_SIZE);
			}
			int type = rand() % 6;
			auto droper = createActor(type, -1, getPosition({ti, pos.second}));
			boardInfo[ti][pos.second] = blockInfo(type, -1, droper);
		}
		//1.3添加奖励特殊方块
		for (ActorInfo toAddActorInfo : killGroup.newInfo)
		{
			//create
			pii pos = toAddActorInfo.pos;
			assert(boardInfo[pos.first][pos.second].type == -1);
			auto newActor = createActor(toAddActorInfo.type, toAddActorInfo.func, getPosition(pos));
			boardInfo[pos.first][pos.second] = blockInfo(toAddActorInfo.type, toAddActorInfo.func, newActor);
			//deleteDropper
			int ti = 2 * BOARD_SIZE - 1;
			while (boardInfo[ti][pos.second].type == -1)
			{
				ti--;
				assert(ti >= BOARD_SIZE);
			}
			removeChild(boardInfo[ti][pos.second].actor);
			boardInfo[ti][pos.second] = blockInfo();
		}
	}

	//处理特殊方块的消除
	if (specialActors.empty())
	{
		runAction(
			Sequence::createWithTwoActions(DelayTime::create(.3f), CCCallFunc::create([&]() { newBlocksDrop(); })));
	}
	else
	{
		KillGroupList causedKillList;
		set<pii> vis;

		for (auto specialActor : specialActors)
		{
			KillGroup nowKill = {specialActor.pos, 114, {}, {}};
			switch (specialActor.func)
			{
			case FUNC_H_1:
				{
					int i = specialActor.pos.first;
					//showThunder_H(getPosition({ i,0 }).second);
					for (int j = 0; j < BOARD_SIZE; j++)
					{
						if (boardInfo[i][j].type == -1 || vis.count({i, j}))continue;
						nowKill.killInfo.push_back(ActorInfo(i, j));
						if (boardInfo[i][j].func == FUNC_SUPER)boardInfo[i][j].type = specialActor.type;
						vis.insert({i, j});
					}
					break;
				}
			case FUNC_V_1:
				{
					int j = specialActor.pos.second;
					//showThunder_V(getPosition({ 0,j }).first);
					for (int i = 0; i < BOARD_SIZE; i++)
					{
						if (boardInfo[i][j].type == -1 || vis.count({i, j}))continue;
						nowKill.killInfo.push_back(ActorInfo(i, j));
						if (boardInfo[i][j].func == FUNC_SUPER)boardInfo[i][j].type = specialActor.type;
						vis.insert({i, j});
					}
					break;
				}
			case FUNC_H_3:
				{
					for (int i = specialActor.pos.first - 1; i <= specialActor.pos.first + 1; i++)
					{
						if (i < 0 || i > BOARD_SIZE)continue;
						//showThunder_H(getPosition({ i,0 }).second);
						for (int j = 0; j < BOARD_SIZE; j++)
						{
							if (boardInfo[i][j].type == -1 || vis.count({i, j}))continue;
							nowKill.killInfo.push_back(ActorInfo(i, j));
							if (boardInfo[i][j].func == FUNC_SUPER)boardInfo[i][j].type = specialActor.type;
							vis.insert({i, j});
						}
					}
					break;
				}
			case FUNC_V_3:
				{
					for (int j = specialActor.pos.second - 1; j <= specialActor.pos.second + 1; j++)
					{
						if (j < 0 || j > BOARD_SIZE)continue;
						//showThunder_V(getPosition({ 0,j }).first);
						for (int i = 0; i < BOARD_SIZE; i++)
						{
							if (boardInfo[i][j].type == -1 || vis.count({i, j}))continue;
							nowKill.killInfo.push_back(ActorInfo(i, j));
							if (boardInfo[i][j].func == FUNC_SUPER)boardInfo[i][j].type = specialActor.type;
							vis.insert({i, j});
						}
					}
					break;
				}
			case FUNC_FIRE:
				{
					//showFire(getPosition(specialActor.pos));
					for (int i = specialActor.pos.first - 1; i <= specialActor.pos.first + 1; i++)
					{
						for (int j = specialActor.pos.second - 1; j <= specialActor.pos.second + 1; j++)
						{
							if (i < 0 || i > BOARD_SIZE)continue;
							if (j < 0 || j > BOARD_SIZE)continue;
							if (boardInfo[i][j].type == -1 || vis.count({i, j}))continue;
							nowKill.killInfo.push_back(ActorInfo(i, j));
							if (boardInfo[i][j].func == FUNC_SUPER)boardInfo[i][j].type = specialActor.type;
							vis.insert({i, j});
						}
					}
					break;
				}
			case FUNC_SUPER:
				{
					int toDelColor = specialActor.type;
					pii center = specialActor.pos;
					boardInfo[center.first][center.second].func = -1;

					for (int i = 0; i < BOARD_SIZE; i++)
					{
						for (int j = 0; j < BOARD_SIZE; j++)
						{
							if (boardInfo[i][j].type == toDelColor && boardInfo[i][j].func != FUNC_SUPER && !vis.count({
								i, j
							}))
							{
								nowKill.killInfo.push_back(ActorInfo(i, j));
							}
						}
					}
					//TODO: anim
					break;
				}
				//TOFO: fill
			default: assert(false);
			}
			causedKillList.push_back(nowKill);
		}

		runAction(Sequence::createWithTwoActions(DelayTime::create(.2f),
		                                         CCCallFunc::create([&, causedKillList]()
		                                         {
			                                         blockVanish(causedKillList);
		                                         })));
	}
}

void GameScene::initBoard()
{
	refreshBoard();
}

void GameScene::refreshBoard()
{
	for (int i = 0; i < 2 * BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (boardInfo[i][j].type != -1)
			{
				removeChild(boardInfo[i][j].actor);
				boardInfo[i][j].actor->release();
			}
			boardInfo[i][j] = blockInfo();
		}
	}
	for (int i = BOARD_SIZE; i < 2 * BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			int banx = ((i >= BOARD_SIZE + 2 && boardInfo[i - 1][j].type == boardInfo[i - 2][j].type)
				            ? (boardInfo[i - 2][j].type)
				            : (-1));
			int bany = ((j >= 2 && boardInfo[i][j - 1].type == boardInfo[i][j - 2].type)
				            ? (boardInfo[i][j - 2].type)
				            : (-1));
			int typ = rand() % 6;
			while (typ == banx || typ == bany)typ = rand() % 6;
			//DEBUG=================
			if (true)
			{
				if (i - 10 == 6 && j == 3)
				{
					boardInfo[i][j] = {0, FUNC_SUPER, createActor(0, FUNC_SUPER, getPosition({i, j}))};
					continue;
				}
				if (i - 10 == 6 && j == 4)
				{
					boardInfo[i][j] = {0, FUNC_SUPER, createActor(0, FUNC_SUPER, getPosition({i, j}))};
					continue;
				}
				//if(i-10==5&&j==4) { boardInfo[i][j] = { 0, FUNC_V_3 ,createActor(0,FUNC_V_3,getPosition({i,j })) }; continue; }
				//if(i-10==5&&j==5) { boardInfo[i][j] = { 0, -1 ,createActor(0,-1,getPosition({i,j })) }; continue; }
			}
			//======================
			boardInfo[i][j] = {typ, -1, createActor(typ, -1, getPosition({i, j}))};
		}
	}
}

void GameScene::newBlocksDrop()
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (boardInfo[i][j].type == -1)
			{
				int ti = i;
				while (boardInfo[ti][j].type == -1)
				{
					ti++;
					assert(ti < 2 * BOARD_SIZE);
				}
				pii ep = getPosition({i, j});
				boardInfo[ti][j].actor->dropTo(ep);
				swap(boardInfo[i][j], boardInfo[ti][j]);
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
		// 如果死局重新刷新面板
		if (isDead())
		{
			refreshBoard();
		}
	}
	else
	{
		blockVanish(newList);
	}
}

bool GameScene::isDead()
{
	return false;
}

void GameScene::setTotalProgress(const int total)
{
	totalProgress = total;
}

void GameScene::setCurrentProgress(int progress)
{
	const float previousPercentage = 100 * currentProgress / totalProgress;
	if (progress < 0) { progress = 0; }
	if (progress > totalProgress) { progress = totalProgress; }
	currentProgress = progress;
	scoreLabel->setString(std::to_string(currentProgress));
	const auto processAction = ProgressFromTo::create(0.25, previousPercentage, 100 * currentProgress / totalProgress);
	progressTimer->runAction(processAction);
}


float GameScene::getCurrentProgress() const { return currentProgress; }
float GameScene::getTotalProgress() const { return totalProgress; }

void GameScene::judgeResult()
{
	// 两个精灵实现结果先后出现
	firstSprite = Sprite::create(result
		                             ? theme->gameSceneResultSprite + "2.png"
		                             : theme->gameSceneResultSprite + +"0.png");
	secondSprite = Sprite::create(result
		                              ? theme->gameSceneResultSprite + +"3.png"
		                              : theme->gameSceneResultSprite + +"1.png");
	firstSprite->setPosition(SCREEN_WIDTH / 2 - firstSprite->getContentSize().width / 2, SCREEN_HEIGHT / 2);
	secondSprite->setPosition(SCREEN_WIDTH / 2 + secondSprite->getContentSize().width / 2, SCREEN_HEIGHT / 2);
	firstSprite->setOpacity(0);
	secondSprite->setOpacity(0);
	this->addChild(firstSprite, 10);
	this->addChild(secondSprite, 10);

	const auto delay = DelayTime::create(1.3);
	const auto fadeIn = FadeIn::create(1.3);
	const auto firstMoveTo = MoveTo::create(1, Vec2(SCREEN_WIDTH / 2 - firstSprite->getContentSize().width / 2,
	                                                SCREEN_HEIGHT / 2 + 200));
	const auto secondMoveTo = MoveTo::create(1, Vec2(SCREEN_WIDTH / 2 + secondSprite->getContentSize().width / 2,
	                                                 SCREEN_HEIGHT / 2 + 200));
	firstSprite->runAction(Sequence::create(fadeIn, delay, firstMoveTo, nullptr));
	secondSprite->runAction(Sequence::create(delay, fadeIn, secondMoveTo, CallFunc::create([&]()
	{
		// Todo 排名相关
		firstSprite->setVisible(false);
		secondSprite->setVisible(false);
	}), nullptr));
}
