#include "stdafx.h"

StaffMng* StaffMng::_staffinstance = NULL;
StaffMng* StaffMng::getInstance()
{
	if (!_staffinstance)
		_staffinstance = new StaffMng;
	return _staffinstance;
}

StaffMng::StaffMng()
{
	_menustaffLayer = NULL;

	for (int i = 0; i < 3; i++)
	{
		_staffPos[i] = GameMng::getInstance()->getStaffInfo(i);
	}

	memset(_staffarr, 0, sizeof(_staffarr));

	//첫번째인덱스는 자리수가아니고 번째 직원이라는뜻
	_staffInfo[0][0] = 0;
	_staffInfo[0][1] = -2;
	_staffInfo[0][2] = 5000;
	_staffInfo[0][3] = 2500;
	_staffInfo[1][0] = 0;
	_staffInfo[1][1] = 0;
	_staffInfo[1][2] = 10000;
	_staffInfo[1][3] = 5000;
	_staffInfo[2][0] = 0;
	_staffInfo[2][1] = 3;
	_staffInfo[2][2] = 100000;
	_staffInfo[2][3] = 25000;
}

void StaffMng::resetSushi(Node* parent)
{
	_parent = parent;

	for (int j = 0; j < N_MATERIAL; j++)
	{
		for (int i = 0; i < 5; i++)
		{
			if (parent->getChildByName(String::createWithFormat("%d %d", j, i)->getCString()) != NULL)
			{
				parent->getChildByName(String::createWithFormat("%d %d", j, i)->getCString())->removeFromParentAndCleanup(true);
			}
		}
	}
	for (int i = 0; i < 5; i++)
	{
		Sprite* sushi = Sprite::create(String::createWithFormat("sushi/Ingame_Hall_Order_Example_%d.png", GameData->getSushi(i))->getCString());
		if (sushi != NULL)
		{
			sushi->setPosition(Vec2(60 + i * 150, 60));
			sushi->setScale(0.75f);
			sushi->setName(String::createWithFormat("%d %d", GameData->getSushi(i), i)->getCString());
			parent->addChild(sushi);
		}
	}
}

void StaffMng::resetCount(Node* parent)
{
	for (int i = 0; i < 3; i++)
	{
		if (_staffPos[i] != 0)
			_staffarr[i]->setWork(GameData->getOnWorkRecipe(i), GameData->getOnWorkRemainTime(i));
	}
}

void StaffMng::update(float dt)
{
	for (int i = 0; i < 3; i++)
	{
		if (!OpenMenu::getInstance()->getCurScene())
		{
			Staff* stff = static_cast<Staff*>(_parent->getChildByTag(i + 850));
			if (stff != NULL)
			{
				if (!stff->subtractTime())
				{
					int it;
					for (int j = 0; j < 5; j++)
					{
						if (GameData->getSushi(j) == 0)
						{
							it = j;
							break;
						}
					}
					Sprite* sushi = Sprite::create(String::createWithFormat("sushi/Ingame_Hall_Order_Example_%d.png", stff->getRecipe())->getCString());
					sushi->setScale(0.75f);
					sushi->setPosition(Vec2(60 + it * 150, 60));
					sushi->setName(String::createWithFormat("%d %d", stff->getRecipe(), it)->getCString());
					_parent->addChild(sushi);
					GameData->setSushi(it, stff->getRecipe());
					//초밥 완성.
				}
			}
		}
		else
		{
			if (GameData->getOnWorkRemainTime(i) > 0)
				GameData->setOnWorkRemainTime(i, GameData->getOnWorkRemainTime(i) - 1);
		}
	}
}

int StaffMng::getPay()
{
	int pay = 0;

	for (int i = 0; i < 3; i++)
	{
		if (_staffPos[i])
		{
			pay += _staffInfo[_staffPos[i] - 1][3];
		}
	}

	return pay;
}

void StaffMng::init(Node* parent)
{
	for (int i = 0; i < 3;i++)
	{
		if (_staffarr[i] != NULL)
		{
			parent->addChild(_staffarr[i]);
		}
	}
}

void StaffMng::kitReset(Node* parent)
{
	for (int i = 0; i < 3; i++)
	{
		if (_parent != NULL)
		{
			_parent->removeChildByTag(i + 850);
			if (_staffPos[i] != 0)
			{
				Staff* staff = Staff::create(_staffPos[i], i);
				staff->setPosition(Vec2(140 + i * 230, 1010));
				staff->setTag(i + 850);
				_staffarr[i] = staff;
				if (!OpenMenu::getInstance()->getCurScene())
					_parent->addChild(staff);
			}
		}
	}

	for (int i = 0; i < 3; i++)
	{
		if (_staffPos[i] != 0)
		{
			if (_parent != NULL)
			{
				Staff* staff = (Staff*)_parent->getChildByTag(i + 850);
				if (staff != NULL)
					staff->setWork(GameData->getOnWorkRecipe(i), GameData->getOnWorkRemainTime(i));
			}
		}
	}
}

void StaffMng::openStaffPopup(Node* parent)
{
	OpenMenu::getInstance()->close();

	_isOpen = true;

	_menustaffLayer = Layer::create();
	_menustaffLayer->setZOrder(ZINVENTORY);
	parent->addChild(_menustaffLayer);

	Sprite* staffmenuback = Sprite::create("staff/staffpopupback.png");
	staffmenuback->setPosition(Vec2(360, 640));
	_menustaffLayer->addChild(staffmenuback);

	for (int i = 0; i < 3; i++)
	{
		if (_staffPos[i] == 0)
		{
			Sprite* spr = Sprite::create("staff/empty.png");
			spr->setPosition(Vec2(50, (3 - i) * 260 + (250)));
			spr->setAnchorPoint(Vec2(0, 1));
			_menustaffLayer->addChild(spr);

			MenuItemImage* employ = MenuItemImage::create("staff/employb.png", "staff/employb2.png", CC_CALLBACK_1(StaffMng::menuCallback, this));
			employ->setTag(300 + i);
			employ->setPosition(Vec2(600, (3 - i) * 260 + (40)));

			Menu* menu = Menu::create(employ, NULL);
			menu->setPosition(Vec2());
			_menustaffLayer->addChild(menu);
		}
		else
		{
			Sprite* spr = Sprite::create(String::createWithFormat("staff/staffimg%d.png", _staffPos[i])->getCString());
			spr->setPosition(Vec2(50, (3 - i) * 260 + (250)));
			spr->setAnchorPoint(Vec2(0, 1));
			_menustaffLayer->addChild(spr);

			MenuItemImage* menude = MenuItemImage::create("staff/deploy.png", "staff/deploy2.png", CC_CALLBACK_1(StaffMng::menuCallback, this));
			menude->setTag(200 + i);
			menude->setPosition(Vec2(600, (3 - i) * 260 + (40)));

			Menu* menu = Menu::create(menude, NULL);
			menu->setPosition(Vec2());
			_menustaffLayer->addChild(menu, 2);

			Label* information = Label::createWithTTF("", GAME_FONT, 40);
			information->setPosition(Vec2(500, (3 - i) * 260 + (160)));
			information->setColor(Color3B::BLACK);
			if (i == 0)
				GameData->setStringAtAll(information, String::create("초급 요리사\n요리 시간 단축 : -2\n월급 : 2500")->getCString());
			else if (i == 1)
				GameData->setStringAtAll(information, String::create("중급 요리사\n요리 시간 단축 : 0\n월급 : 5000")->getCString());
			else if (i == 2)
				GameData->setStringAtAll(information, String::create("고급 요리사\n요리 시간 단축 : 3\n월급 : 25000")->getCString());

			_menustaffLayer->addChild(information);
		}
	}
}

void StaffMng::stopWorkAtAll()
{
	for (int i = 0; i < 3; i++)
	{
		if (_staffarr[i] != NULL)
		{
			_staffarr[i]->stopWork();
		}
	}
}

void StaffMng::openEmployMenu()
{
	_menustaffLayer->removeAllChildrenWithCleanup(true);

	Sprite* staffmenuback = Sprite::create("staff/staffpopupback2.png");
	staffmenuback->setPosition(Vec2(360, 640));
	_menustaffLayer->addChild(staffmenuback);

	MenuItemImage* leftButton = MenuItemImage::create("staff/left.png", "staff/left.png", CC_CALLBACK_1(StaffMng::menuCallback, this));
	leftButton->setPosition(Vec2(215, 850));
	leftButton->setTag(1);

	MenuItemImage* rightButton = MenuItemImage::create("staff/right.png", "staff/right.png", CC_CALLBACK_1(StaffMng::menuCallback, this));
	rightButton->setPosition(Vec2(515, 850));
	rightButton->setTag(2);

	MenuItemImage* employButton = MenuItemImage::create("staff/employ.png", "staff/employ2.png", CC_CALLBACK_1(StaffMng::menuCallback, this));
	employButton->setPosition(Vec2(280, 430));
	employButton->setTag(3);

	MenuItemImage* cancleButton = MenuItemImage::create("staff/cancle.png", "staff/cancle2.png", CC_CALLBACK_1(StaffMng::menuCallback, this));
	cancleButton->setPosition(Vec2(440, 430));
	cancleButton->setTag(4);

	Menu* menu = Menu::create(leftButton, rightButton, employButton, cancleButton, NULL);
	menu->setPosition(Vec2());
	_menustaffLayer->addChild(menu);

	_staffName = Label::createWithTTF("", GAME_FONT, 35);
	_staffName->setPosition(Vec2(360, 690));
	_staffName->setColor(Color3B::BLACK);
	_menustaffLayer->addChild(_staffName);

	_staffHP = Label::createWithTTF("", GAME_FONT, 35);
	_staffHP->setPosition(Vec2(360, 690));
	_staffHP->setColor(Color3B::BLACK);
	_menustaffLayer->addChild(_staffHP);

	_staffCook = Label::createWithTTF("", GAME_FONT, 35);
	_staffCook->setPosition(Vec2(450, 565));
	_staffCook->setColor(Color3B::BLACK);
	_menustaffLayer->addChild(_staffCook);

	_staffDeposit = Label::createWithTTF("", GAME_FONT, 35);
	_staffDeposit->setPosition(Vec2(300, 510));
	_staffDeposit->setColor(Color3B::BLACK);
	_menustaffLayer->addChild(_staffDeposit);

	_staffPay = Label::createWithTTF("", GAME_FONT, 35);
	_staffPay->setPosition(Vec2(510, 510));
	_staffPay->setColor(Color3B::BLACK);
	_menustaffLayer->addChild(_staffPay);

	_staffPic = Sprite::create();
	_staffPic->setPosition(Vec2(365, 850));
	_menustaffLayer->addChild(_staffPic);

	refresh();
}

void StaffMng::closeStaffMenu()
{
	_isOpen = false;
	_menustaffLayer->removeFromParentAndCleanup(true);
}

void StaffMng::refresh()
{
	_staffPic->setTexture(String::createWithFormat("staff/staff%d.png", _curStaff, _curStaff, _curStaff)->getCString());
	switch (_curStaff)
	{
	case 1:
		GameData->setStringAtAll(_staffName, String::createWithFormat("초급 요리사")->getCString());
		break;
	case 2:		
		GameData->setStringAtAll(_staffName, String::createWithFormat("중급 요리사")->getCString());
		break;
	case 3:
		GameData->setStringAtAll(_staffName, String::createWithFormat("고급 요리사")->getCString());
		break;
	}
	GameData->setStringAtAll(_staffCook, String::createWithFormat("%d", _staffInfo[_curStaff - 1][1])->getCString());
	GameData->setStringAtAll(_staffDeposit, String::createWithFormat("%d", _staffInfo[_curStaff - 1][2])->getCString());
	GameData->setStringAtAll(_staffPay, String::createWithFormat("%d", _staffInfo[_curStaff - 1][3])->getCString());
}

void StaffMng::menuCallback(Ref* sender)
{
	switch (((MenuItem*)(sender))->getTag())
	{
	case 1:
		if (_curStaff > 1)
			_curStaff--;
		refresh();
		break;
	case 2:
		if (_curStaff < 3)
			_curStaff++;
		refresh();
		break;
	case 3:
		if (Status::getInstance()->subtractMoney(_staffInfo[_curStaff - 1][2]))
		{
			_staffPos[_employNum] = _curStaff;
			closeStaffMenu();
			updateGameMng();
			kitReset(_parent);
			//addStaff _curStaff
		}
		break;
	case 4:
		closeStaffMenu();
		break;

	case 100:
	case 101:
	case 102:

		break;
	case 200:
	case 201:
	case 202:
		_staffPos[((MenuItem*)(sender))->getTag() - 200] = 0;
		closeStaffMenu();
		openStaffPopup(_parent);
		updateGameMng();
		kitReset(_parent);
		_parent->removeChildByTag(((((MenuItem*)(sender))->getTag() - 200) + 850));
		break;
	case 300:
	case 301:
	case 302:
		_employNum = ((MenuItem*)(sender))->getTag() - 300;
		openEmployMenu();
		break;
	}
}

void StaffMng::updateGameMng()
{
	for (int i = 0; i < 3; i++)
	{
		GameMng::getInstance()->setStaffInfo(i, _staffPos[i]);
	}
}

void StaffMng::close()
{
	for (int i = 0; i < 3; i++)
	{
		if (_staffarr[i] != NULL)
			_staffarr[i]->removeAllChildrenWithCleanup(true);
	}
}

void StaffMng::setNormalSpr(Staff* stff)
{
	int type = stff->getType();

	stff->stopAllActions();
	stff->setTexture(String::createWithFormat("staff/Ingame_Kitchen_Cooker_%d/Ingame_Kitchen_Cooker_%d_Wait/Ingame_Kitchen_Cooker_%d_Wait.png", type, type, type)->getCString());
}

void StaffMng::setWorkSpr(Staff* stff)
{
	int type = stff->getType();

	stff->stopAllActions();
	Animation* animation = Animation::create();
	animation->setDelayPerUnit(0.35);
	animation->setLoops(9999);
	animation->addSpriteFrameWithFileName(String::createWithFormat("staff/Ingame_Kitchen_Cooker_%d/Ingame_Kitchen_Cooker_%d_Work/Ingame_Kitchen_Cooker_%d_Work_1.png", type, type, type)->getCString());
	animation->addSpriteFrameWithFileName(String::createWithFormat("staff/Ingame_Kitchen_Cooker_%d/Ingame_Kitchen_Cooker_%d_Work/Ingame_Kitchen_Cooker_%d_Work_2.png", type, type, type)->getCString());
	Animate* ani = Animate::create(animation);
	stff->runAction(ani);
}