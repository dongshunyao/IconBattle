#include "StructNames.h"
using namespace StructNames;

Actor* Actor::create(int type, int func, pii pos) {
	Actor* actor = new (std::nothrow) Actor();
	if (actor) {
		actor->setType(type);
		actor->setFunc(func);
		actor->setPos(pos);

		assert(type >= 0 && type <= 6);
		assert(func >= -1 && type <= 6);

		actor->setGem(Sprite::create(GEM_N[type]));
		actor->getGem()->setPosition(pos.first, pos.second);
		actor->getGem()->setScale(0.9f);
		actor->getGem()->setZOrder(0);
		actor->addChild(actor->getGem());

		if (func == -1) {
			actor->setIcon(NULL);
		}
		else {
			actor->setIcon(Sprite::createWithSpriteFrameName(SPIC_N[func]));
			actor->getIcon()->setPosition(pos.first, pos.second);
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

void StructNames::Actor::allDo(Action* action) {
	getGem()->runAction(action->clone());
	if (getIcon())getIcon()->runAction(action->clone());
}

void StructNames::Actor::moveTo(pii pos) {
	auto action = Sequence::create(
		CCMoveTo::create(0.25, Vec2(pos.first, pos.second)),
		NULL
	);
	allDo(action);
	this->pos = pos;
}

void StructNames::Actor::moveToThenBack(pii posb) {
	auto action = Sequence::create(
		CCMoveTo::create(0.25, Vec2(posb.first, posb.second)),
		CCMoveTo::create(0.25, Vec2(pos.first, pos.second)),
		NULL
	);
	allDo(action);
}

void StructNames::Actor::dropTo(pii pos) {
	auto action = Sequence::create(
		CCEaseOut::create(CCMoveTo::create(0.5, ccp(pos.first, pos.second)), 2.0f),
		NULL
	);
	allDo(action);
	this->pos = pos;
}

void StructNames::Actor::selfClose() {
	auto action = Sequence::create(
		CCScaleTo::create(.3f, .0f),
		NULL
	);
	allDo(action);
	Node* father = getParent();
	Node* me = this;
	runAction(Sequence::createWithTwoActions(DelayTime::create(.3f), CCCallFunc::create([father, me]() {father->removeChild(me); })));
	//LEAK?
}
