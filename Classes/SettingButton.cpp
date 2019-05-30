#include "SettingButton.h"

bool SettingButton::init()
{
	if (!Node::init()) return false;

	settingButton = ui::Button::create(settingButtonNormal, settingButtonSelected, settingButtonDisabled);
	this->addChild(settingButton, 5);

	//TODO 按钮图片更换
	// 添加精灵菜单
	course = Sprite::create(courseMenuItemNormal);
	courseMenuItem = MenuItemSprite::create(course, course, course, [&](Ref* sender)
	{
		// TODO 教程
	});
	courseMenuItem->setPosition(
		settingButton->getParent()->convertToWorldSpace(settingButton->getPosition()) - Vec2(
			settingButton->getContentSize().width / 2, 0));
	courseMenuItem->setVisible(false);

	music = Sprite::create(musicMenuItemNormal);
	musicMenuItem = MenuItemSprite::create(music, music, music, [&](Ref* sender)
	{
		const auto index = Music::getInstance()->getVolume() / 20;
		Music::getInstance()->setVolume(20 * ((index + 1) % 6)); // 音量设置为0、20、40、60、80、100
		// TODO 音量图片及图标更新
	});
	musicMenuItem->setPosition(
		settingButton->getParent()->convertToWorldSpace(courseMenuItem->getPosition()) - Vec2(
			settingButton->getContentSize().width / 2, 0));
	musicMenuItem->setVisible(false);

	sound = Sprite::create(soundMenuItemNormal);
	soundMenuItem = MenuItemSprite::create(sound, sound, sound, [&](Ref* sender)
	{
		Sound::getInstance()->setStatus(!Sound::getInstance()->getStatus());
	});
	soundMenuItem->setPosition(
		settingButton->getParent()->convertToWorldSpace(musicMenuItem->getPosition()) - Vec2(
			settingButton->getContentSize().width / 2, 0));
	soundMenuItem->setVisible(false);

	menu = Menu::create(courseMenuItem, musicMenuItem, soundMenuItem, nullptr);
	menu->setPosition(Point(0, 0));
	this->addChild(menu, 4);
	// settingButton响应，弹出设置内容
	settingButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			if (!popItem)
			{
#pragma region Appear Action
				// common action
				const auto delay = DelayTime::create(0.25);
				const auto fadeIn = FadeIn::create(0.25);

				// course action
				const auto courseMoveBy = MoveBy::create(0.25, Vec2(-25, 0));
				const auto courseSpawn = Spawn::create(fadeIn, delay, courseMoveBy, delay, nullptr);

				// music action
				const auto musicMoveBy = MoveBy::create(0.25, Vec2(-35, 0));
				const auto musicSpawn = Spawn::create(fadeIn, delay, musicMoveBy, delay, nullptr);

				// sound action
				const auto soundMoveBy = MoveBy::create(0.25, Vec2(-40, 0));
				const auto soundSpawn = Spawn::create(fadeIn, delay, soundMoveBy, delay, nullptr);

				courseMenuItem->setVisible(true);
				musicMenuItem->setVisible(true);
				soundMenuItem->setVisible(true);

				courseMenuItem->runAction(courseSpawn);
				musicMenuItem->runAction(musicSpawn);
				soundMenuItem->runAction(soundSpawn);

#pragma endregion
				popItem = true;
			}
			else
			{
#pragma region Disappear Action
				// common action
				const auto delay = DelayTime::create(0.25);
				const auto fadeOut = FadeOut::create(0.25);

				//course action
				const auto courseMoveBy = MoveBy::create(0.25, Vec2(25, 0));
				const auto courseSpawn = Spawn::create(fadeOut, delay, courseMoveBy, delay, nullptr);

				//music action
				const auto musicMoveBy = MoveBy::create(0.25, Vec2(35, 0));
				const auto musicSpawn = Spawn::create(fadeOut, delay, musicMoveBy, delay, nullptr);

				//sound action
				const auto soundMoveBy = MoveBy::create(0.25, Vec2(40, 0));
				const auto soundSpawn = Spawn::create(fadeOut, delay, soundMoveBy, delay, nullptr);

				courseMenuItem->runAction(Sequence::create(courseSpawn, CallFunc::create([&]()
				{
					courseMenuItem->setVisible(false);
				}), nullptr));
				musicMenuItem->runAction(Sequence::create(musicSpawn, CallFunc::create([&]()
				{
					musicMenuItem->setVisible(false);
				}), nullptr));
				soundMenuItem->runAction(Sequence::create(soundSpawn, CallFunc::create([&]()
				{
					soundMenuItem->setVisible(false);
				}), nullptr));

#pragma endregion
				popItem = false;
			}
		}
	});

	return true;
}
