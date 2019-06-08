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
	bool init() override;
	CREATE_FUNC(SettingButton)

private:
#pragma region Image URL
	const string settingButtonNormal = "/image/common/setting_normal.png";
	const string settingButtonSelected = "/image/common/setting_selected.png";
	const string settingButtonDisabled = "/image/common/setting_disabled.png";

	const string courseMenuItemNormal = "/image/common/course.png";
	const string courseMenuItemSelected = "/image/common/course.png";
	const string courseMenuItemDisabled = "/image/common/course.png";

	const string musicVolumeMenuItem = "/image/common/music3.png";
	const string musicAdjustedVolumeMenuItem = "/image/common/music";

	const string soundMenuItemOnNormal = "/image/common/sound_on.png";
	const string soundMenuItemOffNormal = "/image/common/sound_off.png";

#pragma endregion

	bool popItem = false; // false弹出设置选项，反之收回
	ui::Button* settingButton = nullptr;
	Sprite* sound = nullptr; // 音效
	MenuItemSprite* courseMenuItem = nullptr; // 教程
	MenuItemSprite* musicMenuItem = nullptr; // 音乐
	MenuItemSprite* soundMenuItem = nullptr;
	Menu* menu = nullptr;
};

#endif
