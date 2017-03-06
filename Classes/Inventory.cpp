#include "stdafx.h"

Inventory* Inventory::_invInstance = NULL;

Inventory* Inventory::getInstance()
{
	if (!_invInstance)
		_invInstance = new Inventory;
	return _invInstance;
}

Inventory::Inventory()
{
	_spotItemID = 0;

	_isInvOn = false;

}

void Inventory::open(Node* parent)
{
	_parent = parent;

	_isInvOn = true;

	_invMode = true;

	OpenMenu::getInstance()->close();

	Size winSize = Director::getInstance()->getWinSize();

	_invLayer = Layer::create();
	_invLayer->setName("invLayer");
	_invLayer->setZOrder(ZINVENTORY);
	_parent->addChild(_invLayer);

	_itemLayer = Layer::create();
	_itemLayer->setName("itemLayer");
	_itemLayer->setZOrder(ZINVENTORY - 1);
	_parent->addChild(_itemLayer);
	_originItemLayer = _itemLayer->getPosition();

	_invBack = Sprite::create("inventory/invback.png");
	_invBack->setAnchorPoint(Vec2(0, 0));
	_invBack->setName("invBack");
	_invBack->setPosition(Vec2(25, 260));
	_parent->addChild(_invBack);

	_buttonBack = Sprite::create("inventory/inventory.png");
	_buttonBack->setPosition(winSize / 2);
	_invLayer->addChild(_buttonBack);

	for (int i = 0; i < N_ITEM; i++)
	{
		_item[i] = Sprite::create(String::createWithFormat("inventory/item/item_ (%d).png", i)->getCString());
		_item[i]->setTag(i + 100);
		_item[i]->setPosition(Vec2(150 + (220 * i), 500));

		if (i > N_ITEM / 2 - 1)
		{
			_item[i]->setPosition(Vec2(150 + (220 * (i - (N_ITEM / 2))), 350));
		}

		_itemLayer->addChild(_item[i]);
		_itemVector.pushBack(_item[i]);

		Label* nItem = Label::createWithTTF(String::createWithFormat("%d", GameMng::getInstance()->getItem(i))->getCString(), GAME_FONT, FONT_SIZE_NUM);
		nItem->setTag(i + 100 + 100);
		nItem->setPosition(Vec2(150, 20));
		nItem->setColor(Color3B::BLACK);
		_item[i]->addChild(nItem);
	}

	_spotItem = Sprite::create("inventory/item/spotitem_ (0).png");
	_spotItem->setPosition(Vec2(140, 1025));
	_spotItem->setAnchorPoint(Vec2(0, 1));
	_invLayer->addChild(_spotItem);

	_materialButton = MenuItemImage::create("inventory/materialbutton.png", "inventory/materialbutton1.png", CC_CALLBACK_1(Inventory::menuCallBack, this));
	_materialButton->setPosition(Vec2(540, 645));
	_materialButton->setTag(902);

	_itemButton = MenuItemImage::create("inventory/itembutton.png", "inventory/itembutton1.png", CC_CALLBACK_1(Inventory::menuCallBack, this));
	_itemButton->setPosition(Vec2(190, 650));
	_itemButton->setTag(901);

	Menu* menu = Menu::create(_materialButton, _itemButton, NULL);
	menu->setPosition(Vec2());
	_invLayer->addChild(menu);

	_info = Label::createWithTTF("", GAME_FONT, FONT_SIZE_INFO);
	_info->setColor(Color3B::BLACK);
	_info->setPosition(Vec2(200, 780));
	_invLayer->addChild(_info);
	setInfoString(0);
}

void Inventory::setInfoString(int index)
{
	switch (index)
	{
	case 0:
		GameData->setStringAtAll(_info, String::create("초밥을 바로 바로 만들어 냅니다.")->getCString());
		break;
	case 1:
		GameData->setStringAtAll(_info, String::create("손님이 가게에 올 확률이 2배가 됩니다.")->getCString());
		break;
	case 2:
		GameData->setStringAtAll(_info, String::create("영업을 즉시 종료합니다.")->getCString());
		break;
	case 3:
		GameData->setStringAtAll(_info, String::create("다음 영업까지 초밥을 잘못 \n전달하여도 50%의 가격을 받습니다.")->getCString());
		break;
	case 4:
		GameData->setStringAtAll(_info, String::create("미니게임을 통해 레시피를 \n얻을 수 있는 확률이 늘어납니다.")->getCString());
		break;
	case 5:
		GameData->setStringAtAll(_info, String::create("")->getCString());
		break;
	case 100:
		GameData->setStringAtAll(_info, String::createWithFormat("초밥의 가장 기본이 되는 밥입니다.")->getCString());
		break;
	case 101:
		GameData->setStringAtAll(_info, String::createWithFormat("밥과 함께 사용하는 김입니다.")->getCString());
		break;
	case 102:
		GameData->setStringAtAll(_info, String::createWithFormat("초밥의 주재료가 되는 연어입니다.")->getCString());
		break;
	case 103:
		GameData->setStringAtAll(_info, String::createWithFormat("초밥의 주재료가 되는 참돔입니다.")->getCString());
		break;
	case 104:
		GameData->setStringAtAll(_info, String::createWithFormat("초밥의 주재료가 되는 광어입니다.")->getCString());
		break;
	case 105:
		GameData->setStringAtAll(_info, String::createWithFormat("초밥의 주재료가 되는 고등어입니다.")->getCString());
		break;
	case 106:
		GameData->setStringAtAll(_info, String::createWithFormat("초밥의 주재료가 되는 전갱어입니다.")->getCString());
		break;
	case 107:
		GameData->setStringAtAll(_info, String::createWithFormat("밥과 섞어 초밥 밥을 만드는 식초입니다.")->getCString());
		break;
	case 108:
		GameData->setStringAtAll(_info, String::createWithFormat("초밥의 부재료가 되는 와사비입니다.")->getCString());
		break;
	case 109:
		GameData->setStringAtAll(_info, String::createWithFormat("초밥의 주재료가 되는 장어입니다.")->getCString());
		break;
	case 110:
		GameData->setStringAtAll(_info, String::createWithFormat("초밥의 주재료가 되는 우럭입니다.")->getCString());
		break;
	case 111:
		GameData->setStringAtAll(_info, String::createWithFormat("초밥의 주재료가 되는 참치입니다.")->getCString());
		break;
	case 112:
		GameData->setStringAtAll(_info, String::createWithFormat("초밥의 주재료가 되는 새우입니다.")->getCString());
		break;
	case 113:
		GameData->setStringAtAll(_info, String::createWithFormat("초밥의 주재료가 되는 오징어입니다.")->getCString());
		break;
	case 114:
		GameData->setStringAtAll(_info, String::createWithFormat("초밥의 주재료가 되는 문어입니다.")->getCString());
		break;
	case 115:
		GameData->setStringAtAll(_info, String::createWithFormat("초밥의 주재료가 되는 성게입니다.")->getCString());
		break;
	case 116:
		GameData->setStringAtAll(_info, String::createWithFormat("초밥의 주재료가 되는 전복입니다.")->getCString());
		break;
	case 117:
		GameData->setStringAtAll(_info, String::createWithFormat("초밥의 주재료가 되는 대합입니다.")->getCString());
		break;
	case 118:
		GameData->setStringAtAll(_info, String::createWithFormat("초밥의 주재료가 되는 게입니다.")->getCString());
		break;
	case 119:
		GameData->setStringAtAll(_info, String::createWithFormat("초밥의 주재료가 되는 새조개입니다.")->getCString());
		break;
	case 120:
		GameData->setStringAtAll(_info, String::createWithFormat("초밥의 주재료가 되는 달걀입니다.")->getCString());
		break;
	case 121:
		GameData->setStringAtAll(_info, String::createWithFormat("초밥의 주재료가 되는 오이입니다.")->getCString());
		break;
	default:
		GameData->setStringAtAll(_info, String::create("준비중입니다.")->getCString());
		break;
	}
}

void Inventory::close()
{
	if (_isInvOn)
	{
		_isInvOn = false;

		for (auto it : _itemVector)
		{
			it->removeFromParentAndCleanup(true);
		}

		_itemVector.clear();

		_parent->removeChildByName("invBack", true);

		_parent->removeChildByName("itemLayer", true);

		_parent->removeChildByName("invLayer", true);
	}
}

bool Inventory::getisInvOn()
{
	return _isInvOn;
}

void Inventory::touchBegan(Touch* touch)
{
	Vec2 location = touch->getLocation();
	if (getisInvOn())
	{
		if (_invBack->getBoundingBox().containsPoint(location))
		{
			_invMove = true;
		}

		_touchPoint = location;
	}
}

void Inventory::touchMoved(Touch* touch)
{
	if (getisInvOn())
	{
		float location = _itemLayer->getPosition().x;

		location += touch->getDelta().x;

		if (_invMode)
		{
			if (location < -1)
				location = -1;
		}

		if (!_invMode)
		{
			//log("inv : %f", location);
			if (location < -INVENTORYMATERIALXLIMIT)
				location = -INVENTORYMATERIALXLIMIT;
		}

		if (location > 0)
			location = 0;

		if (_invMove)
		{
			_itemLayer->setPositionX(location);
		}
		//CCLOG("%f", _itemLayer->getPosition().x);
	}
}

void Inventory::touchEnded(Touch* touch)
{
	if (getisInvOn())
	{
		_invMove = false;
		Vec2 itemTempPoint = _touchPoint - (_itemLayer->getPosition() - _originItemLayer);
		if (_touchPoint.x + 40 > touch->getLocation().x &&
			_touchPoint.x - 40 < touch->getLocation().x &&
			_touchPoint.y + 40 > touch->getLocation().y &&
			_touchPoint.y - 40 < touch->getLocation().y)
		{
			for (auto it : _itemVector)
			{
				if (it->getBoundingBox().containsPoint(itemTempPoint))
				{
					if (_invMode)
					{
						setInfoString(it->getTag() - 100);
						//GameMng::getInstance()->setItem(it->getTag() - 100, GameMng::getInstance()->getItem(it->getTag() - 100) + 1);
						_spotItem->setPosition(Vec2(140, 1025));
						_spotItem->setTexture(String::createWithFormat("inventory/item/spotitem_ (%d).png", it->getTag() - 100)->getCString());
					}
					else if (!_invMode)
					{
						setInfoString(it->getTag() - 100);
						_spotItem->setPosition(Vec2(100, 1015));
						_spotItem->setTexture(String::createWithFormat("kitchen/materialspot/material (%d).png", it->getTag() - 200)->getCString());
					}
					break;
				}
			}
		}
	}
}

void Inventory::menuCallBack(Ref* sender)
{
	switch (((MenuItem*)sender)->getTag())
	{
	case 901:
		if (_invMode == false)
		{
			_invMode = true;

			for (auto it : _itemVector)
			{
				it->removeFromParentAndCleanup(true);
			}

			_itemVector.clear();

			for (int i = 0; i < N_ITEM; i++)
			{
				_item[i] = Sprite::create(String::createWithFormat("inventory/item/item_ (%d).png", i)->getCString());
				_item[i]->setTag(i + 100);
				_item[i]->setPosition(Vec2(150 + (220 * i), 500));

				if (i > N_ITEM / 2 - 1)
				{
					_item[i]->setPosition(Vec2(150 + (220 * (i - (N_ITEM / 2))), 350));
				}

				_itemLayer->addChild(_item[i]);
				_itemVector.pushBack(_item[i]);

				Label* nItem = Label::createWithTTF(String::createWithFormat("%d", GameMng::getInstance()->getItem(i))->getCString(), GAME_FONT, FONT_SIZE_NUM);
				nItem->setTag(i + 100 + 100);
				nItem->setPosition(Vec2(150, 20));
				nItem->setColor(Color3B::BLACK);
				_item[i]->addChild(nItem);
			}
		}
		_itemLayer->setPositionX(0);
		break;
	case 902:
		if (_invMode == true)
		{
			_invMode = false;

			for (auto it : _itemVector)
			{
				it->removeFromParentAndCleanup(true);
			}

			_itemVector.clear();

			for (int i = 0; i < N_MATERIAL; i++)
			{
				_material[i] = Sprite::create(String::createWithFormat("kitchen/material/material_ (%d).png", i)->getCString());
				_material[i]->setTag(i + 200);
				_material[i]->setPosition(Vec2(150 + (220 * i), 500));

				if (i > N_MATERIAL / 2 - 1)
				{
					_material[i]->setPosition(Vec2(150 + (220 * (i - (N_MATERIAL / 2))), 350));
				}

				_itemLayer->addChild(_material[i]);
				_itemVector.pushBack(_material[i]);

				Label* nMaterial = Label::createWithTTF(String::createWithFormat("%d", GameMng::getInstance()->getMaterial(i))->getCString(), GAME_FONT, FONT_SIZE_NUM);
				nMaterial->setTag(i + 200 + 1000);
				nMaterial->setPosition(Vec2(150, 20));
				nMaterial->setColor(Color3B::BLACK);
				_material[i]->addChild(nMaterial);
			}
		}
		_itemLayer->setPositionX(0);
		break;
	}
}