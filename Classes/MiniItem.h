#pragma once

#include "stdafx.h"

class MiniItem : public Node
{
public:
	Sprite* body;
	int type;
	int direction;
public:
	MiniItem();
	~MiniItem();
	void Release();
};