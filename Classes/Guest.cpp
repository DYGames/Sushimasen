#include "stdafx.h"

Guest* Guest::create(int type, bool recipe, int pos)
{
	Guest* guest = new Guest;
	if (guest && guest->initWithFile(String::createWithFormat("guest/guest_%d/order/order_1.png", type)->getCString()))
	{
		if (!(type >= 1 && type <= TYPEGUEST))
			type = 1;

		int irecipe = rand() % 21;
		while ((irecipe < 9 && irecipe > 6) || irecipe < 2 || irecipe > 21 || !GameData->getRecipeOn(irecipe))
			irecipe = rand() % 21;

		if (GameData->getRecipe(pos) != 0)
			irecipe = GameData->getRecipe(pos);

		guest->_type = type;
		guest->_wantRecipe = irecipe;
		guest->autorelease();
		guest->_pos = pos;

		if (recipe)
		{
			guest->setOrder();
			Sprite* tooltip = Sprite::create("guest/tooltip.png");
			tooltip->setPosition(Vec2(90, 220));
			guest->addChild(tooltip);

			Sprite*  sushi = Sprite::create(String::createWithFormat("sushi/Ingame_Hall_Order_Example_%d.png", irecipe)->getCString());
			sushi->setPosition(tooltip->getPosition());
			sushi->setScale(0.5f);
			guest->addChild(sushi);

			GameData->setRecipe(pos, irecipe);
		}
		else
		{
			guest->setTexture(String::createWithFormat("guest/wait/wait (%d).png", type)->getCString());
		}
		return guest;
	}
	CC_SAFE_DELETE(guest);
	return nullptr;
}

bool Guest::addwait(int iter)
{
	if (GameData->getGuestLimit(iter) <= 0)
	{
		this->setAngry();
		GameData->setGuestLimit(iter, GUESTLIMIT);
		return true;
	}
	return false;
}

void Guest::setOrder()
{
	this->stopAllActions();
	Animation* animation = Animation::create();
	animation->addSpriteFrameWithFileName(String::createWithFormat("guest/guest_%d/order/order_1.png", _type)->getCString());
	animation->addSpriteFrameWithFileName(String::createWithFormat("guest/guest_%d/order/order_2.png", _type)->getCString());
	animation->setDelayPerUnit(0.5f);
	animation->setLoops(9999);
	this->runAction(Animate::create(animation));
}

void Guest::setEat()
{
	this->stopAllActions();
	Animation* animation = Animation::create();
	animation->addSpriteFrameWithFileName(String::createWithFormat("guest/guest_%d/eat/eat_1.png", _type)->getCString());
	animation->addSpriteFrameWithFileName(String::createWithFormat("guest/guest_%d/eat/eat_2.png", _type)->getCString());
	animation->setDelayPerUnit(0.5f);
	animation->setLoops(3);
	this->runAction(Sequence::create(Animate::create(animation), RemoveSelf::create(), NULL));
}

void Guest::setWait()
{
	this->stopAllActions();
	this->setTexture(String::createWithFormat("guest/guest_%d/wait/wait.png", _type)->getCString());
}

void Guest::setAngry()
{
	this->stopAllActions();
	Animation* animation = Animation::create();
	animation->addSpriteFrameWithFileName(String::createWithFormat("guest/guest_%d/angry/angry_1.png", _type)->getCString());
	animation->addSpriteFrameWithFileName(String::createWithFormat("guest/guest_%d/angry/angry_2.png", _type)->getCString());
	animation->setDelayPerUnit(0.5f);
	animation->setLoops(3);
	this->runAction(Sequence::create(Animate::create(animation), RemoveSelf::create(), CallFunc::create(CC_CALLBACK_0(Guest::setGuestNull, this)), NULL));
}

void Guest::setGuestNull()
{
	GuestMng::getInstance(NULL)->setHallGuest(_pos, 0);
}