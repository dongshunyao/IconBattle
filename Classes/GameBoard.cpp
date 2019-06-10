#include "GameScene.h"

void GameScene::initGameBoard()
{
	// TODO 移动高亮图片修改
	moveHighLight = ImageView::create(theme->gameSceneMouseMoveOn);
	moveHighLight->setPosition(invisiblePosition);
	addChild(moveHighLight, 3);

	// TODO 选中高亮图片修改
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
	// 棋盘可点击范围在465~1165(width),90~790(height)，棋盘中心点为(793，419)
	if (position.first < 465 || position.first > 465 + 700) return {-1, -1};
	if (position.second < 90 || position.second > 90 + 700) return {-1, -1};
	// 宝石大小为64，与缝隙总长86
	return {(position.second - 90) / 86, (position.first - 465) / 86};
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

	ActorInformationList killActorList;

	// 均为Super块
	if (board[blockAIndex.first][blockAIndex.second].type == SUPER_TYPE && board[blockBIndex.first][blockBIndex.second].
		type == SUPER_TYPE)
	{
		for (auto i = 0; i < BOARD_SIZE; i++)
			for (auto j = 0; j < BOARD_SIZE; j++) killActorList.push_back(ActorInformation(i, j));
		killBlock({KillInformation(DOUBLE_SUPER_KILL, DOUBLE_SUPER_KILL_SCORE, killActorList)});
		return;
	}

	// 有一个Super块
	if (board[blockAIndex.first][blockAIndex.second].type == SUPER_TYPE)
	{
		for (auto i = 0; i < BOARD_SIZE; i++)
			for (auto j = 0; j < BOARD_SIZE; j++)
			{
				if (board[i][j].type == board[blockBIndex.first][blockBIndex.second].type)
					killActorList.push_back(ActorInformation(i, j));
			}
		killBlock({KillInformation(SUPER_KILL, SUPER_KILL_SCORE, killActorList)});
		return;
	}

	if (board[blockBIndex.first][blockBIndex.second].type == SUPER_TYPE)
	{
		for (auto i = 0; i < BOARD_SIZE; i++)
			for (auto j = 0; j < BOARD_SIZE; j++)
			{
				if (board[i][j].type == board[blockAIndex.first][blockAIndex.second].type)
					killActorList.push_back(ActorInformation(i, j));
			}
		killBlock({KillInformation(SUPER_KILL, SUPER_KILL_SCORE, killActorList)});
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
