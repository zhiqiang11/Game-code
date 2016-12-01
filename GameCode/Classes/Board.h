//This is a class that derived from Class Entity
//The Board is something on which the hero run.

#ifndef __BOARD_H__
#define __BOARD_H__
#include "cocos2d.h"
#include "Entity.h"

using namespace cocos2d;

#define BoardTag						200

class Board : public Entity
{
public:
	Board();
	~Board();
	CREATE_FUNC(Board);
	virtual bool init();

	virtual void setEBody();
public:
	void FirstBoardFly();
};
#endif // !__BOARD_H__
