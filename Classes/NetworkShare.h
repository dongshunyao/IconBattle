#ifndef __NETWORK_SHARE_H__
#define __NETWORK_SHARE_H__

#include "cocos2d.h"
#include <vector>

USING_NS_CC;
using std::string;
using std::vector;

namespace NetworkShare
{
#pragma region Target Index
	const int QQ = 1;
	const int WEIBO = 2;
	const int RENREN = 3;
	const int DOUBAN = 4;
#pragma endregion

#pragma region URL
	const string QQ_SHARE_URL =
		"https://connect.qq.com/widget/shareqq/index.html?url=http://www.iconbattle.net/";
	const string WEIBO_SHARE_URL =
		"http://service.weibo.com/share/share.php?";
	const string RENREN_SHARE_URL =
		"http://widget.renren.com/dialog/share?url=http://www.iconbattle.net/";
	const string DOUBAN_SHARE_URL =
		"https://www.douban.com/share/service?";
#pragma endregion

#pragma region Share Pic Url
	// TODO: 制作并上传分享图片
	const string QQ_PIC_CLASSICAL = "&pics=https://i.loli.net/2019/05/19/5ce15be219ef569212.jpg&style=201&width=32&height=3";
	const string QQ_PIC = "&pics=https://i.loli.net/2019/05/19/5ce15be219ef569212.jpg&style=201&width=32&height=3";

	const string WEIBO_PIC_CLASSICAL = "&pic=https://i.loli.net/2019/05/19/5ce15be219ef569212.jpg";
	const string WEIBO_PIC = "&pic=https://i.loli.net/2019/05/19/5ce15be219ef569212.jpg";

	const string RENREN_PIC_CLASSICAL = "&pic=https://i.loli.net/2019/05/19/5ce15be219ef569212.jpg";
	const string RENREN_PIC = "&pic=https://i.loli.net/2019/05/19/5ce15be219ef569212.jpg";

	const string DOUBAN_PIC_CLASSICAL = "&image=https://i.loli.net/2019/05/19/5ce15be219ef569212.jpg";
	const string DOUBAN_PIC = "&image=https://i.loli.net/2019/05/19/5ce15be219ef569212.jpg";
#pragma endregion

	bool share(bool isClassical, const string& title, const int target);
	bool sharePractice(bool isClassical, const int target);
	bool shareLevel(bool isClassical, const int target, const int level);
	bool shareRank(bool isClassical, const int target, const int score, const int rank);
};

#endif
