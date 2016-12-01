#include "Board.h"

Board::Board()
{
	eSprite = Sprite::create("shortBoard.png");
	eSprite->setTag(BoardTag);
}

Board::~Board()
{
}

bool Board::init()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	speed = visibleSize.width / 320;
	this->retain();
	return true;
}

void Board::setEBody()
{
	eBody = PhysicsBody::createBox(eSprite->getContentSize());
	eSprite->setPhysicsBody(eBody);
	eBody->setDynamic(false);
	eBody->setContactTestBitmask(12);
}

void Board::FirstBoardFly()
{
	posX = eSprite->getPositionX();
	posX -= speed;
	eSprite->setPositionX(posX);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	if (posX < -eSprite->getContentSize().width *3)
	{
		posX = visibleSize.width + eSprite->getContentSize().width;
	}
	eSprite->setPositionX(posX);
}


