#ifndef __SETTING_BUTTON_H__
#define __SETTING_BUTTON_H__


#include "cocos2d.h"
#include "ui/UIButton.h"

using std::string;
USING_NS_CC;

namespace SettingButton
{
#pragma region Image URL
	const string SETTING_BUTTON_NORMAL_IMAGE = "/image/gamescene/jetbraintheme/setting_normal.png";
	const string SETTING_BUTTON_SELECTED_IMAGE = "/image/gamescene/jetbraintheme/setting_selected.png";
	const string SETTING_BUTTON_DISABLED_IMAGE = "/image/gamescene/jetbraintheme/setting_disabled.png";
#pragma endregion

	ui::Button* create();
};

#endif
