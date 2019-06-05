#include "GameSceneController.h"

GameSceneController* GameSceneController::instance = nullptr;

GameSceneController* GameSceneController::getInstance()
{
	if (instance == nullptr) instance = new GameSceneController;
	return instance;
}

void GameSceneController::startPracticeGame(bool isClassical)
{
	Director::getInstance()->pushScene(GameScene::createScene(30, 1, true, PRACTICE_MODE));
}

void GameSceneController::startLevelGame(const bool isClassical)
{
	Director::getInstance()->pushScene(LevelScene::createScene(isClassical));
}

void GameSceneController::startChallengeGame(bool isClassical) {}
