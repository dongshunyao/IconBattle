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
// TODO 
KillInformationList GameScene::getKillList()
{
	KillInformationList rtn;
	set<Pair> vis;

	//TODO: check cross;
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			int ilen = 1, jlen = 1;
			ActorInformationList tCrossActor;
			tCrossActor.push_back(ActorInformation(i, j));
			for (int ip = i + 1; ip < BOARD_SIZE && board[ip][j].type == board[i][j].type && !vis.count({ip, j})
			     && board[ip][j].func != FUNC_SUPER; ip++)
			{
				ilen++;
				tCrossActor.push_back(ActorInformation(ip, j));
			}
			for (int ip = i - 1; ip >= 0 && board[ip][j].type == board[i][j].type && !vis.count({ip, j}) &&
			     board[ip][j].func != FUNC_SUPER; ip--)
			{
				ilen++;
				tCrossActor.push_back(ActorInformation(ip, j));
			}
			for (int jp = j + 1; jp < BOARD_SIZE && board[i][jp].type == board[i][j].type && !vis.count({i, jp})
			     && board[i][jp].func != FUNC_SUPER; jp++)
			{
				jlen++;
				tCrossActor.push_back(ActorInformation(i, jp));
			}
			for (int jp = j - 1; jp >= 0 && board[i][jp].type == board[i][j].type && !vis.count({i, jp}) &&
			     board[i][jp].func != FUNC_SUPER; jp--)
			{
				jlen++;
				tCrossActor.push_back(ActorInformation(i, jp));
			}
			if (ilen == 3 && jlen == 3)
			{
				rtn.push_back({
					{i, j}, doubleThree, tCrossActor, {ActorInformation(i, j, board[i][j].type, FUNC_FIRE)}
				});
			}
			else if (ilen >= 3 && jlen >= 3)
			{
				rtn.push_back(
					{{i, j}, otherDouble, tCrossActor, {ActorInformation(i, j, board[i][j].type, FUNC_SUPER)}});
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
						ActorInformation(i - 1, j), ActorInformation(i, j), ActorInformation(i + 1, j),
						ActorInformation(i + 2, j),
						ActorInformation(i - 2, j)
					},
					{ActorInformation(i, j, board[i][j].type, FUNC_H_3)}
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
						ActorInformation(i, j - 1), ActorInformation(i, j), ActorInformation(i, j + 1),
						ActorInformation(i, j + 2),
						ActorInformation(i, j - 2)
					},
					{ActorInformation(i, j, board[i][j].type, FUNC_V_3)}
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
				&& (!vis.count({i, j - 1}) && !vis.count({i, j}) && !vis.count({i, j + 1}) && !vis.count({i, j + 2})))
			{
				vis.insert({i, j - 1});
				vis.insert({i, j});
				vis.insert({i, j + 1});
				vis.insert({i, j + 2});
				rtn.push_back({
					{i, j}, FOUR_KILL_SCORE,
					{
						ActorInformation(i, j - 1), ActorInformation(i, j), ActorInformation(i, j + 1),
						ActorInformation(i, j + 2)
					},
					{ActorInformation(i, j, board[i][j].type, FUNC_V_1)}
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
				rtn.push_back({
					{i, j}, threeScore,
					{ActorInformation(i - 1, j), ActorInformation(i, j), ActorInformation(i + 1, j)}, {}
				});
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
				rtn.push_back({
					{i, j}, threeScore,
					{ActorInformation(i, j - 1), ActorInformation(i, j), ActorInformation(i, j + 1)}, {}
				});
			}
		}
	}

	return rtn;
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
			int type =  getRandomNumber(TYPE_NUMBER);
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

	// TODO: 坐标位置未测试，有待调整
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
	particle->setAutoRemoveOnFinish(true);
	addChild(particle, 17);
	// TODO: 粒子特效音效
}
