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

	// TODO 关卡目标数值修改 @PJ
	const GameInfo classicalPractice = {1200, 2333};
	const GameInfo plusPractice = {4000, 2333};

	const GameInfo classicalLevel[10] =
	{
		{300, 2},
		{400, 20},
		{500, 20},
		{600, 20},
		{800, 20},
		{1000, 14},
		{1000, 13},
		{1200, 12},
		{1200, 11},
		{1500, 10},
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

	const GameInfo classicalChallenge = {10000, 60};
	const GameInfo plusChallenge = {10000, 2};
#pragma endregion

	void startPracticeGame(bool isClassical) const;
	// level 0开始
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
