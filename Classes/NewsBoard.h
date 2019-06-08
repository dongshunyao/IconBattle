#ifndef __BULLETIN_BOARD_H__
#define __BULLETIN_BOARD_H__

#include "cocos2d.h"
#include "2d/CCClippingNode.h"
#include "Theme.h"
#include "Network.h"
#include "User.h"

USING_NS_CC;

class NewsBoard final :
	public Node
{
public:
	bool init() override;
	CREATE_FUNC(NewsBoard)

private:
	void scrollText(float);

	Label* news = nullptr;
	Theme* theme = Theme::getInstance();
};

#endif
