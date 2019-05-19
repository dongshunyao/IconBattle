#pragma once
#include "cocos2d.h"
#include "2d/CCClippingNode.h"
USING_NS_CC;

class PannelNews :public Node
{
protected:
	Node* holder = nullptr;
	Sprite* newsBg = nullptr;
	Label* news = nullptr;
	DrawNode* sharpNode = nullptr;
	ClippingNode* clipper = nullptr;

public:
	PannelNews();
	~PannelNews();
	virtual bool init() override;

	void layout();
	void scrollText(float);

	CREATE_FUNC(PannelNews);
};

