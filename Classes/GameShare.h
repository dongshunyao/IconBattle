#ifndef __GAMESHARE_H__
#define __GAMESHARE_H__

#include "cocos2d.h"
using std::string;

namespace GameShareNamespace
{
#pragma region 
	// 分享网址如下，其中图片url有待更新
	const string QQ_SHARE_URL = "https://connect.qq.com/widget/shareqq/index.html?url=http://www.iconbattle.net/&desc=IconBattle%E6%B8%B8%E6%88%8F%E5%88%86%E4%BA%AB&pics=https://i.loli.net/2019/05/19/5ce15be219ef569212.jpg&flash=&site=&style=201&width=32&height=32";
	const string XINLANG_SHARE_URL = "http://service.weibo.com/share/share.php?url=&reason=&retcode=&pic=https://i.loli.net/2019/05/19/5ce15be219ef569212.jpg";
	const string RENREN_SHARE_URL = "http://widget.renren.com/dialog/share?url=http://www.iconbattle.net/&pic=https://i.loli.net/2019/05/19/5ce15be219ef569212.jpg";
	const string DOUBAN_SHARE_URL = "https://www.douban.com/share/service?image=https://i.loli.net/2019/05/19/5ce15be219ef569212.jpg";
#pragma endregion 
};

class GameShare
{
private:
	static GameShare* instance;

public:
	static GameShare* getInstance();
	void sharePicToTencent();
	void sharePicToXinlang();
	void sharePicToRenren();
	void sharePicToDouban();
};

#endif

