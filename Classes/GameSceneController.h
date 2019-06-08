#ifndef __GAME_SCENE_CONTROLLER_H__
#define __GAME_SCENE_CONTROLLER_H__

#include "cocos2d.h"
#include "GameScene.h"
#include "LevelScene.h"
#include "GameBoardInformation.h"
#include "Util.h"

using namespace GameBoardInformation;
USING_NS_CC;

class GameSceneController
{
public:
	static GameSceneController* getInstance();

#pragma region Game Information
	// 基础掉落概率
	int coinPercentage = 5;

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

	const GameInfo classicalChallenge = {100000, 99};
	const GameInfo plusChallenge = {200000, 99};
#pragma endregion

	void startPracticeGame(bool isClassical) const;
	void startLevelGame(bool isClassical, int level) const;
	void startChallengeGame(bool isClassical) const;

	// 挑战模式返回掉落硬币个数
	int updateInformation();
	// 闯关模式返回掉落硬币个数
	int updateInformation(bool isClassical, int level);

private:
	friend class GameScene;
	int randomCoin(int percentage) const;

	static GameSceneController* instance;
	GameSceneController() = default;
};

#endif
