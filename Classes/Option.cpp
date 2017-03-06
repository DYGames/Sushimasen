#include "stdafx.h"

Option* Option::_optinstance = NULL;
Option* Option::getInstance()
{
	if (!_optinstance)
		_optinstance = new Option;
	return _optinstance;
}

void Option::open(Node* parent)
{

	_parent = parent;

	_optionOpen = true;

	_optionLayer = Layer::create();
	_optionLayer->setZOrder(ZINVENTORY);
	_parent->addChild(_optionLayer);

	OpenMenu::getInstance()->close();

	Size winsize = Director::getInstance()->getWinSize();

	if (_mode)
	{
		_optionBack = Sprite::create("option/back.png");
		_optionBack->setPosition(winsize / 2);
		_optionLayer->addChild(_optionBack);

		if (GameData->getMusic())
			_music = MenuItemImage::create("option/musicon.png", "option/musicoff.png", CC_CALLBACK_1(Option::menucallback, this));
		else
			_music = MenuItemImage::create("option/musicoff.png", "option/musicon.png", CC_CALLBACK_1(Option::menucallback, this));

		_music->setPosition(Vec2(500, _optionBack->getPosition().y + 80));
		_music->setTag(1);

		if (GameData->getEffect())
			_effect = MenuItemImage::create("option/effecton.png", "option/effectoff.png", CC_CALLBACK_1(Option::menucallback, this));
		else
			_effect = MenuItemImage::create("option/effectoff.png", "option/effecton.png", CC_CALLBACK_1(Option::menucallback, this));

		_effect->setPosition(Vec2(300, _optionBack->getPosition().y + 80));
		_effect->setTag(2);

		_credit = MenuItemImage::create("option/creditb.png", "option/creditb.png", CC_CALLBACK_1(Option::menucallback, this));
		_credit->setPosition(Vec2(_optionBack->getPosition().x, _optionBack->getPosition().y - 100));
		_credit->setTag(3);

		Menu* menu = Menu::create(_music, _effect, _credit, NULL);
		menu->setPosition(Vec2());
		_optionLayer->addChild(menu);
	}
	else
	{
		_creditBack = Sprite::create("option/credit.png");
		_creditBack->setPosition(winsize / 2);
		_optionLayer->addChild(_creditBack);
	}
}

void Option::close()
{
	if (_optionOpen)
	{
		_optionOpen = false;

		if (!_mode)
			_mode = true;

		_optionLayer->removeAllChildrenWithCleanup(true);
	}
}

void Option::menucallback(Ref* sender)
{
	switch (((MenuItem*)sender)->getTag())
	{
	case 1:
		GameData->setMusic(GameData->getMusic() ? false : true);

		if (!GameData->getMusic())
			CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		else
			CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("main.mp3", true);


		close();
		open(_parent);
		break;
	case 2:
		GameData->setEffect(GameData->getEffect() ? false : true);
		close();
		open(_parent);
		break;
	case 3:
		close();
		if (_mode)
			_mode = false;
		open(_parent);
		break;
	case 4:
		if (!_mode)
		{
			_mode = true;
			close();
			open(_parent);
			break;
		}
		close();
		break;
	}
}