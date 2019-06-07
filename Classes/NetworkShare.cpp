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
			auto renren = WEIBO_SHARE_URL;
			renren += "&title=";
			renren += title;
			if (isClassical) renren += RENREN_PIC_CLASSICAL;
			else renren += RENREN_PIC;

			Application::getInstance()->openURL(RENREN_SHARE_URL);
			break;
		}
	case DOUBAN:
		{
			auto douban = WEIBO_SHARE_URL;
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
	if (isClassical) temp = "我在挑战 Icon Battle 经典练习模式, 快来加入吧！！！";
	else temp = "我在挑战 Icon Battle 进阶练习模式, 快来加入吧！！！";
	return share(isClassical, temp, target);
}

bool NetworkShare::shareLevel(const bool isClassical, const int target, const int level)
{
	string temp;
	if (isClassical) temp = "我挑战成功了 Icon Battle 经典模式第 ";
	else temp = "我挑战成功了 Icon Battle 进阶模式第 ";
	temp += std::to_string(level);
	temp += " 关, 不来试试吗！！！";

	return share(isClassical, temp, target);
}

bool NetworkShare::shareRank(const bool isClassical, const int target, const int score, const int rank)
{
	string temp;
	if (isClassical) temp = "我在 Icon Battle 经典挑战模式中勇夺 ";
	else temp = "我在 Icon Battle 经典挑战模式中勇夺 ";

	temp += std::to_string(score);
	temp += " 分, 斩获全网第 ";
	temp += std::to_string(rank);
	temp += " 名, 速来Battle ! ! !";
	return share(isClassical, temp, target);
}
