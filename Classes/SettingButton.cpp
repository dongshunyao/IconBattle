#include "SettingButton.h"

SettingButton* SettingButton::instance = nullptr;

SettingButton* SettingButton::getInstance()
{
	if (instance == nullptr) instance = create();
	return instance;
}

SettingButton* SettingButton::create()
{
	auto settingButton = new (std::nothrow)SettingButton;
	if (settingButton  && settingButton->init(SETTING_BUTTON_NORMAL_IMAGE, SETTING_BUTTON_SELECTED_IMAGE, SETTING_BUTTON_DISABLED_IMAGE))
	{
		settingButton->autorelease();
		return settingButton;
	}
	CC_SAFE_DELETE(settingButton);
	return nullptr;
}

void SettingButton::settingByUser()
{
	this->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		// TODO …Ë÷√œ‡πÿ
	});
}
