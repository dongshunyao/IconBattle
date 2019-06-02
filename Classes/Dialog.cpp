#include "Dialog.h"

Dialog::~Dialog()
{
	CC_SAFE_RELEASE(menu);
	CC_SAFE_RELEASE(contentText);
	CC_SAFE_RELEASE(title);
}

bool Dialog::init()
{
	if (!LayerColor::init()) return false;

	// 初始化需要的 Menu
	auto menu = Menu::create();
	menu->setPosition(Size::ZERO);
	setMenuButton(menu);

	// add layer touch event
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Dialog::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(Dialog::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(Dialog::onTouchEnded, this);
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	setColor(Color3B(0, 0, 0));
	setOpacity(128);

	return true;
}

Dialog* Dialog::create(const string& background, const Size& size)
{
	auto layer = Dialog::create();
	layer->setBackGround(Scale9Sprite::create(background));
	layer->dialogContentSize = size;
	return layer;
}

void Dialog::setTitle(const string& title, const int fontSize)
{
	// TODO 统一字体？路径放到头文件orTheme？
	const auto label = Label::createWithTTF(title, "/font/marker_felt.ttf", fontSize);
	setLabelTitle(label);
}

void Dialog::setContentText(const string& text, const int fontSize, const int padding, const int paddingTop)
{
	// TODO 统一字体？路径放到头文件orTheme？
	const auto label = Label::createWithTTF(text, theme->semiBoldFont, fontSize);
	setLabelContentText(label);
	contentPadding = padding;
	contentPaddingTop = paddingTop;
}

bool Dialog::addButton(MenuItem* menuItem) const
{
	const auto center = Point(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	menuItem->setPosition(center);
	getMenuButton()->addChild(menuItem);
	return true;
}

void Dialog::onEnter()
{
	LayerColor::onEnter();
	Layer::onEnter();

	_eventDispatcher->pauseEventListenersForTarget(this->getParent(), true); // 阻止事件向下传递

	const auto winSize = Director::getInstance()->getWinSize();
	auto pCenter = Point(winSize.width / 2, winSize.height / 2);


	//添加背景图片
	auto background = getBackGround();
	background->setContentSize(dialogContentSize);
	background->setPosition(Point(winSize.width / 2, winSize.height / 2));
	this->addChild(background, 0, 0);

	// 弹出效果
	Action* dialog = Sequence::create(
		ScaleTo::create(0.0f, 0.0f),
		ScaleTo::create(0.2f, 1.05f),
		ScaleTo::create(0.2f, 0.95f),
		ScaleTo::create(0.1f, 1.0f),
		CallFunc::create(CC_CALLBACK_0(Dialog::backgroundFinish, this)),
		nullptr
	);
	background->runAction(dialog);
}

void Dialog::onExit()
{
	LayerColor::onExit();
	_eventDispatcher->resumeEventListenersForTarget(this->getParent(), true); // 还原事件监听
}

void Dialog::backgroundFinish()
{
	const auto center = Point(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	// 添加按钮，并设置其位置
	this->addChild(getMenuButton());
	const auto buttonWidth = dialogContentSize.width / (getMenuButton()->getChildrenCount() + 1);

	auto nodes = getMenuButton()->getChildren();
	auto i = 0;
	for (auto menuItem : nodes)
	{
		auto node = dynamic_cast<Node*>(menuItem);
		node->setPosition(Point(SCREEN_WIDTH / 2 - dialogContentSize.width / 2 + buttonWidth * (i + 1),
		                        SCREEN_HEIGHT / 2 - dialogContentSize.height / 3));
		i++;
	}

	// 显示对话框标题
	if (getLabelTitle())
	{
		getLabelTitle()->setPosition(center + Vec2(0, dialogContentSize.height / 2 - 35.0f));
		this->addChild(getLabelTitle());
	}

	// 显示文本内容
	if (getLabelContentText())
	{
		auto content = getLabelContentText();
		content->setLineBreakWithoutSpace(true);
		content->setMaxLineWidth(dialogContentSize.width - 2 * contentPadding);
		content->setPosition(Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
		content->setHorizontalAlignment(TextHAlignment::LEFT);
		this->addChild(content);
	}
}
