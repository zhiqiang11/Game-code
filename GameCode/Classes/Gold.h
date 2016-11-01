#ifndef __GOLD_H__
#define __GOLD_H__

#define GoldTag		500
#include "Entity.h"

class Gold : public Entity
{
public:
	Gold();
	~Gold();
	CREATE_FUNC(Gold);
	virtual bool init();
};

#endif // !__GOLD_H__


