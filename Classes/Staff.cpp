#include "stdafx.h"

Staff* Staff::create(int type, int pos)
{
	Staff* staff = new Staff;
	if (staff && staff->initWithFile(String::createWithFormat("staff/Ingame_Kitchen_Cooker_%d/Ingame_Kitchen_Cooker_%d_Wait/Ingame_Kitchen_Cooker_%d_Wait.png", type, type, type)->getCString()))
	{
		if (!(type >= 1 && type <= 3))
			type = 1;

		staff->_type = type;
		staff->_pos = pos;

		if (GameData->getOnWorkRemainTime(staff->_pos) != -1)
			StaffMng::getInstance()->setWorkSpr(staff);

		staff->autorelease();

		return staff;
	}
	CC_SAFE_DELETE(staff);
	return nullptr;
}

void Staff::setWork(int recipe, int remaintime)
{
	if (recipe == 99)
		return;

	this->removeAllChildrenWithCleanup(true);

	_recipe = recipe;

	_remaintime = GameData->getOnWorkRemainTime(_pos);

	if (_remaintime == -1)
	{
		switch (recipe)
		{
		case 5:
		case 6:
		case 12:
		case 13:
		case 17:
		case 18:
		case 19:
		case 20:
		case 21:
			_remaintime = 5;
			break;
		case 2:
		case 4:
		case 10:
		case 11:
		case 14:
			_remaintime = 6;
			break;
		case 3:
		case 9:
			_remaintime = 7;
			break;
		case 15:
		case 16:
			_remaintime = 8;
			break;
		default:
			return;
		}
		switch (_type)
		{
		case 0:
			_remaintime += 2;
			break;
		case 1:
			break;
		case 2:
			_remaintime -= 3;
			break;
		}
		StaffMng::getInstance()->setWorkSpr(this);

	}

	GameData->setOnWorkRemainTime(_pos, _remaintime);
	GameData->setOnWorkRecipe(_pos, _recipe);

	//minute : not yet

	Label* timelabel = Label::createWithTTF(String::createWithFormat("0 : %d", _remaintime)->getCString(), GAME_FONT, FONT_SIZE_NUM);
	if (_remaintime < 10)
		timelabel->setString(String::createWithFormat("0 : 0%d", _remaintime)->getCString());
	timelabel->setColor(Color3B::BLACK);
	timelabel->setPosition(Vec2(83, 180));
	timelabel->setTag(250 + _pos);
	timelabel->setZOrder(2);
	this->addChild(timelabel);
}

void Staff::stopWork()
{
	_remaintime = -1;

	_recipe = 0;

	this->removeAllChildrenWithCleanup(true);
}

bool Staff::subtractTime()
{
	_remaintime = GameData->getOnWorkRemainTime(_pos);
	_recipe = GameData->getOnWorkRecipe(_pos);

	if (_remaintime == -1)
		return true;

	if (_remaintime == 0)
	{
		_remaintime = -1;
		GameData->setOnWorkRemainTime(_pos, _remaintime);
		GameData->setOnWorkRecipe(_pos, -1);

		StaffMng::getInstance()->setNormalSpr(this);
		return false;
	}

	_remaintime--;

	if ((Label*)this->getChildByTag(250 + _pos) != NULL)
		((Label*)this->getChildByTag(250 + _pos))->setString(String::createWithFormat("0 : %d", _remaintime)->getCString());

	if (_remaintime < 10)
	{
		if ((Label*)this->getChildByTag(250 + _pos) != NULL)
			((Label*)this->getChildByTag(250 + _pos))->setString(String::createWithFormat("0 : 0%d", _remaintime)->getCString());
	}

	if (_remaintime == 0)
	{
		_remaintime = -1;

		GameData->setOnWorkRecipe(_pos, -1);
		GameData->setOnWorkRemainTime(_pos, _remaintime);
		StaffMng::getInstance()->setNormalSpr(this);
		return false;
	}

	GameData->setOnWorkRemainTime(_pos, _remaintime);

	return true;
}