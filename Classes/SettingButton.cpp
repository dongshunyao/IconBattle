#include "SettingButton.h"

bool SettingButton::init()
{
	if (!Node::init()) return false;

	settingButton = ui::Button::create(settingButtonNormal, settingButtonSelected,

	                                   settingButtonDisabled);

	this->addChild(settingButton);

	// settingButton响应，弹出设置内容
	settingButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			if (!popItem)
			{
				//TODO 按钮图片更换
				// 添加精灵菜单
				course = Sprite::create(courseMenuItemNormal);
				courseMenuItem = MenuItemSprite::create(course, course, course, [&](Ref* sender)
				{
					// TODO 教程
				});
				courseMenuItem->setPosition(
					settingButton->getParent()->convertToWorldSpace(settingButton->getPosition()));

				music = Sprite::create(musicMenuItemNormal);
				musicMenuItem = MenuItemSprite::create(music, music, music, [&](Ref* sender)
				{
					musicVolume++;
					Music::getInstance()->setVolume(100 - 20 * (musicVolume % 6)); // 音量设置为0、20、40、60、80、100
				});
				musicMenuItem->setPosition(
					settingButton->getParent()->convertToWorldSpace(settingButton->getPosition()));

				sound = Sprite::create(soundMenuItemNormal);
				soundMenuItem = MenuItemSprite::create(sound, sound, sound, [&](Ref* sender)
				{
					if (!soundPlay)
					{
						Sound::getInstance()->stop();
						soundPlay = true;
					}
					else
					{
						Sound::getInstance()->play("/sound/clear.mp3");
						soundPlay = false;
					}
				});
				soundMenuItem->setPosition(
					settingButton->getParent()->convertToWorldSpace(settingButton->getPosition()));


#pragma region Appear Action
				// common action
				const auto delay = DelayTime::create(0.25);
				const auto fadeIn = FadeIn::create(0.25);

				//course action
				const auto courseMoveBy = MoveBy::create(0.25, Vec2(-75, 0));
				const auto courseSpawn = Spawn::create(fadeIn, delay, courseMoveBy, delay, nullptr);

				//music action
				const auto musicMoveBy = MoveBy::create(0.25, Vec2(-135, 0));
				const auto musicSpawn = Spawn::create(fadeIn, delay, musicMoveBy, delay, nullptr);

				//sound action
				const auto soundMoveBy = MoveBy::create(0.25, Vec2(-195, 0));
				const auto soundSpawn = Spawn::create(fadeIn, delay, soundMoveBy, delay, nullptr);

				courseMenuItem->runAction(courseSpawn);
				musicMenuItem->runAction(musicSpawn);
				soundMenuItem->runAction(soundSpawn);

				menu = Menu::create(courseMenuItem, musicMenuItem, soundMenuItem, nullptr);
				Director::getInstance()->getRunningScene()->addChild(menu, 4);
				menu->setPosition(Point(0, 0));


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
				const auto courseMoveBy = MoveBy::create(0.25, Vec2(75, 0));
				const auto courseSpawn = Spawn::create(fadeOut, delay, courseMoveBy, delay, nullptr);

				//music action
				const auto musicMoveBy = MoveBy::create(0.25, Vec2(135, 0));
				const auto musicSpawn = Spawn::create(fadeOut, delay, musicMoveBy, delay, nullptr);

				//sound action
				const auto soundMoveBy = MoveBy::create(0.25, Vec2(195, 0));
				const auto soundSpawn = Spawn::create(fadeOut, delay, soundMoveBy, delay, nullptr);

				courseMenuItem->runAction(courseSpawn);
				musicMenuItem->runAction(musicSpawn);
				soundMenuItem->runAction(soundSpawn);

#pragma endregion
				popItem = false;

				Director::getInstance()->getRunningScene()->removeChild(menu);
			}
		}
	});

	return true;
}
