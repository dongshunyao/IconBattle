#ifndef __JET_BRAIN_THEME_H__
#define __JET_BRAIN_THEME_H__

#include "Theme.h"

class JetBrainTheme
	: public Theme
{
public:
	const string themeName = "JetBrain";

#pragma region Loading Sence
	const string iconSet = "/image/loadingscene/jetbraintheme/iconset/large/";
	const string loadingSceneBackground = "/image/loadingscene/jetbraintheme/scene.png";

#pragma endregion

#pragma region Menu Sence
	const string menuSceneBackground = "/image/menuscene/jetbraintheme/background.jpg";

#pragma endregion

	//  TODO 规范化
	const string levelSceneDistantView = "/image/levelscene/jetbraintheme/far.png";
	const string levelSceneForeground = "/image/levelscene/jetbraintheme/front.png";
	const string levelSceneGameButtonNormal = "/image/levelscene/jetbraintheme/game_normal.png";
	const string levelSceneGameButtonSelected = "/image/levelscene/jetbraintheme/game_selected.png";
	const string levelSceneGameButtonDisabled = "/image/levelscene/jetbraintheme/disabled.png";


	const string gameSceneBackground = "/image/gamescene/jetbraintheme/background.png";
	const string gameSceneLevelSpriteBackground = "/image/gamescene/jetbraintheme/level_sprite.png";
	const string gameSceneHintButtonNormal = "/image/gamescene/jetbraintheme/hint_button_normal.png";
	const string gameSceneHintButtonSelected = "/image/gamescene/jetbraintheme/hint_button_selected.png";
	const string gameSceneHintButtonDisabled = "/image/gamescene/jetbraintheme/hint_button_disabled.png";
	const string gameSceneGreyProcessBar = "/image/gamescene/jetbraintheme/process_bar.png";
	const string gameSceneProcessBar = "/image/gamescene/jetbraintheme/process_bar_score.png";
	const string gameSceneHintNumber = "/image/gamescene/jetbraintheme/hint";


	static JetBrainTheme* getInstance();

protected:
	JetBrainTheme() = default;

private:
	static JetBrainTheme* instance;
};


#endif
