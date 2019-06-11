#ifndef __USER_H__
#define __USER_H__

#include "cocos2d.h"
#include "Theme.h"
#include "Music.h"
#include "Sound.h"
#include "Util.h"
#include "Network.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include <windows.h>
#endif

USING_NS_CC;
using std::string;
using std::wstring;
using std::to_string;

class User
{
public:
	static User* getInstance();

	string getUserName() const { return userName; }
	bool setUserName(const string& name);

	int getCoin() const { return coin; }
	bool setCoin(const int coin);

	vector<string> getUnlockedThemes() const;
	bool setUnlockedThemes(const vector<string>& v);

	int getUnlockedClassicalLevel() const { return unlockedClassicalLevel; }
	bool setUnlockedClassicalLevel(const int level);

	int getUnlockedPlusLevel() const { return unlockedPlusLevel; }
	bool setUnlockedPlusLevel(const int level);

	bool isNewUser() const { return newUser; }
	void setNewUser(const bool isNewUser) { newUser = isNewUser; }
	bool isConnected() const { return connected; }

	string getNewsInformation();
	bool update() const;

private:
	bool newUser = true;

	bool connected = false;
	string newsInformation = "";

	string userName = "玩家3265";
	string hardwareId = getHardwareId();
	int coin = 10; //TODO 更改
	ValueVector unlockedThemes;
	int unlockedClassicalLevel = 1;
	int unlockedPlusLevel = 1;

	const string filename = FileUtils::getInstance()->getWritablePath() + "config.plist";
	/**
	 * 用户名 UserName
	 * 当前主题 CurrentTheme
	 * 当前音量 CurrentVolume
	 * 当前音效状态 CurrentSoundStatus
	 * 
	 * hash串：处理以下变量 Key
	 * 硬件ID（计算机名，仅限Win32）HardwareID
	 * 当前硬币数量 Coin
	 * 主题购买情况 UnlockedThemes
	 * 经典游戏进度 UnlockedClassicalLevel
	 * 加强游戏进度 UnlockedPlusLevel
	 */

	static User* instance;
	User();

	static string getHardwareId();
	int getKey() const;
	int getKey(ValueMap& map) const;
};

#endif
