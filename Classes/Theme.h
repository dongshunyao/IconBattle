#ifndef __THEME_H__
#define __THEME_H__

#include <string>

using std::string;

class Theme
{
public:
	const string themeName = "Theme";

#pragma region Loading Sence
	const string iconSet;
	const string loadingSceneBackground;

	const string loadingSceneLabelPress = "/image/loadingscene/common/label_press.png";
	const string loadingSceneLabelTitle = "/image/loadingscene/common/label_title.png";

#pragma endregion

#pragma region Menu Sence
	const string menuSceneBackground;

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

#pragma endregion

	//TODO 规范化
	const string levelSceneDistantView;
	const string levelSceneForeground;
	const string levelSceneGameButtonNormal;
	const string levelSceneGameButtonSelected;
	const string levelSceneGameButtonDisabled;

	const string gameSceneBackground;
	const string gameSceneLevelSpriteBackground;
	const string gameSceneHintButtonNormal;
	const string gameSceneHintButtonSelected;
	const string gameSceneHintButtonDisabled;
	const string gameSceneGreyProcessBar;
	const string gameSceneProcessBar;
	const string gameSceneHintNumber;


	static Theme* getInstance();

protected:
	Theme() = default;

private:
	static Theme* instance;
};

#endif
