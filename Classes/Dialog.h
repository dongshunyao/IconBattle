#ifndef __DIALOG_H__
#define __DIALOG_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Theme.h"
#include "Network.h"
#include "User.h"

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 900

USING_NS_CC;
using namespace cocos2d::ui;

using std::string;

class Dialog final :
	public LayerColor
{
public:
	Dialog() : menu(nullptr), labelMenu(nullptr), backGround(nullptr), title(nullptr), contentText(nullptr) {}
	~Dialog();

	bool init() override;
	CREATE_FUNC(Dialog);
	static Dialog* create(const string& background, const Size& size);

	// touch事件监听
	bool onTouchBegan(Touch* touch, Event* event) override { return true; }
	void onTouchMoved(Touch* touch, Event* event) override {}
	void onTouchEnded(Touch* touch, Event* event) override {}

	void onEnter() override;
	void onExit() override;

	// 添加标题
	void setTitle(const string& title, int fontSize = 20);
	// 添加文本内容
	void setContentText(const string& text, const int fontSize, const int padding, const int paddingTop);
	// 添加button、label或listView
	bool addButton(MenuItem* menuItem) const;
	bool addLabel(MenuItem* menuItem) const;
	void addListView(bool dialogType, bool inMenu, bool classical, bool noLeadingIn = true);

private:
	Theme* theme = Theme::getInstance();

	// 文字内容两边和顶部的空白区
	int contentPadding = 0;
	int contentPaddingTop = 0;

	Size dialogContentSize;

	// 初始化scene中心位置，方便使用
	const Point center = Point(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	int position = 11; // 滚动条位置
	bool rank = false; // 对话框类型
	bool rankType = false; // 排行榜类型
	bool isInMenu = true; // 排行榜是否在menuScene
	bool isClassical = true; // 游戏模式
	bool changed = false; // 判断排行榜是否改变

	ListView* listView = nullptr;
	Label* nameLabel = nullptr;
	Label* rankLabel = nullptr;
	Label* scoreLabel = nullptr;
	Label* content = nullptr;
	Layout* layout = nullptr;
	EventListenerMouse* listenerMouse = nullptr;

	// 排行榜
	vector<pair<string, int>> classicalRank;
	vector<pair<string, int>> plusRank;

	void backgroundFinish(); // 初始化对话框内容及布局
	void initRankDialog(); // 初始化排行榜对话框
	void initNormalDialog(); // 初始化普通对话框
	void getRankByType(bool type); // 获取排行榜内容


	// set and get
CC_SYNTHESIZE_RETAIN(Menu*, menu, MenuButton);
CC_SYNTHESIZE_RETAIN(Menu*, labelMenu, MenuLabel);
CC_SYNTHESIZE_RETAIN(ui::Scale9Sprite*, backGround, BackGround);
CC_SYNTHESIZE_RETAIN(Label*, title, LabelTitle);
CC_SYNTHESIZE_RETAIN(Label*, contentText, LabelContentText);
};

#endif
