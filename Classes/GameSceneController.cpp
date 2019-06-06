#include "GameSceneController.h"

GameSceneController* GameSceneController::instance = nullptr;

GameSceneController* GameSceneController::getInstance()
{
	if (instance == nullptr) instance = new GameSceneController;
	return instance;
}

void GameSceneController::startPracticeGame(const bool isClassical)
{
	Director::getInstance()->pushScene(GameScene::createScene(30, 1, isClassical, PRACTICE_MODE));
}

void GameSceneController::startLevelGame(const bool isClassical)
{
	Director::getInstance()->pushScene(LevelScene::createScene(isClassical));
}

void GameSceneController::startChallengeGame(const bool isClassical)
{
	Director::getInstance()->pushScene(GameScene::createScene(25, 1, isClassical, CHALLENGE_MODE));
}

int GameSceneController::randomCoins() const
{
	const auto random = Util::getRandomNumber(50);
	if (random == 33)
		return 3;
	return 0;
}

void GameSceneController::update() const
{
	const auto temp = User::getInstance()->getCoin();
	User::getInstance()->setCoin(temp + randomCoins());
}

void GameSceneController::update(const bool isClassical, const int level)
{
	if (isClassical)
		User::getInstance()->setUnlockedClassicalLevel(level);
	else
		User::getInstance()->setUnlockedPlusLevel(level);
}
