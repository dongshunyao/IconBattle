#include "NetworkShare.h"
// TODO 三个分享方法重载 const int target
// bool NetworkShare::share(bool isClassical)
// bool NetworkShare::share(bool isClassical,int level,int score)
// bool NetworkShare::share(bool isClassical,int score,int rank) 
bool NetworkShare::share(vector<string>& info, const int target)
{
	switch (target)
	{
	case QQ:
		{
			auto qq = QQ_SHARE_URL;
			qq += "&desc=";
			qq += info[0];
			qq += QQ_PIC;
			Application::getInstance()->openURL(qq);
			break;
		}
	case WEIBO:
		{
			auto weibo = WEIBO_SHARE_URL;
			weibo += "title=";
			weibo += info[0];
			weibo += WEIBO_PIC;
			Application::getInstance()->openURL(weibo);
			break;
		}
	case RENREN:
		{
			auto renren = WEIBO_SHARE_URL;
			renren += "&title=";
			renren += info[0];
			renren += RENREN_PIC;
			Application::getInstance()->openURL(RENREN_SHARE_URL);
			break;
		}
	case DOUBAN:
		{
			auto douban = WEIBO_SHARE_URL;
			douban += "name=";
			douban += info[0];
			douban += DOUBAN_PIC;
			Application::getInstance()->openURL(douban);
			break;
		}
	default:
		return false;
	}
	return true;
}
