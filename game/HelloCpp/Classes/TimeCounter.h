#ifndef __TIMECOUNTER_H__
#define __TIMECOUNTER_H__

#include"cocos2d.h"

USING_NS_CC;
class TimeCounter :public Node
{
public:
	CREATE_FUNC(TimeCounter);
	virtual bool init();

	virtual void update(float dt);

	void start();
	float getfCurTime();
private:
	float Time;
};

#endif // !__TIMECOUNTER_H__
