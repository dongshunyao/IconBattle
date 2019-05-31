#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "BackButton.h"
#include "SettingButton.h"
#include "Theme.h"
#include <algorithm>
#include  "StructNames.h"

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 900

using std::pair;
using std::swap;
using std::set;
using namespace StructNames;
USING_NS_CC;


class GameScene final :
	public cocos2d::Scene
{
public:

	static cocos2d::Scene* createScene();
	bool init() override;
	CREATE_FUNC(GameScene)

	// 接口函数
	void setTotalProgress(int total);
	void setCurrentProgress(int progress);
	void setRemainStep(int step);
	int getCurrentProgress() const;
	int getTotalProgress() const;
	int getRemainStep() const;
	int getHintNumber() const;


private:
	int steps = 40;
	int hint = 3;
	int totalProgress = 0;
	int currentProgress = 0;
	bool result = false;
	Theme* theme = Theme::getInstance();
	Label* remainStep = nullptr;
	Sprite* hintNumber = nullptr;
	Sprite* progressBarScore = nullptr;
	ProgressTimer* progressTimer = nullptr;
	Label* scoreLabel = nullptr;
	Sprite* firstSprite = nullptr;
	Sprite* secondSprite = nullptr;
	void judgeResult(); // 结果动画

	static const int BOARD_SIZE = 8;


	// 进行动画时锁定棋盘
	bool boardLocked = true;
	// 表示当前选中与否的两块
	pii selectedBlockF = {-1, -1};
	pii selectedBlockS = {-1, -1};

	blockInfo boardInfo[BOARD_SIZE * 2][BOARD_SIZE];

	// 建立布局，添加组件和鼠标监听器
	void initComponents();

	// 由坐标得位置
	pii getPosition(pii index);
	// 由位置得坐标
	pii getIndex(pii pos);

	Actor* createActor(int, int, pii);

	// 获取可消除方块列表
	KillGroupList getKillList();

	// 尝试两方快交换：若不可以交换则不做动画，反之进行
	void trySwap(pii block1, pii block2);
	// 无效交换动画
	void failSwap(pii blocka, pii blockb);

	// 初始化棋盘，调用refreshBoard()
	void initBoard();
	// 刷新棋盘：上半部分BFS填充，下半部分-1初始化
	void refreshBoard();

	// 方块交换动画
	void blockSwap(pii blocka, pii blockb);
	// 方块消除动画
	void blockVanish(KillGroupList killList);
	// 消除后新产生方块下落动画
	void newBlocksDrop();

	// 消除并下落动画回调函数：
	// 检测若新棋盘无可消除则unlock，否则继续消除
	void animationDoneCallback();

	// 判断是否为死局
	bool isDead();
};

#endif
