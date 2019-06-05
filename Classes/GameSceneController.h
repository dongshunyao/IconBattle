#ifndef __GAME_SCENE_CONTROLLER_H__
#define __GAME_SCENE_CONTROLLER_H__

#include "cocos2d.h"
#include "GameScene.h"
#include "LevelScene.h"

USING_NS_CC;

class GameSceneController
{
public:
	static GameSceneController* getInstance();

#pragma region Game Information
	// pair<totalScore, stepNumber>
	using GameInfo = pair<int, int>;

	// TODO 数值修改 @PJ
	const GameInfo classicalPractice = {3000, 2333};
	const GameInfo plusPractice = {4000, 2333};

	const GameInfo classicalLevel[10] =
	{
		{1000, 10},
		{1000, 10},
		{1000, 10},
		{1000, 10},
		{1000, 10},
		{1000, 10},
		{1000, 10},
		{1000, 10},
		{1000, 10},
		{1000, 10},
	};
	const GameInfo plusLevel[10] =
	{
		{1000, 10},
		{1000, 10},
		{1000, 10},
		{1000, 10},
		{1000, 10},
		{1000, 10},
		{1000, 10},
		{1000, 10},
		{1000, 10},
		{1000, 10},
	};

	const GameInfo classicalChallenge = {100000, 100};
	const GameInfo plusChallenge = {200000, 100};
#pragma endregion

	void startPracticeGame(bool isClassical);
	void startLevelGame(bool isClassical);
	void startChallengeGame(bool isClassical);

	// TODO 掉落结算 User更新 网络排行榜更新

private:
	friend class GameScene;

	static GameSceneController* instance;
	GameSceneController() = default;
};

#endif
