#include "NetworkShare.h"

bool NetworkShare::share(const bool isClassical, const string& title, const int target)
{
	switch (target)
	{
	case QQ:
		{
			auto qq = QQ_SHARE_URL;
			qq += "&desc=";
			qq += title;
			if (isClassical) qq += QQ_PIC_CLASSICAL;
			else qq += QQ_PIC;

			Application::getInstance()->openURL(qq);
			break;
		}
	case WEIBO:
		{
			auto weibo = WEIBO_SHARE_URL;
			weibo += "title=";
			weibo += title;
			if (isClassical) weibo += WEIBO_PIC_CLASSICAL;
			else weibo += WEIBO_PIC;

			Application::getInstance()->openURL(weibo);
			break;
		}
	case RENREN:
		{
			auto renren = RENREN_SHARE_URL;
			renren += "&title=";
			renren += title;
			if (isClassical) renren += RENREN_PIC_CLASSICAL;
			else renren += RENREN_PIC;

			Application::getInstance()->openURL(renren);
			break;
		}
	case DOUBAN:
		{
			auto douban = DOUBAN_SHARE_URL;
			douban += "name=";
			douban += title;
			if (isClassical) douban += DOUBAN_PIC_CLASSICAL;
			else douban += DOUBAN_PIC;

			Application::getInstance()->openURL(douban);
			break;
		}
	default:
		return false;
	}
	return true;
}

bool NetworkShare::sharePractice(const bool isClassical, const int target)
{
	string temp;
	if (isClassical)
		temp =
			"%e6%88%91%e5%9c%a8%e6%8c%91%e6%88%98+Icon+Battle+%e7%bb%8f%e5%85%b8%e7%bb%83%e4%b9%a0%e6%a8%a1%e5%bc%8f%2c+%e5%bf%ab%e6%9d%a5%e5%8a%a0%e5%85%a5%e5%90%a7%ef%bc%81%ef%bc%81%ef%bc%81";
	else
		temp =
			"%e6%88%91%e5%9c%a8%e6%8c%91%e6%88%98+Icon+Battle+%e8%bf%9b%e9%98%b6%e7%bb%83%e4%b9%a0%e6%a8%a1%e5%bc%8f%2c+%e5%bf%ab%e6%9d%a5%e5%8a%a0%e5%85%a5%e5%90%a7%ef%bc%81%ef%bc%81%ef%bc%81";
	return share(isClassical, temp, target);
}

bool NetworkShare::shareLevel(const bool isClassical, const int target, const int level)
{
	string temp;
	if (isClassical) temp =
		"%e6%88%91%e6%8c%91%e6%88%98%e6%88%90%e5%8a%9f%e4%ba%86+Icon+Battle+%e7%bb%8f%e5%85%b8%e6%a8%a1%e5%bc%8f%e7%ac%ac+";
	else temp =
		"%e6%88%91%e6%8c%91%e6%88%98%e6%88%90%e5%8a%9f%e4%ba%86+Icon+Battle+%e8%bf%9b%e9%98%b6%e6%a8%a1%e5%bc%8f%e7%ac%ac+";
	temp += std::to_string(level);
	temp += "+%e5%85%b3%2c+%e4%b8%8d%e6%9d%a5%e8%af%95%e8%af%95%e5%90%97%ef%bc%81%ef%bc%81%ef%bc%81";

	return share(isClassical, temp, target);
}

bool NetworkShare::shareRank(const bool isClassical, const int target, const int score, const int rank)
{
	string temp;
	if (isClassical) temp =
		"%e6%88%91%e5%9c%a8+Icon+Battle+%e7%bb%8f%e5%85%b8%e6%8c%91%e6%88%98%e6%a8%a1%e5%bc%8f%e4%b8%ad%e5%8b%87%e5%a4%ba+";
	else temp =
		"%e6%88%91%e5%9c%a8+Icon+Battle+%e7%bb%8f%e5%85%b8%e6%8c%91%e6%88%98%e6%a8%a1%e5%bc%8f%e4%b8%ad%e5%8b%87%e5%a4%ba+";

	temp += std::to_string(score);
	temp += "+%e5%88%86%2c+%e6%96%a9%e8%8e%b7%e5%85%a8%e7%bd%91%e7%ac%ac+";
	temp += std::to_string(rank);
	temp += "+%e5%90%8d%2c+%e9%80%9f%e6%9d%a5Battle+!+!+!";
	return share(isClassical, temp, target);
}
