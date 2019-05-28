#ifndef __SETTING_BUTTON_H__
#define __SETTING_BUTTON_H__


#include "cocos2d.h"
#include "2d/CCClippingNode.h"
#include "Music.h"
#include "Sound.h"
#include "ui/UIButton.h"


using std::string;
USING_NS_CC;

class SettingButton final
	: public Node
{
public:
public:
	bool init() override;
	CREATE_FUNC(SettingButton)

private:
#pragma region Image URL
	const string settingButtonNormal = "/image/common/setting_normal.png";
	const string settingButtonSelected = "/image/common/setting_selected.png";
	const string settingButtonDisabled = "/image/common/setting_disabled.png";

	const string courseMenuItemNormal = "/image/common/course.png";
	const string musicMenuItemNormal = "/image/common/music.png";
	const string soundMenuItemNormal = "/image/common/sound.png";

#pragma endregion

	bool popItem = false; // false弹出设置选项，反之收回
	bool soundPlay = false; // false关闭音效，反之打开
	int musicVolume = 0; // 音量
	ui::Button* settingButton = nullptr;
	Sprite* course = nullptr; // 教程
	Sprite* music = nullptr; // 音乐
	Sprite* sound = nullptr; // 音效
	MenuItemSprite* courseMenuItem = nullptr;
	MenuItemSprite* musicMenuItem = nullptr;
	MenuItemSprite* soundMenuItem = nullptr;
	Menu* menu = nullptr;
};

#endif
