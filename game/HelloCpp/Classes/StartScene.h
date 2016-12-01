#ifndef __START_SCENE_H__
#define __START_SCENE_H__

#include "cocos2d.h"
#include "MatchstickMan.h"
#include "Audio.h"
#include "BasicScene.h"
#include "PlayScene.h"

USING_NS_CC;


class StartScene : public BasicScene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

	void update(float delta) override;

	void menuIntroduceCallback(cocos2d::Ref* pSender);

	void menuHelpCallback(cocos2d::Ref* pSender);

	void menuCloseIntroduceCallback(cocos2d::Ref* pSender);

	void menuCloseHelpCallback(cocos2d::Ref* pSender);
    // a selector callback
    void menuPlayCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(StartScene);
private:
	MatchstickMan* hero;
	Menu* menuCloseIntro;
	Menu* menuCloseHelp;
	Sprite* introduction;
	Sprite* help;
	
};

#endif // __START_SCENE_H__
