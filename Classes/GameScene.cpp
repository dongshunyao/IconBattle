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

pii GameScene::getPosition(pii index)
{
	return pii(495 + 86 * index.second, 120 + 86 * index.first); // (495,120)为左下角第一个宝石的中心坐标
}

pii GameScene::getIndex(pii pos)
{
	if (pos.first < 465 || pos.first > 465 + 700)return {-1, -1};
	// 棋盘可点击范围在465~1165(width),90~790(height)，棋盘中心点为(793，419)
	if (pos.second < 90 || pos.second > 90 + 700)return {-1, -1};
	return pii((pos.second - 90) / 86, (pos.first - 465) / 86); // 宝石大小为64，与缝隙总长86
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
		failSwap(blocka, blockb);
	}
	else
	{
		blockSwap(blocka, blockb);
	}
}

void GameScene::failSwap(pii blocka, pii blockb)
{
	pii posa = getPosition(blocka);
	pii posb = getPosition(blockb);

	boardInfo[blocka.first][blocka.second].actor->moveToThenBack(posb);
	boardInfo[blockb.first][blockb.second].actor->moveToThenBack(posa);

	runAction(Sequence::createWithTwoActions(DelayTime::create(.65f),
	                                         CCCallFunc::create([&]() { animationDoneCallback(); })));
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
		// 如果死局重新刷新面板
		if (isDead())
		{
			refreshBoard();
			newBlocksDrop();
		}
		else if (getHintList().size())
		{
			boardLocked = false;
		}
		else
		{
			// TODO: 次数用尽
		}
	}
	else
	{
		blockVanish(newList);
	}
}

bool GameScene::isDead()
{
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if ((i > 0 && i < BOARD_SIZE - 1)
				&& (boardInfo[i - 1][j].type == boardInfo[i][j].type && boardInfo[i][j].type == boardInfo[i + 1][j].type)
				&& (boardInfo[i - 1][j].func != FUNC_SUPER && boardInfo[i][j].func != FUNC_SUPER && boardInfo[i + 1][j].func != FUNC_SUPER)
				) {
				return true;
			}
			if ((j > 0 && j < BOARD_SIZE - 1)
				&& (boardInfo[i][j - 1].type == boardInfo[i][j].type && boardInfo[i][j].type == boardInfo[i][j + 1].type)
				&& (boardInfo[i][j - 1].func != FUNC_SUPER && boardInfo[i][j].func != FUNC_SUPER && boardInfo[i][j + 1].func != FUNC_SUPER)
				) {
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
	for (int i = 1; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (boardInfo[i][j].func == FUNC_SUPER || boardInfo[i - 1][j].func == FUNC_SUPER) {
				rtn.push_back({ {i,j} ,{i - 1,j} });
				continue;
			}
			swap(boardInfo[i][j], boardInfo[i - 1][j]);
			if (isDead())rtn.push_back({ {i,j} ,{i - 1,j} });
			swap(boardInfo[i][j], boardInfo[i - 1][j]);
		}
	}
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 1; j < BOARD_SIZE; j++) {
			if (boardInfo[i][j].func == FUNC_SUPER || boardInfo[i][j - 1].func == FUNC_SUPER) {
				rtn.push_back({ {i,j} ,{i,j - 1} });
				continue;
			}
			swap(boardInfo[i][j], boardInfo[i][j - 1]);
			if (isDead())rtn.push_back({ {i,j} ,{i,j - 1} });
			swap(boardInfo[i][j], boardInfo[i][j - 1]);
		}
	}

	auto endTime = clock();

	CCLOG("Hit calc time: %dms.", endTime - beginTime);

	return rtn;
}
