#include "GameScene.h"

void GameScene::showResult(const bool result)
{
	// 两个精灵实现结果先后出现
	auto first = Sprite::create(theme->gameSceneResultSprite + (result ? "2.png" : "0.png"));
	auto second = Sprite::create(theme->gameSceneResultSprite + (result ? "3.png" : "1.png"));

	first->setPosition(SCREEN_WIDTH / 2 - first->getContentSize().width / 2, SCREEN_HEIGHT / 2);
	second->setPosition(SCREEN_WIDTH / 2 + second->getContentSize().width / 2, SCREEN_HEIGHT / 2);
	first->setOpacity(0);
	second->setOpacity(0);

	this->addChild(first, 20);
	this->addChild(second, 20);

	const auto delay = DelayTime::create(1.3);
	const auto fadeIn = FadeIn::create(1.3);
	const auto firstMoveTo = MoveTo::create(1, Vec2(SCREEN_WIDTH / 2 - first->getContentSize().width / 2,
	                                                SCREEN_HEIGHT / 2 + 200));
	const auto secondMoveTo = MoveTo::create(1, Vec2(SCREEN_WIDTH / 2 + second->getContentSize().width / 2,
	                                                 SCREEN_HEIGHT / 2 + 200));
	first->runAction(Sequence::create(fadeIn, delay, firstMoveTo, nullptr));
	second->runAction(Sequence::create(
		delay, fadeIn, secondMoveTo, CallFunc::create(
			[&, first, second]()
			{
				// Todo 排名相关
				first->setVisible(false);
				second->setVisible(false);
			}), nullptr));
}
