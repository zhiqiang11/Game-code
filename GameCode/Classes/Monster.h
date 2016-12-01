#ifndef __MONSTER_H__
#define __MONSTER_H__

#define MonsterTag		400
#include "cocos2d.h"
#include "Entity.h"
#include <random>
using namespace cocos2d;
class Monster : public Entity
{
public:
	Monster();
	~Monster();
	CREATE_FUNC(Monster);
	virtual bool init();
	
};
#endif // !__MONSTER_H__
