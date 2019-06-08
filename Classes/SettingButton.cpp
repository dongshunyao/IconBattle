#include "SettingButton.h"

bool SettingButton::init()
{
	if (!Node::init()) return false;

	settingButton = ui::Button::create(settingButtonNormal, settingButtonSelected, settingButtonDisabled);
	this->addChild(settingButton, 5);

	// 添加精灵菜单
	courseMenuItem = MenuItemSprite::create(
		Sprite::create(courseMenuItemNormal),
		Sprite::create(courseMenuItemSelected),
		Sprite::create(courseMenuItemDisabled), [&](Ref* sender)
		{
			// TODO 教程
		});
	courseMenuItem->setPosition(
		settingButton->getParent()->convertToWorldSpace(settingButton->getPosition()) - Vec2(
			settingButton->getContentSize().width - 10, 0));
	courseMenuItem->setVisible(false);

	// 音量图标
	musicMenuItem = MenuItemSprite::create(
		Sprite::create(
			musicAdjustedVolumeMenuItem + std::to_string(Music::getInstance()->getVolume() / 25 + 1) + ".png"),
		Sprite::create(
			musicAdjustedVolumeMenuItem + std::to_string(Music::getInstance()->getVolume() / 25 + 1) + ".png"),
		Sprite::create(
			musicAdjustedVolumeMenuItem + std::to_string(Music::getInstance()->getVolume() / 25 + 1) + ".png"),
		[&](Ref* sender)
		{
			auto index = Music::getInstance()->getVolume() / 25;
			Music::getInstance()->setVolume(25 * ((index + 1) % 5));
			index = Music::getInstance()->getVolume() / 25;
			// 音量设置为0、25、50、75、100

			musicMenuItem->setNormalImage(Sprite::create(
				musicAdjustedVolumeMenuItem + std::to_string(index + 1) + ".png"));
			musicMenuItem->setSelectedImage(Sprite::create(
				musicAdjustedVolumeMenuItem + std::to_string(index + 1) + ".png"));
		});
	musicMenuItem->setPosition(
		settingButton->getParent()->convertToWorldSpace(courseMenuItem->getPosition()) - Vec2(
			settingButton->getContentSize().width - 10, 0));
	musicMenuItem->setVisible(false);

	// TODO 改图改状态
	sound = Sprite::create(soundMenuItemNormal);
	soundMenuItem = MenuItemSprite::create(sound, sound, sound, [&](Ref* sender)
	{
		Sound::getInstance()->setStatus(!Sound::getInstance()->getStatus());
	});
	soundMenuItem->setPosition(
		settingButton->getParent()->convertToWorldSpace(musicMenuItem->getPosition()) - Vec2(
			settingButton->getContentSize().width, 0));
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
				courseMenuItem->setOpacity(0);
				musicMenuItem->setOpacity(0);
				soundMenuItem->setOpacity(0);

				// common action
				const auto delay = DelayTime::create(0.25);
				const auto fadeIn = FadeIn::create(0.25);

				// course action
				const auto courseMoveBy = MoveBy::create(0.25, Vec2(-25, 0));
				const auto courseSpawn = Spawn::create(fadeIn, delay, courseMoveBy, delay, nullptr);

				// music action
				const auto musicMoveBy = MoveBy::create(0.25, Vec2(-35, 0));
				const auto musicSpawn = Sequence::create(
					delay, Spawn::create(fadeIn, delay, musicMoveBy, delay, nullptr), nullptr);

				// sound action
				const auto soundMoveBy = MoveBy::create(0.25, Vec2(-40, 0));
				const auto soundSpawn = Sequence::create(delay, delay,
				                                         Spawn::create(fadeIn, delay, soundMoveBy, delay, nullptr),
				                                         nullptr);

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
				const auto courseSpawn = Sequence::create(delay, delay,
				                                          Spawn::create(courseMoveBy, nullptr),
				                                          nullptr);

				//music action
				const auto musicMoveBy = MoveBy::create(0.25, Vec2(35, 0));
				const auto musicSpawn = Sequence::create(
					delay, Spawn::create(musicMoveBy, nullptr), nullptr);

				//sound action
				const auto soundMoveBy = MoveBy::create(0.25, Vec2(40, 0));
				const auto soundSpawn = Spawn::create(soundMoveBy, nullptr);

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
