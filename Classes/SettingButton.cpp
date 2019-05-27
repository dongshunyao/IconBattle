#include "SettingButton.h"

SettingButton::SettingButton(cocos2d::Scene* scene)
{
	currentScene = scene;
	settingButton = ui::Button::create(settingButtonNormal, settingButtonSelected,

	                                   settingButtonDisabled);


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
				courseMenuItem->setPosition(1050, 850);

				music = Sprite::create(musicMenuItemNormal);
				musicMenuItem = MenuItemSprite::create(music, music, music, [&](Ref* sender)
				{
					musicVolume++;
					Music::getInstance()->setVolume(100 - 20 * (musicVolume % 6)); //音量设置为0、20、40、60、80、100
				});
				musicMenuItem->setPosition(1050, 850);

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
				soundMenuItem->setPosition(1050, 850);


#pragma region Appear Action
				// common action
				const auto delay = DelayTime::create(0.25);
				const auto fadeIn = FadeIn::create(0.25);

				//course action
				const auto courseMoveTo = MoveTo::create(0.25, Vec2(975, 850));
				const auto courseSpawn = Spawn::create(fadeIn, delay, courseMoveTo, delay, nullptr);

				//music action
				const auto musicMoveTo = MoveTo::create(0.25, Vec2(915, 850));
				const auto musicSpawn = Spawn::create(fadeIn, delay, musicMoveTo, delay, nullptr);

				//sound action
				const auto soundMoveTo = MoveTo::create(0.25, Vec2(855, 850));
				const auto soundSpawn = Spawn::create(fadeIn, delay, soundMoveTo, delay, nullptr);

				courseMenuItem->runAction(courseSpawn);
				musicMenuItem->runAction(musicSpawn);
				soundMenuItem->runAction(soundSpawn);

				menu = Menu::create(courseMenuItem, musicMenuItem, soundMenuItem, nullptr);
				currentScene->addChild(menu);
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
				const auto courseMoveTo = MoveTo::create(0.25, Vec2(1050, 850));
				const auto courseSpawn = Spawn::create(fadeOut, delay, courseMoveTo, delay, nullptr);

				//music action
				const auto musicMoveTo = MoveTo::create(0.25, Vec2(1050, 850));
				const auto musicSpawn = Spawn::create(fadeOut, delay, musicMoveTo, delay, nullptr);

				//sound action
				const auto soundMoveTo = MoveTo::create(0.25, Vec2(1050, 850));
				const auto soundSpawn = Spawn::create(fadeOut, delay, soundMoveTo, delay, nullptr);

				courseMenuItem->runAction(courseSpawn);
				musicMenuItem->runAction(musicSpawn);
				soundMenuItem->runAction(soundSpawn);

#pragma endregion
				popItem = false;

				currentScene->removeChild(menu);
			}
		}
	});

	settingButton->setPosition(Point(1050, 850));
	currentScene->addChild(settingButton);
}
