#ifndef __USERINFO_H__
#define __USERINFO_H__

#include "cocos2d.h"
using namespace std;

class UserInfo
{
private:
	static UserInfo* instance;
	/**
	 * userName
	 * score
	 * scoreDate
	 * lastMusic
	 * lastVolume
	 * theme
	 */
	string userInfo[6];

public:
	static UserInfo* getInstance();

	void init();
	void writeUserInfo();

	string getUserName();
	void setUserName(const string name);
	string getScore();
	void setScore(const string name);
	string getScoreDate();
	void setScoreDate(const string name);
	string getLastMusic();
	void setLastMusic(const string name);
	string getLastVolume();
	void setLastVolume(const string name);
	string getTheme();
	void setTheme(const string name);
	
	UserInfo() = default;

};

#endif

