#ifndef __SWORD_H__
#define __SWORD_H__
#define SwordTag 300
#include "cocos2d.h"
#include "Entity.h"
using namespace cocos2d;
class Sword : public Entity
{
public:
	Sword();
	~Sword();
	CREATE_FUNC(Sword);
	virtual bool init();
public:
	void SwordFly();
	bool FlyFinished();
	Animate *creatAnimateFly();
private:
	bool CanFlyAgain;
};
#endif // !__SWORD_H__
