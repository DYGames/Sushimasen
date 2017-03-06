#include "stdafx.h"

CookSushi::CookSushi()
{
	string str;

	char* result;

	str = FileUtils::getInstance()->getStringFromFile("recipedata.txt");

	result = strtok((char*)str.c_str(), "\r\n");

	for (int i = 0; i < N_MATERIAL - 4; i++)
	{
		//for (int k = 0; k < 20; k++)
		//{
		//	if (str[k] == ' ' || str[k] == '\n')
		//	{
		//		for (int l = k; l < 20; l++)
		//		{
		//			str[l] = str[l + 1];
		//		}
		//	}
		//}
		//getline(fp, str);//0,7,8,2

		sscanf(result, "%d %d %d %d %d", &sushiarr[i][0],
			&sushiarr[i][1], &sushiarr[i][2], &sushiarr[i][3], &sushiarr[i][4]);

		result = strtok(NULL, "\r\n");
	}

	_moveLayer = false;

	_cookCount = 1;
}

void CookSushi::init(Node* parent)
{
	_parent = parent;

	Sprite* back = Sprite::create("hall/hall_spring.png");
	back->setPosition(Director::getInstance()->getWinSize() / 2);
	parent->addChild(back);

	_invBack = Sprite::create("kitchen/invback.png");
	_invBack->setAnchorPoint(Vec2(0, 0));
	_invBack->setPosition(Vec2(0, 140 + 50));
	_invBack->setScaleY(0.65f);

	parent->addChild(_invBack);


	_cookLayer = Layer::create();
	parent->addChild(_cookLayer);

	_originCookLayer = _cookLayer->getPosition();

	Sprite* plate = Sprite::create("kitchen/plate.png");
	plate->setPosition(Vec2(360, 650));
	plate->setName("plate");
	plate->setZOrder(1);
	parent->addChild(plate);

	for (int i = 0; i < N_MATERIAL; i++)
	{
		_material[i] = Sprite::create(String::createWithFormat("kitchen/material/material_ (%d).png", i)->getCString());
		_material[i]->setTag(i + 200);
		_material[i]->setPosition(Vec2((230 + (340 * i)) * 0.65f, 500 * 0.65f + 100));
		_material[i]->setUserData((int*)1);

		if (i > N_MATERIAL / 2 - 1)
		{
			_material[i]->setPosition(Vec2((230 + (340 * (i - (N_MATERIAL / 2)))) * 0.65f, 275 * 0.65f + 100));
		}

		_cookLayer->addChild(_material[i]);
		_cookVector.pushBack(_material[i]);

		Label* nMaterial = Label::createWithTTF(String::createWithFormat("%d", GameMng::getInstance()->getMaterial(i))->getCString(), GAME_FONT, FONT_SIZE_NUM);
		nMaterial->setTag(i + 200 + 1000);
		nMaterial->setPosition(Vec2(160, 20));
		nMaterial->setColor(Color3B::BLACK);
		_material[i]->addChild(nMaterial);
	}

	Sprite* kitchen = Sprite::create("kitchen/kitchen.png");
	kitchen->setPosition(Director::getInstance()->getWinSize() / 2);
	parent->addChild(kitchen);
}

int CookSushi::getRecipe()
{
	int temparray[5] = { 99, 99, 99, 99, 99 };
	int a = 0;

	for (auto it : _tempCookVector)
	{
		temparray[a] = it;
		a++;
	}


	for (int i = 0; i < 20; i++)
	{
		int temp = memcmp(temparray, sushiarr[i], sizeof(temparray));
		if (temp == 0)
		{
			//log("if recipe num <= 5 then + 3");
			//log("if recipe num > 5 then + 5");

			if (i < 5)
				i += 2;
			else if (i >= 5)
				i += 4;

			log("recipe num : %d", i);

			return i;
		}
	}

	return 99;
}

void CookSushi::resetPlate()
{
	_tempCookVector.clear();

	_cookCount = 1;

	if (_parent->getChildByName("plate")->getChildrenCount() != 0)
	{
		_parent->getChildByName("plate")->removeAllChildrenWithCleanup(true);
	}
}

bool CookSushi::TouchBegan(Touch* touch)
{
	Vec2 location = touch->getLocation();

	if (CANTTOUCH && !OpenMenu::getInstance()->isOpenMenu())
	{
		for (int i = 0; i < 3; i++)
		{
			if (_parent->getChildByTag(i + 850) != NULL)
			{
				if (_parent->getChildByTag(i + 850)->getBoundingBox().containsPoint(location))
				{
					if (static_cast<Staff*>(_parent->getChildByTag(i + 850))->getRemaintime() != -2)
					{
						if (GameData->getRecipeOn(getRecipe()))
						{
							static_cast<Staff*>(_parent->getChildByTag(i + 850))->setWork(getRecipe(), -1);
						}
						resetPlate();
					}
				}
			}
		}

		if (_invBack->getBoundingBox().containsPoint(location))
		{
			_moveLayer = true;

			_touchPoint = location;
		}
		else
			_moveLayer = false;
		for (int i = 0; i <= N_MATERIAL; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				Node* sushi = _parent->getChildByName(String::createWithFormat("%d %d", i, j)->getCString());
				if (sushi != NULL)
				{
					sushi->setColor(Color3B::WHITE);
					if (sushi->getBoundingBox().containsPoint(location))
					{
						sushi->setColor(Color3B::BLUE);
						GameData->setonSushi(i);
					}
				}
			}
		}
	}
	return true;
}

void CookSushi::TouchMoved(Touch* touch)
{
	float location = _cookLayer->getPosition().x;
	if (CANTTOUCH)
	{
		if (_moveLayer)
			location += touch->getDelta().x;

		//log("cooksushi : %f", location);

		if (location < -COOKSUSHIXLIMIT)
			location = -COOKSUSHIXLIMIT;

		if (location > 0)
			location = 0;
	}


	_cookLayer->setPositionX(location);
}

void CookSushi::update(float dt)
{
	for (int i = 0; i < N_MATERIAL; i++)
	{
		((Label*)_material[i]->getChildByTag(i + 200 + 1000))->setString(String::createWithFormat("%d", GameData->getMaterial(i))->getCString());
	}
}

void CookSushi::TouchEnded(Touch* touch)
{
	if (CANTTOUCH)
	{
		Vec2 itemTempPoint = _touchPoint - (_cookLayer->getPosition() - _originCookLayer);
		if (_touchPoint.x + 40 > touch->getLocation().x &&
			_touchPoint.x - 40 < touch->getLocation().x && 
			_touchPoint.y + 40 > touch->getLocation().y &&
			_touchPoint.y - 40 < touch->getLocation().y &&
			_cookCount < 6)
		{
			for (auto it : _cookVector)
			{
				int tag = it->getTag() - 200;

				int i = GameData->getMaterial(tag);

				if (it->getBoundingBox().containsPoint(itemTempPoint) && i > 0)
				{
					log("%d", tag);

					Sprite* mat = Sprite::create(String::createWithFormat("inventory/material_detail/material_detail_ (%d).png", tag)->getCString());

					mat->setPosition(Vec2(220, 130 + _cookCount * 5));
					mat->setScale(1.5f);
					//mat->setAnchorPoint(Vec2(0, 0));

					_parent->getChildByName("plate")->addChild(mat);

					_cookCount++;

					_tempCookVector.push_back(tag);

					i--;

					GameData->setMaterial(tag, i);

					((Label*)it->getChildByTag(tag + 200 + 1000))->setString(String::createWithFormat("%d", i)->getCString());

					cookEffect(rand() % 6 + 1, touch->getLocation());

					break;
				}
			}
		}
	}
}

void CookSushi::cookEffect(int type, Vec2 point)
{
	Sprite* effect = Sprite::create(String::createWithFormat("kitchen/Ingame_Kitchen_Effect_%d/Ingame_Kitchen_Effect_%d_1.png", type, type)->getCString());
	effect->setPosition(point);
	_parent->addChild(effect);

	Animation* animation = Animation::create();
	for (int i = 1; i < 10; i++)
	{
		animation->addSpriteFrameWithFileName(String::createWithFormat("kitchen/Ingame_Kitchen_Effect_%d/Ingame_Kitchen_Effect_%d_%d.png", type, type, i)->getCString());
	}
	animation->setDelayPerUnit(0.1f);
	effect->runAction(Animate::create(animation));
}