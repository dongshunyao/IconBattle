#include "GameBoardInformation.h"
using namespace GameBoardInformation;

// 创建
Actor* Actor::create(const int type, int func, const Pair position)
{
	auto actor = new(std::nothrow) Actor();
	if (actor)
	{
		actor->setType(type);
		actor->setFunc(func);
		actor->position = position;

		assert(type >= 0 && type <= 6);

		actor->setGem(Sprite::create(GEM_N[type]));
		actor->getGem()->setPosition(position.first, position.second);
		actor->getGem()->setScale(0.9f);
		actor->getGem()->setZOrder(0);
		actor->addChild(actor->getGem());

		if (func == -1)
		{
			actor->setIcon(NULL);
		}
		else
		{
			actor->setIcon(Sprite::createWithSpriteFrameName(SPIC_N[func]));
			actor->getIcon()->setPosition(position.first, position.second);
			actor->getIcon()->setScale(0.9f);
			actor->getIcon()->setZOrder(1);
			actor->addChild(actor->getIcon());
		}
		//DONE: check Zorder -- OK

		actor->autorelease();
		return actor;
	}
	CC_SAFE_DELETE(actor);
	return nullptr;
}

void Actor::dropTo(const Pair toPosition)
{
	const auto action = Sequence::create(
		EaseOut::create(MoveTo::create(0.5, Vec2(toPosition.first, toPosition.second)), 2.0f), nullptr);
	allDo(action);
	this->position = toPosition;
}

// 本cpp文件中所有动画的实现调用方法
void GameBoardInformation::Actor::allDo(Action* action)
{
	getGem()->runAction(action->clone());
	if (getIcon())getIcon()->runAction(action->clone());
}

// 移动
void GameBoardInformation::Actor::moveTo(Pair pos)
{
	auto action = Sequence::create(
		CCMoveTo::create(0.25, Vec2(pos.first, pos.second)),
		NULL
	);
	allDo(action);
	this->position = pos;
}

void Actor::moveToThenBack(Pair posb)
{
	auto action = Sequence::create(
		CCMoveTo::create(0.25, Vec2(posb.first, posb.second)),
		CCMoveTo::create(0.25, Vec2(position.first, position.second)),
		NULL
	);
	allDo(action);
}


// 自己杀自己
void GameBoardInformation::Actor::selfClose()
{
	auto action = Sequence::create(
		CCScaleTo::create(.3f, .0f),
		NULL
	);
	allDo(action);
	Node* father = getParent();
	Node* me = this;
	runAction(Sequence::createWithTwoActions(DelayTime::create(.3f),
	                                         CCCallFunc::create([father, me]() { father->removeChild(me); })));
	//LEAK?
}
