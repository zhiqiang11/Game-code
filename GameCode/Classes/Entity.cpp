#include "Entity.h"


Entity::Entity()
{
	eSprite = NULL;	
}

Entity::~Entity()
{

}

Sprite * Entity::getSprite()
{
	return this->eSprite;
}

PhysicsBody * Entity::getBody()
{
	return eBody;
}

//Set the physics body of the binding sprite
void Entity::setEBody()
{
	eBody = PhysicsBody::createBox(eSprite->getContentSize());
	eSprite->setPhysicsBody(eBody);
	eBody->setDynamic(false);
}

void Entity::hide()
{
	eSprite->setVisible(false);
	eBody->setEnabled(false);
}

void Entity::show()
{
	eSprite->setVisible(true);
	eBody->setEnabled(true);
}

void Entity::fly()
{
	posX = eSprite->getPositionX();
	posX -= speed;
	eSprite->setPositionX(posX);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	if (posX < -eSprite->getContentSize().width / 2)
	{
		posX = visibleSize.width + eSprite->getContentSize().width;
	}

	eSprite->setPositionX(posX);
}

bool Entity::isStart()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	if (visibleSize.width + eSprite->getContentSize().width / 2 <= eSprite->getPosition().x)
	{
		return true;
	}
	else return false;
}

void Entity::setSpeed(float Velocity)
{
	speed = Velocity;
}
