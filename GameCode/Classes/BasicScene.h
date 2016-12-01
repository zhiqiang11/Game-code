#ifndef __BASIC_SCENE_H__
#define __BASIC_SCENE_H__

#include "cocos2d.h"
#include "MatchstickMan.h"
#include "Audio.h"

class BasicScene : public cocos2d::Layer
{
public:
	//static cocos2d::Scene* createScene();

	virtual bool init();

	void initBasicGround();

	void adaptToWinSize(Node *node);

	//Add the sprite of all the entities to this scene
	void addEntitySprite(Entity* entity, int zOrder);

	// implement the "static create()" method manually
	CREATE_FUNC(BasicScene);
private:
	//Audio* audio;
	bool isPause;

};

#endif // __BASIC_SCENE_H__
