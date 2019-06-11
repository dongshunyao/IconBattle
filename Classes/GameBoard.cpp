#include "GameScene.h"

void GameScene::initGameBoard()
{
	moveHighLight = ImageView::create(theme->gameSceneMouseMoveOn);
	moveHighLight->setPosition(invisiblePosition);
	addChild(moveHighLight, 3);

	selectedHighLight = ImageView::create(theme->gameSceneMouseSelected);
	selectedHighLight->setPosition(invisiblePosition);
	addChild(selectedHighLight, 5);

	// 鼠标监听
	auto mouseListener = EventListenerMouse::create();

	// 鼠标按下
	mouseListener->onMouseDown = [&](Event* event)
	{
		if (boardLock) return;

		const auto e = dynamic_cast<EventMouse*>(event);
		// 只按下左键为有效操作
		if (e->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT)
		{
			auto cursorX = e->getCursorX();
			auto cursorY = e->getCursorY();

			log("Click: Position %f, %f; Index %d, %d;", cursorX, cursorY, getIndexByPosition(Pair(cursorX, cursorY)));

			// 还未选中过方块
			if (firstSelectedBlockIndex == Pair(-1, -1))
			{
				firstSelectedBlockIndex = getIndexByPosition(Pair(cursorX, cursorY));
				selectedHighLight->setPosition(Vec2(getPositionByIndex(firstSelectedBlockIndex).first,
				                                    getPositionByIndex(firstSelectedBlockIndex).second));
			}
			else if (firstSelectedBlockIndex.first != -1 && secondSelectedBlockIndex.first == -1)
			{
				//已经选中一个方块
				secondSelectedBlockIndex = getIndexByPosition(Pair(cursorX, cursorY));
				// 判断第二方块是否相邻
				switch (secondSelectedBlockIndex.first - firstSelectedBlockIndex.first)
				{
				case 1:
				case -1:
					{
						// 不相邻，现选择的方块变为第一块
						if (firstSelectedBlockIndex.second != secondSelectedBlockIndex.second)
						{
							firstSelectedBlockIndex = getIndexByPosition(Pair(cursorX, cursorY));
							selectedHighLight->setPosition(Vec2(getPositionByIndex(firstSelectedBlockIndex).first,
							                                    getPositionByIndex(firstSelectedBlockIndex).second));
							secondSelectedBlockIndex = {-1, -1};
						}
						break;
					}

				case 0:
					{
						// 不相邻，现选择的方块变为第一块
						if (firstSelectedBlockIndex.second - secondSelectedBlockIndex.second != -1
							&& firstSelectedBlockIndex.second - secondSelectedBlockIndex.second != 1)
						{
							firstSelectedBlockIndex = getIndexByPosition(Pair(cursorX, cursorY));
							selectedHighLight->setPosition(Vec2(getPositionByIndex(firstSelectedBlockIndex).first,
							                                    getPositionByIndex(firstSelectedBlockIndex).second));
							secondSelectedBlockIndex = {-1, -1};
						}
						break;
					}

					// 不相邻，现选择的方块变为第一块
				default:
					{
						firstSelectedBlockIndex = getIndexByPosition(Pair(cursorX, cursorY));
						selectedHighLight->setPosition(Vec2(getPositionByIndex(firstSelectedBlockIndex).first,
						                                    getPositionByIndex(firstSelectedBlockIndex).second));
						secondSelectedBlockIndex = {-1, -1};
						break;
					}
				}
			}

			if (selectedHighLight->getPosition() == Vec2(409, 34)) selectedHighLight->setPosition(invisiblePosition);
		}
	};

	// 鼠标弹起
	mouseListener->onMouseUp = [&](Event* event)
	{
		const auto e = dynamic_cast<EventMouse*>(event);
		// 只弹起左键为有效操作
		if (e->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT)
		{
			// 已经选中两块则尝试交换，否则不进行操作
			if (firstSelectedBlockIndex != Pair(-1, -1) && secondSelectedBlockIndex != Pair(-1, -1))
				trySwapBlock(firstSelectedBlockIndex, secondSelectedBlockIndex);
		}
	};

	// 鼠标移动
	mouseListener->onMouseMove = [&](Event* event)
	{
		const auto e = dynamic_cast<EventMouse*>(event);
		auto cursorX = e->getCursorX();
		auto cursorY = e->getCursorY();
		if (e->getMouseButton() == EventMouse::MouseButton::BUTTON_UNSET)
		{
			if (boardLock)
			{
				moveHighLight->setPosition(invisiblePosition);
				return;
			}

			const auto block = getIndexByPosition(Pair(cursorX, cursorY));
			if (block != Pair(-1, -1))
			{
				const auto position = getPositionByIndex(block);
				moveHighLight->setPosition(Vec2(position.first, position.second));
			}
			else moveHighLight->setPosition(invisiblePosition);
		}
	};

	// 添加监听器
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, this);

	// 刷新棋盘并下落开始
	refreshBoard();
	runAction(Sequence::createWithTwoActions(DelayTime::create(1.1f), CallFunc::create([&]() { dropBlock(); })));
}

Actor* GameScene::addActor(const int type, const Pair position)
{
	const auto actor = Actor::create(type, position);
	addChild(actor, 1);
	return actor;
}

Pair GameScene::getPositionByIndex(const Pair index)
{
	// (495,120)为左下角第一个宝石的中心坐标
	return {495 + 86 * index.second, 120 + 86 * index.first};
}

Pair GameScene::getIndexByPosition(const Pair position)
{
	// 棋盘可点击范围在452~1140(width),77~765(height)，棋盘中心点为(796，421)
	if (position.first <= 452 || position.first >= 452 + 688) return {-1, -1};
	if (position.second <= 77 || position.second >= 77 + 688) return {-1, -1};

	// 宝石大小为64，与缝隙总长86
	auto xIndex = (position.second - 77) / 86, yIndex = (position.first - 452) / 86;

	assert(xIndex >= 0 && xIndex <= 7);
	assert(yIndex >= 0 && yIndex <= 7);

	return {xIndex, yIndex};
}

void GameScene::refreshBoard()
{
	// 下半部置空
	for (auto i = 0; i < 2 * BOARD_SIZE; i++)
		for (auto j = 0; j < BOARD_SIZE; j++)
		{
			if (board[i][j].type != -1)
			{
				removeChild(board[i][j].actor);
				// 强制回收
				// board[i][j].actor->release();
			}
			board[i][j] = Block();
		}

	// 上半部生成
	for (auto i = BOARD_SIZE; i < 2 * BOARD_SIZE; i++)
		for (auto j = 0; j < BOARD_SIZE; j++)
		{
			// 禁止块
			const auto banX = i >= BOARD_SIZE + 2 && board[i - 1][j].type == board[i - 2][j].type
				                  ? board[i - 2][j].type
				                  : -1;
			const auto banY = j >= 2 && board[i][j - 1].type == board[i][j - 2].type
				                  ? board[i][j - 2].type
				                  : -1;
			auto type = getRandomNumber(TYPE_NUMBER);
			while (type == banX || type == banY) type = getRandomNumber(TYPE_NUMBER);

			board[i][j] = Block(type, addActor(type, getPositionByIndex({i, j})));
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
	                                         CallFunc::create([&]() { mainCallback(); })));
}

bool GameScene::canKill() const
{
	for (auto i = 0; i < BOARD_SIZE; i++)
		for (auto j = 0; j < BOARD_SIZE; j++)
		{
			if (i > 0 && i < BOARD_SIZE - 1 &&
				(board[i - 1][j].type == board[i][j].type && board[i][j].type == board[i + 1][j].type))
				return true;

			if (j > 0 && j < BOARD_SIZE - 1 &&
				(board[i][j - 1].type == board[i][j].type && board[i][j].type == board[i][j + 1].type))
				return true;
		}

	return false;
}

bool GameScene::canKill(const Pair blockAIndex, const Pair blockBIndex)
{
	swap(board[blockAIndex.first][blockAIndex.second], board[blockBIndex.first][blockBIndex.second]);
	const auto flag = canKill();
	swap(board[blockAIndex.first][blockAIndex.second], board[blockBIndex.first][blockBIndex.second]);
	return flag;
}

void GameScene::trySwapBlock(const Pair blockAIndex, const Pair blockBIndex)
{
	selectedHighLight->setPosition(invisiblePosition);
	firstSelectedBlockIndex = {-1, -1};
	secondSelectedBlockIndex = {-1, -1};

	minusStepNumber();
	boardLock = true;
	log("[LOCK] Try Swap: 1st (%d,%d), 2ed (%d,%d)", blockAIndex.first, blockAIndex.second, blockBIndex.first,
	    blockBIndex.second);

	ActorInformationList actorList;

	// 均为Super块
	if (board[blockAIndex.first][blockAIndex.second].type == SUPER_TYPE && board[blockBIndex.first][blockBIndex.second].
		type == SUPER_TYPE)
	{
		for (auto i = 0; i < BOARD_SIZE; i++)
			for (auto j = 0; j < BOARD_SIZE; j++) actorList.push_back(ActorInformation(i, j));
		killBlock({KillInformation(DOUBLE_SUPER_KILL, DOUBLE_SUPER_KILL_SCORE, actorList)});
		return;
	}

	// 有一个Super块
	if (board[blockAIndex.first][blockAIndex.second].type == SUPER_TYPE)
	{
		for (auto i = 0; i < BOARD_SIZE; i++)
			for (auto j = 0; j < BOARD_SIZE; j++)
			{
				if (board[i][j].type == board[blockBIndex.first][blockBIndex.second].type)
					actorList.push_back(ActorInformation(i, j));
			}
		killBlock({KillInformation(SUPER_KILL, SUPER_KILL_SCORE, actorList)});
		return;
	}

	if (board[blockBIndex.first][blockBIndex.second].type == SUPER_TYPE)
	{
		for (auto i = 0; i < BOARD_SIZE; i++)
			for (auto j = 0; j < BOARD_SIZE; j++)
			{
				if (board[i][j].type == board[blockAIndex.first][blockAIndex.second].type)
					actorList.push_back(ActorInformation(i, j));
			}
		killBlock({KillInformation(SUPER_KILL, SUPER_KILL_SCORE, actorList)});
		return;
	}

	if (canKill(blockAIndex, blockBIndex)) swapSuccess(blockAIndex, blockBIndex);
	else swapFail(blockAIndex, blockBIndex);
}

HintOperation GameScene::isImpasse()
{
	const auto beginTime = clock();

	for (auto i = 0; i < BOARD_SIZE; i++)
		for (auto j = 0; j < BOARD_SIZE; j++)
			if (board[i][j].type == SUPER_TYPE)
			{
				log("Hit: Use %d ms; Super (%d, %d);", clock() - beginTime, i, j);
				return {{i, j}, {-1, -1}};
			}

	for (auto i = 1; i < BOARD_SIZE; i++)
		for (auto j = 0; j < BOARD_SIZE; j++)
			if (canKill({i, j}, {i - 1, j}))
			{
				log("Hit: Use %d ms; Normal (%d, %d), (%d, %d);", clock() - beginTime, i, j, i - 1, j);
				return {{i, j}, {i - 1, j}};
			}

	for (auto i = 0; i < BOARD_SIZE; i++)
		for (auto j = 1; j < BOARD_SIZE; j++)
			if (canKill({i, j}, {i, j - 1}))
			{
				log("Hit: Use %d ms; Normal (%d, %d), (%d, %d);", clock() - beginTime, i, j, i, j - 1);
				return {{i, j}, {i, j - 1}};
			}

	log("Impasse: Use %d ms;", clock() - beginTime);
	return {{-1, -1}, {-1, -1}};
}

bool GameScene::showHint()
{
	if (boardLock) return false;

	boardLock = true;
	const auto hint = isImpasse();
	log("[LOCK] Hint: (%d, %d); (%d, %d);", hint.first.first, hint.first.second, hint.second.first, hint.second.second);

	assert(hint != HintOperation({-1, -1},{-1,-1}));

	showSingleParticle(hint.first, 1);
	if (hint.second != Pair(-1, -1)) showSingleParticle(hint.second, 1);

	boardLock = false;
	log("[UNLOCK] Hint");
	return true;
}

void GameScene::swapSuccess(const Pair blockAIndex, const Pair blockBIndex)
{
	board[blockAIndex.first][blockAIndex.second].actor->moveTo(getPositionByIndex(blockBIndex));
	board[blockBIndex.first][blockBIndex.second].actor->moveTo(getPositionByIndex(blockAIndex));

	swap(board[blockAIndex.first][blockAIndex.second], board[blockBIndex.first][blockBIndex.second]);

	runAction(Sequence::createWithTwoActions(DelayTime::create(0.4f),
	                                         CallFunc::create([&]() { mainCallback(); })));
}

void GameScene::swapFail(const Pair blockAIndex, const Pair blockBIndex)
{
	board[blockAIndex.first][blockAIndex.second].actor->moveToAndBack(getPositionByIndex(blockBIndex));
	board[blockBIndex.first][blockBIndex.second].actor->moveToAndBack(getPositionByIndex(blockAIndex));

	runAction(Sequence::createWithTwoActions(DelayTime::create(0.65f),
	                                         CallFunc::create([&]() { mainCallback(); })));
}

void GameScene::mainCallback()
{
	if (canKill())
	{
		log("[CAN_KILL]");
		killBlock(getKillList());
	}
	else
	{
		if (stepNumber == 0 || currentScore >= totalScore)
		{
			log("[END]");
			endGame();
			return;
		}

		if (isImpasse() == HintOperation({-1, -1}, {-1, -1}))
		{
			log("[IMPASSE]");
			refreshBoard();
			dropBlock();
			return;
		}

		log("[UNLOCK]");
		boardLock = false;
	}
}

KillInformationList GameScene::getKillList() const
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
				&& (!visit.count({i, j}) &&
					!visit.count({i + 1, j}) &&
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
				&& (!visit.count({i, j}) &&
					!visit.count({i, j + 1}) &&
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


	// 检查四消
	for (auto i = 0; i < BOARD_SIZE; i++)
		for (auto j = 0; j < BOARD_SIZE; j++)
		{
			if (board[i][j].type == SUPER_TYPE || visit.count({i, j})) continue;

			// 竖直
			if (i > 0 && i < BOARD_SIZE - 2
				&& (board[i][j].type == board[i + 1][j].type &&
					board[i][j].type == board[i + 2][j].type &&
					board[i][j].type == board[i - 1][j].type)
				&& (!visit.count({i, j}) &&
					!visit.count({i + 1, j}) &&
					!visit.count({i + 2, j}) &&
					!visit.count({i - 1, j})))
			{
				visit.insert({i, j});
				visit.insert({i + 1, j});
				visit.insert({i + 2, j});
				visit.insert({i - 1, j});

				ActorInformationList actorList;
				for (auto iIndex = 0; iIndex < BOARD_SIZE; iIndex++) actorList.push_back({iIndex, j});

				killList.push_back({FOUR_VERTICAL_KILL, FOUR_KILL_SCORE, actorList});
			}

			// 水平
			if (j > 0 && j < BOARD_SIZE - 2
				&& (board[i][j].type == board[i][j + 1].type &&
					board[i][j].type == board[i][j + 2].type &&
					board[i][j].type == board[i][j - 1].type)
				&& (!visit.count({i, j}) &&
					!visit.count({i, j + 1}) &&
					!visit.count({i, j + 2}) &&
					!visit.count({i, j - 1})))
			{
				visit.insert({i, j});
				visit.insert({i, j + 1});
				visit.insert({i, j + 2});
				visit.insert({i, j - 1});

				ActorInformationList actorList;
				for (auto jIndex = 0; jIndex < BOARD_SIZE; jIndex++) actorList.push_back({i, jIndex});

				killList.push_back({FOUR_HORIZONTAL_KILL, FOUR_KILL_SCORE, actorList});
			}
		}


	// 检查三消
	for (auto i = 0; i < BOARD_SIZE; i++)
		for (auto j = 0; j < BOARD_SIZE; j++)
		{
			if (board[i][j].type == SUPER_TYPE || visit.count({i, j})) continue;

			// 竖直
			if (i > 0 && i < BOARD_SIZE - 1
				&& (board[i][j].type == board[i + 1][j].type &&
					board[i][j].type == board[i - 1][j].type)
				&& (!visit.count({i, j}) &&
					!visit.count({i + 1, j}) &&
					!visit.count({i - 1, j})))
			{
				visit.insert({i, j});
				visit.insert({i + 1, j});
				visit.insert({i - 1, j});

				killList.push_back({
					BASE_VERTICAL_KILL,
					BASE_KILL_SCORE,
					{
						ActorInformation(i, j),
						ActorInformation(i + 1, j),
						ActorInformation(i - 1, j)
					}
				});
			}

			// 水平
			if (j > 0 && j < BOARD_SIZE - 1
				&& (board[i][j].type == board[i][j + 1].type &&
					board[i][j].type == board[i][j - 1].type
				)
				&& (!visit.count({i, j}) &&
					!visit.count({i, j + 1}) &&
					!visit.count({i, j - 1})))
			{
				visit.insert({i, j});
				visit.insert({i, j + 1});
				visit.insert({i, j - 1});

				killList.push_back({
					BASE_HORIZONTAL_KILL,
					BASE_KILL_SCORE,
					{
						ActorInformation(i, j),
						ActorInformation(i, j + 1),
						ActorInformation(i, j - 1)
					}
				});
			}
		}


	return killList;
}

void GameScene::killBlock(const KillInformationList& killList)
{
	// 所有被消除的块与得分
	map<Pair, int> killBlock;


	// 记录所有得分块
	for (const auto& killInfo : killList)
		for (const auto& actorInfo : killInfo.killActorList) killBlock[actorInfo.blockIndex] += killInfo.killScore;


	// 消除所有得分块
	for (const auto& block : killBlock)
	{
		const auto blockIndex = block.first;

		// 展示分数
		showScore(ActorInformation(blockIndex, -1, block.second));

		board[blockIndex.first][blockIndex.second].actor->disappear();
		board[blockIndex.first][blockIndex.second] = Block();

		// 产生下落块
		auto iIndex = BOARD_SIZE;
		while (board[iIndex][blockIndex.second].type != -1)
		{
			iIndex++;
			assert(iIndex < 2 * BOARD_SIZE);
		}
		const auto type = getRandomNumber(TYPE_NUMBER);
		const auto nowBlock = addActor(type, getPositionByIndex({iIndex, blockIndex.second}));
		board[iIndex][blockIndex.second] = Block(type, nowBlock);
	}

	// 添加Super块
	for (const auto& killInfo : killList)
	{
		if (killInfo.newBlockIndex != Pair(-1, -1))
		{
			const auto newActor = addActor(SUPER_TYPE, getPositionByIndex(killInfo.newBlockIndex));
			board[killInfo.newBlockIndex.first][killInfo.newBlockIndex.second] = Block(SUPER_TYPE, newActor);

			// 删除下落块
			auto iIndex = 2 * BOARD_SIZE - 1;
			while (board[iIndex][killInfo.newBlockIndex.second].type == -1)
			{
				iIndex--;
				assert(iIndex >= BOARD_SIZE);
			}
			removeChild(board[iIndex][killInfo.newBlockIndex.second].actor);
			board[iIndex][killInfo.newBlockIndex.second] = Block();
		}
	}

	// 放特效
	for (const auto& killInfo : killList)
	{
		switch (killInfo.killType)
		{
		case FOUR_HORIZONTAL_KILL:
			showOneLineParticle(killInfo.killActorList[0].blockIndex, false);
			break;

		case FOUR_VERTICAL_KILL:
			showOneLineParticle(killInfo.killActorList[0].blockIndex, true);
			break;

		case FIVE_HORIZONTAL_KILL:
			{
				set<int> index;
				for (const auto& actor : killInfo.killActorList) index.insert(actor.blockIndex.first);
				for (auto it : index) showOneLineParticle({it, 0}, false);
				break;
			}

		case FIVE_VERTICAL_KILL:
			{
				set<int> index;
				for (const auto& actor : killInfo.killActorList) index.insert(actor.blockIndex.second);
				for (auto it : index) showOneLineParticle({0, it}, true);
				break;
			}

		case DOUBLE_BASE_KILL:
			{
				auto iIndex = 3 * BOARD_SIZE, jIndex = 3 * BOARD_SIZE;
				for (const auto& actor : killInfo.killActorList)
				{
					if (actor.blockIndex.first < iIndex) iIndex = actor.blockIndex.first;
					if (actor.blockIndex.second < jIndex) jIndex = actor.blockIndex.second;
				}

				showExplosion({iIndex + 1, jIndex + 1});
				break;
			}

		case SUPER_KILL:
			for (const auto& actor : killInfo.killActorList) showSingleParticle(actor.blockIndex, 0);
			break;

		case DOUBLE_SUPER_KILL:
			showFullBoardParticle();
			break;
		}
	}

	runAction(Sequence::create(DelayTime::create(0.3f), CallFunc::create([&]() { dropBlock(); }), nullptr));
}
