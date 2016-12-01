#include "PreScene.h"

cocos2d::Scene * PreScene::createScene()
{
	auto scene = Scene::create();

	auto layer = PreScene::create();

	scene->addChild(layer);

	return scene;
}

bool PreScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//init a white background
	auto background = Sprite::create("background.jpg");
	adaptToWinSize(background);
	background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(background);

	//init a game title
	auto title = Label::createWithTTF("Matchstick Man", "fonts/Marker Felt.ttf", visibleSize.width / 15);
	title->setColor(Color3B(0, 0, 0));
	title->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height/2));
	this->addChild(title, 1);

	//a timecounter to count time
	timeCounter = TimeCounter::create();
	this->addChild(timeCounter);
	timeCounter->start();


	this->schedule(schedule_selector(PreScene::timeupdate));

	return true;
}

void PreScene::timeupdate(float delta)
{
	float time = timeCounter->getfCurTime();
	//the prescene will last 1 second
	if (time > 1)
	{
		auto startscene = StartScene::createScene();
		auto scene = TransitionFade::create(1.0f,startscene);
		this->unschedule(schedule_selector(PreScene::timeupdate));
		Director::getInstance()->pushScene(scene);
	}
		
}
