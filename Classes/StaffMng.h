#pragma once

#include "stdafx.h"

class Staff;

class StaffMng
{
private:
	static StaffMng* _staffinstance;

	Layer* _kitstaffLayer;

	Layer* _menustaffLayer;

	Sprite* _staffPic;
	Label* _staffName;
	Label* _staffHP;
	Label* _staffCook;
	Label* _staffDeposit;
	Label* _staffPay;

	Node* _parent;

	int _staffInfo[3][4];//HP,COOK,Deposit,PAY
	int _staffPos[3];

	Staff* _staffarr[3];

	int _employNum;

	int _curStaff = 1;

	bool _isOpen = false;
public:
	StaffMng(); 

	void resetSushi(Node* parent);

	static StaffMng* getInstance();

	void update(float dt);

	void menuCallback(Ref* sender);

	void kitReset(Node* parent);

	void openStaffPopup(Node* parent);

	void openEmployMenu();

	void closeStaffMenu();

	void refresh();

	void init(Node* parent);

	void transformString();

	bool getIsStaffMenuOn(){ return _isOpen; }

	int getPay();

	void updateGameMng();

	void close();

	void stopWorkAtAll();

	void resetCount(Node* parent);

	void setNormalSpr(Staff* stff);
	void setWorkSpr(Staff* stff);
};