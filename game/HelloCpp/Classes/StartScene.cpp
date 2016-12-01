#include "StartScene.h"

Scene* StartScene::createScene()
{
    auto scene = Scene::create();
    
    auto layer = StartScene::create();

    scene->addChild(layer);

    return scene;
}


bool StartScene::init()
{
  
    if ( !Layer::init() )
    {
        return false;
    }
    
	initBasicGround();

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    
	auto playItem = MenuItemImage::create(
		"play1.png",
		"play1.png",
		CC_CALLBACK_1(StartScene::menuPlayCallback, this));

	playItem->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2));

	auto IntroductionItem = MenuItemImage::create(
		"introduction.png",
		"introduction.png",
		CC_CALLBACK_1(StartScene::menuIntroduceCallback, this));

	IntroductionItem->setPosition(Vec2(origin.x + visibleSize.width / 20,
		origin.y + visibleSize.height / 1.1));

	auto HelpItem = MenuItemImage::create(
		"help.png",
		"help.png",
		CC_CALLBACK_1(StartScene::menuHelpCallback, this));

	HelpItem->setPosition(Vec2(origin.x + visibleSize.width / 20 + HelpItem->getContentSize().width*1.3,
		origin.y + visibleSize.height / 1.1));


	auto menu = Menu::create(playItem,HelpItem,IntroductionItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	auto title = Label::createWithTTF("Matchstick Man", "fonts/Marker Felt.ttf", visibleSize.width / 15);
	title->setColor(Color3B(0, 0, 0));
	title->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - title->getContentSize().height / 2));

    this->addChild(title, 1);
    
	auto board = Sprite::create("shortBoard.png");
	board->setScaleX(40);

	board->setPosition(visibleSize.width / 4 + origin.x, origin.y + visibleSize.height / 8);
	this->addChild(board, 1);


	hero = MatchstickMan::create();
	hero->getSprite()->setPosition(Vec2(visibleSize.width / 4 + origin.x,
		visibleSize.height / 8 + hero->getSprite()->getContentSize().height / 2 + board->getContentSize().height / 2 + origin.y));
	addEntitySprite(hero, 1);
	
	this->scheduleUpdate();
    return true;
}


void StartScene::update(float delta)
{
	Node::update(delta);
}

void StartScene::menuIntroduceCallback(cocos2d::Ref * pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	introduction = Sprite::create("introduce.jpg");
	introduction->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2));
	this->addChild(introduction,3);
	
	auto closeItem = MenuItemImage::create(
		"close.png",
		"close.png",
		CC_CALLBACK_1(StartScene::menuCloseIntroduceCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width /2+introduction->getContentSize().width/2,
		origin.y + visibleSize.height / 2+introduction->getContentSize().height/2));

	menuCloseIntro = Menu::create(closeItem, NULL);
	menuCloseIntro->setPosition(Vec2::ZERO);
	this->addChild(menuCloseIntro, 5);
	
}

void StartScene::menuHelpCallback(cocos2d::Ref * pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	help = Sprite::create("help.jpg");
	help->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2));
	this->addChild(help, 3);

	auto closeItem = MenuItemImage::create(
		"close.png",
		"close.png",
		CC_CALLBACK_1(StartScene::menuCloseHelpCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width / 2 + help->getContentSize().width / 2,
		origin.y + visibleSize.height / 2 + help->getContentSize().height / 2));

	menuCloseHelp = Menu::create(closeItem, NULL);
	menuCloseHelp->setPosition(Vec2::ZERO);
	this->addChild(menuCloseHelp, 5);
}

void StartScene::menuCloseIntroduceCallback(cocos2d::Ref * pSender)
{
	menuCloseIntro->setOpacity(0);
	this->removeChild(introduction);

}

void StartScene::menuCloseHelpCallback(cocos2d::Ref * pSender)
{
	menuCloseHelp->setOpacity(0);
	this->removeChild(help);
}


void StartScene::menuPlayCallback(Ref* pSender)
{
    Director::getInstance()->replaceScene(PlayScene::createScene());

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
