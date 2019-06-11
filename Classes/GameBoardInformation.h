#ifndef __GAME_BOARD_INFORMATION_H__
#define __GAME_BOARD_INFORMATION_H__

#include <vector>
#include "Theme.h"
#include "cocos2d.h"

using std::pair;
using std::string;
using std::vector;
USING_NS_CC;

namespace GameBoardInformation
{
	// Super块编号
	const int SUPER_TYPE = 5;

	// 游戏模式
	static const int PRACTICE_MODE = 1;
	static const int LEVEL_MODE = 2;
	static const int CHALLENGE_MODE = 3;

	// TODO 粒子特效文件
	const string ONE_LINE_PARTICLE = "/particle/oneLine.plist";
	const string EXPLOSION_PARTICLE = "/particle/explosion.plist";
	const string FULL_PARTICLE = "/particle/fullBoard.plist";
	const string ONE_BLOCK_PARTICLE[2] = {
		"/particle/single.plist",
		"/particle/hint.plist"
	};

	typedef pair<int, int> Pair;

	// 宝石块
	struct Block;
	// 精灵演员
	class Actor;

	// 演员信息
	struct ActorInformation;
	typedef vector<ActorInformation> ActorInformationList;

	// 消除组
	struct KillInformation;
	typedef vector<KillInformation> KillInformationList;

	// 提示
	typedef pair<Pair, Pair> HintOperation;

	// 消除种类
	const int BASE_HORIZONTAL_KILL = 1;
	const int BASE_VERTICAL_KILL = -1;

	const int FOUR_HORIZONTAL_KILL = 2;
	const int FOUR_VERTICAL_KILL = -2;

	const int FIVE_HORIZONTAL_KILL = 3;
	const int FIVE_VERTICAL_KILL = -3;

	const int DOUBLE_BASE_KILL = 4;
	const int DOUBLE_FOUR_KILL = 5;

	const int SUPER_KILL = 6;
	const int DOUBLE_SUPER_KILL = 7;


	// TODO 不同模式得分

	// 提示、剩余步数得分
	const int EVERY_STEP_SCORE = 100;
	const int EVERY_HINT_SCORE = 150;

	// 三消单个得分
	const int BASE_KILL_SCORE = 10;
	// 四消单个加分
	const int FOUR_KILL_SCORE = 20;
	// 五消单个加分
	const int FIVE_KILL_SCORE = 25;
	// 双三消单个加分
	const int DOUBLE_BASE_KILL_SCORE = 40;
	// 双四消单个加分
	const int DOUBLE_FOUR_KILL_SCORE = 50;
	// Super消除单个加分
	const int SUPER_KILL_SCORE = 40;
	// Super交换单个加分
	const int DOUBLE_SUPER_KILL_SCORE = 50;

	/*
	 * 标准模式：
	 * 三消 四消 五消 有交点的双三消 有交点的双三消+横或竖添加任意一至多个宝石
	 * 加强模式：
	 * 三消
	 * 横四消：直接清除在本行的所有宝石
	 * 竖四消：直接清除在本列的所有宝石
	 * 横五消：直接清除在临近三行的所有宝石
	 * 竖五消：直接清除在临近三列的所有宝石
	 * 有交点的双三消（双三DOUBLE_BASE_KILL）：直接清除临近 3X3 的所有宝石
	 * 有交点的双三消+横或竖添加任意一至多个宝石（双四DOUBLE_FOUR_KILL）：生成SUPER宝石
	 * SUPER宝石与某个颜色交换（SUPER_KILL）：消去整个画面中该颜色的宝石
	 * 两个SUPER交换（DOUBLE_SUPER_KILL）：刷新棋盘
	 */
}

struct GameBoardInformation::Block
{
	int type;
	Actor* actor;

	explicit Block(const int type = -1, Actor* actor = nullptr) : type(type), actor(actor) {}
};

class GameBoardInformation::Actor final :
	public Node
{
public:
	static Actor* create(int type, Pair position);

	// 下落到指定位置
	void dropTo(Pair toPosition);
	// 移动到指定位置
	void moveTo(Pair toPosition);
	// 移动到指定位置后移动回原位置
	void moveToAndBack(Pair toPosition) const;
	// 缩小并消失
	void disappear();

private:
	Sprite* sprite = nullptr;
	Pair position = {-1, -1};
	int type = -1;
};

struct GameBoardInformation::ActorInformation
{
	Pair blockIndex;
	int type;
	int score;

	explicit ActorInformation(const Pair blockIndex, const int type = -1, const int score = 0) :
		blockIndex(blockIndex), type(type), score(score) {}

	ActorInformation(const int blockIndexX, const int blockIndexY, const int type = -1,
	                 const int score = 0) :
		blockIndex({blockIndexX, blockIndexY}), type(type), score(score) {}
};

struct GameBoardInformation::KillInformation
{
	int killType;
	int killScore;
	ActorInformationList killActorList;
	Pair newBlockIndex;

	KillInformation(const int killType, const int killScore, const ActorInformationList killActorList,
	                const Pair newBlockIndex = {-1, -1}) :
		killType(killType), killScore(killScore), killActorList(killActorList), newBlockIndex(newBlockIndex) {}
};

#endif
