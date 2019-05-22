#include "SettingButton.h"


ui::Button* SettingButton::create()
{
	auto* settingButton = ui::Button::create(SETTING_BUTTON_NORMAL_IMAGE, SETTING_BUTTON_SELECTED_IMAGE,
	                                         SETTING_BUTTON_DISABLED_IMAGE);

	settingButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		// TODO ÉèÖÃÏà¹Ø
	});
	settingButton->setPosition(Point(1050, 850));

	return settingButton;
}
