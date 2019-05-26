#ifndef __THEME_H__
#define __THEME_H__

#include <string>

using std::string;

class Theme
{
public:
#pragma region Theme Const String
	const string themeName = "Theme";

	const string iconSet;
	const string loadingSceneLabelPress;
	const string loadingSceneLabelTitle;
	const string loadingSceneBackground;
	const string menuSceneBackground;
	const string menuSceneGameButtonNormal;
	const string menuSceneGameButtonSelected;
	const string menuSceneGameButtonDisabled;
	const string menuSceneRankButtonNormal;
	const string menuSceneRankButtonSelected;
	const string menuSceneRankButtonDisabled;
	const string menuSceneStoreButtonNormal;
	const string menuSceneStoreButtonSelected;
	const string menuSceneStoreButtonDisabled;
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
#pragma endregion

	static Theme* getInstance();

private:
	static Theme* instance;
};

#endif
