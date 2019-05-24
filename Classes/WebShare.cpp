#include "WebShare.h"

bool WebShare::share(vector<string>& info, const int target)
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
