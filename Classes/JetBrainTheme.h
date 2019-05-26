#ifndef __JET_BRAIN_THEME_H__
#define __JET_BRAIN_THEME_H__
#include "Theme.h"

class JetBrainTheme
	: public Theme
{
public:
#pragma region JetBrainTheme

	const string themeName = "JetBrain";

	const string iconSet = "/image/loadingscene/jetbraintheme/iconset/large/";
	const string loadingSceneLabelPress = "/image/loadingscene/jetbraintheme/label_press.png";
	const string loadingSceneLabelTitle = "/image/loadingscene/jetbraintheme/label_title.png";
	const string loadingSceneBackground = "/image/loadingscene/jetbraintheme/scene.png";
	const string menuSceneBackground = "/image/menuscene/jetbraintheme/background.jpg";
	const string menuSceneGameButtonNormal = "/image/menuscene/jetbraintheme/game_normal.png";
	const string menuSceneGameButtonSelected = "/image/menuscene/jetbraintheme/game_selected.png";
	const string menuSceneGameButtonDisabled = "/image/menuscene/jetbraintheme/game_disabled.png";
	const string menuSceneRankButtonNormal = "/image/menuscene/jetbraintheme/rank_normal.png";
	const string menuSceneRankButtonSelected = "/image/menuscene/jetbraintheme/rank_selected.png";
	const string menuSceneRankButtonDisabled = "/image/menuscene/jetbraintheme/rank_disabled.png";
	const string menuSceneStoreButtonNormal = "/image/menuscene/jetbraintheme/store_normal.png";
	const string menuSceneStoreButtonSelected = "/image/menuscene/jetbraintheme/store_selected.png";
	const string menuSceneStoreButtonDisabled = "/image/menuscene/jetbraintheme/store_disabled.png";
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


#pragma endregion

	static JetBrainTheme* getInstance();

private:
	static JetBrainTheme* instance;
};


#endif
