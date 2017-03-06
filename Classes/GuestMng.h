#pragma once

#include "stdafx.h"

class Guest;

class GuestMng
{
private:
	static GuestMng* _guestmnginstance;

	Layer* _guestLayer;

	int _hallGuest[N_HALL];
	int _waitGuest[N_WAIT];

	
	float _ctime;
	float _randtime;

public:
	GuestMng(Node* parent);

	static GuestMng* getInstance(Node* parent);

	void setRightPosition();
	void moveForwardWait();

	void addGuest();

	void init(Node* parent);

	void update(float dt, bool addchild);
	void touchBegan(Touch* touch);

	void updateGameMng();

	void setHallGuest(int iter, int value);

	void clearGuest();
};