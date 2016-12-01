#include "Gold.h"

Gold::Gold()
{
	eSprite = Sprite::create("Gold.png");
	eSprite->setTag(GoldTag);
}

Gold::~Gold()
{

}

bool Gold::init()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	speed = visibleSize.width / 320;
	setEBody();
	eBody->setContactTestBitmask(15);
	this->retain();
	return true;
}
