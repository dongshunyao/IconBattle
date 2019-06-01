#include "GameSceneController.h"

GameSceneController* GameSceneController::instance = nullptr;

GameSceneController* GameSceneController::getInstance()
{
	if (instance == nullptr) instance = new GameSceneController;
	return instance;
}

void GameSceneController::startPracticeGame(bool isClassical)
{
}
