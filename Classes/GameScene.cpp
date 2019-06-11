#include "GameScene.h"

Scene* GameScene::createScene(const int stepNumber, const int totalScore, const bool isClassical, const int mode,
                              const int level, const int hintNumber)
{
	const auto scene = GameScene::create();

	// 初始化变量
	scene->stepNumber = stepNumber;
	scene->totalScore = totalScore;
	scene->isClassical = isClassical;
	scene->hintNumber = hintNumber;
	scene->mode = mode;
	scene->level = level;

	// 初始化精灵图集
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("/image/common/adobetheme/icon/adobe.plist",
	                                                         "/image/common/adobetheme/icon/adobe.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("/image/common/jetbraintheme/icon/jetbrain.plist",
	                                                         "/image/common/jetbraintheme/icon/jetbrain.png");

	// 初始化背景板及按钮
	scene->initInformationBoard();

	// 初始化游戏
	scene->initGameBoard();

	return scene;
}

void GameScene::showScore(const ActorInformation actorInformation)
{
	// TODO 换字体？换颜色？
	auto scoreLabel = Label::createWithTTF(to_string(actorInformation.score), theme->semiBoldFont, 36);

	const auto position = getPositionByIndex(actorInformation.blockIndex);
	scoreLabel->setPosition(position.first, position.second);

	scoreLabel->enableShadow(Color4B::ORANGE);
	scoreLabel->runAction(Sequence::create(
		Spawn::create(MoveBy::create(1.0f, {40, 40}), FadeOut::create(1.0f), nullptr),
		CallFunc::create([&, scoreLabel]() { removeChild(scoreLabel); }), nullptr));

	addChild(scoreLabel, 19);

	if (mode == CHALLENGE_MODE && currentScore + actorInformation.score >= 3 * totalScore / 4)
		setTotalScore(totalScore * 3 / 2);

	addCurrentScore(actorInformation.score);
}

void GameScene::endGame()
{
	// TODO 分数折合动画
	switch (mode)
	{
		// 练习模式一定会成功的
	case PRACTICE_MODE:
		{
			const auto usedSteps = GameSceneController::getInstance()->classicalPractice.second - stepNumber;
			showSuccessfulResult(usedSteps, 3 - hintNumber);
			break;
		}

	case LEVEL_MODE:
		{
			const auto stepNumberScore = EVERY_STEP_SCORE * stepNumber;
			const auto hintNumberScore = EVERY_HINT_SCORE * hintNumber;

			// 失败
			if (currentScore + stepNumberScore + hintNumberScore < totalScore)
			{
				showFailedResult(totalScore, currentScore);
				break;
			}

			// 成功
			showSuccessfulResult(false, stepNumberScore, hintNumberScore, currentScore);
			break;
		}
	case CHALLENGE_MODE:
		{
			const auto stepNumberScore = EVERY_STEP_SCORE * stepNumber;
			const auto hintNumberScore = EVERY_HINT_SCORE * hintNumber;

			// 成功
			showSuccessfulResult(true, stepNumberScore, hintNumberScore, currentScore);
			break;
		}
	}
}

/*
KillInformationList GameScene::getKillList()
{
	KillInformationList killList;
	set<Pair> visit;

	// 检查十字消
	for (auto i = 0; i < BOARD_SIZE; i++)
		for (auto j = 0; j < BOARD_SIZE; j++)
		{
			if (board[i][j].type == SUPER_TYPE || visit.count({i, j})) continue;

			auto iLength = 1, jLength = 1;
			ActorInformationList actorList;
			actorList.push_back(ActorInformation(i, j));

			for (auto iIndex = i + 1;
			     iIndex < BOARD_SIZE && board[iIndex][j].type == board[i][j].type && !visit.count({iIndex, j});
			     iIndex++)
			{
				iLength++;
				actorList.push_back(ActorInformation(iIndex, j));
			}
			for (auto iIndex = i - 1;
			     iIndex >= 0 && board[iIndex][j].type == board[i][j].type && !visit.count({iIndex, j});
			     iIndex--)
			{
				iLength++;
				actorList.push_back(ActorInformation(iIndex, j));
			}
			for (auto jIndex = j + 1;
			     jIndex < BOARD_SIZE && board[i][jIndex].type == board[i][j].type && !visit.count({i, jIndex});
			     jIndex++)
			{
				jLength++;
				actorList.push_back(ActorInformation(i, jIndex));
			}
			for (auto jIndex = j - 1;
			     jIndex >= 0 && board[i][jIndex].type == board[i][j].type && !visit.count({i, jIndex});
			     jIndex--)
			{
				jLength++;
				actorList.push_back(ActorInformation(i, jIndex));
			}
			// 双三
			if (iLength == 3 && jLength == 3)
			{
				// 找最小点，添加3*3
				ActorInformationList tempList;

				auto iIndex = 3 * BOARD_SIZE, jIndex = 3 * BOARD_SIZE;
				for (const auto& it : actorList)
				{
					if (it.blockIndex.first < iIndex) iIndex = it.blockIndex.first;
					if (it.blockIndex.second < jIndex) jIndex = it.blockIndex.second;
				}

				for (auto iDelta = 0; iDelta < 3; iDelta++)
					for (auto jDelta = 0; jDelta < 3; jDelta++) tempList.push_back({iIndex + iDelta, jIndex + jDelta});

				killList.push_back({DOUBLE_BASE_KILL, DOUBLE_BASE_KILL_SCORE, tempList});
			}
			else if (iLength >= 3 && jLength >= 3) // 双四
				killList.push_back({DOUBLE_FOUR_KILL, DOUBLE_FOUR_KILL_SCORE, actorList, {i, j}});

			if (iLength >= 3 && jLength >= 3)
				for (const auto& it : actorList) visit.insert(it.blockIndex);
		}


	// 检查五消
	for (auto i = 0; i < BOARD_SIZE; i++)
		for (auto j = 0; j < BOARD_SIZE; j++)
		{
			if (board[i][j].type == SUPER_TYPE || visit.count({i, j})) continue;

			// 竖直
			if (i > 1 && i < BOARD_SIZE - 2
				&& (board[i][j].type == board[i + 1][j].type &&
					board[i][j].type == board[i + 2][j].type &&
					board[i][j].type == board[i - 1][j].type &&
					board[i][j].type == board[i - 2][j].type)
				&& (!visit.count({i + 1, j}) &&
					!visit.count({i + 2, j}) &&
					!visit.count({i - 1, j}) &&
					!visit.count({i - 2, j})))
			{
				visit.insert({i, j});
				visit.insert({i + 1, j});
				visit.insert({i + 2, j});
				visit.insert({i - 1, j});
				visit.insert({i - 2, j});

				ActorInformationList actorList;
				if (j != 0)
					for (auto iIndex = 0; iIndex < BOARD_SIZE; iIndex++) actorList.push_back({iIndex, j - 1});
				if (j != BOARD_SIZE - 1)
					for (auto iIndex = 0; iIndex < BOARD_SIZE; iIndex++) actorList.push_back({iIndex, j + 1});
				for (auto iIndex = 0; iIndex < BOARD_SIZE; iIndex++) actorList.push_back({iIndex, j});

				killList.push_back({FIVE_VERTICAL_KILL, FIVE_KILL_SCORE, actorList});
			}

			// 水平
			if (j > 1 && j < BOARD_SIZE - 2
				&& (board[i][j].type == board[i][j + 1].type &&
					board[i][j].type == board[i][j + 2].type &&
					board[i][j].type == board[i][j - 1].type &&
					board[i][j].type == board[i][j - 2].type)
				&& (!visit.count({i, j + 1}) &&
					!visit.count({i, j + 2}) &&
					!visit.count({i, j - 1}) &&
					!visit.count({i, j - 2})))
			{
				visit.insert({i, j});
				visit.insert({i, j + 1});
				visit.insert({i, j + 2});
				visit.insert({i, j - 1});
				visit.insert({i, j - 2});

				ActorInformationList actorList;
				if (i != 0)
					for (auto jIndex = 0; jIndex < BOARD_SIZE; jIndex++) actorList.push_back({i - 1, jIndex});
				if (i != BOARD_SIZE - 1)
					for (auto jIndex = 0; jIndex < BOARD_SIZE; jIndex++) actorList.push_back({i + 1, jIndex});
				for (auto jIndex = 0; jIndex < BOARD_SIZE; jIndex++) actorList.push_back({i, jIndex});

				killList.push_back({FIVE_HORIZONTAL_KILL, FIVE_KILL_SCORE, actorList});
			}
		}


	// TODO 检查四消
	for (auto i = 0; i < BOARD_SIZE; i++)
		for (auto j = 0; j < BOARD_SIZE; j++)
		{
			if (board[i][j].type == SUPER_TYPE || visit.count({i, j})) continue;

			// 竖直
			if (i > 0 && i < BOARD_SIZE - 2
				&& (board[i][j].type == board[i + 1][j].type &&
					board[i][j].type == board[i + 2][j].type &&
					board[i][j].type == board[i - 1][j].type)
				&& (!visit.count({i + 1, j}) &&
					!visit.count({i + 2, j}) &&
					!visit.count({i - 1, j})))
			{
				visit.insert({i, j});
				visit.insert({i + 1, j});
				visit.insert({i + 2, j});
				visit.insert({i - 1, j});
				killList.push_back({
					{i, j}, FOUR_KILL_SCORE,
					{
						ActorInformation(i - 1, j), ActorInformation(i, j), ActorInformation(i + 1, j),
						ActorInformation(i + 2, j)
					},
					{ActorInformation(i, j, board[i][j].type, FUNC_H_1)}
				});
			}
			if ((j > 0 && j < BOARD_SIZE - 2)
				&& (board[i][j - 1].type == board[i][j].type && board[i][j].type == board[i][j + 1].type
					&& board[i][j].type == board[i][j + 2].type)
				&& (board[i][j - 1].func != FUNC_SUPER && board[i][j].func != FUNC_SUPER && board[i][j + 1].
					func != FUNC_SUPER && board[i][j + 2].func != FUNC_SUPER)
				&& (!visit.count({i, j - 1}) && !visit.count({i, j}) && !visit.count({i, j + 1}) && !visit.count({
					i, j + 2
				})))
			{
				visit.insert({i, j - 1});
				visit.insert({i, j});
				visit.insert({i, j + 1});
				visit.insert({i, j + 2});
				killList.push_back({
					{i, j}, FOUR_KILL_SCORE,
					{
						ActorInformation(i, j - 1), ActorInformation(i, j), ActorInformation(i, j + 1),
						ActorInformation(i, j + 2)
					},
					{ActorInformation(i, j, board[i][j].type, FUNC_V_1)}
				});
			}
		}


	//TODO check 3 link;
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if ((i > 0 && i < BOARD_SIZE - 1)
				&& (board[i - 1][j].type == board[i][j].type && board[i][j].type == board[i + 1][j].type
				)
				&& (board[i - 1][j].func != FUNC_SUPER && board[i][j].func != FUNC_SUPER && board[i + 1][j].
					func != FUNC_SUPER)
				&& (!visit.count({i - 1, j}) && !visit.count({i, j}) && !visit.count({i + 1, j})))
			{
				visit.insert({i - 1, j});
				visit.insert({i, j});
				visit.insert({i + 1, j});
				killList.push_back({
					{i, j}, threeScore,
					{ActorInformation(i - 1, j), ActorInformation(i, j), ActorInformation(i + 1, j)}, {}
				});
			}
			if ((j > 0 && j < BOARD_SIZE - 1)
				&& (board[i][j - 1].type == board[i][j].type && board[i][j].type == board[i][j + 1].type
				)
				&& (board[i][j - 1].func != FUNC_SUPER && board[i][j].func != FUNC_SUPER && board[i][j + 1].
					func != FUNC_SUPER)
				&& (!visit.count({i, j - 1}) && !visit.count({i, j}) && !visit.count({i, j + 1})))
			{
				visit.insert({i, j - 1});
				visit.insert({i, j});
				visit.insert({i, j + 1});
				killList.push_back({
					{i, j}, threeScore,
					{ActorInformation(i, j - 1), ActorInformation(i, j), ActorInformation(i, j + 1)}, {}
				});
			}
		}
	}

	return killList;
}


void GameScene::killBlock(KillInformationList killList)
{
	//移除过程中，检测到的被触发的特殊型宝石暂存于此
	ActorInformationList specialActors;

	//1:移除过程
	for (KillInformation killGroup : killList)
	{
		//1.1展示分数
		showScore(killGroup);
		//1.2移除所有得分块
		for (ActorInformation toDelActorInfo : killGroup.killActorList)
		{
			//delete
			Pair pos = toDelActorInfo.pos;

			assert(board[pos.first][pos.second].type != -1);
			if (board[pos.first][pos.second].func != -1)
			{
				specialActors.push_back({
					pos, board[pos.first][pos.second].type, board[pos.first][pos.second].func
				});
			}
			board[pos.first][pos.second].actor->disappear();
			board[pos.first][pos.second] = Block();
			//placeDropper
			int ti = BOARD_SIZE;
			while (board[ti][pos.second].type != -1)
			{
				ti++;
				assert(ti < 2 * BOARD_SIZE);
			}
			int type = getRandomNumber(TYPE_NUMBER);
			auto droper = addActor(type, -1, getPositionByIndex({ti, pos.second}));
			board[ti][pos.second] = Block(type, -1, droper);
		}
		//1.3添加奖励特殊方块
		for (ActorInformation toAddActorInfo : killGroup.newActorList)
		{
			//create
			Pair pos = toAddActorInfo.pos;
			assert(board[pos.first][pos.second].type == -1);
			auto newActor = addActor(toAddActorInfo.type, toAddActorInfo.func, getPositionByIndex(pos));
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
		KillInformationList causedKillList;
		set<Pair> vis;

		for (auto specialActor : specialActors)
		{
			KillInformation nowKill = {specialActor.pos, 114, {}, {}};
			switch (specialActor.func)
			{
			case FUNC_H_1:
				{
					int i = specialActor.pos.first;
					//showThunder_H(getPosition({ i,0 }).second);
					for (int j = 0; j < BOARD_SIZE; j++)
					{
						if (board[i][j].type == -1 || vis.count({i, j}))continue;
						nowKill.killActorList.push_back(ActorInformation(i, j));
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
						nowKill.killActorList.push_back(ActorInformation(i, j));
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
							nowKill.killActorList.push_back(ActorInformation(i, j));
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
							nowKill.killActorList.push_back(ActorInformation(i, j));
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
							nowKill.killActorList.push_back(ActorInformation(i, j));
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
								nowKill.killActorList.push_back(ActorInformation(i, j));
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
			                                         killBlock(causedKillList);
		                                         })));
	}
}
*/

void GameScene::showOneLineParticle(const Pair index, const bool isVertical)
{
	auto particle = ParticleSystemQuad::create(ONE_LINE_PARTICLE);

	particle->setPosition(getPositionByIndex(index).first, 85 + 700 / 2);
	if (!isVertical)
	{
		particle->setRotation(90);
		particle->setPosition(450 + 700 / 2, getPositionByIndex(index).second);
	}

	particle->setAutoRemoveOnFinish(true);
	addChild(particle, 17);
	// TODO: 粒子特效音效
}

void GameScene::showExplosion(const Pair index)
{
	auto particle = ParticleSystemQuad::create(EXPLOSION_PARTICLE);

	particle->setPosition(getPositionByIndex(index).first, getPositionByIndex(index).second);
	particle->setScale(0.7f);
	particle->setAutoRemoveOnFinish(true);
	addChild(particle, 17);
	// TODO: 粒子特效音效
}

void GameScene::showFullBoardParticle()
{
	auto particle = ParticleSystemQuad::create(FULL_PARTICLE);

	particle->setPosition(450 + 700 / 2, 85 + 700 / 2);
	particle->setScale(0.7f);
	particle->setAutoRemoveOnFinish(true);
	addChild(particle, 17);
	// TODO: 粒子特效音效
}

void GameScene::showSingleParticle(const Pair index, const int type)
{
	auto particle = ParticleSystemQuad::create(ONE_BLOCK_PARTICLE[type]);

	particle->setPosition(getPositionByIndex(index).first, getPositionByIndex(index).second);
	particle->setScale(0.6f);
	// 设置持续时间
	//particle->setDuration(3.0f);
	particle->setAutoRemoveOnFinish(true);
	addChild(particle, 17);
	// TODO: 粒子特效音效
}
