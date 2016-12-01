#include "BasicScene.h"

bool BasicScene::init()
{
	return true;
}

void BasicScene::initBasicGround()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto background = Sprite::create("city.jpg");
	adaptToWinSize(background);

	background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	this->addChild(background, 0);

	auto musicON = Sprite::create("volON.png");
	musicON->setPosition(visibleSize.width / 1.1 + origin.x, visibleSize.height / 1.1 + origin.y);
	this->addChild(musicON, 1);

	auto musicOFF = Sprite::create("volOFF.png");
	musicOFF->setPosition(visibleSize.width / 1.1 + origin.x, visibleSize.height / 1.1 + origin.y);
	this->addChild(musicOFF, 1);

	
	auto audio = SimpleAudioEngine::getInstance();
	if (audio->isBackgroundMusicPlaying())
		isPause = false;
	else
	{
		audio->playBackgroundMusic("backMusic.mp3",true);
		isPause = false;
	}

	auto listenerMusic = EventListenerTouchOneByOne::create();
	listenerMusic->onTouchBegan = [=](Touch* touch, Event* event)
	{
		Point pos = Director::getInstance()->convertToGL(touch->getLocationInView());

		if ((!isPause) && (musicON->getBoundingBox().containsPoint(pos)))
		{
			SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
			musicON->setOpacity(0);
			isPause = true;
			return true;
		}
		else if ((isPause) && (musicON->getBoundingBox().containsPoint(pos)))
		{
			SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
			musicON->setOpacity(255);
			isPause = false;
			return true;
		}

		return false;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerMusic, musicON);

}

void BasicScene::adaptToWinSize(Node * node)
{
	auto myWinSize = Director::getInstance()->getWinSize();
	float winWidth = myWinSize.width;
	float winHeight = myWinSize.height;
	float width = node->getContentSize().width;
	float height = node->getContentSize().height;

	node->setScaleX(winWidth / width);
	node->setScaleY(winHeight / height);
}

void BasicScene::addEntitySprite(Entity * entity, int zOrder)
{
	this->addChild(entity->getSprite(), zOrder);
}
