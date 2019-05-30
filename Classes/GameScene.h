#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "BackButton.h"
#include "SettingButton.h"
#include "Theme.h"
#include <algorithm>

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 900

using std::pair;
USING_NS_CC;

typedef pair<int, Sprite*> BlockInfo;
typedef pair<int, int> Pii;

class GameScene final :
	public cocos2d::Scene
{
public:

	static cocos2d::Scene* createScene();
	bool init() override;
	CREATE_FUNC(GameScene)

	void setTotalProgress(int total);
	void setCurrentProgress(int progress);
	float getCurrentProgress() const;
	float getTotalProgress() const;


private:
	int hint = 3;
	int totalProgress = 0;
	int currentProgress = 0;
	bool result = false;
	Theme* theme = Theme::getInstance();
	Sprite* hintNumber = nullptr;
	Sprite* progressBarScore = nullptr;
	ProgressTimer* progressTimer = nullptr;
	Label* scoreLabel = nullptr;
	Sprite* firstSprite = nullptr;
	Sprite* secondSprite = nullptr;
	void judgeResult(); // 结果动画

	static const int BOARD_SIZE = 8;

	// 方块图片，后期移入Theme.h
	const string BLOCK_N[6] = {
		"/image/gamescene/jetbraintheme/iconset/large/1.png",
		"/image/gamescene/jetbraintheme/iconset/large/2.png",
		"/image/gamescene/jetbraintheme/iconset/large/3.png",
		"/image/gamescene/jetbraintheme/iconset/large/4.png",
		"/image/gamescene/jetbraintheme/iconset/large/5.png",
		"/image/gamescene/jetbraintheme/iconset/large/6.png"
	};

	// 进行动画时锁定棋盘
	bool boardLocked = true;
	// 表示当前选中与否的两块
	Pii selectedBlockF = {-1, -1};
	Pii selectedBlockS = {-1, -1};

	BlockInfo boardInfo[BOARD_SIZE * 2][BOARD_SIZE];

	// 建立布局，添加组件和鼠标监听器
	void initComponents();

	// 由坐标得位置
	Pii getPosition(Pii index);
	// 由位置得坐标
	Pii getIndex(Pii pos);

	Sprite* createSprite(int picType, Pii pos);

	// 获取可消除方块列表
	vector<pair<Pii, Pii>> getKillList();

	// 尝试两方快交换：若不可以交换则不做动画，反之进行
	void trySwap(Pii block1, Pii block2);

	// 初始化棋盘，调用refreshBoard()
	void initBoard();
	// 刷新棋盘：上半部分BFS填充，下半部分-1初始化
	void refreshBoard();

	// 方块交换动画
	void blockSwap(Pii blocka, Pii blockb);
	// 方块消除动画
	void blockVanish(vector<pair<Pii, Pii>> killList);
	// 消除后新产生方块下落动画
	void newBlocksDrop();

	// 消除并下落动画回调函数：
	// 检测若新棋盘无可消除则unlock，否则继续消除
	void animationDoneCallback();
};

#endif
