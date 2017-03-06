#pragma once

#include "stdafx.h"

class Popup
{
private:
	Node* _parent;

	Layer* _popupLayer;
	Layer* _scrollLayer;
	Sprite* _popupBack;
	Sprite* _scrollBack;

	Sprite* _openNPC;

	MenuItemImage* _closeButton;

	Sprite* _tooltip;
	Label* _todayInfo;

	Label* _resultPrice;

	bool _isPopupOpen;

	void menuCallBack(Ref* sender);

	bool _popupmove;

	int _buyArray[N_BUYITEM];
	int _priceItem[N_MATERIAL];

	bool _openclose = true;

	Vec2 _touchPoint;
public:
	Popup();

	void openPopup(Node* parent);

	void closePopup(Node* parent);

	void setRandomLabel();

	void setNumLabel();

	bool getPopupOpen();

	static Popup* getInstance();
	static Popup* _popupInstance;

	void touchBegan(Touch* touch);
	void touchMoved(Touch* touch);
	void touchEnded(Touch* touch);
};