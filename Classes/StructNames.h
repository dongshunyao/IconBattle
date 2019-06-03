#ifndef __STRUCTNAMES_H__
#define __STRUCTNAMES_H__

#include <utility>
#include <string>
#include <vector>
#include "cocos2d.h"

using std::pair;
using std::string;
using std::vector;

USING_NS_CC;

namespace StructNames
{
	typedef pair<int, int> pii;
	class Actor;
	struct blockInfo;
	struct KillGroup;
	typedef vector<KillGroup> KillGroupList;
	struct ActorInfo;
	typedef vector<ActorInfo> ActorInfoList;

	typedef pair<pii, pii> validOperate;
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

class StructNames::Actor : public Node
{
	// protected类型变量创建方式，ctrl点击见源码
CC_SYNTHESIZE(int, type, Type);
CC_SYNTHESIZE(int, func, Func);

CC_SYNTHESIZE(pii, pos, Pos);

CC_SYNTHESIZE_RETAIN(Sprite*, gem, Gem);
CC_SYNTHESIZE_RETAIN(Sprite*, icon, Icon);
public:
	static Actor* create(int, int, pii);
	void allDo(Action*);
	void moveTo(pii);
	void moveToThenBack(pii);
	void dropTo(pii);
	void selfClose();
};

struct StructNames::ActorInfo
{
	pii pos;
	int type;
	int func;

	ActorInfo(pii pos, int type = -1, int func = -1) : pos(pos), type(type), func(func)
	{
	};

	ActorInfo(int x, int y, int type = -1, int func = -1) : pos({x, y}), type(type), func(func)
	{
	};
};

struct StructNames::blockInfo
{
	int type;
	int func;
	Actor* actor;

	blockInfo(int type = -1, int func = -1, Actor* actor = NULL) : type(type), func(func), actor(actor)
	{
	};
};

struct StructNames::KillGroup
{
	pii markPoint;
	int markValue;
	ActorInfoList killInfo;
	ActorInfoList newInfo;
};


#endif
