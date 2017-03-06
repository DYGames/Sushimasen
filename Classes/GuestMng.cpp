#include "stdafx.h"

GuestMng* GuestMng::_guestmnginstance = NULL;
GuestMng* GuestMng::getInstance(Node* parent)
{
	if (!_guestmnginstance)
		_guestmnginstance = new GuestMng(parent);
	return _guestmnginstance;
}

GuestMng::GuestMng(Node* parent)
{
	_randtime = 5;
	_ctime = 0;

	for (int i = 0; i < N_HALL; i++)
	{
		_hallGuest[i] = GameMng::getInstance()->getGuest(i);
	}

	for (int i = 0; i < N_WAIT; i++)
	{
		_waitGuest[i] = GameMng::getInstance()->getGuest(i + N_HALL);

	}
	_guestLayer = Layer::create();
	_guestLayer->setGlobalZOrder(ZGUEST);
	parent->addChild(_guestLayer);
}

void GuestMng::init(Node* parent)
{
	if (parent != NULL)
	{
		_guestLayer = Layer::create();
		_guestLayer->setGlobalZOrder(ZGUEST);
		parent->addChild(_guestLayer);
	}

	for (int i = 0; i < N_HALL; i++)
	{
		if (_hallGuest[i] != NULL)
		{
			Guest* guest = Guest::create(_hallGuest[i], true, i);
			guest->setTag(i + 400);
			if (i < 4)
				guest->setZOrder(3);
			else
				guest->setZOrder(1);
			_guestLayer->addChild(guest);

		}
	}

	for (int i = 0; i < N_WAIT; i++)
	{
		if (_waitGuest[i] != NULL)
		{
			Guest* guest = Guest::create(_waitGuest[i], false,i);
			guest->setTag(i + 500);
			_guestLayer->addChild(guest);
		}
	}

	Sprite* desk = Sprite::create("hall/desk.png");
	desk->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2, 225));
	_guestLayer->addChild(desk, 4);

	Sprite* desk1 = Sprite::create("hall/desk.png");
	desk1->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2, 535));
	_guestLayer->addChild(desk1, 2);

	setRightPosition();
}

void GuestMng::addGuest()
{
	int rands = rand() % TYPEGUEST + 1;

	for (int i = 0; i < N_HALL; i++)
	{
		if (_hallGuest[i] == NULL)
		{
			_hallGuest[i] = rands;
			setRightPosition();
			updateGameMng();
			return;
		}
	}

	for (int i = 0; i < N_WAIT; i++)
	{
		if (_waitGuest[i] == NULL)
		{
			GameData->setRecipe(i, 0);
			_waitGuest[i] = rands;
			setRightPosition();
			updateGameMng();
			return;
		}
	}
}

void GuestMng::setHallGuest(int iter,int value)
{
	_hallGuest[iter] = value;
}

void GuestMng::update(float dt, bool addchild)
{
	if (Popup::getInstance()->getPopupOpen())
		return;

	_ctime += dt;

	for (int i = 0; i < N_HALL; i++)
	{
		if (_hallGuest[i] == 0)
		{
			if (_waitGuest[0] != 0)
			{
				_hallGuest[i] = _waitGuest[0];
				_waitGuest[0] = 0;
				if (addchild)
				{
					moveForwardWait();
					setRightPosition();
				}
				updateGameMng();
				return;
			}
		}
		if (_hallGuest[i] != 0)
		{
			GameData->setGuestLimit(i, GameData->getGuestLimit(i) - 1);
			if (OpenMenu::getInstance()->getCurScene())
			{
				auto guest = static_cast<Guest*>(_guestLayer->getChildByTag(i + 400));
				if (guest == NULL)
				{
					_hallGuest[i] = 0;
					continue;
				}
				guest->addwait(i);
			}
		}
	}
	
	if (_ctime >= _randtime)
	{
		_ctime = 0;
	
		int rands = rand() % TYPEGUEST + 1;

		for (int i = 0; i < N_HALL; i++)
		{
			if (_hallGuest[i] == NULL)
			{
				_hallGuest[i] = rands;
				if (addchild)
					setRightPosition();
				updateGameMng();
				return;
			}
		}
		
		for (int i = 0; i < N_WAIT; i++)
		{
			if (_waitGuest[i] == NULL)
			{
				_waitGuest[i] = rands;
				if (addchild)
					setRightPosition();
				updateGameMng();
				return;
			}
		}
	}
}

void GuestMng::moveForwardWait()
{
	for (int i = 1; i < N_WAIT; i++)
	{
		if (_waitGuest[i - 1] == NULL)
		{
			_waitGuest[i - 1] = _waitGuest[i];
			_waitGuest[i] = 0;
		}
	}

	_guestLayer->removeAllChildrenWithCleanup(true);

	init(NULL);
}

void GuestMng::setRightPosition()
{
	for (int i = 0; i < N_HALL; i++)
	{
		if (_hallGuest[i] != NULL)
		{
			if (_guestLayer->getChildByTag(i + 400) == NULL)
			{
				Guest* guest = Guest::create(_hallGuest[i], true,i);
				guest->setTag(i + 400);
				_guestLayer->addChild(guest);

				if (i < 4)
					guest->setZOrder(3);
				else
					guest->setZOrder(1);
			}

			_guestLayer->getChildByTag(i + 400)->setPosition(Vec2(80 + (180 * i), 410));

			if (i >= N_HALL / 2)
				_guestLayer->getChildByTag(i + 400)->setPosition(Vec2(80 + (180 * (i - N_HALL / 2)), 710));
		}
	}

	for (int i = 0; i < N_WAIT; i++)
	{
		if (_waitGuest[i] != NULL)
		{
			if (_guestLayer->getChildByTag(i + 500) == NULL)
			{
				Guest* guest = Guest::create(_waitGuest[i], false, i);
				guest->setTag(i + 500);
				_guestLayer->addChild(guest);
			}
			_guestLayer->getChildByTag(i + 500)->setPosition(Vec2(390 - (120 * i), 970));
		}
	}
}

void GuestMng::touchBegan(Touch* touch)
{
	Vec2 location = touch->getLocation();

	int price;

	if (CANTTOUCH){}
	else
		return;

	for (int i = 0; i <= N_MATERIAL; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			Node* sushi = _guestLayer->getParent()->getChildByName(String::createWithFormat("%d %d", i, j)->getCString());
			if (sushi != NULL)
			{
				sushi->setColor(Color3B::WHITE);
				if (sushi->getBoundingBox().containsPoint(location))
				{
					sushi->setColor(Color3B::BLUE);
					GameData->setonSushi(j);
				}
			}
		}
	}
	for (int i = 0; i < N_HALL; i++)
	{
		if (_hallGuest[i] != NULL && _guestLayer->getChildrenCount() != 0)
		{
			if (_guestLayer->getChildByTag(i + 400)->getBoundingBox().containsPoint(location) && GameData->getRecipe(i) == GameData->getSushi(GameData->getonSushi()))
			{
				switch (GameData->getRecipe(i))
				{
				case 21:
					price = 800;
					break;
				case 5:
				case 6:
				case 12:
				case 13:
				case 14:
				case 17:
				case 18:
				case 19:
				case 20:
					price = 1000;
					break;
				case 2:
				case 4:
				case 10:
				case 11:
					price = 1100;
					break;
				case 3:
				case 9:
					price = 1200;
					break;
				case 15:
				case 16:
					price = 1300;
					break;

				}
				Status::getInstance()->addMoney(price);
				GameData->setRecipe(i, 0);
				GameData->setIncome(GameData->getIncome() + price);
				for (int j = 0; j < 5; j++)
				{
					if (GameData->getonSushi() == j)
					{
						GameData->setSushi(j, 0);
					}
				}
				StaffMng::getInstance()->resetSushi(_guestLayer->getParent());
				static_cast<Guest*>(_guestLayer->getChildByTag(i + 400))->setEat();
				_hallGuest[i] = 0;
				return;
			}
		}
	}
}

void GuestMng::updateGameMng()
{
	for (int i = 0; i < N_HALL; i++)
	{
		GameMng::getInstance()->setGuest(i, _hallGuest[i]);
	}

	for (int j = 0; j < N_WAIT; j++)
	{
		GameMng::getInstance()->setGuest(j + N_HALL, _waitGuest[j]);
	}
}

void GuestMng::clearGuest()
{
	memset(_hallGuest, 0, sizeof(_hallGuest));
	memset(_waitGuest, 0, sizeof(_waitGuest));

	if (OpenMenu::getInstance()->getCurScene())
	{
		Node* parent = _guestLayer->getParent();

		_guestLayer->removeAllChildrenWithCleanup(true);
		init(parent);
	}

	updateGameMng();
}