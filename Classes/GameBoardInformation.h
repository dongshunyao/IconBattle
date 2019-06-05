#ifndef __GAME_BOARD_INFORMATION_H__
#define __GAME_BOARD_INFORMATION_H__

#include <utility>
#include <string>
#include <vector>
#include "cocos2d.h"

using std::pair;
using std::string;
using std::vector;

USING_NS_CC;

namespace GameBoardInformation
{
	typedef pair<int, int> Pair;

	// 宝石块
	struct Block;


	class Actor;
	struct KillGroup;
	typedef vector<KillGroup> KillGroupList;
	struct ActorInfo;
	typedef vector<ActorInfo> ActorInfoList;

	typedef pair<Pair, Pair> validOperate;
	typedef vector<validOperate> validOperateList;

#pragma region CONST_VAL
	const string GEM_N[6] = {
		"/image/gamescene/jetbraintheme/iconset/large/1.png",
		"/image/gamescene/jetbraintheme/iconset/large/2.png",
		"/image/gamescene/jetbraintheme/iconset/large/3.png",
		"/image/gamescene/jetbraintheme/iconset/large/4.png",
		"/image/gamescene/jetbraintheme/iconset/large/5.png",
		"/image/gamescene/jetbraintheme/iconset/large/6.png"
	};
	const string SPIC_N[6] = {
		"gem_super.png",
		"spcecial_gem_fire.png",
		"spcecial_gem_lighting_hor_1.png",
		"spcecial_gem_lighting_hor_3.png",
		"spcecial_gem_lighting_ver_1.png",
		"spcecial_gem_lighting_ver_3.png"
	};
	// 代表不同粒子特效的函数标号
	const int FUNC_NO = -1;
	const int FUNC_SUPER = 0;
	const int FUNC_FIRE = 1;
	const int FUNC_H_1 = 2;
	const int FUNC_H_3 = 3;
	const int FUNC_V_1 = 4;
	const int FUNC_V_3 = 5;

#pragma endregion
}

struct GameBoardInformation::Block
{
	int type;
	int func; // TODO del
	Actor* actor;

	explicit Block(const int type = -1, const int func = -1, Actor* actor = nullptr)
		: type(type), func(func), actor(actor) {}
};

class GameBoardInformation::Actor :
	public Node
{
	// protected类型变量创建方式，ctrl点击见源码
CC_SYNTHESIZE(int, type, Type);
CC_SYNTHESIZE(int, func, Func);


CC_SYNTHESIZE_RETAIN(Sprite*, gem, Gem);
CC_SYNTHESIZE_RETAIN(Sprite*, icon, Icon);

private:
	Pair position = {-1, -1};

public:
	static Actor* create(int, int, Pair);

	// 下落到指定位置
	void dropTo(Pair toPosition);
	void allDo(Action*);
	void moveTo(Pair);
	void moveToThenBack(Pair);
	void selfClose();
};

struct GameBoardInformation::ActorInfo
{
	Pair pos;
	int type;
	int func;

	ActorInfo(Pair pos, int type = -1, int func = -1) : pos(pos), type(type), func(func) { };

	ActorInfo(int x, int y, int type = -1, int func = -1) : pos({x, y}), type(type), func(func) { };
};


struct GameBoardInformation::KillGroup
{
	Pair markPoint;
	int markValue;
	ActorInfoList killInfo;
	ActorInfoList newInfo;
};


#endif
