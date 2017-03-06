#include "stdafx.h"

Recipe* Recipe::_recipeinstance = NULL;
Recipe* Recipe::getInstance()
{
	if (!_recipeinstance)
		_recipeinstance = new Recipe;
	return _recipeinstance;
}

void Recipe::open(Node* parent)
{
	_parent = parent;

	OpenMenu::getInstance()->close();

	_spotID = 2;
	_isMove = false;

	_isRecipeOn = true;

	memset(_recipearr, NULL, sizeof(_recipearr));

	_recipeLayer = Layer::create();
	_recipeLayer->setZOrder(ZINVENTORY);
	_parent->addChild(_recipeLayer);

	_scrollLayer = Layer::create();
	_scrollLayer->setZOrder(ZINVENTORY - 1);
	_parent->addChild(_scrollLayer);
	_originRecipeLayer = _scrollLayer->getPosition();

	_popupBack = Sprite::create("recipe/back.png");
	_popupBack->setPosition(Vec2(0, 140));
	_popupBack->setAnchorPoint(Vec2(0, 0));
	_recipeLayer->addChild(_popupBack);

	_scrollBack = Sprite::create("popup/scrollback.png");
	_scrollBack->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2, 425));
	_parent->addChild(_scrollBack);

	_spotRecipe = Sprite::create(String::createWithFormat("sushi/Ingame_Hall_Order_Example_%d.png", _spotID)->getCString());
	_spotRecipe->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2, 920));
	_recipeLayer->addChild(_spotRecipe);

	for (int i = 0; i < N_MATERIAL; i++)
	{
		if (i == 0 || i == 1 || i == 7 || i == 8)
			continue;
		int ii = i;
		_recipearr[i] = Sprite::create(String::createWithFormat("recipe/recipe (%d).png", i)->getCString());
		_recipearr[i]->setTag(100 + i);

		if (ii < 7)
			ii -= 2;
		else
			ii -= 4;

		_recipearr[i]->setPosition(Vec2(125 + (190 * ii), 500));

		if (!GameData->getRecipeOn(i))
			_recipearr[i]->setColor(Color3B::GRAY);

		if (i > N_MATERIAL / 2 - 1)
			_recipearr[i]->setPosition(Vec2(125 + (190 * (ii - (N_MATERIAL / 2))), 350));

		_scrollLayer->addChild(_recipearr[i]);
	}

	_sushiName = Label::createWithTTF("", GAME_FONT, 35);
	_sushiName->setColor(Color3B::BLACK);
	_sushiName->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2, 730));
	_recipeLayer->addChild(_sushiName);

	_recipe = Label::createWithTTF("", GAME_FONT, 35);
	_recipe->setColor(Color3B::BLACK);
	_recipe->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2, 670));
	_recipeLayer->addChild(_recipe);
	setRecipeString(_spotID);
}

void Recipe::close()
{
	if (_isRecipeOn)
	{

		_isRecipeOn = false;

		_parent = NULL;

		_recipeLayer->removeFromParentAndCleanup(true);
		_scrollLayer->removeFromParentAndCleanup(true);

		_scrollBack->removeFromParentAndCleanup(true);

		memset(_recipearr, NULL, sizeof(_recipearr));
	}
}

void Recipe::touchBegan(Touch* touch)
{
	Vec2 location = touch->getLocation();
	if (_isRecipeOn)
	{
		if (_scrollBack->getBoundingBox().containsPoint(location))
		{
			_isMove = true;
		}
		_touchPoint = location;
	}
}

void Recipe::touchMoved(Touch* touch)
{
	if (_isRecipeOn)
	{
		float location = _scrollLayer->getPosition().x;

		location += touch->getDelta().x;

		if (location < -675)
			location = -675;
		if (location > 0)
			location = 0;

		if (_isMove)
			_scrollLayer->setPositionX(location);
	}
}

void Recipe::touchEnded(Touch* touch)
{
	if (_isRecipeOn)
	{
		_isMove = false;
		Vec2 itemTempPoint = _touchPoint - (_scrollLayer->getPosition() - _originRecipeLayer);
		if (_touchPoint.x + 40 > touch->getLocation().x &&
			_touchPoint.x - 40 < touch->getLocation().x &&
			_touchPoint.y + 40 > touch->getLocation().y &&
			_touchPoint.y - 40 < touch->getLocation().y)
		{
			for (int i = 0; i < N_MATERIAL; i++)
			{
				if (_recipearr[i] && _recipearr[i]->getBoundingBox().containsPoint(itemTempPoint))
				{
					CCLOG("%d", i);
					if (!GameData->getRecipeOn(i))
						continue;

					_spotID = i;
					_spotRecipe->setTexture(String::createWithFormat("sushi/Ingame_Hall_Order_Example_%d.png", i)->getCString());

					setRecipeString(i);
				}
			}
		}
	}
}

void Recipe::setRecipeString(int recipe)
{
	switch (recipe)
	{
	case 2:
		GameData->setStringAtAll(_sushiName, String::createWithFormat("¿¬¾îÃÊ¹ä")->getCString());
		GameData->setStringAtAll(_recipe, String::createWithFormat("¹ä + ½ÄÃÊ + ¿Í»çºñ + ¿¬¾î")->getCString());
		break;
	case 3:
		GameData->setStringAtAll(_sushiName, String::createWithFormat("Âüµ¼ÃÊ¹ä")->getCString());
		GameData->setStringAtAll(_recipe, String::createWithFormat("¹ä + ½ÄÃÊ + ¿Í»çºñ + Âüµ¼")->getCString());
		break;
	case 4:
		GameData->setStringAtAll(_sushiName, String::createWithFormat("³ÒÄ¡ÃÊ¹ä")->getCString());
		GameData->setStringAtAll(_recipe, String::createWithFormat("¹ä + ½ÄÃÊ + ¿Í»çºñ + ³ÒÄ¡")->getCString());
		break;
	case 5:
		GameData->setStringAtAll(_sushiName, String::createWithFormat("°íµî¾îÃÊ¹ä")->getCString());
		GameData->setStringAtAll(_recipe, String::createWithFormat("¹ä + ½ÄÃÊ + ¿Í»çºñ + °íµî¾î")->getCString());
		break;
	case 6:
		GameData->setStringAtAll(_sushiName, String::createWithFormat("Àü°»¾îÃÊ¹ä")->getCString());
		GameData->setStringAtAll(_recipe, String::createWithFormat("¹ä + ½ÄÃÊ + ¿Í»çºñ + Àü°»¾î")->getCString());
		break;
	case 9:
		GameData->setStringAtAll(_sushiName, String::createWithFormat("Àå¾îÃÊ¹ä")->getCString());
		GameData->setStringAtAll(_recipe, String::createWithFormat("¹ä + ½ÄÃÊ + Àå¾î + ±è")->getCString());
		break;
	case 10:
		GameData->setStringAtAll(_sushiName, String::createWithFormat("¿ì·°ÃÊ¹ä")->getCString());
		GameData->setStringAtAll(_recipe, String::createWithFormat("¹ä + ½ÄÃÊ + ¿Í»çºñ + ¿ì·°")->getCString());
		break;
	case 11:
		GameData->setStringAtAll(_sushiName, String::createWithFormat("ÂüÄ¡ÃÊ¹ä")->getCString());
		GameData->setStringAtAll(_recipe, String::createWithFormat("¹ä + ½ÄÃÊ + ¿Í»çºñ + ÂüÄ¡")->getCString());
		break;
	case 12:
		GameData->setStringAtAll(_sushiName, String::createWithFormat("»õ¿ìÃÊ¹ä")->getCString());
		GameData->setStringAtAll(_recipe, String::createWithFormat("¹ä + ½ÄÃÊ + ¿Í»çºñ + »õ¿ì")->getCString());
		break;
	case 13:
		GameData->setStringAtAll(_sushiName, String::createWithFormat("¿ÀÂ¡¾îÃÊ¹ä")->getCString());
		GameData->setStringAtAll(_recipe, String::createWithFormat("¹ä + ½ÄÃÊ + ¿Í»çºñ + ¿ÀÂ¡¾î")->getCString());
		break;
	case 14:
		GameData->setStringAtAll(_sushiName, String::createWithFormat("¹®¾îÃÊ¹ä")->getCString());
		GameData->setStringAtAll(_recipe, String::createWithFormat("¹ä + ½ÄÃÊ + ¿Í»çºñ + ¹®¾î")->getCString());
		break;
	case 15:
		GameData->setStringAtAll(_sushiName, String::createWithFormat("¼º°ÔÃÊ¹ä")->getCString());
		GameData->setStringAtAll(_recipe, String::createWithFormat("¹ä + ±è + ½ÄÃÊ + ¿Í»çºñ + ¼º°Ô")->getCString());
		break;
	case 16:
		GameData->setStringAtAll(_sushiName, String::createWithFormat("Àüº¹ÃÊ¹ä")->getCString());
		GameData->setStringAtAll(_recipe, String::createWithFormat("¹ä + ½ÄÃÊ + ¿Í»çºñ + Àüº¹")->getCString());
		break;
	case 17:
		GameData->setStringAtAll(_sushiName, String::createWithFormat("»õÁ¶°³ÃÊ¹ä")->getCString());
		GameData->setStringAtAll(_recipe, String::createWithFormat("¹ä + ½ÄÃÊ + ¿Í»çºñ + »õÁ¶°³")->getCString());
		break;
	case 18:
		GameData->setStringAtAll(_sushiName, String::createWithFormat("°ÔÃÊ¹ä")->getCString());
		GameData->setStringAtAll(_recipe, String::createWithFormat("¹ä + ½ÄÃÊ + ¿Í»çºñ + °Ô")->getCString());
		break;
	case 19:
		GameData->setStringAtAll(_sushiName, String::createWithFormat("´ëÇÕÃÊ¹ä")->getCString());
		GameData->setStringAtAll(_recipe, String::createWithFormat("¹ä + ½ÄÃÊ + ¿Í»çºñ + ´ëÇÕ")->getCString());
		break;
	case 20:
		GameData->setStringAtAll(_sushiName, String::createWithFormat("°è¶õÃÊ¹ä")->getCString());
		GameData->setStringAtAll(_recipe, String::createWithFormat("¹ä + ½ÄÃÊ + °è¶õ + ±è")->getCString());
		break;
	case 21:
		GameData->setStringAtAll(_sushiName, String::createWithFormat("¿ÀÀÌÃÊ¹ä")->getCString());
		GameData->setStringAtAll(_recipe, String::createWithFormat("¹ä + ½ÄÃÊ + ±è + ¿ÀÀÌ")->getCString());
		break;
	}
}