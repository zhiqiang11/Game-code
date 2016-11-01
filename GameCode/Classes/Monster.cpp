#include "Monster.h"

Monster::Monster()
{
	int mRandom = rand() % 3 + 1;
	eSprite = Sprite::create(StringUtils::format("monster%d.png", mRandom));
}

Monster::~Monster()
{
}

bool Monster::init()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	speed = visibleSize.width / 320;
	setEBody();
	eBody->setContactTestBitmask(12);
	
	eSprite->setTag(MonsterTag);
	this->retain();
	return true;
}
