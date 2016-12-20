//This is a base class of all the entities in the game.

#ifndef __ENTITY_H__
#define __ENTITY_H__	

#include "cocos2d.h"
using namespace cocos2d;

class Entity : public Node
{
public:
	Entity();
	~Entity();

	Sprite* getSprite();
	PhysicsBody* getBody();
	virtual void setEBody();

public:

	void fly();
	void setSpeed(float Velocity);

	virtual void hide();
	virtual void show();
	bool isStart();
	//void SwordFly();
	//bool FlyFinished();

protected:
	
	Sprite* eSprite;				//The binding sprite of this Entity.
	PhysicsBody* eBody;				//The physics body of eSprite.

	float posX;
	float speed;
	//bool CanFlyAgain;
};


#endif // !__ENTITY_H__
