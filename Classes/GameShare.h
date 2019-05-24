#ifndef __GAME_SHARE_H__
#define __GAME_SHARE_H__

#include "cocos2d.h"
#include <vector>

USING_NS_CC;
using std::string;
using std::vector;

namespace GameShare
{
#pragma region Target Index
	const int QQ = 1;
	const int WEIBO = 2;
	const int RENREN = 3;
	const int DOUBAN = 4;
#pragma endregion

#pragma region URL
	// TODO 规范URL，放到函数里，动态处理字符串
	const string QQ_SHARE_URL =
		"https://connect.qq.com/widget/shareqq/index.html?url=http://www.iconbattle.net/&desc=IconBattle%E6%B8%B8%E6%88%8F%E5%88%86%E4%BA%AB&pics=https://i.loli.net/2019/05/19/5ce15be219ef569212.jpg&flash=&site=&style=201&width=32&height=32";
	const string WEIBO_SHARE_URL =
		"http://service.weibo.com/share/share.php?url=&reason=&retcode=&pic=https://i.loli.net/2019/05/19/5ce15be219ef569212.jpg";
	const string RENREN_SHARE_URL =
		"http://widget.renren.com/dialog/share?url=http://www.iconbattle.net/&pic=https://i.loli.net/2019/05/19/5ce15be219ef569212.jpg";
	const string DOUBAN_SHARE_URL =
		"https://www.douban.com/share/service?image=https://i.loli.net/2019/05/19/5ce15be219ef569212.jpg";
#pragma endregion

	bool share(vector<string>& info, const int target);
};

#endif
