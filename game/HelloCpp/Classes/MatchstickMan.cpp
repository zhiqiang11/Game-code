#include "MatchstickMan.h"

MatchstickMan::MatchstickMan()
{
	
	eSprite = Sprite::create("run1.png");
	JumpTimes = 0;
	GoldNumber = 0;
	eSprite->setTag(StickManTag);
}

MatchstickMan::~MatchstickMan()
{
	
}

bool MatchstickMan::init()
{
	eSprite->runAction(creatAnimateRUN());
	this->retain();
	return true;
}

void MatchstickMan::jump()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	float force = (visibleSize.width / 64) * 100;
	//float damping = force / 300;
	if (JumpTimes <= 2)
	{
		eBody->setVelocity(Vec2(0, force));
		eBody->setLinearDamping(5.0f);
	}
}

void MatchstickMan::setEBody()
{
	eBody = PhysicsBody::createBox(eSprite->getContentSize());
	eSprite->setPhysicsBody(eBody);
	eBody->setRotationEnable(false);
	eBody->setContactTestBitmask(0xFFFFFFFF);
}

void MatchstickMan::addGoldNumber()
{
	GoldNumber += 1;
}

void MatchstickMan::resetGoldNumber()
{
	GoldNumber = 0;
}

bool MatchstickMan::Invincible()
{
	if (GoldNumber == InvincibleGoldNum)
	{
		resetGoldNumber();
		resetJumpTimes();
		hide();
		return true;
	}
	else return false;
}

void MatchstickMan::ExitInvincible()
{
	resetJumpTimes();
	show();
}

Animate* MatchstickMan::creatAnimateRUN()
{
	SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("runs.plist", "runs.png");
	int iFrameNum = 6;
	SpriteFrame* frame = NULL;
	Vector<SpriteFrame*>frameVec;
	for (int i = 1; i <= iFrameNum; i++)
	{
		frame = frameCache->getSpriteFrameByName(StringUtils::format("run%d.png", i));
		frameVec.pushBack(frame);
	}
	Animation* animation = Animation::createWithSpriteFrames(frameVec);
	animation->setLoops(-1);
	animation->setDelayPerUnit(0.08f);
	Animate* action = Animate::create(animation);
	return action;
}

/*Animate * MatchstickMan::AnimateInvincible()
{
	SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("runsIn.plist", "runsIn.png");


	int iFrameNum = 6;
	SpriteFrame* frame = NULL;
	Vector<SpriteFrame*>frameVec;

	for (int i = 1; i <= iFrameNum; i++)
	{
		frame = frameCache->getSpriteFrameByName(StringUtils::format("runIn%d.png", i));
		frameVec.pushBack(frame);
	}
	Animation* animation = Animation::createWithSpriteFrames(frameVec);
	animation->setLoops(-1);
	animation->setDelayPerUnit(0.05f);

	Animate* action = Animate::create(animation);

	return action;
}*/

void MatchstickMan::addJumpTimes()
{
	JumpTimes += 1;
}

void MatchstickMan::resetJumpTimes()
{
	JumpTimes = 0;
}
Animate * InvincibleStickMan::AnimateInvincible()
{
	SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("runsIn.plist", "runsIn.png");


	int iFrameNum = 6;
	SpriteFrame* frame = NULL;
	Vector<SpriteFrame*>frameVec;

	for (int i = 1; i <= iFrameNum; i++)
	{
		frame = frameCache->getSpriteFrameByName(StringUtils::format("runIn%d.png", i));
		frameVec.pushBack(frame);
	}
	Animation* animation = Animation::createWithSpriteFrames(frameVec);
	animation->setLoops(-1);
	animation->setDelayPerUnit(0.05f);

	Animate* action = Animate::create(animation);

	return action;
}