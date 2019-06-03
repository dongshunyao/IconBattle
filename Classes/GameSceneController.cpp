#include "GameSceneController.h"

GameSceneController* GameSceneController::instance = nullptr;

GameSceneController* GameSceneController::getInstance()
{
	if (instance == nullptr) instance = new GameSceneController;
	return instance;
}

void GameSceneController::startPracticeGame(bool isClassical)
{
	Director::getInstance()->pushScene(GameScene::createScene(1, 1, true));
}

void GameSceneController::startLevelGame(bool isClassical, int level) {}
void GameSceneController::startInfiniteGame(bool isClassical) {}
