#include "Dialog.h"

Dialog::~Dialog()
{
	CC_SAFE_RELEASE(menu);
	CC_SAFE_RELEASE(labelMenu);
	CC_SAFE_RELEASE(contentText);
	CC_SAFE_RELEASE(title);
}

bool Dialog::init()
{
	if (!LayerColor::init()) return false;

	// 预加载排行榜，解决卡顿
	classicalRank = Network::getInstance()->getRank(true);
	plusRank = Network::getInstance()->getRank(false);

	// 初始化需要的 Menu
	// button菜单
	auto menu = Menu::create();
	menu->setPosition(Size::ZERO);
	setMenuButton(menu);

	// label菜单
	auto labelMenu = Menu::create();
	labelMenu->setPosition(Size::ZERO);
	setMenuLabel(labelMenu);

	// 添加layer的事件监听事件
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Dialog::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(Dialog::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(Dialog::onTouchEnded, this);
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	// 设置背景版透明，达到对话框下层变灰暗效果
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

#pragma region Override
void Dialog::onEnter()
{
	LayerColor::onEnter();
	Layer::onEnter();

	_eventDispatcher->pauseEventListenersForTarget(this->getParent(), true); // 阻止事件向下传递

	//添加背景图片
	auto background = getBackGround();
	background->setContentSize(dialogContentSize);
	background->setPosition(Point(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
	this->addChild(background, 0, 0);

	// 弹出效果
	Action* dialog = Sequence::create(
		ScaleTo::create(0.0f, 0.0f),
		ScaleTo::create(0.3f, 1.0f),
		CallFunc::create(CC_CALLBACK_0(Dialog::backgroundFinish, this)),
		nullptr
	);

	background->runAction(dialog);
}

void Dialog::onExit()
{
	Layer::onExit();
	LayerColor::onExit();
	_eventDispatcher->resumeEventListenersForTarget(this->getParent(), true); // 还原事件监听
}

#pragma endregion

#pragma region Add Component
void Dialog::setTitle(const string& title, const int fontSize/*=20*/)
{
	const auto label = Label::createWithTTF(title, theme->semiBoldFont, fontSize);
	setLabelTitle(label);
}

void Dialog::setContentText(const string& text, const int fontSize, const int padding, const int paddingTop)
{
	const auto label = Label::createWithTTF(text, theme->semiBoldFont, fontSize);
	setLabelContentText(label);
	contentPadding = padding;
	contentPaddingTop = paddingTop;
}

bool Dialog::addButton(MenuItem* menuItem) const
{
	// 添加精灵菜单项
	const auto center = Point(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	menuItem->setPosition(center);
	getMenuButton()->addChild(menuItem);
	return true;
}

bool Dialog::addLabel(MenuItem* menuItem) const
{
	// 添加标签菜单项
	const auto center = Point(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	menuItem->setPosition(center);
	getMenuLabel()->addChild(menuItem);
	return true;
}

void Dialog::addListView(bool dialogType, bool inMenu, bool classical)
{
	// 设置窗口类型为排行榜窗口，并判断排行榜显示游戏模式
	rank = dialogType;
	isInMenu = inMenu;
	isClassical = classical;
}

#pragma endregion

void Dialog::backgroundFinish()
{
	// 判断窗口类型为排行榜窗口或普通窗口，true为排行榜窗口
	if (rank)
	{
		initRankDialog();
	}
	else
	{
		initNormalDialog();
	}
	rank = false; // 默认为普通对话框
}

void Dialog::initNormalDialog()
{
	// 显示对话框标题
	if (getLabelTitle())
	{
		getLabelTitle()->setPosition(
			center + Vec2(0, dialogContentSize.height / 2 - title->getContentSize().height / 2 - 15));
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

	// 添加label或button，并设置其位置
	//label
	this->addChild(getMenuLabel());
	auto adaptHeight = 0;
	if (title) adaptHeight = title->getContentSize().height;
	const auto labelHeight = (dialogContentSize.height - adaptHeight - 15) / (getMenuLabel()
		->getChildrenCount() + 2);

	// 布局labelMenuItem
	auto labels = getMenuLabel()->getChildren();
	auto i = 0;
	for (auto menuItem : labels)
	{
		auto node = dynamic_cast<Node*>(menuItem);
		node->setPosition(Point(SCREEN_WIDTH / 2,
		                        (SCREEN_HEIGHT + dialogContentSize.height / -adaptHeight + 50) /
		                        2 - dialogContentSize.height / 2.5 + labelHeight * (getMenuLabel()->
			                        getChildrenCount() - i)));
		i++;
	}

	// button
	this->addChild(getMenuButton());

	const auto buttonWidth = dialogContentSize.width / (getMenuButton()->getChildrenCount() + 1);
	auto nodes = getMenuButton()->getChildren();
	i = 0;
	for (auto menuItem : nodes)
	{
		auto node = dynamic_cast<Node*>(menuItem);

		node->setPosition(Point(SCREEN_WIDTH / 2 - dialogContentSize.width / 2 + buttonWidth * (i + 1),
		                        SCREEN_HEIGHT / 2 - dialogContentSize.height / 2.5));
		i++;
	}
}

void Dialog::initRankDialog()
{
	// 显示对话框标题
	if (getLabelTitle())
	{
		getLabelTitle()->setPosition(center + Vec2(0, dialogContentSize.height / 2 - 75.0f));
		this->addChild(getLabelTitle());
	}

	this->addChild(getMenuButton());

	// 添加button，设置布局
	const auto buttonWidth = dialogContentSize.width / (getMenuButton()->getChildrenCount() + 1);
	auto nodes = getMenuButton()->getChildren();

	auto i = 0;
	for (auto menuItem : nodes)
	{
		auto node = dynamic_cast<Node*>(menuItem);
		node->setPosition(Point(SCREEN_WIDTH / 2 - dialogContentSize.width / 2 + buttonWidth * (i + 1),
		                        SCREEN_HEIGHT / 2 - dialogContentSize.height / 2.5));
		i++;
	}


	listView = ListView::create();
	listView->setDirection(ScrollView::Direction::VERTICAL);
	listView->setTouchEnabled(true);
	listView->setBounceEnabled(true);
	listView->setBackGroundImageScale9Enabled(true);
	listView->setAnchorPoint(Point(0.5f, 0.5f));
	listView->setContentSize(Size(500, 400));
	listView->setPosition(Point(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
	listView->setScrollBarAutoHideTime(0);
	listView->setScrollBarColor(Color3B::WHITE);
	this->addChild(listView);

	//添加鼠标事件侦听
	listenerMouse = EventListenerMouse::create();
	listenerMouse->setEnabled(true);
	listenerMouse->onMouseScroll = [&](EventMouse* event)
	{
		const auto y = event->getScrollY(); //滚轮上滑y值大于0，下滑y值小于0

		if (y > 0)
		{
			if (position % 11 < 10)
				position++;
			listView->scrollToPercentVertical(10 * (position % 11), 0.5, true);
		}
		else
		{
			if (position % 11 > 0)
				position--;
			listView->scrollToPercentVertical(10 * (position % 11), 0.5, true);
		}
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerMouse, this);


	// 不同游戏模式的排行榜切换按钮         
	auto changeTypeButton = Button::create(theme->menuChangeTypeButtonNormalBackground,
	                                       theme->menuChangeTypeButtonSelectedBackground,
	                                       theme->menuChangeTypeButtonDisabledBackground); // 切换到进阶

	auto backTypeButton = Button::create(theme->menuBackTypeButtonNormalBackground,
	                                     theme->menuBackTypeButtonSelectedBackground,
	                                     theme->menuBackTypeButtonDisabledBackground); // 切换到经典


	changeTypeButton->setPosition(Point(SCREEN_WIDTH / 2 + listView->getContentSize().width / 2 + 50,
	                                    SCREEN_HEIGHT / 2));

	backTypeButton->setPosition(Point(SCREEN_WIDTH / 2 - listView->getContentSize().width / 2 - 50,
	                                  SCREEN_HEIGHT / 2));
	backTypeButton->setOpacity(0); // 切换经典初始不可见

	backTypeButton->addTouchEventListener(
		[&, changeTypeButton, backTypeButton](Ref* sender, ui::Widget::TouchEventType type)
		{
			if (type == Widget::TouchEventType::ENDED)
			{
				title->setString("Classical Rank List");
				backTypeButton->setOpacity(0);
				changeTypeButton->runAction(FadeIn::create(0.25));
				if (changed)
					getRankByType(true);
				changed = false;
			}
		});

	changeTypeButton->addTouchEventListener(
		[&, changeTypeButton, backTypeButton](Ref* sender, ui::Widget::TouchEventType type)
		{
			if (type == Widget::TouchEventType::ENDED)
			{
				title->setString("Plus Rank List");
				changeTypeButton->setOpacity(0);
				backTypeButton->runAction(FadeIn::create(0.25));
				if (!changed)
					getRankByType(false);
				changed = true;
			}
		});

	// 如果在menuScene中，排行榜可切换，gameScene中排行榜不可切换
	if (isInMenu)
	{
		this->addChild(changeTypeButton);
		this->addChild(backTypeButton);
	}

	// 根据游戏模式初始化排行榜
	this->getRankByType(isClassical);
}


void Dialog::getRankByType(bool type)
{
	rankType = type;
	if (content)
	{
		this->removeChild(content);
		listView->setScrollBarEnabled(true);
		listView->setScrollBarAutoHideTime(0);
	}

	if (!(rankType ? classicalRank.empty() : plusRank.empty()))
	{
		if (listView->getChildrenCount() > 0)listView->removeAllChildren();
		for (auto i = 0; i < 10; i++)
		{
			auto icon = ImageView::create(theme->iconSet + std::to_string(i) + ".png");
			layout = Layout::create();
			layout->setLayoutType(Layout::Type::ABSOLUTE);
			layout->setContentSize(Size(500, icon->getContentSize().height + 30));

			icon->setPosition(Vec2(icon->getContentSize().width / 2 + 60, 30));
			layout->addChild(icon);
			layout->setBackGroundColorType(Layout::BackGroundColorType::NONE);

			rankLabel = Label::createWithTTF(std::to_string(i + 1), "/font/marker_felt.ttf", 30);
			rankLabel->setPosition(Vec2(icon->getContentSize().width / 2 + 10, 30));
			layout->addChild(rankLabel);


			if (i > (rankType ? classicalRank.size() : plusRank.size()) - 1)
			{
				nameLabel = Label::createWithTTF("------------------", "/font/marker_felt.ttf", 30);
				nameLabel->setPosition(Vec2(
					icon->getContentSize().width + nameLabel->getContentSize().width / 2 + 75,
					30));
				layout->addChild(nameLabel);

				scoreLabel = Label::createWithTTF("---------", "/font/marker_felt.ttf", 30);
				scoreLabel->setPosition(Vec2(465 - scoreLabel->getContentSize().width / 2, 30));
				layout->addChild(scoreLabel);
			}
			else
			{
				nameLabel = Label::createWithTTF(rankType ? classicalRank.at(i).first : plusRank.at(i).first,
				                                 theme->semiBoldFont, 30);
				nameLabel->setPosition(Vec2(
					icon->getContentSize().width + nameLabel->getContentSize().width / 2 + 75,
					30));
				layout->addChild(nameLabel);

				scoreLabel = Label::createWithTTF(
					std::to_string(rankType ? classicalRank.at(i).second : plusRank.at(i).second),
					"/font/marker_felt.ttf", 30);
				scoreLabel->setPosition(Vec2(465 - scoreLabel->getContentSize().width / 2, 30));
				layout->addChild(scoreLabel);
			}
			listView->pushBackCustomItem(layout);
			listView->setBottomPadding(icon->getContentSize().height);
		}
	}
	else
	{
		if (listView->getChildrenCount() > 0)listView->removeAllChildren();
		listView->setScrollBarEnabled(false);
		setContentText("网络连接失败，请重试", 36, 60, 20);
		content = getLabelContentText();
		content->setLineBreakWithoutSpace(true);
		content->setMaxLineWidth(dialogContentSize.width - 2 * contentPadding);
		content->setPosition(Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
		content->setHorizontalAlignment(TextHAlignment::LEFT);
		this->addChild(content);
	}
}
