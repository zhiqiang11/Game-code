#pragma once
#include <iostream>  
#include <string>  
#include <vector>
#include "cocos2d.h"
#include "Gold.h"

using namespace std;
USING_NS_CC;
//using namespace CocosDenshion;

class Iterator {
public:
	Iterator() {}
	virtual ~Iterator() {};
	virtual Gold* First() = 0;
	virtual Gold* Next() = 0;
	virtual Gold* GetCur() = 0;
	virtual Gold* Getenty(int cnt) = 0;
	virtual void Erase() = 0;
	virtual bool IsEnd() = 0;
};

class Aggregate {
public:
	virtual int Count() = 0;
	virtual void Push(Gold* sprite) = 0;
	virtual Gold* Pop(int cnt) = 0;
	virtual void Erase(int i) = 0;
	virtual Iterator* CreateIterator() = 0;
};

class ConcreteIterator : public Iterator {
public:
	ConcreteIterator(Aggregate *p_aggregate) :m_aggregate(p_aggregate) { m_cnt = 0; }

	Gold* First() {
		m_cnt = 0;
		return m_aggregate->Pop(0);
	}

	Gold* Next() {
		Gold* a = nullptr;
		m_cnt++;
		if (m_cnt < m_aggregate->Count()) {
			a = m_aggregate->Pop(m_cnt);
		}
		return a;
	}

	Gold* GetCur() {
		return m_aggregate->Pop(m_cnt);
	}
	Gold* Getenty(int cnt) {
		return m_aggregate->Pop(cnt);
	}

	bool IsEnd() {
		return m_cnt >= m_aggregate->Count() ? true : false;
	}

	void Erase() {
		m_aggregate->Erase(m_cnt);
	}

	~ConcreteIterator() { }


private:
	Aggregate *m_aggregate;
	int m_cnt;
};

class ConcreteAggregate : public Aggregate {
public:
	ConcreteAggregate() :m_pIterator(NULL) {
		m_vecItem.clear();
	}

	~ConcreteAggregate() {
		if (NULL != m_pIterator) {
			delete m_pIterator;
			m_pIterator = NULL;
		}
	}

	int Count() {
		return m_vecItem.size();
	}

	void Push(Gold* sprite) {
		//m_vecItem.push_back(strValue);
		m_vecItem.pushBack(sprite);
	}

	Gold* Pop(int cnt) {
		Gold* a;
		if (cnt < Count()) {
			a = m_vecItem.at(cnt);
		}
		return a;
	}

	void Erase(int i) {
		m_vecItem.erase(i);
	}

	Iterator* CreateIterator() {
		//if (NULL == m_pIterator) {
		m_pIterator = new ConcreteIterator(this);
		//}
		return m_pIterator;
	}

private:
	Vector<Gold*> m_vecItem;
	Iterator *m_pIterator;
};