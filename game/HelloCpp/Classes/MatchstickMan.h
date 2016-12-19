#ifndef __MATCHSTICK_MAN_H__
#define __MATCHSTICK_MAN_H__
#include "cocos2d.h"
#include "Entity.h"
#include "TimeCounter.h"
#include "Sword.h"
using namespace cocos2d;

#define StickManTag						100
#define InvincibleGoldNum				1

class MatchstickMan : public Entity
{
public:
	MatchstickMan();
	~MatchstickMan();
	CREATE_FUNC(MatchstickMan);

	virtual bool init();
public:

	Animate*  creatAnimateRUN();
//	Animate*  AnimateInvincible();
	
	void jump();
	void addJumpTimes();
	void resetJumpTimes();

	void addGoldNumber();
	void resetGoldNumber();

	bool Invincible();
	void ExitInvincible();

	virtual void setEBody();
private:
	int GoldNumber;
	int JumpTimes;
	
	//Sprite* InvincibleSprite;
};
class InvincibleStickMan : public MatchstickMan {
private:
	MatchstickMan *_Man;
public:
	InvincibleStickMan(){}
	InvincibleStickMan(MatchstickMan *m_Man) {
		_Man = m_Man;
	}
	//~InvincibleStickMan(){}
	Animate*  AnimateInvincible();
	
};
#endif // !__MATCHSTICK_MAN_H__


