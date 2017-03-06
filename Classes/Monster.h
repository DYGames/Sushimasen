#pragma once

#include "stdafx.h"

class Monster : public Node
{
public:
	Sprite* body;
	int type;
	int Xspeed;
	int Yspeed;
	bool life;
public:
	Monster();
	~Monster();

	void Release();
};