#pragma once

#include "stdafx.h"

enum E_MATERIAL
	:int
{
	RICE = 1,					//밥.
	LAVER,						//김.
	SALMON,						//연어.
	PAGRUSMAJOR,				//참돔.
	FLATFISH,					//넙치.
	CHUBMACKEREL,				//고등어.
	HORSEMACKEREL,				//전갱어.
	KONOSIRUSPUNCTATUS,			//전어.
	SARDINOPSMELANOSTICTUS,		//정어리.
	UNAGI,						//장어.
	MATSUBARA,					//우럭.
	TUNA,						//참치.
	SHRIMP,						//새우.
	CUTTLEFISH,					//오징어.
	OCTOPUS,					//문어.
	ECHINOIDEA,					//성게.
	ABALONE,					//전복.
	SCHRENCK,					//피조개.
	EGGCOCKLE,					//새조개.
	SCALLOP,					//가리비.
	RODING,						//대합.
	HENCLAM,					//개량조개.
	EGG,						//계란.
	CUCUMBER,					//오이.
	FRIEDTOFU,					//유부.
};

#define GameData GameMng::getInstance()

class GameMng
{
private:
	int _NitemArray[N_ITEM];
	int _NmaterialArray[N_MATERIAL];
	bool _recipeOnArray[N_MATERIAL];
	int _guestlimit[N_HALL];

	int _NstaffInfoArray[3];
	int _NguestArray[N_HALL + N_WAIT];

	int _recipeArray[N_HALL];

	int _onWorkArray[3][2];

	int _sushiArray[5];

	int _season;

	int _year;
	int _month;
	int _week;

	int _hour;
	int _minute;

	bool _music;
	bool _effect;

	float _money;

	bool _isFast;

	int _willPayMat = 0;
	int _willPayItem = 0;
	int _willPayEmploy = 0;
	
	int _income = 0;

	int _onSushi;

	bool _minioverpower;
public:
	GameMng();

	int getGuestLimit(int iter);
	void setGuestLimit(int iter, int value);

	bool getMiniOverPower();
	void setMiniOverPower(bool power);

	int getItem(int iter);
	void setItem(int iter, int value);

	int getMaterial(int iter);
	void setMaterial(int iter, int value);

	int getSeason();
	void setSeason(int season);

	int getYear();
	void setYear(int year);

	int getMonth();
	void setMonth(int month);

	int getWeek();
	void setWeek(int week);

	int getHour();
	void setHour(int hour);

	int getMinute();
	void setMinute(int minute);

	bool getMusic();
	void setMusic(bool music);

	bool getEffect();
	void setEffect(bool effect);

	float getMoney();
	void setMoney(float money);

	int getStaffInfo(int iter);
	void setStaffInfo(int iter, int value);

	int getGuest(int iter);
	void setGuest(int iter, int value);

	bool getFast();
	void setFast(bool fast);

	int getWillPay();
	void setWillPay(int pay);
	void resetWillPay();

	int getonSushi();
	void setonSushi(int material);

	int getSushi(int iter);
	void setSushi(int iter, int value);

	int getOnWorkRemainTime(int iter);
	void setOnWorkRemainTime(int iter, int value);

	int getOnWorkRecipe(int iter);
	void setOnWorkRecipe(int iter, int value);

	int getRecipe(int iter);
	void setRecipe(int iter, int value);

	int getIncome();
	void setIncome(int income);

	bool getRecipeOn(int iter);
	void setRecipeOn(int iter, bool value);

	void setStringAtAll(Label* label, const char* sstring);

	void reset();

	static GameMng* _gameInstance;

	static GameMng* getInstance();
	static void removeInstance()
	{
		if (_gameInstance != nullptr)
		{
			delete _gameInstance;
			_gameInstance = nullptr;
		}
	}
};