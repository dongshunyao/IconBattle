#include "GameScene.h"

void GameScene::showResult(const bool result, int mode)
{
	// TODO 代码复用，但dialog声明放在外面，在else语句块中会报异常

	if (mode == 0)
	{
		const auto resultDialog = Dialog::create(theme->gameSceneDialogBackground, Size(640, 480));

		resultDialog->addButton(MenuItemSprite::create(
			Sprite::create(theme->gameSceneNoButtonNormal),
			Sprite::create(theme->gameSceneNoButtonSelected),
			Sprite::create(theme->gameSceneNoButtonNormal),
			[&](Ref* sender)
			{
				Director::getInstance()->popScene();
			}));

		resultDialog->addButton(MenuItemSprite::create(
			Sprite::create("/image/gamescene/common/share_button_normal.png"),
			Sprite::create("/image/gamescene/common/share_button_selected.png"),
			Sprite::create("/image/gamescene/common/share_button_normal.png"),
			[&,resultDialog](Ref* sender)
			{
				const auto width = resultDialog->getContentSize().width / 7;
				auto qq = MenuItemSprite::create(Sprite::create("/image/gamescene/common/qq.png"),
				                                 Sprite::create("/image/gamescene/common/qq.png"),
				                                 Sprite::create("/image/gamescene/common/qq.png"));

				qq->setPosition(Point(
					SCREEN_WIDTH / 2 - resultDialog->getContentSize().width / 2.8 + width,
					SCREEN_HEIGHT / 2 - resultDialog->getContentSize().height / 2 + 150));

				qq->setOpacity(0);

				auto weibo = MenuItemSprite::create(Sprite::create("/image/gamescene/common/weibo.png"),
				                                    Sprite::create("/image/gamescene/common/weibo.png"),
				                                    Sprite::create("/image/gamescene/common/weibo.png"));

				weibo->setPosition(Point(
					SCREEN_WIDTH / 2 - resultDialog->getContentSize().width / 2.8 + width * 2,
					SCREEN_HEIGHT / 2 - resultDialog->getContentSize().height / 2 + 150));
				weibo->setOpacity(0);

				auto renren = MenuItemSprite::create(Sprite::create("/image/gamescene/common/renren.png"),
				                                     Sprite::create("/image/gamescene/common/renren.png"),
				                                     Sprite::create("/image/gamescene/common/renren.png"));

				renren->setPosition(Point(
					SCREEN_WIDTH / 2 - resultDialog->getContentSize().width / 2.8 + width * 3,
					SCREEN_HEIGHT / 2 - resultDialog->getContentSize().height / 2 + 150));
				renren->setOpacity(0);
				auto douban = MenuItemSprite::create(Sprite::create("/image/gamescene/common/douban.png"),
				                                     Sprite::create("/image/gamescene/common/douban.png"),
				                                     Sprite::create("/image/gamescene/common/douban.png"));


				douban->setPosition(Point(
					SCREEN_WIDTH / 2 - resultDialog->getContentSize().width / 2.8 + width * 4,
					SCREEN_HEIGHT / 2 - resultDialog->getContentSize().height / 2 + 150));

				douban->setOpacity(0);

				const auto fadeIn = FadeIn::create(0.5);
				const auto fadeOut = FadeOut::create(0.5);
				const auto delay = DelayTime::create(0.5);

				if (!isAppear)
				{
					const auto menu = Menu::create(qq, weibo, douban, renren, nullptr);
					menu->setPosition(Point(0, 0));
					this->addChild(menu, 24);

					qq->runAction(fadeIn);
					weibo->runAction(Sequence::create(delay, fadeIn, nullptr));
					renren->runAction(Sequence::create(delay, delay, fadeIn, nullptr));
					douban->runAction(Sequence::create(delay, delay, delay, fadeIn, nullptr));
					isAppear = true;
				}
				else
				{
					qq->runAction(fadeOut);
					weibo->runAction(Sequence::create(delay, fadeOut, nullptr));
					renren->runAction(Sequence::create(delay, delay, fadeOut, nullptr));
					douban->runAction(Sequence::create(delay, delay, delay, fadeOut, nullptr));
					isAppear = false;
				}
			}));

		resultDialog->addButton(MenuItemSprite::create(
			Sprite::create("/image/gamescene/common/next_button_normal.png"),
			Sprite::create("/image/gamescene/common/next_button_selected.png"),
			Sprite::create("/image/gamescene/common/next_button_normal.png"),
			[&](Ref* sender)
			{
				// TODO next
			}));

		resultDialog->setTitle("Congratulations", 50);
		resultDialog->addLabel(MenuItemLabel::create(
			Label::createWithTTF("Used Steps : " + std::to_string(stepNumber), theme->semiBoldFont, 50)));


		this->addChild(resultDialog, 22);
	}
	else
	{
		auto layerColor = LayerColor::create();
		layerColor->setScale(SCREEN_WIDTH, SCREEN_HEIGHT);
		layerColor->setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		layerColor->setColor(Color3B(0, 0, 0));
		layerColor->setOpacity(128);
		this->addChild(layerColor, 21);
		_eventDispatcher->pauseEventListenersForTarget(this, true);

		// 两个精灵实现结果先后出现
		auto first = Sprite::create(theme->gameSceneResultSprite + (result ? "0.png" : "2.png"));
		auto second = Sprite::create(theme->gameSceneResultSprite + (result ? "1.png" : "3.png"));

		first->setPosition(SCREEN_WIDTH / 2 - first->getContentSize().width / 2, SCREEN_HEIGHT / 2);
		second->setPosition(SCREEN_WIDTH / 2 + second->getContentSize().width / 2, SCREEN_HEIGHT / 2);
		first->setOpacity(0);
		second->setOpacity(0);

		this->addChild(first, 22);
		this->addChild(second, 22);

		const auto delay = DelayTime::create(1);
		const auto fadeIn = FadeIn::create(1);
		const auto fadeOut = FadeOut::create(1);

		/*const auto firstMoveTo = MoveTo::create(1, Vec2(SCREEN_WIDTH / 2 - first->getContentSize().width / 2,
		                                                SCREEN_HEIGHT / 2 + 200));
		const auto secondMoveTo = MoveTo::create(1, Vec2(SCREEN_WIDTH / 2 + second->getContentSize().width / 2,
		                                                 SCREEN_HEIGHT / 2 + 200));*/

		first->runAction(Sequence::create(fadeIn, delay, fadeOut, delay, nullptr));
		second->runAction(Sequence::create(
			delay, fadeIn, delay, fadeOut, DelayTime::create(0.5), CallFunc::create(
				[&,layerColor,result,mode]()
				{
					const auto resultDialog = Dialog::create(theme->gameSceneDialogBackground, Size(640, 480));
					resultDialog->addButton(MenuItemSprite::create(
						Sprite::create(theme->gameSceneNoButtonNormal),
						Sprite::create(theme->gameSceneNoButtonSelected),
						Sprite::create(theme->gameSceneNoButtonNormal),
						[&](Ref* sender)
						{
							Director::getInstance()->popScene();
						}));

					resultDialog->addButton(MenuItemSprite::create(
						Sprite::create("/image/gamescene/common/share_button_normal.png"),
						Sprite::create("/image/gamescene/common/share_button_selected.png"),
						Sprite::create("/image/gamescene/common/share_button_normal.png"),
						[&](Ref* sender)
						{
							// TODO share
						}));

					resultDialog->addButton(MenuItemSprite::create(
						Sprite::create("/image/gamescene/common/next_button_normal.png"),
						Sprite::create("/image/gamescene/common/next_button_selected.png"),
						Sprite::create("/image/gamescene/common/next_button_normal.png"),
						[&](Ref* sender)
						{
							// TODO next
						}));
					resultDialog->setTitle(result ? "Congratulations" : "Pity", 50);

					// TODO COIN

					if (result)
					{
						resultDialog->addLabel(MenuItemLabel::create(
							Label::createWithTTF("Used Steps : " + std::to_string(stepNumber), theme->semiBoldFont,
							                     50)));
						resultDialog->addLabel(MenuItemLabel::create(
							Label::createWithTTF("Used Hints : " + std::to_string(3 - hintNumber), theme->semiBoldFont,
							                     50)));
						resultDialog->addLabel(MenuItemLabel::create(
							Label::createWithTTF("Score : " + currentScoreLabel->getString(), theme->semiBoldFont,
							                     50)));
					}

					resultDialog->addLabel(MenuItemLabel::create(
						Label::createWithTTF("Coins : " + std::to_string(5), theme->semiBoldFont, 50)));

					if (mode == 2)
					{
						auto rank = Network::getInstance()->getRank(isClassical);
						for (auto item : rank)
						{
							if (item.first == User::getInstance()->getUserName())
								resultDialog->addLabel(MenuItemLabel::create(
									Label::createWithTTF("Rank : " + std::to_string(item.second), theme->semiBoldFont,
									                     50)));
						}
					}

					this->removeChild(layerColor);


					this->addChild(resultDialog, 22);
				}), nullptr));
	}
}
