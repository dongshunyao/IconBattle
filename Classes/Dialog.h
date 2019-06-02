#ifndef __DIALOG_H__
#define __DIALOG_H__

#include "cocos2d.h"
#include "cocos-ext.h"

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 900

namespace cocos2d
{
	namespace ui
	{
		class Button;
	}
}

using std::string;
using namespace cocos2d;
using namespace cocos2d::extension;

class Dialog : public LayerColor
{
public:
	Dialog();
	~Dialog();

	bool init() override;
	CREATE_FUNC(Dialog);
	static Dialog* create(const std::string background, Size size);

	// touch事件监听
	bool onTouchBegan(Touch* touch, Event* event) override;
	void onTouchMoved(Touch* touch, Event* event) override;
	void onTouchEnded(Touch* touch, Event* event) override;

	// 标题
	void setTitle(const string title, int fontSize = 20);
	// 文本
	void setContentText(const string text, const int fontSize, const int padding, const int paddingTop);
	// 添加button
	bool addButton(MenuItem* menuItem) const;

	void onEnter() override;
	void onExit() override;

	void backgroundFinish();

private:
	// 文字内容两边的空白区
	int contentPadding;
	int contentPaddingTop;

	Size dialogContentSize;

	// set and get
CC_SYNTHESIZE_RETAIN(Menu*, menu, MenuButton);
CC_SYNTHESIZE_RETAIN(ui::Scale9Sprite*,backGround, BackGround);
CC_SYNTHESIZE_RETAIN(Label*, title, LabelTitle);
CC_SYNTHESIZE_RETAIN(Label*,contentText, LabelContentText);
};

#endif
