#include "GameScene.h"

Scene* GameScene::createScene(const int stepNumber, const int totalScore, const bool isClassical, const int mode,
                              const int level, const int hintNumber)
{
	const auto scene = GameScene::create();

	// 初始化变量
	scene->stepNumber = stepNumber;
	scene->totalScore = totalScore;
	scene->isClassical = isClassical;
	scene->hintNumber = hintNumber;
	scene->mode = mode;
	scene->level = level;

	// 初始化精灵图集
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("/image/common/adobetheme/icon/adobe.plist",
	                                                         "/image/common/adobetheme/icon/adobe.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("/image/common/jetbraintheme/icon/jetbrain.plist",
	                                                         "/image/common/jetbraintheme/icon/jetbrain.png");

	// 初始化背景板及按钮
	scene->initInformationBoard();

	// 初始化游戏
	scene->initGameBoard();

	return scene;
}

void GameScene::showScore(const ActorInformation actorInformation)
{
	// TODO 换字体？换颜色？
	auto scoreLabel = Label::createWithTTF(to_string(actorInformation.score), theme->semiBoldFont, 36);

	const auto position = getPositionByIndex(actorInformation.blockIndex);
	scoreLabel->setPosition(position.first, position.second);

	scoreLabel->enableShadow(Color4B::ORANGE);
	scoreLabel->runAction(Sequence::create(
		Spawn::create(MoveBy::create(1.0f, {40, 40}), FadeOut::create(1.0f), nullptr),
		CallFunc::create([&, scoreLabel]() { removeChild(scoreLabel); }), nullptr));

	addChild(scoreLabel, 19);

	if (mode == CHALLENGE_MODE && currentScore + actorInformation.score >= 3 * totalScore / 4)
		setTotalScore(totalScore * 3 / 2);

	addCurrentScore(actorInformation.score);
}

void GameScene::endGame()
{
	switch (mode)
	{
		// 练习模式一定会成功的
	case PRACTICE_MODE:
		{
			const auto usedSteps = GameSceneController::getInstance()->classicalPractice.second - stepNumber;
			showSuccessfulResult(usedSteps, 3 - hintNumber);
			break;
		}

	case LEVEL_MODE:
		{
			const auto stepNumberScore = EVERY_STEP_SCORE * stepNumber;
			const auto hintNumberScore = EVERY_HINT_SCORE * hintNumber;

			// 失败
			if (currentScore + stepNumberScore + hintNumberScore < totalScore)
			{
				showFailedResult(totalScore, currentScore);
				break;
			}

			// 成功
			showSuccessfulResult(false, stepNumberScore, hintNumberScore, currentScore);
			break;
		}
	case CHALLENGE_MODE:
		{
			const auto stepNumberScore = EVERY_STEP_SCORE * stepNumber;
			const auto hintNumberScore = EVERY_HINT_SCORE * hintNumber;

			// 成功
			showSuccessfulResult(true, stepNumberScore, hintNumberScore, currentScore);
			break;
		}
	}
}

void GameScene::showOneLineParticle(const Pair index, const bool isVertical)
{
	auto particle = ParticleSystemQuad::create(ONE_LINE_PARTICLE);

	particle->setPosition(getPositionByIndex(index).first, 85 + 700 / 2);
	if (!isVertical)
	{
		particle->setRotation(90);
		particle->setPosition(450 + 700 / 2, getPositionByIndex(index).second);
	}

	particle->setAutoRemoveOnFinish(true);
	addChild(particle, 17);
	// TODO: 粒子特效音效
}

void GameScene::showExplosion(const Pair index)
{
	auto particle = ParticleSystemQuad::create(EXPLOSION_PARTICLE);

	particle->setPosition(getPositionByIndex(index).first, getPositionByIndex(index).second);
	particle->setScale(0.7f);
	particle->setAutoRemoveOnFinish(true);
	addChild(particle, 17);
	// TODO: 粒子特效音效
}

void GameScene::showFullBoardParticle()
{
	auto particle = ParticleSystemQuad::create(FULL_PARTICLE);

	particle->setPosition(450 + 700 / 2, 85 + 700 / 2);
	particle->setScale(0.7f);
	particle->setAutoRemoveOnFinish(true);
	addChild(particle, 17);
	// TODO: 粒子特效音效
}

void GameScene::showSingleParticle(const Pair index, const int type)
{
	auto particle = ParticleSystemQuad::create(ONE_BLOCK_PARTICLE[type]);

	particle->setPosition(getPositionByIndex(index).first, getPositionByIndex(index).second);
	particle->setScale(0.6f);
	// 设置持续时间
	//particle->setDuration(3.0f);
	particle->setAutoRemoveOnFinish(true);
	addChild(particle, 17);
	// TODO: 粒子特效音效
}
