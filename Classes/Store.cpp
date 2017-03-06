#include "stdafx.h"

Store* Store::_storeinstance = NULL;
Store* Store::getInstance()
{
	if (!_storeinstance)
		_storeinstance = new Store;
	return _storeinstance;
}

void Store::reset()
{
	_scrollLayer->removeAllChildrenWithCleanup(true);
	memset(_buyArray, 0, sizeof(_buyArray));
	memset(_itembuyArray, 0, sizeof(_itembuyArray));
	_storeLayer->removeChildByTag(4253);

	
	if (_mode)
	{
		_matMenu = MenuItemImage::create("store/button1.png", "store/button2.png", CC_CALLBACK_1(Store::menuCallBack, this));
		_matMenu->setPosition(Vec2(220, 650));
		_matMenu->setTag(800);
		for (int i = 0; i < N_ITEM; i++)
		{
			MenuItemImage* left = MenuItemImage::create("popup/leftbutton.png", "popup/leftbutton.png", CC_CALLBACK_1(Store::menuCallBack, this));
			left->setTag(1100 + i);
			left->setPosition(Vec2(90 + (230 * i), 450));

			MenuItemImage* right = MenuItemImage::create("popup/rightbutton.png", "popup/rightbutton.png", CC_CALLBACK_1(Store::menuCallBack, this));
			right->setTag(1200 + i);
			right->setPosition(Vec2(220 + (230 * i), 450));

			Sprite* fish = Sprite::create(String::createWithFormat("inventory/item/item_ (%d).png", i)->getCString());

			fish->setTag(i + 100);
			fish->setPosition(Vec2(155 + (230 * i), left->getPositionY() + 50));
			_scrollLayer->addChild(fish);

			Sprite* numback = Sprite::create("popup/numback.png");
			numback->setPosition(Vec2(155 + (230 * i), 450));
			_scrollLayer->addChild(numback);

			if (i > N_ITEM / 2 - 1)
			{
				left->setPosition(Vec2(90 + (230 * (i - (N_ITEM / 2))), left->getPositionY() - 140));
				right->setPosition(Vec2(220 + (230 * (i - (N_ITEM / 2))), right->getPositionY() - 140));
				numback->setPosition(Vec2(155 + (230 * (i - (N_ITEM / 2))), numback->getPositionY() - 140));
				fish->setPosition(Vec2(155 + (230 * (i - (N_ITEM / 2))), left->getPositionY() + 50));
			}

			Label* num = Label::createWithTTF("0", GAME_FONT, 30);
			num->setPosition(numback->getPosition());
			num->setColor(Color3B::BLACK);
			num->setTag(300 + i);
			_scrollLayer->addChild(num);

			Label* price = Label::createWithTTF(String::createWithFormat("%d", _priceItem[i])->getCString(), GAME_FONT, 20);
			price->setColor(Color3B::BLACK);
			price->setPosition(Vec2(fish->getPositionX(), fish->getPositionY() - 70));
			_scrollLayer->addChild(price);

			Menu* menu = Menu::create(left, right, NULL);
			menu->setPosition(Vec2());
			_scrollLayer->addChild(menu);

		}
	}
	else
	{
		_matMenu = MenuItemImage::create("store/button2.png", "store/button1.png", CC_CALLBACK_1(Store::menuCallBack, this));
		_matMenu->setPosition(Vec2(220, 650));
		_matMenu->setTag(800);
		for (int i = 0; i < N_BUYITEM; i++)
		{
			MenuItemImage* left = MenuItemImage::create("popup/leftbutton.png", "popup/leftbutton.png", CC_CALLBACK_1(Store::menuCallBack, this));
			left->setTag(100 + i);
			left->setPosition(Vec2(90 + (230 * i), 450));

			MenuItemImage* right = MenuItemImage::create("popup/rightbutton.png", "popup/rightbutton.png", CC_CALLBACK_1(Store::menuCallBack, this));
			right->setTag(200 + i);
			right->setPosition(Vec2(220 + (230 * i), 450));

			Sprite* fish = Sprite::create(String::createWithFormat("kitchen/material/material_ (%d).png", i)->getCString());

			fish->setTag(i);
			fish->setPosition(Vec2(155 + (230 * i), left->getPositionY() + 50));
			_scrollLayer->addChild(fish);

			Sprite* numback = Sprite::create("popup/numback.png");
			numback->setPosition(Vec2(155 + (230 * i), 450));
			_scrollLayer->addChild(numback);

			if (i > N_BUYITEM / 2 - 1)
			{
				left->setPosition(Vec2(90 + (230 * (i - (N_BUYITEM / 2))), left->getPositionY() - 140));
				right->setPosition(Vec2(220 + (230 * (i - (N_BUYITEM / 2))), right->getPositionY() - 140));
				numback->setPosition(Vec2(155 + (230 * (i - (N_BUYITEM / 2))), numback->getPositionY() - 140));
				fish->setPosition(Vec2(155 + (230 * (i - (N_BUYITEM / 2))), left->getPositionY() + 50));
			}

			Label* num = Label::createWithTTF("0", GAME_FONT, 30);
			num->setPosition(numback->getPosition());
			num->setColor(Color3B::BLACK);
			num->setTag(300 + i);
			_scrollLayer->addChild(num);

			Label* price = Label::createWithTTF(String::createWithFormat("%d", _priceItem[i])->getCString(), GAME_FONT, 20);
			price->setColor(Color3B::BLACK);
			price->setPosition(Vec2(fish->getPositionX(), fish->getPositionY() - 70));
			_scrollLayer->addChild(price);

			Menu* menu = Menu::create(left, right, NULL);
			menu->setPosition(Vec2());
			_scrollLayer->addChild(menu);
		}
	}

	_buyMenu = MenuItemImage::create("store/buymenu1.png", "store/buymenu2.png", CC_CALLBACK_1(Store::menuCallBack, this));
	_buyMenu->setPosition(Vec2(570, 650));
	_buyMenu->setTag(802);
	Menu* menu = Menu::create(_matMenu, _buyMenu, NULL);
	menu->setPosition(Vec2());
	menu->setTag(4253);
	_storeLayer->addChild(menu);
}

void Store::menuCallBack(Ref* sender)
{
	int tag = ((MenuItem*)sender)->getTag();
	switch (tag)
	{
	case 800://mat
		_scrollLayer->setPositionX(0);

		if (_mode)
			_mode = false;
		else
			_mode = true;
		reset();
		break;
	case 802://buy
		closeStore(true);
		break;
	default:
		if (tag >= 100 && tag < 200)
		{
			if (_buyArray[tag - 100] > 0)
			{
				_buyArray[tag - 100] -= 5;
			}
		}
		if (tag >= 200 && tag < 300)
		{
			_buyArray[tag - 200] += 5;
		}

		if (tag >= 1100 && tag < 1200)
		{
			if (_itembuyArray[tag - 1100] > 0)
			{
				_itembuyArray[tag - 1100] -= 1;
			}
		}
		if (tag >= 1200 && tag < 1300)
		{
			_itembuyArray[tag - 1200] += 1;
		}
		setNumLabel();
		break;
	}
}

void Store::setNumLabel()
{
	if (_mode)
	{
		for (int i = 0; i < N_ITEM; i++)
		{
			((Label*)_scrollLayer->getChildByTag(300 + i))->setString(String::createWithFormat("%d", _itembuyArray[i])->getCString());
		}
	}
	else
	{
		for (int i = 0; i < N_BUYITEM; i++)
		{
			((Label*)_scrollLayer->getChildByTag(300 + i))->setString(String::createWithFormat("%d", _buyArray[i])->getCString());
		}
	}
}

void Store::touchBegan(Touch* touch)
{
	Vec2 location = touch->getLocation();
	if (_isStoreOpen)
	{
		if (_scrollBack->getBoundingBox().containsPoint(location))
		{
			_move = true;
		}

		_touchPoint = location;
	}

}

void Store::touchMoved(Touch* touch)
{
	if (_isStoreOpen)
	{
		float location = _scrollLayer->getPosition().x;

		location += touch->getDelta().x;

		if (_mode)
		{
			if (location < -STOREITEMXLIMIT)
				location = -STOREITEMXLIMIT;
		}

		if (!_mode)
		{
			if (location < -STOREMATXLIMIT)
				location = -STOREMATXLIMIT;
		}

		if (location > 0)
			location = 0;

		if (_move)
		{
			_scrollLayer->setPositionX(location);
		}

	}
}

void Store::touchEnded(Touch* touch)
{
	if (_isStoreOpen)
	{
		_move = false;

		Vec2 itemTempPoint = _touchPoint - (_scrollLayer->getPosition() - _originItemLayerPoint);
		if (_touchPoint.x + 40 > touch->getLocation().x &&
			_touchPoint.x - 40 < touch->getLocation().x &&
			_touchPoint.y + 40 > touch->getLocation().y &&
			_touchPoint.y - 40 < touch->getLocation().y)
		{
			if (_mode)
			{
				for (int i = 0; i < N_ITEM; i++)
				{
					if (_scrollLayer->getChildByTag(i + 100)->getBoundingBox().containsPoint(itemTempPoint))
					{
						setInformString(i + 100);
						_spotItem->setTexture(String::createWithFormat("inventory/item/item_ (%d).png", i)->getCString());
					}
				}
			}
			else
			{
				for (int i = 0; i < N_MATERIAL; i++)
				{
					if (_scrollLayer->getChildByTag(i)->getBoundingBox().containsPoint(itemTempPoint))
					{
						setInformString(i);
						_spotItem->setTexture(String::createWithFormat("kitchen/materialspot/material (%d).png", i)->getCString());
					}
				}
			}
		}

	}
}

void Store::openStore(Node* parent)
{
	int time = GameData->getHour();

	if (time < 9 || time > 22)
		return;

	_parent = parent;

	_isStoreOpen = true;

	_mode = false;

	OpenMenu::getInstance()->close();

	memset(_buyArray, 0, sizeof(_buyArray));

	string str;
	char* result;

	str = FileUtils::getInstance()->getStringFromFile("pricedata.txt");
	result = strtok((char*)str.c_str(), "\r\n");
	for (int i = 0; i < N_MATERIAL; i++)
	{
		sscanf(result, "%d", &_priceItem[i]);

		_priceItem[i] += EXPITEM;

		result = strtok(NULL, "\r\n");
	}

	Size winSize = Director::getInstance()->getWinSize();

	_storeLayer = Layer::create();
	_storeLayer->setZOrder(ZINVENTORY);
	_parent->addChild(_storeLayer);

	_scrollLayer = Layer::create();
	_scrollLayer->setZOrder(ZINVENTORY - 1);
	_parent->addChild(_scrollLayer);

	_scrollBack = Sprite::create("store/scrollback.png");
	_scrollBack->setAnchorPoint(Vec2());
	_scrollBack->setPosition(Vec2(25, 260));
	_parent->addChild(_scrollBack);

	_buttonback = Sprite::create("store/back.png");
	_buttonback->setPosition(winSize / 2);
	_storeLayer->addChild(_buttonback);

	reset();

	_spotItem = Sprite::create("kitchen/materialspot/material (0).png");
	_spotItem->setPosition(Vec2(100, 1030));
	_spotItem->setAnchorPoint(Vec2(0, 1));
	_storeLayer->addChild(_spotItem);

	_matMenu = MenuItemImage::create("store/button2.png", "store/button1.png", CC_CALLBACK_1(Store::menuCallBack, this));
	_matMenu->setPosition(Vec2(220, 650));
	_matMenu->setTag(800);
	_buyMenu = MenuItemImage::create("store/buymenu1.png", "store/buymenu2.png", CC_CALLBACK_1(Store::menuCallBack, this));
	_buyMenu->setPosition(Vec2(570, 650));
	_buyMenu->setTag(802);
	Menu* menu = Menu::create(_matMenu, _buyMenu, NULL);
	menu->setPosition(Vec2());
	menu->setTag(4253);
	_storeLayer->addChild(menu);

	_inform = Label::createWithTTF("", GAME_FONT, FONT_SIZE_INFO);
	_inform->setColor(Color3B::BLACK);
	_inform->setPosition(Vec2(200, 790));
	_storeLayer->addChild(_inform);
	setInformString(0);
}

void Store::closeStore(bool buy)
{
	if (!_isStoreOpen)
		return;

	int resultprice = 0;
	int resultprice2 = 0;
	if (buy)
	{
		if (_mode)
		{
			for (int i = 0; i < N_ITEM; i++)
			{
				int price = _itembuyArray[i] * _priceItem[i];
				int cmoney = GameMng::getInstance()->getMoney();

				if (cmoney < price)
				{
					return;//돈 부족.
				}
			}

			for (int i = 0; i < N_ITEM; i++)
			{
				int price = _itembuyArray[i] * _priceItem[i];
				int cmoney = GameMng::getInstance()->getMoney();

				GameMng::getInstance()->setItem(i, GameMng::getInstance()->getItem(i) + _itembuyArray[i]);

				resultprice2 += price;

				GameMng::getInstance()->setWillPay(price);
			}
			Status::getInstance()->subtractMoney(resultprice2);
		}
		else
		{

			for (int i = 0; i < N_BUYITEM; i++)
			{
				int price = _buyArray[i] * _priceItem[i];
				int cmoney = GameMng::getInstance()->getMoney();

				if (cmoney < price)
				{
					return;//돈 부족.
				}
			}

			for (int i = 0; i < N_BUYITEM; i++)
			{
				int price = _buyArray[i] * _priceItem[i];
				int cmoney = GameMng::getInstance()->getMoney();

				GameMng::getInstance()->setMaterial(i, GameMng::getInstance()->getMaterial(i) + _buyArray[i]);

				resultprice += price;

				GameMng::getInstance()->setWillPay(price);
			}
			Status::getInstance()->subtractMoney(resultprice);
		}
	}

	_isStoreOpen = false;

	_scrollBack->removeFromParentAndCleanup(true);
	_storeLayer->removeFromParentAndCleanup(true);
	_scrollLayer->removeFromParentAndCleanup(true);
}

void Store::setInformString(int iter)
{
	switch (iter)
	{
	case 100:
		GameData->setStringAtAll(_inform, String::createWithFormat("초밥을 바로 바로 만들어 냅니다.")->getCString());
		break;
	case 101:
		GameData->setStringAtAll(_inform, String::createWithFormat("손님이 가게에 올 확률이 2배가 됩니다.")->getCString());
		break;
	case 102:
		GameData->setStringAtAll(_inform, String::createWithFormat("영업을 즉시 종료합니다.")->getCString());
		break;
	case 103:
		GameData->setStringAtAll(_inform, String::createWithFormat("다음 영업까지 초밥을 잘못 \n전달하여도 50%의 가격을 받습니다.")->getCString());
		break;
	case 104:
		GameData->setStringAtAll(_inform, String::createWithFormat("미니게임을 통해 레시피를 \n얻을 수 있는 확률이 늘어납니다.")->getCString());
		break;
	case 105:
		GameData->setStringAtAll(_inform, String::createWithFormat("")->getCString());
		break;
	case 0:
		GameData->setStringAtAll(_inform, String::createWithFormat("초밥의 가장 기본이 되는 밥입니다.")->getCString());
		break;
	case 1:
		GameData->setStringAtAll(_inform, String::createWithFormat("밥과 함께 사용하는 김입니다.")->getCString());
		break;
	case 2:
		GameData->setStringAtAll(_inform, String::createWithFormat("초밥의 주재료가 되는 연어입니다.")->getCString());
		break;
	case 3:
		GameData->setStringAtAll(_inform, String::createWithFormat("초밥의 주재료가 되는 참돔입니다.")->getCString());
		break;
	case 4:
		GameData->setStringAtAll(_inform, String::createWithFormat("초밥의 주재료가 되는 광어입니다.")->getCString());
		break;
	case 5:
		GameData->setStringAtAll(_inform, String::createWithFormat("초밥의 주재료가 되는 고등어입니다.")->getCString());
		break;
	case 6:
		GameData->setStringAtAll(_inform, String::createWithFormat("초밥의 주재료가 되는 전갱어입니다.")->getCString());
		break;
	case 7:
		GameData->setStringAtAll(_inform, String::createWithFormat("밥과 섞어 초밥 밥을 만드는 식초입니다.")->getCString());
		break;
	case 8:
		GameData->setStringAtAll(_inform, String::createWithFormat("초밥의 부재료가 되는 와사비입니다.")->getCString());
		break;
	case 9:
		GameData->setStringAtAll(_inform, String::createWithFormat("초밥의 주재료가 되는 장어입니다.")->getCString());
		break;
	case 10:
		GameData->setStringAtAll(_inform, String::createWithFormat("초밥의 주재료가 되는 우럭입니다.")->getCString());
		break;
	case 11:
		GameData->setStringAtAll(_inform, String::createWithFormat("초밥의 주재료가 되는 참치입니다.")->getCString());
		break;
	case 12:
		GameData->setStringAtAll(_inform, String::createWithFormat("초밥의 주재료가 되는 새우입니다.")->getCString());
		break;
	case 13:
		GameData->setStringAtAll(_inform, String::createWithFormat("초밥의 주재료가 되는 오징어입니다.")->getCString());
		break;
	case 14:
		GameData->setStringAtAll(_inform, String::createWithFormat("초밥의 주재료가 되는 문어입니다.")->getCString());
		break;
	case 15:
		GameData->setStringAtAll(_inform, String::createWithFormat("초밥의 주재료가 되는 성게입니다.")->getCString());
		break;
	case 16:
		GameData->setStringAtAll(_inform, String::createWithFormat("초밥의 주재료가 되는 전복입니다.")->getCString());
		break;
	case 17:
		GameData->setStringAtAll(_inform, String::createWithFormat("초밥의 주재료가 되는 대합입니다.")->getCString());
		break;
	case 18:
		GameData->setStringAtAll(_inform, String::createWithFormat("초밥의 주재료가 되는 게입니다.")->getCString());
		break;
	case 19:
		GameData->setStringAtAll(_inform, String::createWithFormat("초밥의 주재료가 되는 새조개입니다.")->getCString());
		break;
	case 20:
		GameData->setStringAtAll(_inform, String::createWithFormat("초밥의 주재료가 되는 달걀입니다.")->getCString());
		break;
	case 21:
		GameData->setStringAtAll(_inform, String::createWithFormat("초밥의 주재료가 되는 오이입니다.")->getCString());
		break;
	}
}