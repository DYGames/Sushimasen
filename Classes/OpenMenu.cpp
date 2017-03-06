#include "stdafx.h"
OpenMenu::OpenMenu()
{
	_menuTag = 8;
	_isMenuOpen = false;
	_isMenuSelect = false;
}

OpenMenu* OpenMenu::_openMenuInstance = NULL;
OpenMenu* OpenMenu::getInstance()
{
	if (!_openMenuInstance)
		_openMenuInstance = new OpenMenu;
	return _openMenuInstance;
}

void OpenMenu::initRect()
{
	for (int i = 0; i < 7; i++)
	{
		_openMenuRect[i] = Rect(116, 1173 - (85 * (i + 1)), 308, 76);
	}
}

void OpenMenu::openMenuTouch(Vec2 location)
{
	_menuTag = 8;
	for (int i = 0; i < 7; i++)
	{
		if (_openMenuRect[i].containsPoint(location))
			_menuTag = i;
	}
	if (_menuTag == 8)
		return;
	_isMenuSelect = true;
	Rect tempRect = _openMenuRect[_menuTag];

	Sprite* temp = Sprite::create("openmenu/openmenuselect.png");
	temp->setPosition(Vec2(tempRect.getMinX(), tempRect.getMaxY()));
	temp->setAnchorPoint(Vec2(0, 1));
	temp->setName("MenuSelect");
	temp->setOpacity(100);
	temp->setGlobalZOrder(ZOPENMENU);
	_parent->addChild(temp);
}

void OpenMenu::runOpenAction(bool onoff)
{
	_openMenu->setVisible(true);

	Animation* ani = Animation::create();
	ani->setDelayPerUnit(0.03f);

	if (onoff)
	{
		for (int i = 1; i < 10; i++)
		{
			ani->addSpriteFrameWithFileName(String::createWithFormat("openmenu/status_ani/status_ (%d).png", i)->getCString());
		}
		_openMenu->runAction(Animate::create(ani));
	}
	else
	{
		for (int i = 9; i > 0; i--)
		{
			ani->addSpriteFrameWithFileName(String::createWithFormat("openmenu/status_ani/status_ (%d).png", i)->getCString());
		}
		_openMenu->runAction(Sequence::create(Animate::create(ani), Hide::create(), NULL));
	}
}

void OpenMenu::init(Node* parent, bool scene)
{
	_parent = parent;
	_scene = scene;
	_isMenuOpen = false;
	_openMenuLayer = Layer::create();
	_openMenuLayer->setZOrder(ZOPENMENU);
	_parent->addChild(_openMenuLayer);

	_openMenu = Sprite::create("openmenu/status_ani/status_ (1).png");
	_openMenu->setPosition(Vec2(270, 900));
	//_openMenu->setAnchorPoint(Vec2(0, 1));
	_openMenu->setZOrder(ZOPENMENU);
	_openMenu->setVisible(_isMenuOpen);
	_openMenuLayer->addChild(_openMenu);

	initRect();
}
void OpenMenu::menuCallback()
{
	if (!Popup::getInstance()->getPopupOpen())
	{
		bool inv = Inventory::getInstance()->getisInvOn();
		bool staffmng = StaffMng::getInstance()->getIsStaffMenuOn();
		bool store = Store::getInstance()->getStoreOpen();
		bool recipe = Recipe::getInstance()->isRecipeOn();
		bool option = Option::getInstance()->getOptionOpen();
		if (inv || staffmng || _isMenuOpen || store || recipe || option)
		{
			if (inv)
				Inventory::getInstance()->close();
			if (staffmng)
				StaffMng::getInstance()->closeStaffMenu();
			if (store)
				Store::getInstance()->closeStore(false);
			if (recipe)
				Recipe::getInstance()->close();
			if (option)
				Option::getInstance()->close();
			if (_isMenuOpen)
			{
				_isMenuOpen = false;
				_openMenu->setVisible(_isMenuOpen);
				runOpenAction(_isMenuOpen);
			}
		}
		else
		{
			onoffMenu();
		}
	}
}

void OpenMenu::onoffMenu()
{
	if (_isMenuOpen == false)
		_isMenuOpen = true;
	else if (_isMenuOpen == true)
		_isMenuOpen = false;
	_openMenu->setVisible(_isMenuOpen);
	runOpenAction(_isMenuOpen);
}

void OpenMenu::close()
{
	if (_isMenuOpen)
	{
		_isMenuOpen = false;
		_openMenu->setVisible(_isMenuOpen);
	}
}

void OpenMenu::touchBegan(Touch* touch)
{
	Vec2 location = touch->getLocation();
	if (_parent->getChildByName("status")->getBoundingBox().containsPoint(location))
	{
		menuCallback();
	}
	if (_isMenuOpen && (CANTTOUCH))
		openMenuTouch(location);
}

void OpenMenu::touchMoved(Touch* touch){}

void OpenMenu::touchEnded(Touch* touch)
{
	Vec2 location = touch->getLocation();
	if (_isMenuSelect)
	{
		for (int i = 0; i < 7; i++)
		{
			if (_openMenuRect[i].containsPoint(location))
			{
				if (_menuTag == i)
				{
					switch (_menuTag)
					{
					case MINIGAME:
						if (Status::getInstance()->subtractMoney(5000))
						{
							MOVESCENE(0.15f, MiniGame::createScene());
						}
						break;
					case STORE:
						Store::getInstance()->openStore(_parent);
						break;
					case RECIPE:
						Recipe::getInstance()->open(_parent);
						break;
					case INVENTORY:
						Inventory::getInstance()->open(_parent);
						break;
					case OPTION:
						Option::getInstance()->open(_parent);
						break;
					case STAFF:
						StaffMng::getInstance()->openStaffPopup(_parent);
						break;
					case EXIT:
						Director::getInstance()->end();
						break;
					}
					_menuTag = 8;
				}
			}
		}
		_parent->removeChildByName("MenuSelect");
		_isMenuSelect = false;
	}
}