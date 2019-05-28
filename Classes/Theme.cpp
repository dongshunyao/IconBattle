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

	level1Disabled = "/image/levelscene/jetbraintheme/level1_disabled.png";
	level2Disabled = "/image/levelscene/jetbraintheme/level2_disabled.png";
	level3Disabled = "/image/levelscene/jetbraintheme/level3_disabled.png";
	level4Disabled = "/image/levelscene/jetbraintheme/level4_disabled.png";
	level5Disabled = "/image/levelscene/jetbraintheme/level5_disabled.png";
	level6Disabled = "/image/levelscene/jetbraintheme/level6_disabled.png";
	level7Disabled = "/image/levelscene/jetbraintheme/level7_disabled.png";
	level8Disabled = "/image/levelscene/jetbraintheme/level8_disabled.png";
	level9Disabled = "/image/levelscene/jetbraintheme/level9_disabled.png";
	level10Disabled = "/image/levelscene/jetbraintheme/level10_disabled.png";

	level1Selected = "/image/levelscene/jetbraintheme/level1_selected.png";
	level2Selected = "/image/levelscene/jetbraintheme/level2_selected.png";
	level3Selected = "/image/levelscene/jetbraintheme/level3_selected.png";
	level4Selected = "/image/levelscene/jetbraintheme/level4_selected.png";
	level5Selected = "/image/levelscene/jetbraintheme/level5_selected.png";
	level6Selected = "/image/levelscene/jetbraintheme/level6_selected.png";
	level7Selected = "/image/levelscene/jetbraintheme/level7_selected.png";
	level8Selected = "/image/levelscene/jetbraintheme/level8_selected.png";
	level9Selected = "/image/levelscene/jetbraintheme/level9_selected.png";
	level10Selected = "/image/levelscene/jetbraintheme/level10_selected.png";

	level1Normal = "/image/levelscene/jetbraintheme/level1_normal.png";
	level2Normal = "/image/levelscene/jetbraintheme/level2_normal.png";
	level3Normal = "/image/levelscene/jetbraintheme/level3_normal.png";
	level4Normal = "/image/levelscene/jetbraintheme/level4_normal.png";
	level5Normal = "/image/levelscene/jetbraintheme/level5_normal.png";
	level6Normal = "/image/levelscene/jetbraintheme/level6_normal.png";
	level7Normal = "/image/levelscene/jetbraintheme/level7_normal.png";
	level8Normal = "/image/levelscene/jetbraintheme/level8_normal.png";
	level9Normal = "/image/levelscene/jetbraintheme/level9_normal.png";
	level10Normal = "/image/levelscene/jetbraintheme/level10_normal.png";

#pragma endregion

#pragma region Game Scene
	gameSceneBackground = "/image/gamescene/jetbraintheme/background.png";
	gameSceneLevelSpriteBackground = "/image/gamescene/jetbraintheme/level_sprite.png";
	gameSceneHintButtonNormal = "/image/gamescene/jetbraintheme/hint_button_normal.png";
	gameSceneHintButtonSelected = "/image/gamescene/jetbraintheme/hint_button_selected.png";
	gameSceneHintButtonDisabled = "/image/gamescene/jetbraintheme/hint_button_disabled.png";

#pragma endregion
}
