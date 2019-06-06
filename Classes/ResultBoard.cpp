#include "GameScene.h"

// 失败结果
void GameScene::showFailedResult(int targetScore, int realScore)
{
	auto layerColor = LayerColor::create();
	layerColor->setScale(SCREEN_WIDTH, SCREEN_HEIGHT);
	layerColor->setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	layerColor->setColor(Color3B(0, 0, 0));
	layerColor->setOpacity(128);
	this->addChild(layerColor, 21);
	_eventDispatcher->pauseEventListenersForTarget(this, true);
	auto first = Sprite::create(theme->gameSceneResultSprite + ("2.png"));
	auto second = Sprite::create(theme->gameSceneResultSprite + ("3.png"));

	first->setPosition(SCREEN_WIDTH / 2 - first->getContentSize().width / 2, SCREEN_HEIGHT / 2);
	second->setPosition(SCREEN_WIDTH / 2 + second->getContentSize().width / 2, SCREEN_HEIGHT / 2);
	first->setOpacity(0);
	second->setOpacity(0);

	this->addChild(first, 22);
	this->addChild(second, 22);

	const auto delay = DelayTime::create(1);
	const auto fadeIn = FadeIn::create(1);

	first->runAction(Sequence::create(fadeIn, delay, nullptr));
	second->runAction(Sequence::create(
		delay, fadeIn, CallFunc::create(
			[&, layerColor,targetScore,realScore,first,second]()
			{
				this->removeChild(first);
				this->removeChild(second);

				const auto resultDialog = Dialog::create(theme->gameSceneDialogBackground, Size(640, 480));
				resultDialog->addButton(MenuItemSprite::create(
					Sprite::create(theme->gameSceneNoButtonNormal),
					Sprite::create(theme->gameSceneNoButtonSelected),
					Sprite::create(theme->gameSceneNoButtonNormal),
					[&](Ref* sender)
					{
						Director::getInstance()->popScene();
					}));

				resultDialog->setTitle("遗憾", 100);

				resultDialog->addLabel(MenuItemLabel::create(
					Label::createWithTTF("目标分数 : " + std::to_string(targetScore), theme->semiBoldFont,
					                     50)));
				resultDialog->addLabel(MenuItemLabel::create(
					Label::createWithTTF("实际得分 : " + std::to_string(realScore), theme->semiBoldFont,
					                     50)));

				resultDialog->addLabel(MenuItemLabel::create(
					Label::createWithTTF("很遗憾你没有达到目标分数", theme->semiBoldFont,
					                     50)));

				this->removeChild(layerColor);


				this->addChild(resultDialog, 22);
			}), nullptr));
}

// 练习结果
void GameScene::showSuccessfulResult(int usedSteps, int usedHints)
{
	auto layerColor = LayerColor::create();
	layerColor->setScale(SCREEN_WIDTH, SCREEN_HEIGHT);
	layerColor->setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	layerColor->setColor(Color3B(0, 0, 0));
	layerColor->setOpacity(128);
	this->addChild(layerColor, 21);
	_eventDispatcher->pauseEventListenersForTarget(this, true);
	auto first = Sprite::create(theme->gameSceneResultSprite + ("0.png"));
	auto second = Sprite::create(theme->gameSceneResultSprite + ("1.png"));

	first->setPosition(SCREEN_WIDTH / 2 - first->getContentSize().width / 2, SCREEN_HEIGHT / 2);
	second->setPosition(SCREEN_WIDTH / 2 + second->getContentSize().width / 2, SCREEN_HEIGHT / 2);
	first->setOpacity(0);
	second->setOpacity(0);

	this->addChild(first, 22);
	this->addChild(second, 22);

	const auto delay = DelayTime::create(1);
	const auto fadeIn = FadeIn::create(1);

	first->runAction(Sequence::create(fadeIn, delay, nullptr));
	second->runAction(Sequence::create(
		delay, fadeIn, CallFunc::create(
			[&, layerColor, usedSteps, usedHints,first,second]()
			{
				this->removeChild(first);
				this->removeChild(second);

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
					Sprite::create(theme->gameSceneShareButtonNormal),
					Sprite::create(theme->gameSceneShareButtonSelected),
					Sprite::create(theme->gameSceneShareButtonNormal),
					[&, resultDialog](Ref* sender)
					{
						const auto width = resultDialog->getContentSize().width / 7;
						auto qq = MenuItemSprite::create(Sprite::create(theme->gameSceneQQShareButtonNormal),
						                                 Sprite::create(theme->gameSceneQQShareButtonSelected),
						                                 Sprite::create(theme->gameSceneQQShareButtonNormal));
						[&](Ref* sender)
						{
							// TODO share
						};
						qq->setPosition(Point(
							SCREEN_WIDTH / 2 - resultDialog->getContentSize().width / 2.8 + width,
							SCREEN_HEIGHT / 2 - resultDialog->getContentSize().height / 2 + 150));

						qq->setOpacity(0);

						auto weibo = MenuItemSprite::create(Sprite::create(theme->gameSceneWBShareButtonNormal),
						                                    Sprite::create(theme->gameSceneWBShareButtonSelected),
						                                    Sprite::create(theme->gameSceneWBShareButtonNormal),
						                                    [&](Ref* sender)
						                                    {
							                                    // TODO share
						                                    });

						weibo->setPosition(Point(
							SCREEN_WIDTH / 2 - resultDialog->getContentSize().width / 2.8 + width * 2,
							SCREEN_HEIGHT / 2 - resultDialog->getContentSize().height / 2 + 150));
						weibo->setOpacity(0);

						auto renren = MenuItemSprite::create(Sprite::create(theme->gameSceneRRShareButtonNormal),
						                                     Sprite::create(theme->gameSceneRRShareButtonSelected),
						                                     Sprite::create(theme->gameSceneRRShareButtonNormal),
						                                     [&](Ref* sender)
						                                     {
							                                     // TODO share
						                                     });

						renren->setPosition(Point(
							SCREEN_WIDTH / 2 - resultDialog->getContentSize().width / 2.8 + width * 3,
							SCREEN_HEIGHT / 2 - resultDialog->getContentSize().height / 2 + 150));
						renren->setOpacity(0);
						auto douban = MenuItemSprite::create(Sprite::create(theme->gameSceneDBShareButtonNormal),
						                                     Sprite::create(theme->gameSceneDBShareButtonSelected),
						                                     Sprite::create(theme->gameSceneDBShareButtonNormal),
						                                     [&](Ref* sender)
						                                     {
							                                     // TODO share
						                                     });

						douban->setPosition(Point(
							SCREEN_WIDTH / 2 - resultDialog->getContentSize().width / 2.8 + width * 4,
							SCREEN_HEIGHT / 2 - resultDialog->getContentSize().height / 2 + 150));

						douban->setOpacity(0);

						const auto buttonFadeIn = FadeIn::create(0.5);
						const auto buttonDelay = DelayTime::create(0.5);


						const auto menu = Menu::create(qq, weibo, douban, renren, nullptr);
						menu->setPosition(Point(0, 0));

						if (!isShareButtonAppear)
						{
							this->addChild(menu, 24);
							qq->runAction(buttonFadeIn);
							weibo->runAction(Sequence::create(buttonDelay, buttonFadeIn, nullptr));
							renren->runAction(Sequence::create(buttonDelay, buttonDelay, buttonFadeIn, nullptr));
							douban->runAction(
								Sequence::create(buttonDelay, buttonDelay, buttonDelay, buttonFadeIn, nullptr));
							isShareButtonAppear = true;
						}
					}));

				resultDialog->setTitle("恭喜", 100);

				resultDialog->addLabel(MenuItemLabel::create(
					Label::createWithTTF("交换次数 : " + std::to_string(usedSteps), theme->semiBoldFont,
					                     50)));
				resultDialog->addLabel(MenuItemLabel::create(
					Label::createWithTTF("提示次数 : " + std::to_string(usedHints), theme->semiBoldFont,
					                     50)));

				this->removeChild(layerColor);


				this->addChild(resultDialog, 22);
			}), nullptr));
}

// 闯关和挑战结果
void GameScene::showSuccessfulResult(bool isChallenge, int remainSteps, int remainHints, int score)
{
	auto layerColor = LayerColor::create();
	layerColor->setScale(SCREEN_WIDTH, SCREEN_HEIGHT);
	layerColor->setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	layerColor->setColor(Color3B(0, 0, 0));
	layerColor->setOpacity(128);
	this->addChild(layerColor, 21);
	_eventDispatcher->pauseEventListenersForTarget(this, true);
	auto first = Sprite::create(theme->gameSceneResultSprite + ("0.png"));
	auto second = Sprite::create(theme->gameSceneResultSprite + ("1.png"));

	first->setPosition(SCREEN_WIDTH / 2 - first->getContentSize().width / 2, SCREEN_HEIGHT / 2);
	second->setPosition(SCREEN_WIDTH / 2 + second->getContentSize().width / 2, SCREEN_HEIGHT / 2);
	first->setOpacity(0);
	second->setOpacity(0);

	this->addChild(first, 22);
	this->addChild(second, 22);

	const auto delay = DelayTime::create(1);
	const auto fadeIn = FadeIn::create(1);

	first->runAction(Sequence::create(fadeIn, delay, nullptr));
	second->runAction(Sequence::create(
		delay, fadeIn, CallFunc::create(
			[&, layerColor, isChallenge,remainSteps, remainHints,score,first,second]()
			{
				this->removeChild(first);
				this->removeChild(second);

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
					Sprite::create(theme->gameSceneShareButtonNormal),
					Sprite::create(theme->gameSceneShareButtonSelected),
					Sprite::create(theme->gameSceneShareButtonNormal),
					[&, resultDialog](Ref* sender)
					{
						const auto width = resultDialog->getContentSize().width / 7;
						auto qq = MenuItemSprite::create(Sprite::create(theme->gameSceneQQShareButtonNormal),
						                                 Sprite::create(theme->gameSceneQQShareButtonSelected),
						                                 Sprite::create(theme->gameSceneQQShareButtonNormal),
						                                 [&](Ref* sender)
						                                 {
							                                 // TODO share
						                                 });

						qq->setPosition(Point(
							SCREEN_WIDTH / 2 - resultDialog->getContentSize().width / 2.8 + width,
							SCREEN_HEIGHT / 2 - resultDialog->getContentSize().height / 2 + 150));

						qq->setOpacity(0);

						auto weibo = MenuItemSprite::create(Sprite::create(theme->gameSceneWBShareButtonNormal),
						                                    Sprite::create(theme->gameSceneWBShareButtonSelected),
						                                    Sprite::create(theme->gameSceneWBShareButtonNormal),
						                                    [&](Ref* sender)
						                                    {
							                                    // TODO share
						                                    });

						weibo->setPosition(Point(
							SCREEN_WIDTH / 2 - resultDialog->getContentSize().width / 2.8 + width * 2,
							SCREEN_HEIGHT / 2 - resultDialog->getContentSize().height / 2 + 150));
						weibo->setOpacity(0);

						auto renren = MenuItemSprite::create(Sprite::create(theme->gameSceneRRShareButtonNormal),
						                                     Sprite::create(theme->gameSceneRRShareButtonSelected),
						                                     Sprite::create(theme->gameSceneRRShareButtonNormal),
						                                     [&](Ref* sender)
						                                     {
							                                     // TODO share
						                                     });

						renren->setPosition(Point(
							SCREEN_WIDTH / 2 - resultDialog->getContentSize().width / 2.8 + width * 3,
							SCREEN_HEIGHT / 2 - resultDialog->getContentSize().height / 2 + 150));
						renren->setOpacity(0);
						auto douban = MenuItemSprite::create(Sprite::create(theme->gameSceneDBShareButtonNormal),
						                                     Sprite::create(theme->gameSceneDBShareButtonSelected),
						                                     Sprite::create(theme->gameSceneDBShareButtonNormal),
						                                     [&](Ref* sender)
						                                     {
							                                     // TODO share
						                                     });


						douban->setPosition(Point(
							SCREEN_WIDTH / 2 - resultDialog->getContentSize().width / 2.8 + width * 4,
							SCREEN_HEIGHT / 2 - resultDialog->getContentSize().height / 2 + 150));

						douban->setOpacity(0);

						const auto buttonFadeIn = FadeIn::create(0.5);
						const auto buttonDelay = DelayTime::create(0.5);


						const auto menu = Menu::create(qq, weibo, douban, renren, nullptr);
						menu->setPosition(Point(0, 0));
						this->addChild(menu, 24);

						qq->runAction(buttonFadeIn);
						weibo->runAction(Sequence::create(buttonDelay, buttonFadeIn, nullptr));
						renren->runAction(Sequence::create(buttonDelay, buttonDelay, buttonFadeIn, nullptr));
						douban->runAction(
							Sequence::create(buttonDelay, buttonDelay, buttonDelay, buttonFadeIn, nullptr));
					}));

				const auto addedScore = remainSteps + remainHints + score;


				resultDialog->setTitle("恭喜", 100);

				resultDialog->addLabel(MenuItemLabel::create(
					Label::createWithTTF("交换次数 : " + to_string(remainSteps), theme->semiBoldFont,
					                     50)));
				resultDialog->addLabel(MenuItemLabel::create(
					Label::createWithTTF("提示次数 : " + to_string(remainHints), theme->semiBoldFont,
					                     50)));
				resultDialog->addLabel(MenuItemLabel::create(
					Label::createWithTTF("玩家分数 : " + to_string(score), theme->semiBoldFont,
					                     50)));

				resultDialog->addLabel(MenuItemLabel::create(
					Label::createWithTTF("本局总分 : " + to_string(addedScore), theme->semiBoldFont, 50)));

				if (isChallenge)
				{
					auto rank = Network::getInstance()->getRank(isClassical);


					int position = -1;
					for (auto i = 0; i < rank.size(); i++)
					{
						if (rank[i].first == User::getInstance()->getUserName() && rank[i].second == addedScore)
						{
							position = i;
							break;
						}
					}

					if (position == -1)
					{
						rank.emplace_back(User::getInstance()->getUserName(), remainSteps + remainHints + score);
						sort(rank.begin(), rank.end(), [](const auto& x, const auto& y)
						{
							return x.second == y.second ? x.first < y.first : x.second > y.second;
						});
						for (auto i = 0; i < rank.size(); i++)
						{
							if (rank[i].first == User::getInstance()->getUserName() && rank[i].second == addedScore)
							{
								resultDialog->addLabel(MenuItemLabel::create(
									Label::createWithTTF("当前排名 : " + to_string(i + 1), theme->semiBoldFont, 50)));
								break;
							}
						}
					}
					else
					{
						resultDialog->addLabel(MenuItemLabel::create(
							Label::createWithTTF("当前排名 : " + to_string(position + 1), theme->semiBoldFont, 50)));
					}

					Network::getInstance()->postScore(User::getInstance()->getUserName(),
					                                  remainSteps + remainHints + score, isClassical);


					resultDialog->addButton(MenuItemSprite::create(
						Sprite::create("/image/gamescene/common/rank_normal.png"),
						Sprite::create("/image/gamescene/common/rank_selected.png"),
						Sprite::create("/image/gamescene/common/rank_normal.png"),
						[&,resultDialog](Ref* sender)
						{
							this->removeChild(resultDialog);

							const auto dialog = Dialog::create(theme->menuRankListBackground, Size(500, 600));

							dialog->addListView(true, false, isClassical);
							dialog->setTitle("Classical Rank List", 50);
							dialog->addButton(MenuItemSprite::create(Sprite::create(theme->gameSceneYesButtonNormal),
							                                         Sprite::create(theme->gameSceneYesButtonSelected),
							                                         Sprite::create(theme->gameSceneYesButtonNormal),
							                                         [&](Ref* sender)
							                                         {
								                                         Director::getInstance()
									                                         ->popScene();
							                                         }
							));
							this->addChild(dialog, 20);
						}));
				}
				this->removeChild(layerColor);


				auto coin = Sprite::create(theme->storeSceneCoin);
				coin->setPosition(Point(SCREEN_WIDTH / 2 + resultDialog->getContentSize().width / 2 - 100,
				                        SCREEN_HEIGHT / 2 + resultDialog->getContentSize().height / 2 - 150));
				coin->runAction(Spawn::create(ScaleTo::create(1.5, 0),
				                              MoveTo::create(
					                              1.5, Point(SCREEN_WIDTH / 2 + 300, SCREEN_HEIGHT / 2 + 200)),
				                              nullptr));
				// TODO 硬币清算

				this->addChild(coin, 25);

				this->addChild(resultDialog, 22);
			}), nullptr));
}
