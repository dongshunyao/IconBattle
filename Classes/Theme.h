#ifndef __THEME_H__
#define __THEME_H__

#include <string>

using std::string;

class Theme
{
public:
#pragma region Theme Const String
	const string themeName = "Theme";

	const string iconSetZero;
	const string iconSetOne;
	const string iconSetTwo;
	const string iconSetThree;
	const string iconSetFour;
	const string iconSetFive;
	const string iconSetSix;
	const string iconSetSeven;
	const string iconSetEight;
	const string iconSetNine;
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
	const string levelSceneVision;
	const string levelSceneProspect;
	const string levelSceneGameButtonNormal;
	const string levelSceneGameButtonSelected;
	const string levelSceneGameButtonDisabled;
	const string gameSceneBackground;
	const string gameSceneLevelSpriteBackground;
	const string gameScenePromptButtonNormal;
	const string gameScenePromptButtonSelected;
	const string gameScenePromptButtonDisabled;
#pragma endregion

	static Theme* getInstance();

private:
	static Theme* instance;
};

#endif
