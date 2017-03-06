#include "stdafx.h"

Status::Status()
{
}

Status* Status::_instance = NULL;
Status* Status::getInstance()
{
	if (!_instance)
		_instance = new Status;
	return _instance;
}

bool Status::init(Node* parent)
{
	_parent = parent;

	_popupLayer = Layer::create();
	_parent->addChild(_popupLayer);

	_statusBar = Sprite::create("status/statusbar.png");
	_statusBar->setName("status");
	switch (GameMng::getInstance()->getSeason())
	{
	case SPRING:
		_seasonPic = Sprite::create("status/season/spring.png");
		break;
	case SUMMER:
		_seasonPic = Sprite::create("status/season/summer.png");
		break;
	case FALL:
		_seasonPic = Sprite::create("status/season/fall.png");
		break;
	case WINTER:
		_seasonPic = Sprite::create("status/season/winter.png");
		break;
	}

	_seasonPic->setName("Pic");

	_statusBar->setPosition(Vec2(25, Director::getInstance()->getWinSize().height - 20));
	_seasonPic->setPosition(Vec2(25, Director::getInstance()->getWinSize().height - 20));

	_statusBar->setAnchorPoint(Vec2(0, 1));
	_seasonPic->setAnchorPoint(Vec2(0, 1));

	_parent->addChild(_seasonPic);
	_parent->addChild(_statusBar, 5);

	_date = Label::createWithTTF("", GAME_FONT, 30);
	updateDate();
	_date->setPosition(Vec2(135, 1210));
	_date->setColor(Color3B::WHITE);
	_date->setAnchorPoint(Vec2(0.f, 0.5f));

	_time = Label::createWithTTF("", GAME_FONT, 30);
	updateTime();
	_time->setColor(Color3B::WHITE);
	_time->setAnchorPoint(Vec2(0.f, 0.5f));
	_time->setPosition(Vec2(325, 1210));

	_lMoney = Label::createWithTTF("", GAME_FONT, 30);
	updateMoney();
	_lMoney->setColor(Color3B::WHITE);
	_lMoney->setAnchorPoint(Vec2(1.f, 0.5f));
	_lMoney->setPosition(Vec2(665, 1210));

	_parent->addChild(_date, 5);
	_parent->addChild(_time, 5);
	_parent->addChild(_lMoney, 5);

	return true;
}

void Status::updateDate()
{
	String* sstr;

	int year = GameMng::getInstance()->getYear();
	int month = GameMng::getInstance()->getMonth();
	int week = GameMng::getInstance()->getWeek();

	GameData->setStringAtAll(_date, String::createWithFormat("%d년 %d월 %d째 주", year, month, week)->getCString());
}

void Status::updateTime()
{
	int hour = GameMng::getInstance()->getHour();
	int minute = GameMng::getInstance()->getMinute();

	if (hour < 10)
	{
		if (minute < 10)
			GameData->setStringAtAll(_time, String::createWithFormat("0%d : 0%d", hour, minute)->getCString());
		else
			GameData->setStringAtAll(_time, String::createWithFormat("0%d : %d", hour, minute)->getCString());
	}
	else
	{
		if (minute < 10)
			GameData->setStringAtAll(_time, String::createWithFormat("%d : 0%d", hour, minute)->getCString());
		else
			GameData->setStringAtAll(_time, String::createWithFormat("%d : %d", hour, minute)->getCString());
	}
}

void Status::addSeason()
{
	int season = GameMng::getInstance()->getSeason();

	++season;

	switch (season)
	{
	case SPRING:
		_seasonPic->setTexture("status/season/spring.png");
		if (_parent->getChildByName("hallback") != NULL)
			((Sprite*)_parent->getChildByName("hallback"))->setTexture("hall/hall_spring.png");
		break;
	case SUMMER:
		_seasonPic->setTexture("status/season/summer.png");
		if (_parent->getChildByName("hallback") != NULL)
			((Sprite*)_parent->getChildByName("hallback"))->setTexture("hall/hall_summer.png");
		break;
	case FALL:
		_seasonPic->setTexture("status/season/fall.png");
		if (_parent->getChildByName("hallback") != NULL)
			((Sprite*)_parent->getChildByName("hallback"))->setTexture("hall/hall_fall.png");
		break;
	case WINTER:
		_seasonPic->setTexture("status/season/winter.png");
		if (_parent->getChildByName("hallback") != NULL)
			((Sprite*)_parent->getChildByName("hallback"))->setTexture("hall/hall_winter.png");
		break;
	}

	if (season >= 5)
	{
		season = SPRING;
	}

	GameMng::getInstance()->setSeason(season);
}

void Status::addYear()
{
	int year = GameMng::getInstance()->getYear();

	++year;

	if (year > 12)
	{
		//ending or something
	}

	GameMng::getInstance()->setYear(year);
}

void Status::addMonth()
{
	int month = GameMng::getInstance()->getMonth();

	++month;

	GameMng::getInstance()->setMonth(month);

	if (month % 3 == 0)
	{
		addSeason();
	}

	if (month >= 13)
	{
		month = 1;

		GameMng::getInstance()->setMonth(month);

		addYear();
	}
}

void Status::addWeek()
{
	int week = GameMng::getInstance()->getWeek();

	++week;

	GameMng::getInstance()->setWeek(week);

	if (week >= 5)
	{
		week = 1;

		GameMng::getInstance()->setWeek(week);

		addMonth();
	}

	updateDate();
}

void Status::addHour()
{
	int hour = GameMng::getInstance()->getHour();

	++hour;

	GameMng::getInstance()->setHour(hour);

	if (hour == 9)
	{
		openPopup();
		return;
	}

	if (hour == 22)
	{
		closePopup();
		return;
	}

	if (hour >= 24)
	{
		hour = 0;

		GameMng::getInstance()->setHour(hour);

		addWeek();
	}
}

void Status::openPopup()
{
	Popup::getInstance()->openPopup(_parent);
}

void Status::closePopup()
{
	Popup::getInstance()->closePopup(_parent);
}

void Status::addMoneyEffect(int price, bool flag)
{
	if (price == 0)
		return;
	Label* resultLabel = Label::createWithTTF("", GAME_FONT, 40);
	resultLabel->setPosition(Vec2(620, 1150));
	_popupLayer->getParent()->addChild(resultLabel, 99);
	if (flag){
		GameData->setStringAtAll(resultLabel, String::createWithFormat("+%d", price)->getCString());
		resultLabel->setColor(Color3B::GREEN);
	}
	else{
		GameData->setStringAtAll(resultLabel, String::createWithFormat("-%d", price)->getCString());
		resultLabel->setColor(Color3B::RED);
	}

	resultLabel->runAction(Sequence::create(Spawn::create(FadeOut::create(1.0f), MoveTo::create(1.0f, Vec2(620, 1230)), NULL), RemoveSelf::create(), NULL));
}

void Status::addMinute()
{
	if (!Popup::getInstance()->getPopupOpen())
	{
		int minute = GameMng::getInstance()->getMinute();

		++minute;

		for (int i = 0; i < 3; i++)
		{//getstaffremaintime and --
			//StaffMng::getInstance()->
		}

		GameMng::getInstance()->setMinute(minute);

		if (minute >= 60)
		{
			minute = 0;

			GameMng::getInstance()->setMinute(minute);

			addHour();
		}

		updateTime();
	}
}

void Status::addMoney(float money)
{
	int moneyy = GameMng::getInstance()->getMoney();

	moneyy += money;

	GameMng::getInstance()->setMoney(moneyy);

	addMoneyEffect(money, true);

	updateMoney();
}

bool Status::subtractMoney(float money)
{
	int moneyy = GameMng::getInstance()->getMoney();

	if (moneyy < money)
	{
		return false;
	}

	GameMng::getInstance()->setMoney(moneyy - money);

	addMoneyEffect(money, false);

	updateMoney();

	return true;
}

void Status::updateMoney()
{
	int moneyy = GameMng::getInstance()->getMoney();

	GameData->setStringAtAll(_lMoney, String::createWithFormat("%d", moneyy)->getCString());
}
