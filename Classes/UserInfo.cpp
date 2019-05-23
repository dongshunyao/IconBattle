#include  "UserInfo.h"
#include "platform/CCFileUtils.h"

USING_NS_CC;

UserInfo* UserInfo::instance = nullptr;

UserInfo* UserInfo::getInstance()
{
	if (instance == nullptr) instance = new UserInfo;
	return instance;
}

void UserInfo::init()
{
	if (FileUtils::getInstance()->isFileExist("userinfo.ini"))
	{
		const auto userInfo = FileUtils::getInstance()->getStringFromFile("userinfo.ini");

		//将用户信息复制到char[]以便strtok()函数处理信息
		char temp[200];
		strcpy(temp, userInfo.c_str());

		auto *split = "\t";

		//以\t分隔符处理文件信息
		auto i = 0;
		auto tempStr = strtok(temp, split);
		while (tempStr != nullptr)
		{
			string toStr = tempStr;
			

		}

	}
}
