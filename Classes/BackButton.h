#ifndef __BACK_BUTTON_H__
#define __BACK_BUTTON_H__

#include "cocos2d.h"
#include "ui/UIButton.h"

using std::string;
USING_NS_CC;

namespace BackButton
{
#pragma region Image URL
	const string BACK_BUTTON_NORMAL_IMAGE = "/image/gamescene/common/back_normal.png";
	const string BACK_BUTTON_SELECTED_IMAGE = "/image/gamescene/common/back_selected.png";
	const string BACK_BUTTON_DISABLED_IMAGE = "/image/gamescene/common/back_disabled.png";
#pragma endregion

	ui::Button* create();
};

#endif
