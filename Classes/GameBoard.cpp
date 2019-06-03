#include "GameScene.h"

void GameScene::initGameBoard()
{
	//TODO addMouseListener
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
							selectedBlockS = { -1, -1 };
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
							selectedBlockS = { -1, -1 };
						}
						break;
					}

					// 不相邻，现选择的方块变为第一块
					default:
					{
						selectedBlockF = getIndex(pii(cursorX, cursorY));
						selectedBlockS = { -1, -1 };
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

	refreshBoard();
	newBlocksDrop();
}