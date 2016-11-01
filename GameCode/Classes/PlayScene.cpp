#include "PlayScene.h"

Scene* PlayScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	
	//Set hero's jumping height according to the device's visible size
	float force = (Director::getInstance()->getVisibleSize().width / 64) * 100;
	scene->getPhysicsWorld()->setGravity(Vec2(0.0f, -force));
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	
	auto layer = PlayScene::create();
	scene->addChild(layer);

	return scene;
}

bool PlayScene::init()
{

	if (!Layer::init())
	{
		return false;
	}

	initBasicGround();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto pauseItem = MenuItemImage::create(
		"pause.png",
		"pause.png",
		CC_CALLBACK_1(PlayScene::menuPauseCallback, this));
	pauseItem->setPosition(Vec2(origin.x + visibleSize.width/15,
		origin.y + visibleSize.height/1.1));
	menuPause = Menu::create(pauseItem, NULL);
	menuPause->setPosition(Vec2::ZERO);
	this->addChild(menuPause, 1);

	//Initialize some variables that used for game controling
	InvincibleStartTime = 10000000;
	GainGoldAmount = 0;
	BeatMonsterAmount = 0;

	//Init FirstBoard and hero
	FirstBoard = Board::create();

	hero = MatchstickMan::create();
	hero->getSprite()->setPosition(Vec2(origin.x + visibleSize.width / 4,
		origin.y + visibleSize.height / 8 + hero->getSprite()->getContentSize().height / 2 
		+ FirstBoard->getSprite()->getContentSize().height / 2));
	hero->setEBody();
	addEntitySprite(hero, 5);
	
	heroInvincible = Sprite::create("runIn1.png");
	heroInvincible->runAction(hero->AnimateInvincible());
	heroInvincible->setVisible(false);
	this->addChild(heroInvincible, 5);

	//log("heroSize:%f", hero->getSprite()->getContentSize().width);
	
	FirstBoard->getSprite()->setScaleX(visibleSize.width /
		FirstBoard->getSprite()->getContentSize().width);
	FirstBoard->setEBody();
	FirstBoard->getSprite()->setPosition(visibleSize.width / 2,
		origin.y + visibleSize.height / 8);
	addEntitySprite(FirstBoard, 1);

	//Initialize boards
	for (int count = 0; count < BoardNumber; count++)
	{
		auto topBoard = Board::create();
		auto midBoard = Board::create();
		auto bottomBoard = Board::create();

		auto fourWidth = visibleSize.width / BoardNumber;
		double firstWidth = 0.75*0.5 / BoardNumber;

		topBoard->setEBody();
		midBoard->setEBody();
		bottomBoard->setEBody();

		topBoard->getSprite()->setPosition(Vec2(origin.x + visibleSize.width +
			count*(topBoard->getSprite()->getContentSize().width + 0.5*fourWidth)
			+ topBoard->getSprite()->getContentSize().width,
			origin.y + 5 * visibleSize.height / 8));

		midBoard->getSprite()->setPosition(Vec2(origin.x + visibleSize.width +
			count*(midBoard->getSprite()->getContentSize().width + 0.5*fourWidth)
			+ midBoard->getSprite()->getContentSize().width,
			origin.y + 3 * visibleSize.height / 8));

		bottomBoard->getSprite()->setPosition(Vec2(origin.x + visibleSize.width +
			count*(bottomBoard->getSprite()->getContentSize().width + fourWidth*0.5)
			+ bottomBoard->getSprite()->getContentSize().width,
			origin.y + visibleSize.height / 8));


		addEntitySprite(topBoard, 1);
		TopBoards.pushBack(topBoard);
		addEntitySprite(midBoard, 1);
		MidBoards.pushBack(midBoard);
		addEntitySprite(bottomBoard, 1);
		BotBoards.pushBack(bottomBoard);
	}

	//Init Swords
	for (int count = 0; count < SwordNum; count++)
	{
		auto sword = Sword::create();

		addEntitySprite(sword, 2);
		sword->hide();
		sword->getSprite()->runAction(sword->creatAnimateFly());
		AttackSwords.pushBack(sword);
	}

	//Init Monsters
	for (int count = 0; count < MonsterNum; count++)
	{
		auto monster = Monster::create();
		monster->getSprite()->setPosition(Vec2(origin.x + visibleSize.width +
			monster->getSprite()->getContentSize().width,
			origin.y + (2 * count + 1) *visibleSize.height / 8 + 
			FirstBoard->getSprite()->getContentSize().height +
			monster->getSprite()->getContentSize().height / 2));
		addEntitySprite(monster, 2);
		Monsters.pushBack(monster);
	}

	//Init Golds
	for (int count = 0; count < GoldNum; count++)
	{
		auto gold = Gold::create();
		gold->getSprite()->setPosition(Vec2(origin.x + visibleSize.width +
			gold->getSprite()->getContentSize().width,
			origin.y + (2 * count + 1) *visibleSize.height / 8 +
			4*gold->getSprite()->getContentSize().height / 2));
		
		addEntitySprite(gold, 2);
		Golds.pushBack(gold); 
	}

	//The top edge of the physics world,which prevents the hero from jumping out of the screen
	auto topEdge = PhysicsBody::createEdgeSegment(Vec2(origin.x, origin.y + visibleSize.height),
		Vec2(origin.x + visibleSize.width, origin.y + visibleSize.height));
	auto topEdgeNode = Node::create();
	topEdgeNode->setPhysicsBody(topEdge);
	this->addChild(topEdgeNode, 1);

	addTouchListener();

	//To add contact listener to the physics world,
	//and this function can finish all the contacting effects.
	addContactListener();

	timeCounter = TimeCounter::create();
	this->addChild(timeCounter);
	timeCounter->start();
	this->schedule(schedule_selector(PlayScene::calculateScore), 0.01f);

	this->scheduleUpdate();

	return true;
}

void PlayScene::update(float delta)
{
	//When the game starts, the first board must fly and get disappeared.
	FirstBoard->FirstBoardFly();
	if (FirstBoard->isStart())
	{
		FirstBoard->hide();
	}

	//The three rows of the boards will fly, and they will be judged whether to show when they 
	//get to the start position that set by designer, every columns will have only one board that
	//can show. And with time going on, the speed of the boards' flying will be accelerate,
	//so the drop speed of the hero will be accelerate too.
	for (int count = 0; count < BoardNumber; count++)
	{
		TopBoards.at(count)->fly();
		MidBoards.at(count)->fly();
		BotBoards.at(count)->fly();
						
		randomFly(TopBoards.at(count), MidBoards.at(count), BotBoards.at(count), 3);
		
		//Change the difficulty according to the current time.
		addDifficulty(TopBoards.at(count));
		addDifficulty(MidBoards.at(count));
		addDifficulty(BotBoards.at(count));
	}
	//To judge if the hero drops lower than the bottom boards.If true, you will lose the game.
	if (hero->getSprite()->getPosition().y < (FirstBoard->getPosition().y + hero->getSprite()->getPosition().y / 2))
	{
		this->getScene()->getPhysicsWorld()->setGravity(Vec2(0.0f, -10000.0f));
		GameOver();
	}
	//To make the attacking weapon of the hero fly.
	for (auto sword : AttackSwords)
	{
		sword->SwordFly();
	}
	//To make the monsters random fly.Just like boards.
	for (auto monster : Monsters)
	{
		monster->fly();
		addDifficulty(monster);
	}
	randomFly(Monsters.at(0), Monsters.at(1), Monsters.at(2), 5);
	
	//To make the golds fly, just like the boards and the monsters.
	for (auto gold : Golds)
	{
		gold->fly();
		addDifficulty(gold);
	}
	randomFly(Golds.at(0), Golds.at(1), Golds.at(2), 4);
}

void PlayScene::menuPauseCallback(cocos2d::Ref * pSender)
{
	this->pause();
	
	for (const auto& node : this->getChildren())
	{
		node->pause();
	}

	menuPause->setOpacity(0);

	hero->getBody()->setEnabled(false);

	SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	isMusicPause = true;

	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto playItem = MenuItemImage::create(
		"play1.png",
		"play1.png",
		CC_CALLBACK_1(PlayScene::menuResumeCallback, this));

	playItem->setPosition(Vec2(visibleSize.width / 2,
		visibleSize.height / 2));

	auto replayItem = MenuItemImage::create(
		"replay.png",
		"replay.png",
		CC_CALLBACK_1(PlayScene::menuReplayCallback, this));

	replayItem->setPosition(Vec2(visibleSize.width / 3,
		visibleSize.height / 2));

	auto homeItem = MenuItemImage::create(
		"home.png",
		"home.png",
		CC_CALLBACK_1(PlayScene::menuHomeCallback, this));
	homeItem->setPosition(Vec2(visibleSize.width / 1.5,
		visibleSize.height / 2));

	menu = Menu::create(playItem,replayItem,homeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

}

void PlayScene::menuResumeCallback(cocos2d::Ref * pSender)
{
	this->resume();

	for (const auto& node : this->getChildren())
	{
		node->resume();
	}

	menuPause->setOpacity(255);

	hero->getBody()->setEnabled(true);

	if (isMusicPause)
		SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	removeChild(menu);
}

void PlayScene::menuReplayCallback(cocos2d::Ref * pSender)
{
	if (isMusicPause)
		SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
	_eventDispatcher->removeAllEventListeners();
	Director::getInstance()->pushScene(PlayScene::createScene());
}

void PlayScene::menuHomeCallback(cocos2d::Ref * pSender)
{
	if (isMusicPause)
		SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
	_eventDispatcher->removeAllEventListeners();
	Director::getInstance()->replaceScene(StartScene::createScene());
}

void PlayScene::addContactListener()
{
	auto ContactListener = EventListenerPhysicsContact::create();
	ContactListener->onContactBegin = [=](PhysicsContact& contact)
	{
		auto spriteA = (Sprite*)contact.getShapeA()->getBody()->getNode();
		auto spriteB = (Sprite*)contact.getShapeB()->getBody()->getNode();

		//To check out whether hero and boards is contacting.
		if (spriteA&&spriteB && ((spriteB->getTag() == BoardTag&&spriteA->getTag() == StickManTag)
			|| spriteB->getTag() == StickManTag&&spriteA->getTag() == BoardTag))
		{
			hero->resetJumpTimes();
		}

		//To check out whether monster and sword is contacting.
		if (spriteA&&spriteB && ((spriteB->getTag() == MonsterTag&&spriteA->getTag() == SwordTag)
			|| spriteB->getTag() == SwordTag&&spriteA->getTag() == MonsterTag))
		{
			spriteA->setVisible(false);
			spriteA->getPhysicsBody()->setEnabled(false);
			spriteB->setVisible(false);
			spriteB->getPhysicsBody()->setEnabled(false);
			BeatMonsterAmount += 1;
		}
		//To check out whether monster and hero is contacting.
		if (spriteA&&spriteB && ((spriteB->getTag() == MonsterTag&&spriteA->getTag() == StickManTag)
			|| spriteB->getTag() == StickManTag&&spriteA->getTag() == MonsterTag))
		{
			GameOver();
		}
		//To check out whether hero and golds is contacting.
		if (spriteA&&spriteB && ((spriteB->getTag() == GoldTag&&spriteA->getTag() == StickManTag)
			|| spriteB->getTag() == StickManTag&&spriteA->getTag() == GoldTag))
		{
			if (spriteA->getTag() == GoldTag)
			{
				spriteA->setVisible(false);
				spriteA->getPhysicsBody()->setEnabled(false);
			}
			else if (spriteB->getTag() == GoldTag)
			{
				spriteB->setVisible(false);
				spriteB->getPhysicsBody()->setEnabled(false);
			}
			hero->addGoldNumber();
			GainGoldAmount += 1;
			if (hero->Invincible())
			{
				InvincibleStartTime = timeCounter->getfCurTime();
				heroInvincible->setPosition(hero->getSprite()->getPosition());
				heroInvincible->setVisible(true);
			}
			log("gold eat!");
			return false;		//To avoid hero's contact effect(rebound) of contacting gold
		}
		return true;
	};
	ContactListener->onContactSeparate = [](PhysicsContact& contact)
	{
		//For possible future use, temporarily empty.
	};
	Director::getInstance()->getEventDispatcher()->
		addEventListenerWithFixedPriority(ContactListener, 100);
}

void PlayScene::addTouchListener()
{
	//To add eventlistener to the actions of the hero, including jumping and attacking.
	auto PlayListener = EventListenerTouchAllAtOnce::create();
	PlayListener->onTouchesBegan = CC_CALLBACK_2(PlayScene::touchBegan, this);
	PlayListener->onTouchesEnded = CC_CALLBACK_2(PlayScene::touchEnded, this);
	EventDispatcher *eventDispatcher = Director::getInstance()->getEventDispatcher();
	eventDispatcher->addEventListenerWithFixedPriority(PlayListener, 3);

}

bool PlayScene::touchBegan(const std::vector< Touch * > &  touches, Event * event)
{
	for (auto touch : touches)
	{
		if (LeftIsTap(this, touch))
		{
			hero->addJumpTimes();
			hero->jump();
		}
		else if (RightIsTap(this, touch))
		{
			for (auto sword : AttackSwords)
			{
				if (sword->FlyFinished())
				{
					sword->getSprite()->setPosition(Vec2(hero->getSprite()->getPosition().x + 
						hero->getSprite()->getContentSize().width / 2 ,
						hero->getSprite()->getPosition().y));
					sword->show();
					break;
				}
			}
		}
	}
	return false;
}

void PlayScene::touchEnded(const std::vector< Touch * > &  touches, Event * event)
{
	//For possible future use, temporarily empty.
}

bool PlayScene::LeftIsTap(Node * node, Touch * touch)
{
	//If you touch the left side of the screen, return true.
	if (touch->getLocation().x <= node->getContentSize().width / 2)
	{
		return true;
	}
	return false;
}

bool PlayScene::RightIsTap(Node * node, Touch * touch)
{
	//If you touch the right side of the screen, return true.
	if (touch->getLocation().x > node->getContentSize().width / 2)
	{
		return true;
	}
	return false;
}

void PlayScene::addDifficulty(Entity * entity)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	//With time going on, the difficulty will grow by the following variables.
	float addSpeed = visibleSize.width / 640;
	float force = (visibleSize.width / 64) * 100;

	if (timeCounter->getfCurTime() > 5 && timeCounter->getfCurTime()<15)
	{
		entity->setSpeed(3 * addSpeed);
		this->getScene()->getPhysicsWorld()->setGravity(Vec2(0.0f, -(force + 1000)));
	}
	else if (timeCounter->getfCurTime() >= 15 && timeCounter->getfCurTime() < 40)
	{
		entity->setSpeed(4 * addSpeed);
		this->getScene()->getPhysicsWorld()->setGravity(Vec2(0.0f, -(force + 2000)));
	}
	else if (timeCounter->getfCurTime() >= 40 && timeCounter->getfCurTime() < 80)
	{
		entity->setSpeed(5 * addSpeed);
		this->getScene()->getPhysicsWorld()->setGravity(Vec2(0.0f, -(force + 3000)));
	}
	else if (timeCounter->getfCurTime() >= 80 && timeCounter->getfCurTime() < 150)
	{
		entity->setSpeed(6 * addSpeed);
		this->getScene()->getPhysicsWorld()->setGravity(Vec2(0.0f, -(force + 4000)));
	}
	else if (timeCounter->getfCurTime() >= 150)
	{
		entity->setSpeed(7 * addSpeed);
		this->getScene()->getPhysicsWorld()->setGravity(Vec2(0.0f, -(force + 5000)));
	}
}

void PlayScene::randomFly(Entity * top, Entity * mid, Entity * bot, int randFrequency)
{
	//To judge whether this column of the entities get to the start position
	//Start position is at the right side out of the screen
	if (top->isStart())			
	{
		//To produce a random number to judge which entity to show.
		int randNum = rand() % randFrequency;
		switch (randNum)
		{
		case 0:
			top->show();
			mid->hide();
			bot->hide();
			break;
		case 1:
			mid->show();
			top->hide();
			bot->hide();
			break;
		case 2:
			bot->show();
			mid->hide();
			top->hide();
			break;
		default:
			bot->hide();
			mid->hide();
			top->hide();
			break;
		}
	}
}

void PlayScene::GameOver()
{
	//When you lose (drop or come across monsters), the game will be over.
	//And when the game is over, this function will deliver some important factors used for 
	//calculating your final score to the GameOverScene.
	auto gameOverLayer = GameoverScene::createWithScore(Time,BeatMonsterAmount,GainGoldAmount);
	auto gameOverScene = Scene::create();
	gameOverScene->addChild(gameOverLayer);

	//auto tsc = TransitionFade::create(1.0f, gameOverScene);
	Director::getInstance()->pushScene(gameOverScene);
}

void PlayScene::calculateScore(float delta)
{
	Time = timeCounter->getfCurTime();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Node* n = this->getChildByTag(TimeTag);
	if (n) {
		this->removeChildByTag(TimeTag);
	}
	if (this->Time < 0)
		this->Time = 0;
	
	cocos2d::__String* time = cocos2d::__String::createWithFormat("%.2f", Time);
	auto lblTime = Label::createWithTTF(time->getCString(), "fonts/Marker Felt.ttf", visibleSize.width / 20);
	lblTime->setPosition(Vec2(visibleSize.width / 1.5, visibleSize.height - lblTime->getContentSize().height / 2));
	lblTime->setColor(Color3B(0, 0, 0));
	this->addChild(lblTime, 2, TimeTag);

	if (Time - InvincibleStartTime >= 5)
	{
		heroInvincible->setVisible(false);
		hero->ExitInvincible();
		InvincibleStartTime = 10000000;
	}
}
