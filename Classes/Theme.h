#ifndef __THEME_H__
#define __THEME_H__

#include <string>

using std::string;

class Theme
{
public:
#pragma region Theme Name
	const string jetBrainThemeName = "JetBrainTheme";
	const string adobeThemeName = "AdobeTheme";
	const string officeThemeName = "OfficeTheme";
#pragma endregion

#pragma region Font TTF
	const string markerFeltFont = "/font/marker_felt.ttf";
	const string semiBoldFont = "/font/semi_bold.ttf";
#pragma endregion

#pragma region Music
	string backgroundMusic;
#pragma endregion

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

#pragma region Store Scene

	string storeSceneJetBrainThemeIcon;
	string storeSceneAdobeThemeIcon;
	string storeSceneOfficeThemeIcon;
	string storeSceneStoreLabel;

	const string storeSceneCoin = "/image/storescene/common/coins.png";

	// 选择按钮
	const string storeSceneChoiceButtonNormal = "/image/storescene/common/choice_normal.png";
	const string storeSceneChoiceButtonSelected = "/image/storescene/common/choice_selected.png";
	const string storeSceneChoiceButtonDisabled = "/image/storescene/common/choice_disabled.png";

	// Adobe RMB 按钮
	const string storeSceneAdobeRmbButtonNormal = "/image/storescene/common/adobe_RMB_normal.png";
	const string storeSceneAdobeRmbButtonSelected = "/image/storescene/common/adobe_RMB_selected.png";
	const string storeSceneAdobeRmbButtonDisabled = "/image/storescene/common/adobe_RMB_disabled.png";

	// Office RMB 按钮
	const string storeSceneOfficeRmbButtonNormal = "/image/storescene/common/office_RMB_normal.png";
	const string storeSceneOfficeRmbButtonSelected = "/image/storescene/common/office_RMB_selected.png";
	const string storeSceneOfficeRmbButtonDisabled = "/image/storescene/common/office_RMB_disabled.png";

	// Adobe COINS 按钮
	const string storeSceneAdobeCoinsButtonNormal = "/image/storescene/common/adobe_coins_normal.png";
	const string storeSceneAdobeCoinsButtonSelected = "/image/storescene/common/adobe_coins_selected.png";
	const string storeSceneAdobeCoinsButtonDisabled = "/image/storescene/common/adobe_coins_disabled.png";

	// Office COINS 按钮
	const string storeSceneOfficeCoinsButtonNormal = "/image/storescene/common/office_coins_normal.png";
	const string storeSceneOfficeCoinsButtonSelected = "/image/storescene/common/office_coins_selected.png";
	const string storeSceneOfficeCoinsButtonDisabled = "/image/storescene/common/office_coins_disabled.png";

#pragma endregion

#pragma region Game Scene
	string gameSceneTopBackground;
	string gameSceneBottomBackground;
	string gameSceneLevelSpriteBackground;
	string gameSceneHintButtonNormal;
	string gameSceneHintButtonSelected;
	string gameSceneHintButtonDisabled;

	const string gameSceneGreyProcessBar = "/image/gamescene/common/process_bar.png";
	const string gameSceneProcessBar = "/image/gamescene/common/process_bar_score.png";
	const string gameSceneHintNumber = "/image/gamescene/common/hint";
	const string gameSceneResultSprite = "/image/gamescene/common/";
	const string gameSceneDialogBackground = "/image/gamescene/common/dialog_background.png";
	const string gameSceneYesButtonNormal = "/image/gamescene/common/yes_normal.png";
	const string gameSceneYesButtonSelected = "/image/gamescene/common/yes_selected.png";
	const string gameSceneNoButtonNormal = "/image/gamescene/common/no_normal.png";
	const string gameSceneNoButtonSelected = "/image/gamescene/common/no_selected.png";

#pragma endregion

	static Theme* getInstance();
	void setCurrentTheme(const string& theme);
	string getCurrentThemeName() const { return currentTheme; }

private:
	static Theme* instance;
	Theme();

	string currentTheme;
	void setJetBrainTheme();
	void setAdobeTheme();
	void setOfficeTheme();
};

#endif
