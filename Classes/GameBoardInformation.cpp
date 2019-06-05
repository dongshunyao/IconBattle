#include "GameBoardInformation.h"
using namespace GameBoardInformation;

Actor* Actor::create(const int type, const Pair position)
{
	auto actor = new(std::nothrow) Actor();
	if (actor)
	{
		actor->type = type;
		actor->position = position;

		assert(type >= 0 && type <= 6);

		actor->sprite = Sprite::create(SPRITE_URL[type]);
		actor->sprite->setPosition(position.first, position.second);
		actor->sprite->setScale(0.9f);
		actor->addChild(actor->sprite);
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
	runAction(action);
	this->position = toPosition;
}

void Actor::moveTo(const Pair toPosition)
{
	const auto action = Sequence::create(MoveTo::create(0.25, Vec2(toPosition.first, toPosition.second)), nullptr);
	runAction(action);
	this->position = toPosition;
}

void Actor::moveToAndBack(const Pair toPosition)
{
	const auto action = Sequence::create(
		MoveTo::create(0.25, Vec2(toPosition.first, toPosition.second)),
		MoveTo::create(0.25, Vec2(position.first, position.second)),
		nullptr);
	runAction(action);
}

void Actor::disappear()
{
	runAction(Sequence::create(ScaleTo::create(0.3f, 0.0f), nullptr));

	auto parent = getParent();
	Node* child = this;
	runAction(Sequence::createWithTwoActions(DelayTime::create(0.3f),
	                                         CallFunc::create([parent, child]() { parent->removeChild(child); })));
}
