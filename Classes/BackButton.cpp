#include "BackButton.h"


ui::Button* ::BackButton::create()
{
	auto* backButton = ui::Button::create(BACK_BUTTON_NORMAL_IMAGE, BACK_BUTTON_SELECTED_IMAGE,
	                                      BACK_BUTTON_DISABLED_IMAGE);

	backButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		//返回到菜单界面
		if (type == ui::Widget::TouchEventType::ENDED) Director::getInstance()->popScene();
	});
	backButton->setPosition(Point(1150, 850));

	return backButton;
}
