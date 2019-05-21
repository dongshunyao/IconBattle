#include "ReturnButtom.h"

void ReturnButton::returnLastScene()
{
	this->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		if (type == ui::Widget::TouchEventType::ENDED) Director::getInstance()->popScene();
	});
}
