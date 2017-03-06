#include "stdafx.h"

class Recipe
{
private:
	static Recipe* _recipeinstance;

	Node* _parent;

	Layer* _recipeLayer;
	Layer* _scrollLayer;

	Sprite* _popupBack;
	Sprite* _scrollBack;

	Sprite* _spotRecipe;

	Label* _sushiName;

	Label* _recipe;

	Vec2 _touchPoint;
	Vec2 _originRecipeLayer;

	Sprite* _recipearr[N_MATERIAL];

	int _spotID;
	bool _isMove = false;

	bool _isRecipeOn = false;
public:
	static Recipe* getInstance();

	bool isRecipeOn(){ return _isRecipeOn; }

	void open(Node* parent);
	void close();

	void setRecipeString(int recipe);

	void touchBegan(Touch* touch);
	void touchMoved(Touch* touch);
	void touchEnded(Touch* touch);

};