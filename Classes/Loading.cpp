#include "stdafx.h"

Scene* Loading::createScene()
{
	auto scene = Scene::create();

	auto layer = Loading::create();

	scene->addChild(layer);

	return scene;
}

bool Loading::init()
{
	if (!LayerColor::initWithColor(Color4B::WHITE))
		return false;

	srand(time(NULL));

	GameData->setSeason(UserDefault::getInstance()->getIntegerForKey("Season", SPRING));
	GameData->setYear(UserDefault::getInstance()->getIntegerForKey("Year", 1));
	GameData->setMonth(UserDefault::getInstance()->getIntegerForKey("Month", 3));
	GameData->setWeek(UserDefault::getInstance()->getIntegerForKey("Week", 1));
	GameData->setHour(UserDefault::getInstance()->getIntegerForKey("Hour", 8));
	GameData->setMinute(UserDefault::getInstance()->getIntegerForKey("Minute", 50));
	GameData->setMusic(UserDefault::getInstance()->getBoolForKey("Music", true));
	GameData->setEffect(UserDefault::getInstance()->getBoolForKey("Effect", true));
	GameData->setMoney(UserDefault::getInstance()->getFloatForKey("Money", 100000));
	GameData->setFast(UserDefault::getInstance()->getBoolForKey("isFast", false));
	GameData->setWillPay(UserDefault::getInstance()->getIntegerForKey("willPay", 0));
	GameData->setIncome(UserDefault::getInstance()->getIntegerForKey("Income", 0));
	GameData->setonSushi(0);
	GameData->setMiniOverPower(UserDefault::getInstance()->getBoolForKey("MiniPower", false));

	for (int i = 0; i < N_HALL; i++)
	{
		GameData->setGuestLimit(i, UserDefault::getInstance()->getIntegerForKey(String::createWithFormat("guestlimit_%d", i)->getCString(), GUESTLIMIT));
	}
	for (int i = 0; i < N_ITEM; i++)
	{
		GameData->setItem(i, UserDefault::getInstance()->getIntegerForKey(String::createWithFormat("item_%d", i)->getCString(), 0));
	}

	for (int i = 0; i < N_MATERIAL; i++)
	{
		GameData->setMaterial(i, UserDefault::getInstance()->getIntegerForKey(String::createWithFormat("material_%d", i)->getCString(), 0));
	}

	for (int i = 0; i < 3; i++)
	{
		GameData->setStaffInfo(i, UserDefault::getInstance()->getIntegerForKey(String::createWithFormat("staff_%d", i)->getCString(), 0));
	}

	for (int i = 0; i < N_HALL + N_WAIT; i++)
	{
		GameData->setGuest(i, UserDefault::getInstance()->getIntegerForKey(String::createWithFormat("guest_%d", i)->getCString(), 0));
	}

	for (int i = 0; i < 5; i++)
	{
		GameData->setSushi(i, UserDefault::getInstance()->getIntegerForKey(String::createWithFormat("sushi_%d", i)->getCString(), 0));
	}

	for (int i = 0; i < 3; i++)
	{
		GameData->setOnWorkRemainTime(i, UserDefault::getInstance()->getIntegerForKey(String::createWithFormat("onworkremaintime_%d", i)->getCString(), -1));
	}

	for (int i = 0; i < 3; i++)
	{
		GameData->setOnWorkRecipe(i, UserDefault::getInstance()->getIntegerForKey(String::createWithFormat("onworkrecipe_%d", i)->getCString(), -1));
	}

	for (int i = 0; i < N_HALL; i++)
	{
		GameData->setRecipe(i, UserDefault::getInstance()->getIntegerForKey(String::createWithFormat("recipe_%d", i)->getCString(), 0));
	}

	for (int i = 0; i < N_MATERIAL; i++)
	{
		GameData->setRecipeOn(i, UserDefault::getInstance()->getBoolForKey(String::createWithFormat("recipeon_%d", i)->getCString(), false));
		if (i == 2 || i == 3)
			GameData->setRecipeOn(i, true);
	}

	_back = Sprite::create("mainmenu/illhasen.png");
	_back->setPosition(Director::getInstance()->getWinSize() / 2);
	_back->setOpacity(0);
	this->addChild(_back);
	_back->runAction(Sequence::create(FadeTo::create(1.f, 255), FadeTo::create(1.f, 0), CallFunc::create(CC_CALLBACK_0(Loading::calledfunc, this)), FadeTo::create(1.f, 255), FadeTo::create(1.f, 0), CallFunc::create(CC_CALLBACK_0(Loading::calledfunc, this)), FadeTo::create(1.f, 255), CallFunc::create(CC_CALLBACK_0(Loading::calledfunc, this)), NULL));

	MenuItemImage* menuitem = MenuItemImage::create("mainmenu/startbutton_0.png", "mainmenu/startbutton_1.png", CC_CALLBACK_1(Loading::menucallback, this));
	menuitem->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2, 250));
	_menu = Menu::create(menuitem, NULL);
	_menu->setPosition(Vec2());
	_menu->setOpacity(0);
	this->addChild(_menu);

	_logoani = Sprite::create("mainmenu/title_ (6).png");
	_logoani->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2, 1000));
	_logoani->setOpacity(0);
	this->addChild(_logoani);

	return true;
}

void Loading::menucallback(Ref* sender)
{
	if (GameData->getMusic())
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("main.mp3", true);

	Director::getInstance()->replaceScene(TransitionFade::create(0.5f, Start::createScene()));
}

void Loading::calledfunc()
{
	if (_count == 0)
	{
		_back->setTexture("mainmenu/kgsh.png");
		_count++;
	}
	else if (_count == 1)
	{
		_back->setTexture("mainmenu/background.png");
		_menu->runAction(FadeTo::create(1.f, 255));

		Animation* ani = Animation::create();
		ani->setDelayPerUnit(0.1f);
		ani->setLoops(99);
		for (int i = 6; i <= 19; i++)
		{
			ani->addSpriteFrameWithFileName(String::createWithFormat("mainmenu/title_ (%d).png", i)->getCString());
		}

		_logoani->runAction(Sequence::create(FadeTo::create(1.f, 255), Animate::create(ani), NULL));
	}
}