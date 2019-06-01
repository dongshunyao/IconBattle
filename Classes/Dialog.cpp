#include "Dialog.h"
#include "ui/UIButton.h"

Dialog::Dialog() :
	menu(nullptr)
	, contentPadding(0)
	, contentPaddingTop(0)
	, backGround(nullptr)
	, s9BackGround(nullptr)
	, contentText(nullptr)
	, title(nullptr)
{
}

Dialog::~Dialog()
{
	CC_SAFE_RELEASE(menu);
	CC_SAFE_RELEASE(backGround);
	CC_SAFE_RELEASE(contentText);
	CC_SAFE_RELEASE(title);
}

bool Dialog::init()
{
	if (!LayerColor::init())
	{
		return false;
	}
	// 初始化需要的 Menu
	auto menu = Menu::create();
	menu->setPosition(Size::ZERO);
	setMenuButton(menu);

	//add layer touch event
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

bool Dialog::onTouchBegan(Touch* touch, Event* event)
{
	return true;
}

void Dialog::onTouchMoved(Touch* touch, Event* event)
{
}

void Dialog::onTouchEnded(Touch* touch, Event* event)
{
}

Dialog* Dialog::create(const std::string background, const Size size)
{
	auto layer = Dialog::create();

	layer->setSprite9BackGround(ui::Scale9Sprite::create(background));

	layer->dialogContentSize = size;

	return layer;
}

void Dialog::setTitle(const char* title, int fontSize)
{
	const auto label = Label::createWithTTF(title, "/font/marker_felt.ttf", fontSize);
	setLabelTitle(label);
}

void Dialog::setContentText(const char* text, const int fontSize, const int padding, const int paddingTop)
{
	const auto label = Label::createWithTTF(text, "/font/marker_felt.ttf", fontSize);
	setLabelContentText(label);
	contentPadding = padding;
	contentPaddingTop = paddingTop;
}


bool Dialog::addButton(MenuItem*  menuItem) const
{
	const auto size = Director::getInstance()->getWinSize();
	const auto center = Point(size.width / 2, size.height / 2);

	menuItem->setPosition(center);

	getMenuButton()->addChild(menuItem);

	return true;
}


void Dialog::onEnter()
{
	LayerColor::onEnter();
	Layer::onEnter();

	_eventDispatcher->pauseEventListenersForTarget(this->getParent(), true);

	const auto winSize = Director::getInstance()->getWinSize();
	auto pCenter = Point(winSize.width / 2, winSize.height / 2);


	//添加背景图片
	auto background = getSprite9BackGround();
	background->setContentSize(dialogContentSize);
	background->setPosition(Point(winSize.width / 2, winSize.height / 2));
	this->addChild(background, 0, 0);

	// 弹出效果
	Action* dialog = Sequence::create(
		ScaleTo::create(0.0, 0.0),
		ScaleTo::create(0.2, 1.05),
		ScaleTo::create(0.2, 0.95),
		ScaleTo::create(0.1, 1.0),
		CallFunc::create(CC_CALLBACK_0(Dialog::backgroundFinish, this)),
		nullptr
	);
	background->runAction(dialog);
}

void Dialog::onExit()
{
	LayerColor::onExit();
	_eventDispatcher->resumeEventListenersForTarget(this->getParent(), true);
}


void Dialog::backgroundFinish()
{
	const auto windowSize = Director::getInstance()->getWinSize();
	const auto center = Point(windowSize.width / 2, windowSize.height / 2);

	// 添加按钮，并设置其位置
	this->addChild(getMenuButton());
	const auto btnWidth = dialogContentSize.width / (getMenuButton()->getChildrenCount() + 1);

	auto vector = getMenuButton()->getChildren();
	Ref* pObj = nullptr;
	auto i = 0;
	for (auto pObj : vector)
	{
		auto node = dynamic_cast<Node*>(pObj);
		node->setPosition(Point(windowSize.width / 2 - dialogContentSize.width / 2 + btnWidth * (i + 1),
		                        windowSize.height / 2 - dialogContentSize.height / 3));
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
		auto ltf = getLabelContentText();
		ltf->setPosition(Vec2(windowSize.width / 2, windowSize.height / 2));
		// ltf->setDimensions(Size(dialogContentSize.width - contentPadding * 2,
		//dialogContentSize.height - contentPaddingTop));
		ltf->setHorizontalAlignment(TextHAlignment::LEFT);
		this->addChild(ltf);
	}
}


