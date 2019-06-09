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
	else if (theme == adobeThemeName)
	{
		currentTheme = adobeThemeName;
		setAdobeTheme();
	}
	else if (theme == officeThemeName)
	{
		currentTheme = officeThemeName;
		setOfficeTheme();
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

#pragma region Common
	iconSet = "/image/common/jetbraintheme/icon/";
#pragma endregion

#pragma region Dialog
	messageDialogBackground = "/image/gamescene/jetbraintheme/result_dialog_background.png";
	resultDialogBackground = "/image/gamescene/jetbraintheme/message_dialog_background.png";
#pragma region

#pragma region Loading Scene
	loadingSceneBackground = "/image/loadingscene/jetbraintheme/scene.png";

#pragma endregion

#pragma region Menu Scene
	menuSceneBackground = "/image/menuscene/jetbraintheme/background.jpg";
	menuSceneClassicLabel = "/image/menuscene/jetbraintheme/classic_label.png";
	menuSceneClassicPlate = "/image/menuscene/jetbraintheme/classic_plate.png";
	menuSceneEnhancedLabel = "/image/menuscene/jetbraintheme/enhanced_label.png";
	menuSceneEnhancedPlate = "/image/menuscene/jetbraintheme/enhanced_plate.png";
	menuSceneRankListBackground = "/image/menuscene/jetbraintheme/rank_list_background.png";

#pragma endregion

#pragma region Level Scene

	levelSelectButton = "/image/levelscene/jetbraintheme/level";
	levelSceneDistantView = "/image/levelscene/jetbraintheme/far.png";
	levelSceneForeground = "/image/levelscene/jetbraintheme/front.png";

#pragma endregion

#pragma region Store Scene

	storeSceneJetBrainThemeIcon = "/image/storescene/jetbraintheme/jetbrains.png";
	storeSceneAdobeThemeIcon = "/image/storescene/jetbraintheme/adobe.png";
	storeSceneOfficeThemeIcon = "/image/storescene/jetbraintheme/office.png";
	storeSceneStoreLabel = "/image/storescene/jetbraintheme/store_label.png";
	storeSceneBackground = "/image/storescene/jetbraintheme/background.png";

#pragma endregion

#pragma region Game Scene
	gameSceneTopBackground = "/image/gamescene/jetbraintheme/top_background.png";
	gameSceneBottomBackground = "/image/gamescene/jetbraintheme/bottom_background.png";
	gameSceneStepSpriteBackground = "/image/gamescene/jetbraintheme/level_sprite_background.png";
	gameSceneInfStepSpriteBackground = "/image/gamescene/jetbraintheme/level_sprite.png";
	gameSceneHintButtonNormal = "/image/gamescene/jetbraintheme/hint_button_normal.png";
	gameSceneHintButtonSelected = "/image/gamescene/jetbraintheme/hint_button_selected.png";
	gameSceneHintButtonDisabled = "/image/gamescene/jetbraintheme/hint_button_disabled.png";
	gameSceneResultSpriteBackground= "/image/gamescene/jetbraintheme/result_sprite_background.png";

#pragma endregion
}

void Theme::setAdobeTheme()
{
#pragma region BGM
	backgroundMusic = "/music/adobetheme/background.mp3";
#pragma endregion

#pragma region Common
	iconSet = "/image/common/adobetheme/icon/";
#pragma endregion

#pragma region Dialog
	messageDialogBackground ="/image/gamescene/adobetheme/result_dialog_background.png";
	resultDialogBackground = "/image/gamescene/adobetheme/message_dialog_background.png";
#pragma region

#pragma region Loading Scene
	loadingSceneBackground = "/image/loadingscene/adobetheme/scene.png";

#pragma endregion

#pragma region Menu Scene
	menuSceneBackground = "/image/menuscene/adobetheme/background.jpg";
	menuSceneClassicLabel = "/image/menuscene/adobetheme/classic_label.png";
	menuSceneClassicPlate = "/image/menuscene/adobetheme/classic_plate.png";
	menuSceneEnhancedLabel = "/image/menuscene/adobetheme/enhanced_label.png";
	menuSceneEnhancedPlate = "/image/menuscene/adobetheme/enhanced_plate.png";
	menuSceneRankListBackground = "/image/menuscene/adobetheme/rank_list_background.png";

#pragma endregion

#pragma region Level Scene

	levelSelectButton = "/image/levelscene/adobetheme/level";
	levelSceneDistantView = "/image/levelscene/adobetheme/far.png";
	levelSceneForeground = "/image/levelscene/adobetheme/front.png";

#pragma endregion

#pragma region Store Scene

	storeSceneJetBrainThemeIcon = "/image/storescene/adobetheme/jetbrains.png";
	storeSceneAdobeThemeIcon = "/image/storescene/adobetheme/adobe.png";
	storeSceneOfficeThemeIcon = "/image/storescene/adobetheme/office.png";
	storeSceneStoreLabel = "/image/storescene/adobetheme/store_label.png";
	storeSceneBackground = "/image/storescene/adobetheme/background.png";

#pragma endregion

#pragma region Game Scene
	gameSceneTopBackground = "/image/gamescene/adobetheme/top_background.png";
	gameSceneBottomBackground = "/image/gamescene/adobetheme/bottom_background.png";
	gameSceneStepSpriteBackground = "/image/gamescene/adobetheme/level_sprite_background.png";
	gameSceneInfStepSpriteBackground = "/image/gamescene/adobetheme/level_sprite.png";
	gameSceneHintButtonNormal = "/image/gamescene/adobetheme/hint_button_normal.png";
	gameSceneHintButtonSelected = "/image/gamescene/adobetheme/hint_button_selected.png";
	gameSceneHintButtonDisabled = "/image/gamescene/adobetheme/hint_button_disabled.png";
	gameSceneResultSpriteBackground = "/image/gamescene/adobetheme/result_sprite_background.png";

#pragma endregion
}

void Theme::setOfficeTheme() { }
