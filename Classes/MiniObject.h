#pragma once
#include "stdafx.h"

class MiniObject : public Node
{
public:
	Sprite* body;
	Sprite* hitpoint;
	int o_speed;
	int type;
	int direction;
	int sectype;
public:
	MiniObject();
	~MiniObject();
	void Release();
};