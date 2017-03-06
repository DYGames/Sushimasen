#pragma once

#include "stdafx.h"

class Inventory
{
private:
	Node* _parent;

	Layer* _invLayer;
	Layer* _itemLayer;

	Sprite* _invBack;

	Sprite* _spotItem;
	int _spotItemID;

	Sprite* _item[N_ITEM];
	Sprite* _material[N_MATERIAL];

	Sprite* _buttonBack;
	MenuItemImage* _materialButton;
	MenuItemImage* _itemButton;

	Label* _info;

	bool _isInvOn;
	bool _invMove;
	bool _invMode; // true = item false = material

	Vec2 _touchPoint;
	Vec2 _originItemLayer;

	Vector<Sprite*> _itemVector;
public:
	Inventory();

	bool getisInvOn();

	void open(Node* parent);

	void close();

	void setInfoString(int index);

	static Inventory* getInstance();

	static Inventory* _invInstance;

	void touchBegan(Touch* touch);
	void touchMoved(Touch* touch);
	void touchEnded(Touch* touch);

	void menuCallBack(Ref* sender);
};

template<typename T>
inline T Lerp(T value1, T value2, float amount)
{
	return T(value1 + ((T)(value2 - value1) * amount));
}