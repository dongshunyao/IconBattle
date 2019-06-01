#ifndef __GAME_SCENE_CONTROLLER_H__
#define __GAME_SCENE_CONTROLLER_H__

class GameSceneController
{
public:
	static GameSceneController* getInstance();

	void startPracticeGame(bool isClassical);
	//void startLevelGame(bool isClassical, int level);
	//void startInfiniteGame(bool isClassical);

private:
	static GameSceneController* instance;
	GameSceneController() = default;


};

#endif
