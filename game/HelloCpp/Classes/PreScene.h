#ifndef __PRE_SCENE_H__
#define __PRE_SCENE_H__

#include "cocos2d.h"
#include "BasicScene.h"
#include "TimeCounter.h"
#include "StartScene.h"

class PreScene : public BasicScene 
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void timeupdate(float delta);

	// implement the "static create()" method manually
	CREATE_FUNC(PreScene);
private:
	TimeCounter* timeCounter;
};

#endif // __START_SCENE_H__

