#include "User.h"

User* User::instance = nullptr;

User* User::getInstance()
{
	if (instance == nullptr) instance = new User;
	return instance;
}

bool User::setUserName(const string& name)
{
	userName = name;
	return update();
}

bool User::setCoin(const int coin)
{
	if (coin >= 0)
	{
		this->coin = coin;
		return update();
	}
	return false;
}

vector<string> User::getUnlockedThemes() const
{
	vector<string> v;
	for (const auto& it : unlockedThemes) v.emplace_back(it.asString());
	return v;
}

bool User::setUnlockedThemes(const vector<string>& v)
{
	ValueVector temp;
	for (const auto& it : v) temp.emplace_back(it);
	unlockedThemes = temp;
	return update();
}

bool User::setUnlockedClassicalLevel(const int level)
{
	if (level >= 1 && level <= 10)
	{
		unlockedClassicalLevel = level;
		return update();
	}
	return false;
}

bool User::setUnlockedPlusLevel(const int level)
{
	if (level >= 1 && level <= 10)
	{
		unlockedPlusLevel = level;
		return update();
	}
	return false;
}

bool User::update() const
{
	ValueMap map;
	map["UserName"] = userName;
	map["CurrentTheme"] = Theme::getInstance()->getCurrentThemeName();
	map["CurrentVolume"] = Music::getInstance()->getVolume();
	map["CurrentSoundStatus"] = Sound::getInstance()->getStatus();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	map["HardwareID"] = hardwareId;
#endif
	map["Coin"] = coin;
	map["UnlockedThemes"] = unlockedThemes;
	map["UnlockedClassicalLevel"] = unlockedClassicalLevel;
	map["UnlockedPlusLevel"] = unlockedPlusLevel;
	map["Key"] = getKey();

	return FileUtils::getInstance()->writeValueMapToFile(map, filename);
}

User::User()
{
	if (!FileUtils::getInstance()->isFileExist(filename))
	{
		unlockedThemes.emplace_back(Theme::getInstance()->jetBrainThemeName);
		update();
		return;
	}

	auto map = FileUtils::getInstance()->getValueMapFromFile(filename);
	newUser = false;
	if (map.count("UserName")) userName = map["UserName"].asString();
	if (map.count("CurrentTheme")) Theme::getInstance()->setCurrentTheme(map["CurrentTheme"].asString());
	if (map.count("CurrentVolume")) Music::getInstance()->setVolume(map["CurrentVolume"].asInt());
	if (map.count("CurrentSoundStatus")) Sound::getInstance()->setStatus(map["CurrentSoundStatus"].asBool());
	if (map.count("Key") && getKey(map) == map["Key"].asInt())
	{
		if (map.count("Coin")) coin = map["Coin"].asInt();
		if (map.count("UnlockedThemes"))
			for (const auto& it : map["UnlockedThemes"].asValueVector()) unlockedThemes.emplace_back(it.asString());
		if (map.count("UnlockedClassicalLevel")) unlockedClassicalLevel = map["UnlockedClassicalLevel"].asInt();
		if (map.count("UnlockedPlusLevel")) unlockedPlusLevel = map["UnlockedPlusLevel"].asInt();
	}
	else unlockedThemes.emplace_back(Theme::getInstance()->jetBrainThemeName);
}

string User::getHardwareId()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	TCHAR buffer[MAX_COMPUTERNAME_LENGTH + 2];
	DWORD bufferSize = sizeof buffer - 1;
	GetComputerName(buffer, &bufferSize);
	const wstring temp = buffer;
	string str(temp.length(), ' ');
	WideCharToMultiByte(CP_ACP, 0, LPCWSTR(temp.c_str()), temp.length(), LPSTR(str.c_str()), temp.length(), nullptr,
	                    nullptr);
	return str;
#endif

	return "";
}

int User::getKey() const
{
	vector<string> v;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	v.emplace_back(hardwareId);
#endif
	v.emplace_back(to_string(coin));
	for (const auto& it : unlockedThemes) v.emplace_back(it.asString());
	v.emplace_back(to_string(unlockedClassicalLevel));
	v.emplace_back(to_string(unlockedPlusLevel));

	return Util::getStringHash(v);
}

int User::getKey(ValueMap& map) const
{
	vector<string> v;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	if (map.count("HardwareID")) v.emplace_back(map["HardwareID"].asString());
#endif
	if (map.count("Coin")) v.emplace_back(to_string(map["Coin"].asInt()));
	if (map.count("UnlockedThemes"))
		for (const auto& it : map["UnlockedThemes"].asValueVector()) v.emplace_back(it.asString());
	if (map.count("UnlockedClassicalLevel")) v.emplace_back(to_string(map["UnlockedClassicalLevel"].asInt()));
	if (map.count("UnlockedPlusLevel")) v.emplace_back(to_string(map["UnlockedPlusLevel"].asInt()));

	return Util::getStringHash(v);
}
