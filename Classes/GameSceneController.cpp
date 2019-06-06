#include "GameSceneController.h"

GameSceneController* GameSceneController::instance = nullptr;

GameSceneController* GameSceneController::getInstance()
{
	if (instance == nullptr) instance = new GameSceneController;
	return instance;
}

void GameSceneController::startPracticeGame(const bool isClassical)
{
	// TODO @PJ
	//Director::getInstance()->pushScene(GameScene::createScene(30, 1000, isClassical, PRACTICE_MODE));
}

void GameSceneController::startLevelGame(const bool isClassical, const int level)
{
	// TODO @PJ
}

void GameSceneController::startChallengeGame(const bool isClassical)
{
	// TODO @PJ
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
