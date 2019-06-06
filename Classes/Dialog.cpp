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

	classicalRank = Network::getInstance()->getRank(true);
	plusRank = Network::getInstance()->getRank(false);
	// 初始化需要的 Menu

	auto menu = Menu::create();
	menu->setPosition(Size::ZERO);
	setMenuButton(menu);

	auto labelMenu = Menu::create();
	labelMenu->setPosition(Size::ZERO);
	setMenuLabel(labelMenu);

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
	const auto label = Label::createWithTTF(title, theme->semiBoldFont, fontSize);
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

bool Dialog::addLabel(MenuItem* menuItem) const
{
	const auto center = Point(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	menuItem->setPosition(center);
	getMenuLabel()->addChild(menuItem);
	return true;
}

void Dialog::addListView(bool dialogType, bool inMenu, bool classical)
{
	rank = dialogType;
	isInMenu = inMenu;
	isClassical = classical;
}

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

void Dialog::backgroundFinish()
{
	const auto center = Point(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	if (rank)
	{
		if (getLabelTitle())
		{
			getLabelTitle()->setPosition(center + Vec2(0, dialogContentSize.height / 2 - 75.0f));
			this->addChild(getLabelTitle());
		}

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

		auto changeTypeButton = Button::create(theme->menuChangeTypeButtonNormalBackground,
		                                       theme->menuChangeTypeButtonSelectedBackground,
		                                       theme->menuChangeTypeButtonDisabledBackground);

		auto backTypeButton = Button::create(theme->menuBackTypeButtonNormalBackground,
		                                     theme->menuBackTypeButtonSelectedBackground,
		                                     theme->menuBackTypeButtonDisabledBackground);

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

		changeTypeButton->setPosition(Point(SCREEN_WIDTH / 2 + listView->getContentSize().width / 2 + 50,
		                                    SCREEN_HEIGHT / 2));

		backTypeButton->setPosition(Point(SCREEN_WIDTH / 2 - listView->getContentSize().width / 2 - 50,
		                                  SCREEN_HEIGHT / 2));
		backTypeButton->setOpacity(0);

		if (isInMenu)
		{
			this->addChild(changeTypeButton);
			this->addChild(backTypeButton);
		}


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

		this->getRankByType(isClassical);
	}
	else
	{
		// 添加按钮，并设置其位置
		this->addChild(getMenuLabel());
		const auto labelHeight = (dialogContentSize.height-title->getContentSize().height-15) / (getMenuLabel()->getChildrenCount() + 2);
		auto labels = getMenuLabel()->getChildren();
		i = 0;
		for (auto menuItem : labels)
		{
			auto node = dynamic_cast<Node*>(menuItem);
			node->setPosition(Point(SCREEN_WIDTH / 2,
			                        (SCREEN_HEIGHT+ dialogContentSize.height / -title->getContentSize().height+50) / 2 - dialogContentSize.height / 2.5 + labelHeight * (getMenuLabel()->
				                        getChildrenCount() - i)));
			i++;
		}


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

		// 显示对话框标题
		if (getLabelTitle())
		{
			getLabelTitle()->setPosition(center + Vec2(0, dialogContentSize.height / 2 -title->getContentSize().height/2-15));
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
	rank = false;
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
		for (i = 0; i < 10; i++)
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

		if (!changed)
			this->addChild(listView);
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
