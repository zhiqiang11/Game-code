#include "Sword.h"

Sword::Sword()
{
}

Sword::~Sword()
{
}

bool Sword::init()
{
	eSprite = Sprite::create("sword1.png");
	setEBody();
	eSprite->setTag(SwordTag);
	eBody->setContactTestBitmask(0xFFFFFFFF);
	eBody->setDynamic(true);
	eBody->setGravityEnable(false);
	speed = 10;
	CanFlyAgain = true;
	this->retain();
	return true;
}

void Sword::SwordFly()
{
	if (eSprite->isVisible())
	{
		CanFlyAgain = false;
	}
	posX = eSprite->getPositionX();
	posX += speed;
	eSprite->setPositionX(posX);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	if (posX > visibleSize.width+eSprite->getContentSize().width/2)
	{
		hide();
		CanFlyAgain = true;
	}
	eSprite->setPositionX(posX);
}

bool Sword::FlyFinished()
{
	return CanFlyAgain;
}

Animate * Sword::creatAnimateFly()
{
	SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("swords.plist", "swords.png");

	int iFrameNum = 6;
	SpriteFrame* frame = NULL;
	Vector<SpriteFrame*>frameVec;

	for (int i = 1; i <= iFrameNum; i++)
	{
		frame = frameCache->getSpriteFrameByName(StringUtils::format("sword%d.png", i));
		frameVec.pushBack(frame);
	}
	Animation* animation = Animation::createWithSpriteFrames(frameVec);
	animation->setLoops(-1);
	animation->setDelayPerUnit(0.01f);

	Animate* action = Animate::create(animation);

	return action;
}
