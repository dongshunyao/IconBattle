#include "NetworkShare.h"
 // TODO 三个分享方法重载 const int target
 // bool NetworkShare::share(bool isClassical)
 // bool NetworkShare::share(bool isClassical,int level,int score)
 // bool NetworkShare::share(bool isClassical,int score,int rank) 
bool NetworkShare::share(vector<string>& info, const int target)
{
	// TODO 处理信息并生成相应字符串
	switch (target)
	{
	case QQ:
		{
			Application::getInstance()->openURL(QQ_SHARE_URL);
			break;
		}
	case WEIBO:
		{
			Application::getInstance()->openURL(WEIBO_SHARE_URL);
			break;
		}
	case RENREN:
		{
			Application::getInstance()->openURL(RENREN_SHARE_URL);
			break;
		}
	case DOUBAN:
		{
			Application::getInstance()->openURL(DOUBAN_SHARE_URL);
			break;
		}
	default:
		return false;
	}
	return true;
}
