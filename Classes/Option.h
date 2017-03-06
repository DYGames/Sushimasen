#include "stdafx.h"

class Option
{
private:
	Node* _parent;

	Layer* _optionLayer;

	Sprite* _optionBack;

	Sprite* _creditBack;

	MenuItemImage* _music;
	MenuItemImage* _effect;
	MenuItemImage* _credit;
	MenuItemImage* _exit;

	bool _optionOpen = false;

	bool _mode = true;;

	static Option* _optinstance;
public:
	static Option* getInstance();
	void open(Node* parent);
	void close();

	void menucallback(Ref* sender);

	bool getOptionOpen(){ return _optionOpen; }
};