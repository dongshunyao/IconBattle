#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <set>
#include "Theme.h"
#include "User.h"
#include "GameBoardInformation.h"
#include "BackButton.h"
#include "SettingButton.h"
#include "Dialog.h"


#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 900


using std::swap;
using std::set;
using namespace GameBoardInformation;
using namespace Util;
USING_NS_CC;

/*
 * 图层顺序
 * 从底到顶
 * -1层 宝石的背景板
 * 1+层 宝石
 * 10+层 主背景板+所有按钮
 * 20+层 结算结果框
 * 30+层 返回提示框
 */

class GameScene final :
	public Scene
{
public:
	static Scene* createScene(int stepNumber, int totalScore, bool isClassical, int hintNumber = 3);
	bool init() override { return Scene::init(); }
	CREATE_FUNC(GameScene)

private:
	bool isClassical = true;
	bool isAppear = false;
	Theme* theme = Theme::getInstance();

#pragma region Information Board
	int stepNumber = 0;
	int hintNumber = 0;
	int totalScore = 0;
	int currentScore = 0;

	void setStepNumber(int step);
	// 剩余步数减一
	void minusStepNumber();
	void setTotalScore(int score);
	// 添加分数，可正可负，需要直接设置请另加方法
	void addCurrentScore(int deltaScore);

	Label* stepNumberLabel = nullptr;
	Sprite* hintNumberSprite = nullptr;
	Label* scoreLabel = nullptr;
	Sprite* currentProgressBar = nullptr;
	ProgressTimer* progressController = nullptr;

	void initInformationBoard();

#pragma endregion

#pragma region Result Board
	void showResult(bool result, int mode); // 0为练习模式，1为闯关模式，2为无尽模式

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
	ImageView* actorHighLight = nullptr;
	// 当前先后选中的块
	Pair firstSelectedBlock = {-1, -1};
	Pair secondSelectedBlock = {-1, -1};


	// 初始化棋盘和鼠标监听器
	void initGameBoard();

	// 由坐标得棋盘位置
	Pair getPositionByIndex(Pair index);
	// 由棋盘位置得坐标
	Pair getIndexByPosition(Pair position);

	// 刷新棋盘：上方BFS填充，下方置空
	void refreshBoard();
	// 上方块下落
	void dropBlock();

#pragma endregion

	// TODO 不同模式得分，待调整
	const int threeScore = 100;
	const int fourScore = 150;
	const int fiveScore = 200;
	const int doubleThree = 300;
	const int otherDouble = 500;
	const int super = 800;
	const int superKillScore = 10000;

	/*
	 * 标准模式：
	 * 三消 四消 五消 有交点的双三消 有交点的双三消+横或竖添加任意一至多个宝石
	 * 加强模式：
	 * 三消（threeKill）
	 * 横四消（fourKill）：直接清除在本行的所有宝石
	 * 竖四消：直接清除在本列的所有宝石
	 * 横五消（fiveKill）：直接清除在临近三行的所有宝石
	 * 竖五消：直接清除在临近三列的所有宝石
	 * 有交点的双三消（双三doubleThreeKill）：直接清除临近 3X3 的所有宝石
	 * 有交点的双三消+横或竖添加任意一至多个宝石（双四doubleFourKill）：生成SUPER宝石
	 * SUPER宝石与某个颜色交换（superKill）：消去整个画面中该颜色的宝石
	 * 两个SUPER交换（doubleSuperKill）：刷新棋盘
	 */


	Actor* createActor(int, int, Pair);

	// 获取可消除方块列表
	KillGroupList getKillList();

	// 尝试两方快交换：若不可以交换则不做动画，反之进行
	void trySwap(Pair block1, Pair block2);
	// 无效交换动画
	void failSwap(Pair blocka, Pair blockb);


	// 方块交换动画
	void blockSwap(Pair blocka, Pair blockb);
	// 方块消除动画
	void blockVanish(KillGroupList killList);


	// 消除并下落动画回调函数：
	// 检测若新棋盘无可消除则unlock，否则继续消除
	void animationDoneCallback();

	// 判断是否为死局
	bool isDead();
	// 得到提示
	validOperateList getHintList();

	// 显示得分动画
	void showScore(int value, Pair pos);
};

#endif
