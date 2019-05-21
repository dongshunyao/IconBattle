#include "BackButton.h"

BackButton* BackButton::instance = nullptr;

BackButton* BackButton::getInstance()
{
	if(instance==nullptr) instance=create();
	return instance;
}

BackButton* BackButton::create()
{
	auto backButton = new (std::nothrow) BackButton;
	if (backButton  && backButton->init(BACK_BUTTON_NORMAL_IMAGE, BACK_BUTTON_SELECTED_IMAGE, BACK_BUTTON_DISABLED_IMAGE))
	{
		backButton->autorelease();
		return backButton;
	}
	CC_SAFE_DELETE(backButton);
	return nullptr;
}

void BackButton::backLastScene()
{
	this->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		if (type == ui::Widget::TouchEventType::ENDED) Director::getInstance()->popScene();
	});
}
