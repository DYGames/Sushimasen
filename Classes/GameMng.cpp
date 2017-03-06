#include "stdafx.h"

GameMng* GameMng::_gameInstance = 0;
GameMng* GameMng::getInstance()
{
	if (!_gameInstance)
		_gameInstance = new GameMng;
	return _gameInstance;
}

GameMng::GameMng()
{
	memset(_NitemArray, NULL, sizeof(_NitemArray));
	memset(_NitemArray, NULL, sizeof(_NitemArray));
}

int GameMng::getItem(int iter)
{
	return _NitemArray[iter];
}

void GameMng::setItem(int iter, int value)
{
	_NitemArray[iter] = value;

	UserDefault::getInstance()->setIntegerForKey(String::createWithFormat("item_%d", iter)->getCString(), value);
}

int GameMng::getMaterial(int iter)
{
	return _NmaterialArray[iter];
}

void GameMng::setMaterial(int iter, int value)
{
	_NmaterialArray[iter] = value;

	UserDefault::getInstance()->setIntegerForKey(String::createWithFormat("material_%d", iter)->getCString(), value);
}

int GameMng::getSeason()
{
	return _season;
}

void GameMng::setSeason(int season)
{
	_season = season;
	UserDefault::getInstance()->setIntegerForKey("Season", _season);
}

int GameMng::getYear()
{
	return _year;
}

void GameMng::setYear(int year)
{
	_year = year;
	UserDefault::getInstance()->setIntegerForKey("Year", _year);
}

int GameMng::getMonth()
{
	return _month;
}

void GameMng::setMonth(int month)
{
	_month = month;
	UserDefault::getInstance()->setIntegerForKey("Month", _month);
}

int GameMng::getWeek()
{
	return _week;
}

void GameMng::setWeek(int week)
{
	_week = week;
	UserDefault::getInstance()->setIntegerForKey("Week", _week);
}

int GameMng::getHour()
{
	return _hour;
}

void GameMng::setHour(int hour)
{
	_hour = hour;

	UserDefault::getInstance()->setIntegerForKey("Hour", _hour);
}

int GameMng::getMinute()
{
	return _minute;
}

void GameMng::setMinute(int minute)
{
	_minute = minute;
	UserDefault::getInstance()->setIntegerForKey("Minute", _minute);
}

bool GameMng::getMusic()
{
	return _music;
}

void GameMng::setMusic(bool music)
{
	_music = music;

	UserDefault::getInstance()->setBoolForKey("Music", _music);
}

bool GameMng::getEffect()
{
	return _effect;
}

void GameMng::setEffect(bool effect)
{
	_effect = effect;

	UserDefault::getInstance()->setBoolForKey("Effect", _effect);
}

float GameMng::getMoney()
{
	return _money;
}

void GameMng::setMoney(float money)
{
	_money = money;

	UserDefault::getInstance()->setFloatForKey("Money", _money);
}

int GameMng::getStaffInfo(int iter)
{
	return _NstaffInfoArray[iter];
}

void GameMng::setStaffInfo(int iter, int value)
{
	_NstaffInfoArray[iter] = value;

	UserDefault::getInstance()->setIntegerForKey(String::createWithFormat("staff_%d", iter)->getCString(), value);
}

int GameMng::getGuest(int iter)
{
	return _NguestArray[iter];
}

void GameMng::setGuest(int iter, int value)
{
	_NguestArray[iter] = value;

	UserDefault::getInstance()->setIntegerForKey(String::createWithFormat("guest_%d", iter)->getCString(), value);
}

bool GameMng::getFast()
{
	return _isFast;
}

void GameMng::setFast(bool fast)
{
	_isFast = fast;

	UserDefault::getInstance()->setBoolForKey("isFast", fast);
}

int GameMng::getWillPay()
{
	return _willPayMat;
}

void GameMng::resetWillPay()
{
	_willPayMat = 0;

	UserDefault::getInstance()->setIntegerForKey("willPay", _willPayMat);
}

void GameMng::setWillPay(int pay)
{
	_willPayMat += pay;

	UserDefault::getInstance()->setIntegerForKey("willPay", _willPayMat);
}

int GameMng::getonSushi()
{
	return _onSushi;
}

void GameMng::setonSushi(int material)
{
	_onSushi = material;
}

int GameMng::getSushi(int iter)
{
	return _sushiArray[iter];
}

void GameMng::setSushi(int iter, int value)
{
	_sushiArray[iter] = value;

	UserDefault::getInstance()->setIntegerForKey(String::createWithFormat("sushi_%d", iter)->getCString(), value);
}

int GameMng::getOnWorkRemainTime(int iter)
{
	return _onWorkArray[iter][0];
}

void GameMng::setOnWorkRemainTime(int iter, int value)
{
	_onWorkArray[iter][0] = value;

	UserDefault::getInstance()->setIntegerForKey(String::createWithFormat("onworkremaintime_%d", iter)->getCString(), value);
}

int GameMng::getOnWorkRecipe(int iter)
{
	return _onWorkArray[iter][1];
}

void GameMng::setOnWorkRecipe(int iter, int value)
{
	_onWorkArray[iter][1] = value;

	UserDefault::getInstance()->setIntegerForKey(String::createWithFormat("onworkrecipe_%d", iter)->getCString(), value);
}

int GameMng::getRecipe(int iter)
{
	return _recipeArray[iter];
}

void GameMng::setRecipe(int iter, int  value)
{
	_recipeArray[iter] = value;

	UserDefault::getInstance()->setIntegerForKey(String::createWithFormat("recipe_%d", iter)->getCString(), value);
}

int GameMng::getIncome()
{
	return _income;
}

void GameMng::setIncome(int income)
{
	_income = income;

	UserDefault::getInstance()->setIntegerForKey("Income", _income);
}

bool GameMng::getRecipeOn(int iter)
{
	return _recipeOnArray[iter];
}

void GameMng::setRecipeOn(int iter, bool value)
{
	_recipeOnArray[iter] = value;

	UserDefault::getInstance()->setBoolForKey(String::createWithFormat("recipeon_%d", iter)->getCString(), value);
}

bool GameMng::getMiniOverPower()
{
	return _minioverpower;
}

void GameMng::setMiniOverPower(bool power)
{
	_minioverpower = power;

	UserDefault::getInstance()->setBoolForKey("MiniPower", power);
}

int GameMng::getGuestLimit(int iter)
{
	return _guestlimit[iter];
}

void GameMng::setGuestLimit(int iter, int value)
{
	_guestlimit[iter] = value;

	UserDefault::getInstance()->setIntegerForKey(String::createWithFormat("guestlimit_%d", iter)->getCString(), value);
}

void GameMng::setStringAtAll(Label* label, const char* sstring)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	WCHAR wstr[256];
	char str[256];
	sprintf(str, "%s", sstring);
	MultiByteToWideChar(CP_ACP, 0, str, -1, wstr, sizeof(wstr));
	memset(str, 0, sizeof(str));
	WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, sizeof(str), 0, 0);
	label->setString(str);
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	label->setString(sstring);
#endif
}

void GameMng::reset()
{
	GameData->setSeason(SPRING);
	GameData->setYear(1);
	GameData->setMonth(3);
	GameData->setWeek(1);
	GameData->setHour(8);
	GameData->setMinute(50);
	GameData->setMusic(true);
	GameData->setEffect(true);
	GameData->setMoney(100000);
	GameData->setFast(false);
	GameData->resetWillPay();
	GameData->setIncome(0);
	GameData->setMiniOverPower(false);

	for (int i = 0; i < N_HALL; i++)
	{
		GameData->setGuestLimit(i, GUESTLIMIT);
	}
	for (int i = 0; i < N_ITEM; i++)
	{
		GameData->setItem(i, 0);
	}

	for (int i = 0; i < N_MATERIAL; i++)
	{
		GameData->setMaterial(i, 0);
	}

	for (int i = 0; i < 3; i++)
	{
		GameData->setStaffInfo(i, 0);
	}

	for (int i = 0; i < N_HALL + N_WAIT; i++)
	{
		GameData->setGuest(i, 0);
	}

	for (int i = 0; i < 5; i++)
	{
		GameData->setSushi(i, 0);
	}

	for (int i = 0; i < 3; i++)
	{
		GameData->setOnWorkRemainTime(i, -1);
	}

	for (int i = 0; i < 3; i++)
	{
		GameData->setOnWorkRecipe(i, -1);
	}

	for (int i = 0; i < N_HALL; i++)
	{
		GameData->setRecipe(i, 0);
	}

	for (int i = 0; i < N_MATERIAL; i++)
	{
		GameData->setRecipeOn(i, false);
		if (i == 2 || i == 3)
			GameData->setRecipeOn(i, true);
	}
}