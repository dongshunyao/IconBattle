#ifndef __THEME_H__
#define __THEME_H__

#include <string>

using std::string;

class Theme
{
public:
	const string jetBrainThemeName = "JetBrainTheme";
	const string adobeThemeName = "AdobeTheme";

	string backgroundMusic;

#pragma region Loading Sence
	string iconSet;
	string loadingSceneBackground;

	const string loadingSceneLabelPress = "/image/loadingscene/common/label_press.png";
	const string loadingSceneLabelTitle = "/image/loadingscene/common/label_title.png";

#pragma endregion

#pragma region Menu Sence
	string menuSceneBackground;

	const string menuSceneGameButtonNormal = "/image/menuscene/common/game_normal.png";
	const string menuSceneGameButtonSelected = "/image/menuscene/common/game_selected.png";
	const string menuSceneGameButtonDisabled = "/image/menuscene/common/game_disabled.png";

	const string menuSceneRankButtonNormal = "/image/menuscene/common/rank_normal.png";
	const string menuSceneRankButtonSelected = "/image/menuscene/common/rank_selected.png";
	const string menuSceneRankButtonDisabled = "/image/menuscene/common/rank_disabled.png";

	const string menuSceneStoreButtonNormal = "/image/menuscene/common/store_normal.png";
	const string menuSceneStoreButtonSelected = "/image/menuscene/common/store_selected.png";
	const string menuSceneStoreButtonDisabled = "/image/menuscene/common/store_disabled.png";

	const string menuSceneNewsBoardIcon = "/image/menuscene/common/icon.png";
	const string menuSceneUserIcon = "/image/menuscene/common/user.png";
	const string menuSceneEditIcon = "/image/menuscene/common/edit.png";
#pragma endregion

#pragma region Level Scene
	string levelSelectButton;
	
	// TODO 暂时不更换
	const string levelSceneDistantView = "/image/levelscene/jetbraintheme/far.png";
	const string levelSceneForeground = "/image/levelscene/jetbraintheme/front.png";
	const string levelSceneGameButtonNormal = "/image/levelscene/jetbraintheme/game_normal.png";
	const string levelSceneGameButtonSelected = "/image/levelscene/jetbraintheme/game_selected.png";
	const string levelSceneGameButtonDisabled = "/image/levelscene/jetbraintheme/game_disabled.png";

#pragma endregion

#pragma region Game Scene
	string gameSceneBackground;
	string gameSceneLevelSpriteBackground;
	string gameSceneHintButtonNormal;
	string gameSceneHintButtonSelected;
	string gameSceneHintButtonDisabled;

	const string gameSceneGreyProcessBar = "/image/gamescene/common/process_bar.png";
	const string gameSceneProcessBar = "/image/gamescene/common/process_bar_score.png";
	const string gameSceneHintNumber = "/image/gamescene/common/hint";
	const string gameSceneResultSprite = "/image/gamescene/common/";

#pragma endregion

	static Theme* getInstance();
	void setCurrentTheme(const string& theme);
	string getCurrentThemeName() const { return currentTheme; }

private:
	static Theme* instance;
	Theme();

	string currentTheme;
	void setJetBrainTheme();
};

#endif