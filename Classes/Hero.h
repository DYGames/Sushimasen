#pragma once

#include "stdafx.h"

class Hero : public Node
{
public:
	Sprite* body;
	int type;
public:
	Hero();
	~Hero();
	void Release();
};