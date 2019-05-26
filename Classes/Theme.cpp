#include "Theme.h"

Theme* Theme::instance = nullptr;

Theme* Theme::getInstance(const string& theme)
{
	if (instance == nullptr) instance = new Theme(theme);
	return instance;
}

void Theme::setTheme(const string& theme)
{
	if (theme == "JetBrain")
	{
#pragma region Loading Scene
		iconSet = "/image/loadingscene/jetbraintheme/iconset/large/";
		loadingSceneBackground = "/image/loadingscene/jetbraintheme/scene.png";

#pragma endregion

#pragma region Menu Scene
		menuSceneBackground = "/image/menuscene/jetbraintheme/background.jpg";

#pragma endregion

#pragma region Game Scene
		gameSceneBackground = "/image/gamescene/jetbraintheme/background.png";
		gameSceneLevelSpriteBackground = "/image/gamescene/jetbraintheme/level_sprite.png";
		gameSceneHintButtonNormal = "/image/gamescene/jetbraintheme/hint_button_normal.png";
		gameSceneHintButtonSelected = "/image/gamescene/jetbraintheme/hint_button_selected.png";
		gameSceneHintButtonDisabled = "/image/gamescene/jetbraintheme/hint_button_disabled.png";

#pragma endregion
	}
}

Theme::Theme(const string& theme)
{
	setTheme(theme);
}
