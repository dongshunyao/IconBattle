#include "PannelNews.h"

PannelNews::PannelNews() {}

PannelNews::~PannelNews() {}

bool PannelNews::init()
{
	if (!Node::init())
		return false;
	setPosition(Point(100.f, 40.f));
	holder = Node::create();
	addChild(holder);

	// newsBg = Sprite::create("/images/menuScene/jetBrainTheme/timg.png");
	// newsBg->setPosition(80, 40);
	// holder->addChild(newsBg);

	sharpNode = DrawNode::create();
	Point point[4] = { Point(60.f,10.f), Point(900.f,10.f), Point(900.f,35.f),   Point(60.f,35.f) };
	//标记显示的矩形区域
	sharpNode->drawPolygon(point, 4, Color4F(0, 200, 200, 255), 2, Color4F(0, 200, 200, 255));
	//剪切用于显示的矩形区域，参数对应：用于标识区域的Point(Vec2)数组指针，数组长度，填充颜色，边框宽度，边框颜色
	clipper = ClippingNode::create();
	clipper->setAnchorPoint(Point(0.5, 0.5));
	clipper->setStencil(sharpNode);

	news = Label::createWithSystemFont("testing notice borad ~~~~~~~~~~~~", "/fonts/Marker Felt.ttf", 24);
	news->setColor(Color3B(255, 255, 255));
	clipper->addChild(news);

	layout();
	holder->addChild(clipper);

	return true;
}

void PannelNews::layout()
{
	news->setAnchorPoint(Point::ZERO);
	news->setPosition(Point(720, 10));//设置公告文字内容的初始位置
	schedule(schedule_selector(PannelNews::scrollText));//实现公告文字滚动
}

void PannelNews::scrollText(float)
{
	news->getPosition().x < (-1 * news->getContentSize().width) ? news->setPositionX(910) : news->setPositionX(news->getPositionX() - 2);
}