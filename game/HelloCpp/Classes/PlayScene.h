//This is a scene in which we can play the game.
#ifndef __PLAY_SCENE_H__
#define __PLAY_SCENE_H__

#include "cocos2d.h"

//The following header files are all Entities files
#include "MatchstickMan.h"
#include "Board.h"
#include "Sword.h"
#include "Monster.h"
#include "Gold.h"

//The following header files are all Scene-Control files
#include "Audio.h"
#include "TimeCounter.h"

//The following header files are all Scene files
#include "BasicScene.h"
#include "StartScene.h"
#include"GameoverScene.h"

//The following header file is for the producing random number purpose
#include <random>

USING_NS_CC;										//using namespace cocos2d

#define TimeTag										303
#define SwordNum									3
#define BoardNumber									4
#define MonsterNum									3
#define GoldNum										3

class PlayScene : public BasicScene
{
public:
	
	static cocos2d::Scene* createScene();
	virtual bool init();
	void update(float delta) override;
	
	//Some menu Item Callback functions
	void menuPauseCallback(cocos2d::Ref* pSender);
	void menuResumeCallback(cocos2d::Ref* pSender);
	void menuReplayCallback(cocos2d::Ref* pSender);
	void menuHomeCallback(cocos2d::Ref* pSender);

	//All the events about contact are packed in this function,
	//and it can add the contact listener to this scene.
	void addContactListener();

	//Add the listener of touch event
	void addTouchListener();

	//The following functions are all about touch event.
	bool touchBegan(const std::vector< Touch * > &  touches, Event * event);
	void touchEnded(const std::vector< Touch * > &  touches, Event * event);
	bool LeftIsTap(Node * node, Touch* touch);
	bool RightIsTap(Node * node, Touch* touch);

	void addDifficulty(Entity* entity);
	void randomFly(Entity* top, Entity* mid, Entity* bot, int randFrequency);

	void GameOver();

	//To calculate final score according to time, GainGoldAmount and BeatMonsterAmount.
	void calculateScore(float delta);

	// implement the "static create()" method manually
	CREATE_FUNC(PlayScene);

private:
	
	bool isGamePause;
	bool isMusicPause;
	float Time;
	int GainGoldAmount;						//To count the amout of hero gaining golds.
	int BeatMonsterAmount;					//To count the amout of hero beating monsters.
	float InvincibleStartTime;				//To record the invincible status's Starting time.
	
	TimeCounter* timeCounter;
	Menu* menu;
	Menu* menuPause;

	//The following private members are different entities defined by single object or Vector.
	
	MatchstickMan* hero;					//Our game's hero.
	Sprite* heroInvincible;					//When the hero get invincible, use this sprite.
	
	Board* FirstBoard;						//The First and the longest board when playing starts.
	Vector<Board*> TopBoards;				//Three rows of boards that make a matrix of boards,
	Vector<Board*> MidBoards;				//and hero can run on every boards. When hero's
	Vector<Board*> BotBoards;				//position.y<=the bottomBoard's position,game over.

											//The attck weapon of the hero,
	Vector<Sword*> AttackSwords;			//which can beat the monsters.
											//But hero can only release 3(SwordNum) at one time.

											//The monsters that to be beat or elude,
	Vector<Monster*> Monsters;				//but when the hero crash to the monster,game will over.
											//Beat monster will bring score bonus.

											//The golds that can bring score bonus 
	Vector<Gold*> Golds;					//and when gold number come to some degree,
											//hero will get invincible
};

#endif // __PLAY_SCENE_H__

