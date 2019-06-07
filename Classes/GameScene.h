#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <set>
#include "Theme.h"
#include "User.h"
#include "GameBoardInformation.h"
#include "SettingButton.h"
#include "Dialog.h"
#include "NetworkShare.h"
#include "MenuScene.h"
#include "LevelScene.h"

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 900

using std::swap;
using std::set;

using namespace GameBoardInformation;
using namespace Util;
using namespace NetworkShare;
USING_NS_CC;

/*
 * 图层顺序
 * 从底到顶
 * -1层 宝石的背景板
 * 1+层 宝石 宝石1 选中高亮3 移动高亮5
 * 10+层 主背景板+所有按钮
 * 15+层 所有特效
 * 20+层 结算结果框
 * 30+层 返回提示框
 */

class GameScene final :
	public Scene
{
public:
	static Scene* createScene(int stepNumber, int totalScore, bool isClassical, int mode, int hintNumber = 3);
	bool init() override { return Scene::init(); }
	CREATE_FUNC(GameScene)

private:
	bool isClassical = true;
	int mode = -1;
	Theme* theme = Theme::getInstance();

	// 显示得分
	void showScore(ActorInformation actorInformation);

	// 结束游戏
	void endGame();

#pragma region Information Board
	int stepNumber = 0;
	int hintNumber = 0;
	int totalScore = 0;
	int currentScore = 0;

	void setStepNumber(int step);
	// 剩余步数减一
	void minusStepNumber();
	void setTotalScore(int score);
	// 添加分数，可正可负
	void addCurrentScore(int deltaScore);

	Label* stepNumberLabel = nullptr;
	Label* totalScoreLabel = nullptr;
	Sprite* hintNumberSprite = nullptr;
	Label* currentScoreLabel = nullptr;
	Sprite* currentProgressBar = nullptr;
	ProgressTimer* progressController = nullptr;

	void initInformationBoard();

#pragma endregion

#pragma region Result Board
	bool isShareButtonAppear = false;

	void showFailedResult(int targetScore, int realScore);
	void showSuccessfulResult(int usedSteps, int usedHints);
	void showSuccessfulResult(bool isChallenge, int stepNumberScore, int hintNumberScore, int playerScore);

#pragma endregion

#pragma region Game Board

	// 棋盘
	static const int BOARD_SIZE = 8;
	// 块的种类，不含Super块
	static const int TYPE_NUMBER = 5;
	// 上方不可见，下方可见
	Block board[BOARD_SIZE * 2][BOARD_SIZE];
	// 棋盘锁：进行动画时锁定
	bool boardLock = true;

	// 鼠标移动高亮
	ImageView* moveHighLight = nullptr;
	// 选中块高亮
	ImageView* selectedHighLight = nullptr;
	// 当前先后选中的块
	Pair firstSelectedBlockIndex = {-1, -1};
	Pair secondSelectedBlockIndex = {-1, -1};


	// 初始化棋盘和鼠标监听器
	void initGameBoard();
	// 添加Actor
	Actor* addActor(int type, Pair position);

	// 由坐标得棋盘位置
	Pair getPositionByIndex(Pair index);
	// 由棋盘位置得坐标
	Pair getIndexByPosition(Pair position);

	// 刷新棋盘：上方BFS填充，下方置空
	void refreshBoard();
	// 上方块下落
	void dropBlock();
	// 尝试交换
	void trySwapBlock(Pair blockAIndex, Pair blockBIndex);

	// 判断当前局面是否有可消除块
	bool canKill() const;
	// 交换后判断是否有可消除块
	bool canKill(Pair blockAIndex, Pair blockBIndex);
	// HintOperation({-1, -1}, {-1, -1})表示当前死局，反之返回提示
	HintOperation isImpasse();
	// 展示提示
	bool showHint();

	// 交换失败
	void swapFail(Pair blockAIndex, Pair blockBIndex);
	// 交换成功
	void swapSuccess(Pair blockAIndex, Pair blockBIndex);

	// 主回调函数
	void mainCallback();
#pragma endregion


	// TODO 获取可消除方块列表
	KillInformationList getKillList() { return {}; };

	// TODO 方块消除动画
	void killBlock(KillInformationList killList) {};
};

#endif
