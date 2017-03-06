#pragma once

#include "stdafx.h"

class OpenMenu
{
private:
	Node* _parent;

	Layer* _openMenuLayer;

	MenuItemImage* _menuMenu;
	MenuItemImage* _backMenu;
	
	Menu* _menu;

	Sprite* _openMenu;

	int _menuTag;

	//true = hall , false = kitchen
	bool _scene;
	bool _isMenuOpen;
	bool _isMenuSelect;

	Rect _openMenuRect[7];
	
	static OpenMenu* _openMenuInstance;

	void initRect();

	void openMenuTouch(Vec2 location);

	void menuCallback();

	void runOpenAction(bool onoff);
public:
	OpenMenu();
	~OpenMenu(){ delete _openMenuInstance; _openMenuInstance = nullptr; }

	bool getCurScene(){ return _scene; }

	static OpenMenu* getInstance();

	void init(Node* parent, bool scene);
	void touchBegan(Touch* touch);
	void touchMoved(Touch* touch);

	bool isOpenMenu(){ return _isMenuOpen; }

	void touchEnded(Touch* touch);

	void onoffMenu();

	void close();
};
