#include "NetworkShare.h"
// TODO 三个分享方法重载 const int target
// bool NetworkShare::share(bool isClassical)
// bool NetworkShare::share(bool isClassical,int level,int score)
// bool NetworkShare::share(bool isClassical,int score,int rank) 
bool NetworkShare::share(const bool isClassical, const string title, const int target)
{
	switch (target)
	{
	case QQ:
		{
			auto qq = QQ_SHARE_URL;
			qq += "&desc=";
			qq += title;
			if(isClassical)
				qq += QQ_PIC_CLASSICAL;
			else
				qq += QQ_PIC;
			
			Application::getInstance()->openURL(qq);
			break;
		}
	case WEIBO:
		{
			auto weibo = WEIBO_SHARE_URL;
			weibo += "title=";
			weibo += title;
			if (isClassical)
				weibo += WEIBO_PIC_CLASSICAL;
			else
				weibo += WEIBO_PIC;

			Application::getInstance()->openURL(weibo);
			break;
		}
	case RENREN:
		{
			auto renren = WEIBO_SHARE_URL;
			renren += "&title=";
			renren += title;
			if (isClassical)
				renren += RENREN_PIC_CLASSICAL;
			else
				renren += RENREN_PIC;

			Application::getInstance()->openURL(RENREN_SHARE_URL);
			break;
		}
	case DOUBAN:
		{
			auto douban = WEIBO_SHARE_URL;
			douban += "name=";
			douban += title;
			if (isClassical)
				douban += DOUBAN_PIC_CLASSICAL;
			else
				douban += DOUBAN_PIC;

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
	{
		temp = "I'm playing IconBattle practicing mode, come and join me.";
		share(isClassical, temp, target);
		return true;
	}

	temp = "I'm playing IconBattle advanced mode, come and join me.";
	share(isClassical, temp, target);
	return true;
}

bool NetworkShare::shareLevel(const bool isClassical, const int target, const int level)
{
	string temp;
	if (isClassical)
	{
		temp = "I've passed level ";
		temp += std::to_string(level);
		temp += " of IconBattle practicing mode. That would be nice.";
		share(isClassical, temp, target);
		return true;
	}

	temp = "I've passed level ";
	temp += std::to_string(level);
	temp += " of IconBattle advanced mode. Awesome!";
	share(isClassical, temp, target);
	return true;
}

bool NetworkShare::shareRank(const bool isClassical, const int target, const int score, const int rank)
{
	string temp;
	if (isClassical)
	{
		temp = "I've got ";
		temp += std::to_string(score);
		temp += " points of IconBattle practicing mode and ranked No.";
		temp += std::to_string(rank);
		share(isClassical, temp, target);
		return true;
	}

	temp = "I've got ";
	temp += std::to_string(score);
	temp += " points of IconBattle advanced mode and ranked No.";
	temp += std::to_string(rank);
	share(isClassical, temp, target);
	return true;
}
