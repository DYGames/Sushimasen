#pragma once

#include "stdafx.h"

class Guest : public Sprite
{
private:
	int _type;
	bool _isWork;
	int _wantRecipe;
	int _pos;
	int _waitlimit = 0;
public:
	static Guest* create(int type, bool recipe, int pos);

	int getType(){ return _type; }
	void setType(int type){ _type = type; }
	
	int getRecipe(){ return _wantRecipe; }

	bool addwait(int iter);

	void setGuestNull();

	void setOrder();
	void setEat();
	void setWait();
	void setAngry();
};