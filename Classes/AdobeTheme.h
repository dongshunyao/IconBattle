#ifndef __ADOBE_THEME_H__
#define __ADOBE_THEME_H__
#include "Theme.h"

class AdobeTheme
	: public Theme
{
public:
#pragma region AdobeTheme

	const string themeName = "Adobe";

	const string iconSetZero;
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

	static AdobeTheme* getInstance();

private:
	static AdobeTheme* instance;
};


#endif
