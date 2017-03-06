#include "stdafx.h"

Scene* Start::createScene()
{
	auto scene = Scene::create();

	auto layer = Start::create();

	scene->addChild(layer);

	return scene;
}

bool Start::init()
{
	if (!Layer::init())
		return false;

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Start::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	Sprite* back = Sprite::create("startmenu/background.png");
	back->setPosition(Director::getInstance()->getWinSize() / 2);
	this->addChild(back);

	Sprite* logo = Sprite::create("mainmenu/title_ (6).png");
	logo->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2, 1000));
	this->addChild(logo);

	Animation* anim = Animation::create();
	anim->setDelayPerUnit(0.1f);
	anim->setLoops(99);
	for (int i = 6; i <= 19; i++)
	{
		anim->addSpriteFrameWithFileName(String::createWithFormat("mainmenu/title_ (%d).png", i)->getCString());
	}
	logo->runAction(Animate::create(anim));

	MenuItemImage* newitem = MenuItemImage::create("startmenu/new_1.png", "startmenu/new_2.png", CC_CALLBACK_1(Start::menucallback, this));
	newitem->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2, 850)); 
	newitem->setTag(1);
	MenuItemImage* loaditem = MenuItemImage::create("startmenu/load_1.png", "startmenu/load_2.png", CC_CALLBACK_1(Start::menucallback, this));
	loaditem->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2, 600));
	loaditem->setTag(2);
	MenuItemImage* opitem = MenuItemImage::create("startmenu/option_1.png", "startmenu/option_2.png", CC_CALLBACK_1(Start::menucallback, this));
	opitem->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2, 350));
	opitem->setTag(3);
	MenuItemImage* exititem = MenuItemImage::create("startmenu/exit_1.png", "startmenu/exit_2.png", CC_CALLBACK_1(Start::menucallback, this));
	exititem->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2, 100));
	exititem->setTag(4);

	Menu* menu = Menu::create(newitem, loaditem, opitem, exititem, NULL);
	menu->setPosition(Vec2());
	menu->setScale(0.65f);
	this->addChild(menu);

	return true;
}

bool Start::onTouchBegan(Touch* touch, Event* unused_event)
{
	Option::getInstance()->close();

	return true;
}

void Start::menucallback(Ref* sender)
{
	bool optionclose = Option::getInstance()->getOptionOpen();
	switch (((MenuItem*)sender)->getTag())
	{
	case 1:
		if (!optionclose)
		{
			GameData->reset();
			CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("main.mp3", true);
		}
	case 2:
		if (optionclose == false)
		{
			MOVESCENE(0.5f, Hall::createScene());
		}
		break;
	case 3:
		if (!optionclose)
			Option::getInstance()->open(_parent);
		break; 
	case 4:
		if (!optionclose)
			Director::getInstance()->end();
		break;
	}
}