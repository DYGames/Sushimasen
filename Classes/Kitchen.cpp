#include "stdafx.h"
Scene* Kitchen::createScene()
{
	auto scene = Scene::create();

	auto layer = Kitchen::create();

	scene->addChild(layer);

	return scene;
}

bool Kitchen::init()
{
	if (!Layer::init())
		return false;

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Kitchen::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(Kitchen::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(Kitchen::onTouchEnded, this);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	Sprite* moveButton = Sprite::create("move.png");
	moveButton->setPosition(Vec2(700, 750));
	moveButton->setTag(MOVEBTAG);
	moveButton->setZOrder(ZMOVEBUT);
	moveButton->setFlippedX(!KITCHEN);
	this->addChild(moveButton);

	_cookSushi = new CookSushi;
	_cookSushi->init(this);

	OpenMenu::getInstance()->init(this, KITCHEN);
	StaffMng::getInstance()->resetSushi(this);
	StaffMng::getInstance()->kitReset(this);
	StaffMng::getInstance()->resetCount(this);
	Status::getInstance()->init(this);

	if (GameMng::getInstance()->getFast())
		schedule(schedule_selector(Kitchen::updateStatus), 0.01f);
	else
		schedule(schedule_selector(Kitchen::updateStatus), 1.f);
	schedule(schedule_selector(Kitchen::getInput));
	return true;
}

void Kitchen::getInput(float dt)
{
	Cheat::getInstance()->getInput();
}

void Kitchen::updateStatus(float dt)
{
	int hour = GameMng::getInstance()->getHour();
	
	if (!GameMng::getInstance()->getFast() && hour >= 9)
		GuestMng::getInstance(NULL)->update(dt, NULL);

	Status::getInstance()->addMinute();

	StaffMng::getInstance()->update(dt);

	_cookSushi->update(dt);

	if (hour == 22 && GameMng::getInstance()->getFast() == false)
	{
		GameMng::getInstance()->setFast(true);

		unschedule(schedule_selector(Kitchen::updateStatus));

		schedule(schedule_selector(Kitchen::updateStatus), 0.01f);
	}

	if (hour == 9 && GameMng::getInstance()->getFast() == true)
	{
		GameMng::getInstance()->setFast(false);

		unschedule(schedule_selector(Kitchen::updateStatus));

		schedule(schedule_selector(Kitchen::updateStatus), 1.f);
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

bool Kitchen::onTouchBegan(Touch* touch, Event* unused_event)
{
	OpenMenu::getInstance()->touchBegan(touch);

	if (CANTTOUCH)
	{
		_cookSushi->TouchBegan(touch);

		if (this->getChildByTag(MOVEBTAG)->getBoundingBox().containsPoint(touch->getLocation()))
		{
			MOVESCENE(0.15f, Hall::createScene())
		}
	}

	Recipe::getInstance()->touchBegan(touch);

	Inventory::getInstance()->touchBegan(touch);

	Popup::getInstance()->touchBegan(touch);

	Store::getInstance()->touchBegan(touch);

	return true;
}

void Kitchen::onTouchMoved(Touch* touch, Event* unused_event)
{
	Recipe::getInstance()->touchMoved(touch);

	OpenMenu::getInstance()->touchMoved(touch);

	Inventory::getInstance()->touchMoved(touch);

	Popup::getInstance()->touchMoved(touch);

	Store::getInstance()->touchMoved(touch);

	_cookSushi->TouchMoved(touch);
}

void Kitchen::onTouchEnded(Touch* touch, Event* unused_event)
{
	Recipe::getInstance()->touchEnded(touch);

	OpenMenu::getInstance()->touchEnded(touch);

	Inventory::getInstance()->touchEnded(touch);

	Popup::getInstance()->touchEnded(touch);
	
	Store::getInstance()->touchEnded(touch);

	_cookSushi->TouchEnded(touch);
}
