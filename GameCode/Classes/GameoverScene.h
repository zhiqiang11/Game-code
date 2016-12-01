#ifndef __GAMEOVER_SCENE_H__
#define __GAMEOVER_SCENE_H__

#include "cocos2d.h"
#include "Audio.h"
#include "BasicScene.h"
#include "PlayScene.h"
#include "StartScene.h"
USING_NS_CC;

class GameoverScene : public BasicScene
{
public:

	virtual bool init();

	GameoverScene(float Score, int BeatMonsterAmount,int GainGoldAmount);

	void menuReplayCallback(cocos2d::Ref* pSender);

	void menuHomeCallback(cocos2d::Ref* pSender);

	static GameoverScene* createWithScore(float Time, int BeatMonsterAmount, int GainGoldAmount);

private:
	float Time;
	int BeatMonsterAmount;
	int GainGoldAmount;
	int Score;
	Menu* menu;
};

#endif // __START_SCENE_H__

