#include"TimeCounter.h"

bool TimeCounter::init()
{
	return true;
}

void TimeCounter::update(float dt)
{
	Time += dt;
}

void TimeCounter::start()
{
	Time = 0;
	this->scheduleUpdate();
}

float TimeCounter::getfCurTime()
{
	return Time;
}
