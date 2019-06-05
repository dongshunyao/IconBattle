#ifndef __DIALOG_H__
#define __DIALOG_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Theme.h"
#include "Network.h"

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

	// 标题
	void setTitle(const string& title, int fontSize = 20);
	// 文本
	void setContentText(const string& text, const int fontSize, const int padding, const int paddingTop);
	// 添加button或列表
	bool addButton(MenuItem* menuItem) const;
	bool addLabel(MenuItem* menuItem) const;
	void addListView(bool dialogType, bool inMenu,bool classical);

	void onEnter() override;
	void onExit() override;

	void backgroundFinish();

private:
	Theme* theme = Theme::getInstance();

	// 文字内容两边的空白区
	int contentPadding = 0;
	int contentPaddingTop = 0;

	Size dialogContentSize;

	int i = 0; // 循环计数器
	int position = 11;
	bool rank = false; // 对话框类型
	bool rankType = false; // 排行榜类型
	bool isInMenu = true; // 排行榜是否在menuScene
	bool isClassical = true;
	bool changed = false;
	ListView* listView = nullptr;
	Label* nameLabel = nullptr;
	Label* rankLabel = nullptr;
	Label* scoreLabel = nullptr;
	Label* content = nullptr;
	Layout* layout = nullptr;
	EventListenerMouse* listenerMouse = nullptr;

	vector<pair<string, int>> classicalRank;
	vector<pair<string, int>> plusRank;

	void getRankByType(bool type);


	// set and get
CC_SYNTHESIZE_RETAIN(Menu*, menu, MenuButton);
CC_SYNTHESIZE_RETAIN(Menu*, labelMenu, MenuLabel);
CC_SYNTHESIZE_RETAIN(ui::Scale9Sprite*, backGround, BackGround);
CC_SYNTHESIZE_RETAIN(Label*, title, LabelTitle);
CC_SYNTHESIZE_RETAIN(Label*, contentText, LabelContentText);
};

#endif
