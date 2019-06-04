#include "GameScene.h"

void GameScene::initGameBoard()
{
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

			// TODO 选中标识动画+图层

			// 还未选中过方块
			if (firstSelectedBlock == Pair(-1, -1)) firstSelectedBlock = getIndexByPosition(Pair(cursorX, cursorY));
				//已经选中一个方块
			else if (firstSelectedBlock.first != -1 && secondSelectedBlock.first == -1)
			{
				secondSelectedBlock = getIndexByPosition(Pair(cursorX, cursorY));
				// 判断第二方块是否相邻
				switch (secondSelectedBlock.first - firstSelectedBlock.first)
				{
				case 1:
				case -1:
					{
						// 不相邻，现选择的方块变为第一块
						if (firstSelectedBlock.second != secondSelectedBlock.second)
						{
							firstSelectedBlock = getIndexByPosition(Pair(cursorX, cursorY));
							secondSelectedBlock = {-1, -1};
						}
						break;
					}

				case 0:
					{
						// 不相邻，现选择的方块变为第一块
						if (firstSelectedBlock.second - secondSelectedBlock.second != -1
							&& firstSelectedBlock.second - secondSelectedBlock.second != 1)
						{
							firstSelectedBlock = getIndexByPosition(Pair(cursorX, cursorY));
							secondSelectedBlock = {-1, -1};
						}
						break;
					}

					// 不相邻，现选择的方块变为第一块
				default:
					{
						firstSelectedBlock = getIndexByPosition(Pair(cursorX, cursorY));
						secondSelectedBlock = {-1, -1};
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
		// 只弹起左键为有效操作
		if (e->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT)
		{
			// 已经选中两块则尝试交换，否则不进行操作
			if (firstSelectedBlock != Pair(-1, -1) && secondSelectedBlock != Pair(-1, -1))
				trySwap(firstSelectedBlock, secondSelectedBlock);
		}
	};

	// 添加监听器
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, this);

	// 刷新棋盘并下落开始
	refreshBoard();
	newBlocksDrop();
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
	return Pair((position.second - 90) / 86, (position.first - 465) / 86);
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
			auto type = rand() % TYPE_NUMBER;
			while (type == banX || type == banY) type = rand() % TYPE_NUMBER;

			board[i][j] = Block(type, -1, createActor(type, -1, getPositionByIndex({ i, j })));
		}
}