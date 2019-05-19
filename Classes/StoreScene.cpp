#include "StoreScene.h"

Scene* StoreScene::createScene()
{
	return StoreScene::create();
}

bool StoreScene::init()
{
	if (!Scene::init()) return false;

	// TODO 替换设置按钮
	auto settingButton = ui::Button::create("/image/menuscene/jetbraintheme/setting_normal.png",
	                                        "/image/menuscene/jetbraintheme/setting_selected.png",
	                                        "/image/menuscene/jetbraintheme/setting_disabled.png");
	settingButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		// TODO 设置相关
	});
	settingButton->setPosition(Point(1050, 850));
	this->addChild(settingButton);

	// 返回按钮
	auto backButton = ui::Button::create("/image/menuscene/jetbraintheme/back_normal.png",
	                                     "/image/menuscene/jetbraintheme/back_selected.png",
	                                     "/image/menuscene/jetbraintheme/back_disabled.png");
	backButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		//返回到菜单界面
		if (type == ui::Widget::TouchEventType::ENDED) Director::getInstance()->popScene();
	});
	backButton->setPosition(Point(1150, 850));
	this->addChild(backButton);

	return true;
}
