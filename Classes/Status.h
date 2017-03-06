#pragma once

#include "stdafx.h"

class Status
{
private:
	Layer* _popupLayer;

	Sprite* _statusBar;
	Sprite* _seasonPic;

	Label* _date;
	Label* _time;
	Label* _lMoney;

	Node* _parent;

	void addSeason();

	void addYear();
	void addMonth();
	void addWeek();

	void addHour();

	void updateTime();
	void updateDate();
	void updateMoney();

	static Status* _instance;
public:
	Status();
	~Status(){ delete _instance; _instance = nullptr; }

	static Status* getInstance();

	bool init(Node* parent);

	void openPopup();
	void closePopup();

	void addMinute();

	void addMoneyEffect(int price, bool flag);

	void addMoney(float money);
	bool subtractMoney(float money);
};