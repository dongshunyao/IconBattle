#ifndef __GAME_BOARD_INFORMATION_H__
#define __GAME_BOARD_INFORMATION_H__

#include <vector>
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

	// TODO 
	const string SPRITE_URL[6] =
	{
		"/image/gamescene/jetbraintheme/iconset/large/1.png",
		"/image/gamescene/jetbraintheme/iconset/large/2.png",
		"/image/gamescene/jetbraintheme/iconset/large/3.png",
		"/image/gamescene/jetbraintheme/iconset/large/4.png",
		"/image/gamescene/jetbraintheme/iconset/large/5.png",
		"/image/gamescene/jetbraintheme/iconset/large/6.png"
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

	// TODO 不同模式得分+剩余步数和提示兑换分数
	const int BASE_KILL_SCORE = 10;

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


	// TODO DEL 代表不同粒子特效的函数标号
	const int FUNC_NO = -1;
	const int FUNC_SUPER = 0;
	const int FUNC_FIRE = 1;
	const int FUNC_H_1 = 2;
	const int FUNC_H_3 = 3;
	const int FUNC_V_1 = 4;
	const int FUNC_V_3 = 5;
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
	void moveToAndBack(Pair toPosition);
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

	explicit ActorInformation(const Pair blockIndex, const int type = -1, const int score = BASE_KILL_SCORE) :
		blockIndex(blockIndex), type(type), score(score) {}

	ActorInformation(const int blockIndexX, const int blockIndexY, const int type = -1,
	                 const int score = BASE_KILL_SCORE) :
		blockIndex({blockIndexX, blockIndexY}), type(type), score(score) {}
};

struct GameBoardInformation::KillInformation
{
	Pair newBlockIndex;
	int killType;
	ActorInformationList killActorList;

	KillInformation(const int killType, const ActorInformationList killActorList, const Pair newBlockIndex = {-1, -1}) :
		newBlockIndex(newBlockIndex), killType(killType), killActorList(killActorList) {}
};

#endif
