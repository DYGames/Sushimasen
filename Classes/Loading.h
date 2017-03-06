#pragma once

#include "stdafx.h"

class Loading : public LayerColor
{
private:
	Sprite* _back;
	Sprite* _logoani;

	Menu* _menu;

	int _count = 0;
public:
	static Scene* createScene();

	virtual bool init();

	void menucallback(Ref* sender);

	void calledfunc();

	CREATE_FUNC(Loading);
};