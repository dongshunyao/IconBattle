#include "GameSceneController.h"

GameSceneController* GameSceneController::instance = nullptr;

GameSceneController* GameSceneController::getInstance()
{
	if (instance == nullptr) instance = new GameSceneController;
	return instance;
}

void GameSceneController::startPracticeGame(const bool isClassical)
{
	if (isClassical)
		Director::getInstance()->pushScene(
			GameScene::createScene(classicalPractice.second, classicalPractice.first, isClassical, PRACTICE_MODE));
	else
		Director::getInstance()->pushScene(
			GameScene::createScene(classicalPractice.second, classicalPractice.first, isClassical, PRACTICE_MODE));
}

void GameSceneController::startLevelGame(const bool isClassical, const int level)
{
	if(isClassical)
		Director::getInstance()->pushScene(
			GameScene::createScene(classicalLevel[level].second, classicalLevel[level].first, isClassical, LEVEL_MODE));
	else
		Director::getInstance()->pushScene(
			GameScene::createScene(plusLevel[level].second, plusLevel[level].first, isClassical, LEVEL_MODE));
}

void GameSceneController::startChallengeGame(const bool isClassical)
{
	if (isClassical)
		Director::getInstance()->pushScene(
			GameScene::createScene(classicalChallenge.second, classicalChallenge.first, isClassical, CHALLENGE_MODE));
	else
		Director::getInstance()->pushScene(
			GameScene::createScene(classicalChallenge.second, classicalChallenge.first, isClassical, CHALLENGE_MODE));
}

int GameSceneController::randomCoin(const int percentage) const
{
	const auto random = Util::getRandomNumber(100);
	if (random <= percentage)
	{
		switch (getRandomNumber(5))
		{
		case 3:
			return 3;

		case 2:
		case 1:
			return 2;

		default:
			return 1;
		}
	}

	return 0;
}

int GameSceneController::updateInformation()
{
	coinPercentage += 60 + getRandomNumber(60);
	coinPercentage %= 80;

	const auto coin = randomCoin(coinPercentage);
	User::getInstance()->setCoin(User::getInstance()->getCoin() + coin);
	return coin;
}

int GameSceneController::updateInformation(const bool isClassical, const int level)
{
	if (isClassical) User::getInstance()->setUnlockedClassicalLevel(level);
	else User::getInstance()->setUnlockedPlusLevel(level);

	return updateInformation();
}
