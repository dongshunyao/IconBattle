#include "NewsBoard.h"

bool NewsBoard::init()
{
	if (!Node::init()) return false;
	setPosition(Point(80.f, 30.f));

	auto newsIcon = Sprite::create(theme->menuSceneNewsBoardIcon);
	newsIcon->setPosition(30, 30);
	this->addChild(newsIcon);

	auto sharpNode = DrawNode::create();
	Point point[4] = {Point(60.f, 10.f), Point(900.f, 10.f), Point(900.f, 35.f), Point(60.f, 35.f)};
	//标记显示的矩形区域
	sharpNode->drawPolygon(point, 4, Color4F(0, 200, 200, 255), 2, Color4F(0, 200, 200, 255));

	//剪切用于显示的矩形区域，参数对应：用于标识区域的Point(Vec2)数组指针，数组长度，填充颜色，边框宽度，边框颜色
	auto clipper = ClippingNode::create();
	clipper->setAnchorPoint(Point(0.5, 0.5));
	clipper->setStencil(sharpNode);

	news = Label::createWithTTF(Network::getInstance()->getNews(), theme->semiBoldFont, 26);
	news->setColor(Color3B(255, 255, 255));
	news->setAnchorPoint(Point::ZERO);
	news->setPosition(Point(720, 10)); //设置公告文字内容的初始位置
	schedule(schedule_selector(NewsBoard::scrollText)); //实现公告文字滚动

	clipper->addChild(news);
	this->addChild(clipper);

	return true;
}

void NewsBoard::scrollText(float)
{
	if (news->getPosition().x < -1 * news->getContentSize().width) news->setPositionX(910);
	else news->setPositionX(news->getPositionX() - 2);
}
