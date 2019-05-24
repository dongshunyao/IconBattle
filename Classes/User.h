#ifndef __USER_H__
#define __USER_H__

#include "cocos2d.h"

//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
//#include <windows.h>
//#endif

USING_NS_CC;
using std::string;

class User
{
public:
	static User* getInstance();

private:
	/**
	 * 用户名
	 * 当前主题
	 * 当前音量
	 * 当前音效状态
	 * 
	 * hash串：处理以下变量
	 * 硬件ID（计算机名，仅限Win32）
	 * 当前碎片数量
	 * 主题购买情况
	 * 游戏进度
	 */

	static User* instance;
	User();
};

#endif
