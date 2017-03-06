#include "stdafx.h"

class Store
{
private:
	Node* _parent;

	Layer* _storeLayer;
	Layer* _scrollLayer;

	Sprite* _scrollBack;

	Sprite* _buttonback;
	Sprite* _spotItem;
	Label* _inform;

	MenuItemImage* _matMenu;
	MenuItemImage* _buyMenu;

	bool _isStoreOpen = false;
	bool _move = false;;
	bool _mode = false;

	Vec2 _touchPoint;
	Vec2 _originItemLayerPoint;

	int _buyArray[N_BUYITEM];
	int _itembuyArray[N_ITEM];
	int _priceItem[N_MATERIAL];
	
	void reset();
	void menuCallBack(Ref* sender);

	static Store* _storeinstance;
public:
	static Store* getInstance();

	void openStore(Node* parent);
	void closeStore(bool buy);

	void touchBegan(Touch* touch);
	void touchMoved(Touch* touch);
	void touchEnded(Touch* touch);

	void setInformString(int iter);

	void setNumLabel();

	bool getStoreOpen(){ return _isStoreOpen; }
};