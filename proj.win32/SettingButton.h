#ifndef __SETTING_BUTTON_H__
#define __SETTING_BUTTON_H__


#include "cocos2d.h"
#include "ui/UIButton.h"

#pragma region 
const std::string NORMAL_IMAGE = "/image/gamescene/jetbraintheme/back_normal.png";
const std::string SELECTED_IMAGE = "/image/gamescene/jetbraintheme/back_selected.png";
const std::string DISABLED_IMAGE = "/image/gamescene/jetbraintheme/back_disabled.png";
#pragma endregion 

USING_NS_CC;

// 返回按钮继承Button
class BackButton final
	:public ui::Button
{
public:
	static BackButton* getInstance();// 单例
	void backLastScene();//弹出将要返回的界面

private:
	static BackButton *instance;
	static BackButton* create();

};

#endif 
