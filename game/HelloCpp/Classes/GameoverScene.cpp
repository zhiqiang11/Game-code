#include "GameoverScene.h"

bool GameoverScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	initBasicGround();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	if (this->Time < 0)
		this->Time = 0;

	auto title = Label::createWithTTF("Game Over", "fonts/Marker Felt.ttf", visibleSize.width / 15);
	title->setColor(Color3B(0, 0, 0));
	title->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - title->getContentSize().height / 2));
	addChild(title, 2);


	cocos2d::__String* time = cocos2d::__String::createWithFormat("%.2f", Time);
	auto lblTime = Label::createWithTTF(time->getCString(), "fonts/Marker Felt.ttf", visibleSize.width / 25);
	lblTime->setPosition(Vec2(visibleSize.width / 1.7, visibleSize.height / 1.3));
	lblTime->setColor(Color3B(0, 0, 0));
	this->addChild(lblTime, 2);

	auto timeTitle = Label::createWithTTF("Time", "fonts/Marker Felt.ttf", visibleSize.width / 25);
	timeTitle->setColor(Color3B(0, 0, 0));
	timeTitle->setPosition(Vec2(visibleSize.width / 2.5, visibleSize.height / 1.3));
	addChild(timeTitle, 2);

	__String* gold = __String::createWithFormat("%d", GainGoldAmount);
	auto lblGold = Label::createWithTTF(gold->getCString(), "fonts/Marker Felt.ttf", visibleSize.width / 25);
	lblGold->setPosition(Vec2(visibleSize.width / 1.7, visibleSize.height / 1.5));
	lblGold->setColor(Color3B(0, 0, 0));
	this->addChild(lblGold, 2);

	auto goldTitle = Label::createWithTTF("Gold", "fonts/Marker Felt.ttf", visibleSize.width / 25);
	goldTitle->setColor(Color3B(0, 0, 0));
	goldTitle->setPosition(Vec2(visibleSize.width / 2.5, visibleSize.height / 1.5));
	addChild(goldTitle, 2);


	__String* monster = __String::createWithFormat("%d", BeatMonsterAmount);
	auto lblMonster = Label::createWithTTF(monster->getCString(), "fonts/Marker Felt.ttf", visibleSize.width / 25);
	lblMonster->setPosition(Vec2(visibleSize.width / 1.7, visibleSize.height / 1.7));
	lblMonster->setColor(Color3B(0, 0, 0));
	this->addChild(lblMonster, 2);

	auto monsterTitle = Label::createWithTTF("Monster", "fonts/Marker Felt.ttf", visibleSize.width / 25);
	monsterTitle->setColor(Color3B(0, 0, 0));
	monsterTitle->setPosition(Vec2(visibleSize.width / 2.5, visibleSize.height / 1.7));
	addChild(monsterTitle, 2);

	int iTime = (int)Time;
	Score = iTime * 10 + BeatMonsterAmount * 10;

	__String* score = __String::createWithFormat("%d", Score);
	auto lblScore = Label::createWithTTF(score->getCString(), "fonts/Marker Felt.ttf", visibleSize.width / 25);
	lblScore->setPosition(Vec2(visibleSize.width / 1.7, visibleSize.height / 2));
	lblScore->setColor(Color3B(0, 0, 0));
	this->addChild(lblScore, 2);

	auto scoreTitle = Label::createWithTTF("Score", "fonts/Marker Felt.ttf", visibleSize.width / 25);
	scoreTitle->setColor(Color3B(0, 0, 0));
	scoreTitle->setPosition(Vec2(visibleSize.width / 2.5, visibleSize.height / 2));
	addChild(scoreTitle, 2);

	auto replayItem = MenuItemImage::create(
		"replay.png",
		"replay.png",
		CC_CALLBACK_1(GameoverScene::menuReplayCallback, this));
	replayItem->setPosition(Vec2(visibleSize.width / 1.1,
		visibleSize.height / 1.4));
	auto homeItem = MenuItemImage::create(
		"home.png",
		"home.png",
		CC_CALLBACK_1(GameoverScene::menuHomeCallback, this));
	homeItem->setPosition(Vec2(visibleSize.width / 1.1,
		visibleSize.height / 2));
	menu = Menu::create(replayItem, homeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 10);
	return true;
}
GameoverScene::GameoverScene(float Time, int BeatMonsterAmount,int GainGoldAmount)
{
	this->Time = Time;
	this->BeatMonsterAmount = BeatMonsterAmount;
	this->GainGoldAmount = GainGoldAmount;
}
GameoverScene * GameoverScene::createWithScore(float Time, int BeatMonsterAmount,int GainGoldAmount)
{
	GameoverScene* gover = new GameoverScene(Time,BeatMonsterAmount, GainGoldAmount);
	if (gover&&gover->init())
	{
		gover->autorelease();
		return gover;
	}
	CC_SAFE_DELETE(gover);
	return nullptr;
}
void GameoverScene::menuReplayCallback(cocos2d::Ref * pSender)
{
	Director::getInstance()->replaceScene(PlayScene::createScene());
}
void GameoverScene::menuHomeCallback(cocos2d::Ref * pSender)
{
	Director::getInstance()->replaceScene(StartScene::createScene());
}