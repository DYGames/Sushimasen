#pragma once

#include "stdafx.h"

class CookSushi
{
private:
	int sushiarr[20][5];

	Node* _parent;

	Layer* _cookLayer;

	Vec2 _originCookLayer;

	Sprite* _material[N_MATERIAL];
	Sprite* _invBack;
	Vec2 _touchPoint;

	Vector<Sprite*> _cookVector;

	vector<int> _tempCookVector;

	bool _moveLayer;

	int _cookCount;
public:
	CookSushi();

	void init(Node* parent);

	bool TouchBegan(Touch* touch);
	void TouchMoved(Touch* touch);
	void TouchEnded(Touch* touch);

	int getRecipe();

	void resetPlate();

	void cookEffect(int type, Vec2 point);

	void update(float dt);
};