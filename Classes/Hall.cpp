#include "stdafx.h"

Scene* Hall::createScene()
{
	auto scene = Scene::create();

	auto layer = Hall::create();

	scene->addChild(layer);

	return scene;
}

bool Hall::init()
{
	if (!Layer::init())
		return false;

	Size winSize = Director::getInstance()->getWinSize();

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Hall::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(Hall::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(Hall::onTouchEnded, this);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	
	Sprite* hallback = Sprite::create();

	switch (GameData->getSeason())
	{
	case SPRING:
		hallback->setTexture("hall/hall_spring.png");
		break;
	case SUMMER:
		hallback->setTexture("hall/hall_summer.png");
		break;
	case FALL:
		hallback->setTexture("hall/hall_fall.png");
		break;
	case WINTER:
		hallback->setTexture("hall/hall_winter.png");
		break;
	}

	hallback->setPosition(Vec2());
	hallback->setAnchorPoint(Vec2());
	hallback->setName("hallback");
	this->addChild(hallback);

	Sprite* moveButton = Sprite::create("move.png");
	moveButton->setPosition(Vec2(20, 750));
	moveButton->setTag(MOVEBTAG);
	moveButton->setFlippedX(!HALL);
	this->addChild(moveButton);
	
	OpenMenu::getInstance()->init(this, HALL);
	Status::getInstance()->init(this);
	GuestMng::getInstance(this)->init(this);
	StaffMng::getInstance()->resetSushi(this);

	if (GameMng::getInstance()->getFast())
		schedule(schedule_selector(Hall::updateStatus), 0.01f);
	else
		schedule(schedule_selector(Hall::updateStatus), 1.f);

	schedule(schedule_selector(Hall::getInput));

	return true;
}

void Hall::getInput(float dt)
{
	Cheat::getInstance()->getInput();
}


void Hall::updateStatus(float dt)
{
	int hour = GameMng::getInstance()->getHour();

	int minute = GameMng::getInstance()->getMinute();

	if (!GameMng::getInstance()->getFast() && hour >= 9)
		GuestMng::getInstance(this)->update(dt, true);

	Status::getInstance()->addMinute();

	StaffMng::getInstance()->update(dt);

	if (hour == 22 && minute == 0 && GameMng::getInstance()->getFast() == false)
	{
		GameMng::getInstance()->setFast(true);

		unschedule(schedule_selector(Hall::updateStatus));

		schedule(schedule_selector(Hall::updateStatus), 0.01f);
	}

	if (hour == 9 && minute == 0 && GameMng::getInstance()->getFast() == true)
	{
		GameMng::getInstance()->setFast(false);

		unschedule(schedule_selector(Hall::updateStatus));

		schedule(schedule_selector(Hall::updateStatus), 1.f);
	}

	if (GameData->getFast())
	{
		unschedule(schedule_selector(Hall::updateStatus));

		schedule(schedule_selector(Hall::updateStatus), 0.01f);
	}
	else
	{
		unschedule(schedule_selector(Hall::updateStatus));

		schedule(schedule_selector(Hall::updateStatus), 1.f);
	}
}

bool Hall::onTouchBegan(Touch* touch, Event* unused_event)
{
	OpenMenu::getInstance()->touchBegan(touch);

	if (CANTTOUCH)
	{
		if (this->getChildByTag(MOVEBTAG)->getBoundingBox().containsPoint(touch->getLocation()))
		{
			MOVESCENE(0.15f, Kitchen::createScene())
		}

		if (touch->getLocation().x < 675 && touch->getLocation().x > 500 && touch->getLocation().y < 1060 && touch->getLocation().y > 775)
		{
			//MOVESCENE(0.15f, MiniOutScene::createScene());
		}
	}

	Recipe::getInstance()->touchBegan(touch);

	Inventory::getInstance()->touchBegan(touch);

	Popup::getInstance()->touchBegan(touch);

	Store::getInstance()->touchBegan(touch);

	GuestMng::getInstance(this)->touchBegan(touch);

	return true;
}

void Hall::onTouchMoved(Touch* touch, Event* unused_event)
{
	Recipe::getInstance()->touchMoved(touch);

	OpenMenu::getInstance()->touchMoved(touch);

	Store::getInstance()->touchMoved(touch);

	Inventory::getInstance()->touchMoved(touch);

	Popup::getInstance()->touchMoved(touch);
}

void Hall::onTouchEnded(Touch* touch, Event* unused_event)
{
	Recipe::getInstance()->touchEnded(touch);

	OpenMenu::getInstance()->touchEnded(touch);

	Store::getInstance()->touchEnded(touch);

	Inventory::getInstance()->touchEnded(touch);

	Popup::getInstance()->touchEnded(touch);
}