#include "Theme.h"

Theme* Theme::instance = nullptr;

Theme* Theme::getInstance()
{
	if (instance == nullptr) instance = new Theme;
	return instance;
}

void Theme::setCurrentTheme(const string& theme)
{
	if (theme == jetBrainThemeName)
	{
		currentTheme = jetBrainThemeName;
		setJetBrainTheme();
	}
}

Theme::Theme()
{
	setCurrentTheme(jetBrainThemeName);
}

void Theme::setJetBrainTheme()
{
#pragma region BGM
	backgroundMusic = "/music/jetbraintheme/background.mp3";
#pragma endregion

#pragma region Loading Scene
	iconSet = "/image/loadingscene/jetbraintheme/iconset/large/";
	loadingSceneBackground = "/image/loadingscene/jetbraintheme/scene.png";

#pragma endregion

#pragma region Menu Scene
	menuSceneBackground = "/image/menuscene/jetbraintheme/background.jpg";

#pragma endregion

#pragma region Level Scene

	levelSelectButton = "/image/levelscene/jetbraintheme/level";

#pragma endregion

#pragma region Store Scene

	storeSceneJetBrainThemeIcon = "/image/storescene/jetbraintheme/jetbrains.png";
	storeSceneAdobeThemeIcon = "/image/storescene/jetbraintheme/adobe.png";
	storeSceneOfficeThemeIcon = "/image/storescene/jetbraintheme/office.png";
	storeSceneStoreLabel = "/image/storescene/jetbraintheme/store_label.png";

#pragma endregion

#pragma region Game Scene
	gameSceneBackground = "/image/gamescene/jetbraintheme/background.png";
	gameSceneLevelSpriteBackground = "/image/gamescene/jetbraintheme/level_sprite.png";
	gameSceneHintButtonNormal = "/image/gamescene/jetbraintheme/hint_button_normal.png";
	gameSceneHintButtonSelected = "/image/gamescene/jetbraintheme/hint_button_selected.png";
	gameSceneHintButtonDisabled = "/image/gamescene/jetbraintheme/hint_button_disabled.png";

#pragma endregion
}
