#pragma once

#include "stdafx.h"

class MiniOutGuest : public Node
{
public:
	Sprite* body;
	int type;
	int speed;
	int randomselect;
	int posX;
	int posY;
public:
	MiniOutGuest();
	~MiniOutGuest();
	void Release();
};