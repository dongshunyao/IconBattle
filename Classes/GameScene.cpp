#include "GameScene.h"

Scene* GameScene::createScene(const int stepNumber, const int totalScore, const bool isClassical, const int hintNumber)
{
	const auto scene = GameScene::create();

	// 初始化变量
	scene->stepNumber = stepNumber;
	scene->totalScore = totalScore;
	scene->isClassical = isClassical;
	scene->hintNumber = hintNumber;

	// TODO 初始化精灵缓存
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(
		"/image/gamescene/jetbraintheme/iconset/large/super_gems.plist",
		"/image/gamescene/jetbraintheme/iconset/large/super_gems.png");

	// 初始化背景板及按钮
	scene->initInformationBoard();

	// 初始化游戏
	scene->initGameBoard();

	return scene;
}

Actor* GameScene::createActor(int typ, int spv, Pair pos)
{
	Actor* rtn = Actor::create(typ, spv, pos);
	addChild(rtn);
	return rtn;
}

KillGroupList GameScene::getKillList()
{
	KillGroupList rtn;
	set<Pair> vis;

	//TODO: check cross;
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			int ilen = 1, jlen = 1;
			ActorInfoList tCrossActor;
			tCrossActor.push_back(ActorInfo(i, j));
			for (int ip = i + 1; ip < BOARD_SIZE && board[ip][j].type == board[i][j].type && !vis.count({ip, j})
			     && board[ip][j].func != FUNC_SUPER; ip++)
			{
				ilen++;
				tCrossActor.push_back(ActorInfo(ip, j));
			}
			for (int ip = i - 1; ip >= 0 && board[ip][j].type == board[i][j].type && !vis.count({ip, j}) &&
			     board[ip][j].func != FUNC_SUPER; ip--)
			{
				ilen++;
				tCrossActor.push_back(ActorInfo(ip, j));
			}
			for (int jp = j + 1; jp < BOARD_SIZE && board[i][jp].type == board[i][j].type && !vis.count({i, jp})
			     && board[i][jp].func != FUNC_SUPER; jp++)
			{
				jlen++;
				tCrossActor.push_back(ActorInfo(i, jp));
			}
			for (int jp = j - 1; jp >= 0 && board[i][jp].type == board[i][j].type && !vis.count({i, jp}) &&
			     board[i][jp].func != FUNC_SUPER; jp--)
			{
				jlen++;
				tCrossActor.push_back(ActorInfo(i, jp));
			}
			if (ilen == 3 && jlen == 3)
			{
				rtn.push_back({{i, j}, doubleThree, tCrossActor, {ActorInfo(i, j, board[i][j].type, FUNC_FIRE)}});
			}
			else if (ilen >= 3 && jlen >= 3)
			{
				rtn.push_back({{i, j}, otherDouble, tCrossActor, {ActorInfo(i, j, board[i][j].type, FUNC_SUPER)}});
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
				&& (board[i - 1][j].type == board[i][j].type && board[i][j].type == board[i + 1][j].type
					&& board[i][j].type == board[i + 2][j].type && board[i][j].type == board[i - 2][j].
					type)
				&& (board[i - 1][j].func != FUNC_SUPER && board[i][j].func != FUNC_SUPER && board[i + 1][j].
					func != FUNC_SUPER && board[i + 2][j].func != FUNC_SUPER && board[i - 2][j].func !=
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
					{i, j}, fiveScore,
					{
						ActorInfo(i - 1, j), ActorInfo(i, j), ActorInfo(i + 1, j), ActorInfo(i + 2, j),
						ActorInfo(i - 2, j)
					},
					{ActorInfo(i, j, board[i][j].type, FUNC_H_3)}
				});
			}
			if ((j > 1 && j < BOARD_SIZE - 2)
				&& (board[i][j - 1].type == board[i][j].type && board[i][j].type == board[i][j + 1].type
					&& board[i][j].type == board[i][j + 2].type && board[i][j].type == board[i][j - 2].
					type)
				&& (board[i][j - 1].func != FUNC_SUPER && board[i][j].func != FUNC_SUPER && board[i][j + 1].
					func != FUNC_SUPER && board[i][j + 2].func != FUNC_SUPER && board[i][j - 2].func !=
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
					{i, j}, fiveScore,
					{
						ActorInfo(i, j - 1), ActorInfo(i, j), ActorInfo(i, j + 1), ActorInfo(i, j + 2),
						ActorInfo(i, j - 2)
					},
					{ActorInfo(i, j, board[i][j].type, FUNC_V_3)}
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
				&& (board[i - 1][j].type == board[i][j].type && board[i][j].type == board[i + 1][j].type
					&& board[i][j].type == board[i + 2][j].type)
				&& (board[i - 1][j].func != FUNC_SUPER && board[i][j].func != FUNC_SUPER && board[i + 1][j].
					func != FUNC_SUPER && board[i + 2][j].func != FUNC_SUPER)
				&& (!vis.count({i - 1, j}) && !vis.count({i, j}) && !vis.count({i + 1, j}) && !vis.count({i + 2, j})))
			{
				vis.insert({i - 1, j});
				vis.insert({i, j});
				vis.insert({i + 1, j});
				vis.insert({i + 2, j});
				rtn.push_back({
					{i, j}, fourScore, {ActorInfo(i - 1, j), ActorInfo(i, j), ActorInfo(i + 1, j), ActorInfo(i + 2, j)},
					{ActorInfo(i, j, board[i][j].type, FUNC_H_1)}
				});
			}
			if ((j > 0 && j < BOARD_SIZE - 2)
				&& (board[i][j - 1].type == board[i][j].type && board[i][j].type == board[i][j + 1].type
					&& board[i][j].type == board[i][j + 2].type)
				&& (board[i][j - 1].func != FUNC_SUPER && board[i][j].func != FUNC_SUPER && board[i][j + 1].
					func != FUNC_SUPER && board[i][j + 2].func != FUNC_SUPER)
				&& (!vis.count({i, j - 1}) && !vis.count({i, j}) && !vis.count({i, j + 1}) && !vis.count({i, j + 2})))
			{
				vis.insert({i, j - 1});
				vis.insert({i, j});
				vis.insert({i, j + 1});
				vis.insert({i, j + 2});
				rtn.push_back({
					{i, j}, fourScore, {ActorInfo(i, j - 1), ActorInfo(i, j), ActorInfo(i, j + 1), ActorInfo(i, j + 2)},
					{ActorInfo(i, j, board[i][j].type, FUNC_V_1)}
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
				&& (board[i - 1][j].type == board[i][j].type && board[i][j].type == board[i + 1][j].type
				)
				&& (board[i - 1][j].func != FUNC_SUPER && board[i][j].func != FUNC_SUPER && board[i + 1][j].
					func != FUNC_SUPER)
				&& (!vis.count({i - 1, j}) && !vis.count({i, j}) && !vis.count({i + 1, j})))
			{
				vis.insert({i - 1, j});
				vis.insert({i, j});
				vis.insert({i + 1, j});
				rtn.push_back({{i, j}, threeScore, {ActorInfo(i - 1, j), ActorInfo(i, j), ActorInfo(i + 1, j)}, {}});
			}
			if ((j > 0 && j < BOARD_SIZE - 1)
				&& (board[i][j - 1].type == board[i][j].type && board[i][j].type == board[i][j + 1].type
				)
				&& (board[i][j - 1].func != FUNC_SUPER && board[i][j].func != FUNC_SUPER && board[i][j + 1].
					func != FUNC_SUPER)
				&& (!vis.count({i, j - 1}) && !vis.count({i, j}) && !vis.count({i, j + 1})))
			{
				vis.insert({i, j - 1});
				vis.insert({i, j});
				vis.insert({i, j + 1});
				rtn.push_back({{i, j}, threeScore, {ActorInfo(i, j - 1), ActorInfo(i, j), ActorInfo(i, j + 1)}, {}});
			}
		}
	}

	return rtn;
}

void GameScene::trySwap(Pair blocka, Pair blockb)
{
	selectedHighLight->setPosition({9999, 9999});
	firstSelectedBlockIndex = {-1, -1};
	secondSelectedBlockIndex = {-1, -1};

	CCLOG("[LOCK] Try Swap (%d,%d),(%d,%d)", blocka.first, blocka.second, blockb.first, blockb.second);
	boardLock = true;

	// 如果交换的方块有特效方块
	if (board[blocka.first][blocka.second].func == FUNC_SUPER && board[blockb.first][blockb.second].func ==
		FUNC_SUPER)
	{
		Pair center = blocka;
		ActorInfoList tCrossActor;
		for (int i = 0; i < BOARD_SIZE; i++)
		{
			for (int j = 0; j < BOARD_SIZE; j++)
			{
				if (board[i][j].func == FUNC_SUPER) board[i][j].func = FUNC_NO;
				tCrossActor.push_back(ActorInfo(i, j));
			}
		}
		blockVanish({{center, 5000, tCrossActor, {}}});
		return;
	}
	else if (board[blocka.first][blocka.second].func == FUNC_SUPER || board[blocka.first][blocka.second].func ==
		FUNC_SUPER)
	{
		int toDelColor = -1;
		Pair center = {-1, -1};
		ActorInfoList tCrossActor;
		if (board[blocka.first][blocka.second].func == FUNC_SUPER)
		{
			board[blocka.first][blocka.second].func = -1;
			board[blocka.first][blocka.second].type = board[blockb.first][blockb.second].type;
			center = blocka;
			toDelColor = board[blockb.first][blockb.second].type;
		}
		else
		{
			board[blockb.first][blockb.second].func = -1;
			board[blockb.first][blockb.second].type = board[blocka.first][blocka.second].type;
			center = blockb;
			toDelColor = board[blocka.first][blocka.second].type;
		}
		for (int i = 0; i < BOARD_SIZE; i++)
		{
			for (int j = 0; j < BOARD_SIZE; j++)
			{
				if (board[i][j].type == toDelColor && board[i][j].func != FUNC_SUPER)
				{
					tCrossActor.push_back(ActorInfo(i, j));
				}
			}
		}
		//TODO: anim
		blockVanish({{center, 5000, tCrossActor, {}}});
		return;
	}


	swap(board[blocka.first][blocka.second], board[blockb.first][blockb.second]);
	auto rst = getKillList();
	swap(board[blocka.first][blocka.second], board[blockb.first][blockb.second]);

	if (rst.empty())
	{
		failSwap(blocka, blockb);
	}
	else
	{
		blockSwap(blocka, blockb);
	}
}

void GameScene::failSwap(Pair blocka, Pair blockb)
{
	Pair posa = getPositionByIndex(blocka);
	Pair posb = getPositionByIndex(blockb);

	board[blocka.first][blocka.second].actor->moveToThenBack(posb);
	board[blockb.first][blockb.second].actor->moveToThenBack(posa);

	runAction(Sequence::createWithTwoActions(DelayTime::create(.65f),
	                                         CCCallFunc::create([&]() { animationDoneCallback(); })));
}

void GameScene::blockSwap(Pair blocka, Pair blockb)
{
	minusStepNumber();
	Pair posa = getPositionByIndex(blocka);
	Pair posb = getPositionByIndex(blockb);

	board[blocka.first][blocka.second].actor->moveTo(posb);
	board[blockb.first][blockb.second].actor->moveTo(posa);

	swap(board[blocka.first][blocka.second], board[blockb.first][blockb.second]);

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
		showScore(killGroup.markValue, killGroup.markPoint);
		//1.2移除所有得分块
		for (ActorInfo toDelActorInfo : killGroup.killInfo)
		{
			//delete
			Pair pos = toDelActorInfo.pos;
			// TODO BUG
			assert(board[pos.first][pos.second].type != -1);
			if (board[pos.first][pos.second].func != -1)
			{
				specialActors.push_back({
					pos, board[pos.first][pos.second].type, board[pos.first][pos.second].func
				});
			}
			board[pos.first][pos.second].actor->selfClose();
			board[pos.first][pos.second] = Block();
			//placeDropper
			int ti = BOARD_SIZE;
			while (board[ti][pos.second].type != -1)
			{
				ti++;
				assert(ti < 2 * BOARD_SIZE);
			}
			int type = rand() % TYPE_NUMBER;
			auto droper = createActor(type, -1, getPositionByIndex({ti, pos.second}));
			board[ti][pos.second] = Block(type, -1, droper);
		}
		//1.3添加奖励特殊方块
		for (ActorInfo toAddActorInfo : killGroup.newInfo)
		{
			//create
			Pair pos = toAddActorInfo.pos;
			assert(board[pos.first][pos.second].type == -1);
			auto newActor = createActor(toAddActorInfo.type, toAddActorInfo.func, getPositionByIndex(pos));
			board[pos.first][pos.second] = Block(toAddActorInfo.type, toAddActorInfo.func, newActor);
			//deleteDropper
			int ti = 2 * BOARD_SIZE - 1;
			while (board[ti][pos.second].type == -1)
			{
				ti--;
				assert(ti >= BOARD_SIZE);
			}
			removeChild(board[ti][pos.second].actor);
			board[ti][pos.second] = Block();
		}
	}

	//处理特殊方块的消除
	if (specialActors.empty())
	{
		runAction(
			Sequence::createWithTwoActions(DelayTime::create(.3f), CCCallFunc::create([&]() { dropBlock(); })));
	}
	else
	{
		KillGroupList causedKillList;
		set<Pair> vis;

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
						if (board[i][j].type == -1 || vis.count({i, j}))continue;
						nowKill.killInfo.push_back(ActorInfo(i, j));
						if (board[i][j].func == FUNC_SUPER)board[i][j].type = specialActor.type;
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
						if (board[i][j].type == -1 || vis.count({i, j}))continue;
						nowKill.killInfo.push_back(ActorInfo(i, j));
						if (board[i][j].func == FUNC_SUPER)board[i][j].type = specialActor.type;
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
							if (board[i][j].type == -1 || vis.count({i, j}))continue;
							nowKill.killInfo.push_back(ActorInfo(i, j));
							if (board[i][j].func == FUNC_SUPER)board[i][j].type = specialActor.type;
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
							if (board[i][j].type == -1 || vis.count({i, j}))continue;
							nowKill.killInfo.push_back(ActorInfo(i, j));
							if (board[i][j].func == FUNC_SUPER)board[i][j].type = specialActor.type;
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
							if (i < 0 || i >= BOARD_SIZE)continue;
							if (j < 0 || j >= BOARD_SIZE)continue;
							if (board[i][j].type == -1 || vis.count({i, j}))continue;
							nowKill.killInfo.push_back(ActorInfo(i, j));
							if (board[i][j].func == FUNC_SUPER)board[i][j].type = specialActor.type;
							vis.insert({i, j});
						}
					}
					break;
				}
			case FUNC_SUPER:
				{
					int toDelColor = specialActor.type;
					Pair center = specialActor.pos;
					board[center.first][center.second].func = -1;

					for (int i = 0; i < BOARD_SIZE; i++)
					{
						for (int j = 0; j < BOARD_SIZE; j++)
						{
							if (board[i][j].type == toDelColor && board[i][j].func != FUNC_SUPER && !vis.count({
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

void GameScene::dropBlock()
{
	for (auto i = 0; i < BOARD_SIZE; i++)
		for (auto j = 0; j < BOARD_SIZE; j++)
		{
			if (board[i][j].type == -1)
			{
				auto upperI = i;
				while (board[upperI][j].type == -1)
				{
					upperI++;
					assert(upperI < 2 * BOARD_SIZE);
				}
				const auto nowBlock = getPositionByIndex({i, j});
				board[upperI][j].actor->dropTo(nowBlock);
				swap(board[i][j], board[upperI][j]);
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
		if (stepNumber == 0)
		{
			// TODO: 剩余次数为0
			// 练习模式不用判断
			// 其余模式要加判断currentScore和totalScore的关系
		}
			// 如果死局重新刷新面板
		else if (isDead())
		{
			refreshBoard();
			dropBlock();
			boardLock = false;
		}
		else
		{
			boardLock = false;
		}
	}
	else
	{
		blockVanish(newList);
	}
}

bool GameScene::isDead()
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if ((i > 0 && i < BOARD_SIZE - 1)
				&& (board[i - 1][j].type == board[i][j].type && board[i][j].type == board[i + 1][j].type
				)
				&& (board[i - 1][j].func != FUNC_SUPER && board[i][j].func != FUNC_SUPER && board[i + 1][j].
					func != FUNC_SUPER)
			)
			{
				return true;
			}
			if ((j > 0 && j < BOARD_SIZE - 1)
				&& (board[i][j - 1].type == board[i][j].type && board[i][j].type == board[i][j + 1].type
				)
				&& (board[i][j - 1].func != FUNC_SUPER && board[i][j].func != FUNC_SUPER && board[i][j + 1].
					func != FUNC_SUPER)
			)
			{
				return true;
			}
		}
	}
	return false;
}

validOperateList GameScene::getHintList()
{
	validOperateList rtn;
	auto beginTime = clock();

	//1ms
	for (int i = 1; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (board[i][j].func == FUNC_SUPER || board[i - 1][j].func == FUNC_SUPER)
			{
				rtn.push_back({{i, j}, {i - 1, j}});
				continue;
			}
			swap(board[i][j], board[i - 1][j]);
			if (isDead())rtn.push_back({{i, j}, {i - 1, j}});
			swap(board[i][j], board[i - 1][j]);
		}
	}
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 1; j < BOARD_SIZE; j++)
		{
			if (board[i][j].func == FUNC_SUPER || board[i][j - 1].func == FUNC_SUPER)
			{
				rtn.push_back({{i, j}, {i, j - 1}});
				continue;
			}
			swap(board[i][j], board[i][j - 1]);
			if (isDead())rtn.push_back({{i, j}, {i, j - 1}});
			swap(board[i][j], board[i][j - 1]);
		}
	}

	auto endTime = clock();

	CCLOG("Hit calc time: %dms.", endTime - beginTime);

	return rtn;
}

void GameScene::showScore(int value, Pair pos)
{
	auto labelScore = Label::createWithSystemFont(std::to_string(value), "Arial", 36);
	pos = getPositionByIndex(pos);
	labelScore->setPosition(pos.first, pos.second);
	labelScore->enableShadow(Color4B::ORANGE);
	labelScore->runAction(
		Sequence::create(
			Spawn::create(
				MoveBy::create(1.0f, {40, 40}),
				FadeOut::create(1.0f),
				NULL),
			CallFunc::create([&, labelScore]() { removeChild(labelScore); }),
			NULL
		));
	addChild(labelScore, 5);

	addCurrentScore(value);
}
