#ifndef __FACTORY_H__
#define __FACTORY_H__
#pragma   once 

#include "Gold.h"
#include "Sword.h"
#include "Monster.h"
#include "Board.h"
#include "Entity.h"
#include <iostream>
#include "MatchstickMan.h"
USING_NS_CC;

class Factory {
	/*private:
	static Factory* instance;
	Factory() {}
	~Factory() {
		if (instance)
			delete instance;
	}*/
public: 
	/*static Factory* GetInstance() {
		if (instance == nullptr)
			instance = new Factory();
		return instance;
	}*/
	virtual Entity* create() = 0;
};

class SwordFactory : public Factory {
private:
	static SwordFactory* instence1;
	SwordFactory(){}
	~SwordFactory() {}
public:
	static SwordFactory* GetInstance1() {
		if (instence1 == nullptr)
			instence1 = new SwordFactory();
		return instence1;
	}
	Sword* create() {
		Sword* a = Sword::create();
		return a;
	}
};


class GoldFactory : public Factory {
private:
	static GoldFactory* instance2;
	GoldFactory() {}
	~GoldFactory() {
		if (instance2)
			delete instance2;
	}
public:
	static GoldFactory* GetInstance2() {
		if (instance2 == nullptr)
			instance2 = new GoldFactory();
		return instance2;
	}
	Gold* create() {
		Gold* a =Gold::create();
		return a;
	}
};


class ManFactory : public Factory {
private:
	static ManFactory* instance3;
	ManFactory() {}
	~ManFactory() {
		if (instance3)
			delete instance3;
	}
public:
	static ManFactory* GetInstance3() {
		if (instance3 == nullptr)
			instance3 = new ManFactory();
		return instance3;
	}
	MatchstickMan* create() {
		MatchstickMan* a =MatchstickMan::create();
		return a;
	}
};


class BoardFactory : public Factory {
private:
	static BoardFactory* instance4;
	BoardFactory() {}
	~BoardFactory() {
		if (instance4)
			delete instance4;
	}
public:
	static BoardFactory* GetInstance4() {
		if (instance4 == nullptr)
			instance4 = new BoardFactory();
		return instance4;
	}
	Board* create() {
		Board* a =Board::create();
		return a;
	}
};


class MonsterFactory : public Factory {
private:
	static MonsterFactory* instance5;
	MonsterFactory() {}
	~MonsterFactory() {
		if (instance5)
			delete instance5;
	}
public:
	static MonsterFactory* GetInstance5() {
		if (instance5 == nullptr)
			instance5 = new MonsterFactory();
		return instance5;
	}
	Monster* create() {
		Monster* a =Monster::create();
		return a;
	}
};

#endif
