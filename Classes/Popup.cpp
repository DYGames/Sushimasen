#include "stdafx.h"

Popup* Popup::_popupInstance = NULL;
Popup* Popup::getInstance()
{
	if (!_popupInstance)
		_popupInstance = new Popup;
	return _popupInstance;
}

Popup::Popup()
{
	_isPopupOpen = false;
}

void Popup::openPopup(Node* parent)
{
	_parent = parent;

	OpenMenu::getInstance()->close();

	Store::getInstance()->closeStore(false);

	Inventory::getInstance()->close();

	if (StaffMng::getInstance()->getIsStaffMenuOn())
		StaffMng::getInstance()->closeStaffMenu();

	Recipe::getInstance()->close();

	Option::getInstance()->close();

	_isPopupOpen = true;

	_openclose = true;

	memset(_buyArray, 0, sizeof(_buyArray));

	string str;

	char* result;

	str = FileUtils::getInstance()->getStringFromFile("pricedata.txt");

	result = strtok((char*)str.c_str(), "\r\n");

	for (int i = 0; i < N_MATERIAL; i++)
	{
		sscanf(result, "%d", &_priceItem[i]);

		result = strtok(NULL, "\r\n");
		//_priceItem[i] = atoi(str.c_str() + (i * 5));
	}

	_popupLayer = Layer::create();
	_popupLayer->setGlobalZOrder(ZPOPUP);
	_parent->addChild(_popupLayer, 2);

	_scrollLayer = Layer::create();
	_scrollLayer->setGlobalZOrder(ZPOPUPSCROLL);
	_parent->addChild(_scrollLayer, 1);

	_scrollBack = Sprite::create("popup/scrollback.png");
	_scrollBack->setPosition(Vec2(355, 420));
	//_scrollBack->setGlobalZOrder(ZPOPUPSCROLL);
	_scrollBack->setTag(99);
	_parent->addChild(_scrollBack);


	/////////////////////////////scroll////////////////////////////////////////////
	for (int i = 0; i < N_BUYITEM; i++)
	{
		MenuItemImage* left = MenuItemImage::create("popup/leftbutton.png", "popup/leftbutton.png", CC_CALLBACK_1(Popup::menuCallBack, this));
		left->setTag(100 + i);
		left->setScale(1.75f);
		left->setPosition(Vec2(85 + (225 * i), 450));

		MenuItemImage* right = MenuItemImage::create("popup/rightbutton.png", "popup/rightbutton.png", CC_CALLBACK_1(Popup::menuCallBack, this));
		right->setTag(200 + i);
		right->setScale(1.75f);
		right->setPosition(Vec2(215 + (225 * i), 450));

		Sprite* fish = Sprite::create(String::createWithFormat("kitchen/material/material_ (%d).png", i)->getCString());
		fish->setPosition(Vec2(150 + (225 * i), left->getPositionY() + 50));
		_scrollLayer->addChild(fish);

		Sprite* numback = Sprite::create("popup/numback.png");
		numback->setPosition(Vec2(150 + (225 * i), 450));
		_scrollLayer->addChild(numback);

		if (i > N_BUYITEM / 2 - 1)
		{
			left->setPosition(Vec2(85 + (225 * (i - (N_BUYITEM / 2))), 300));
			right->setPosition(Vec2(215 + (225 * (i - (N_BUYITEM / 2))), 300));
			numback->setPosition(Vec2(150 + (225 * (i - (N_BUYITEM / 2))), 300));
			fish->setPosition(Vec2(150 + (225 * (i - (N_BUYITEM / 2))), left->getPositionY() + 50));
		}

		Label* num = Label::createWithTTF("0", GAME_FONT, 30);
		num->setPosition(numback->getPosition());
		num->setColor(Color3B::BLACK);
		num->setTag(300 + i);
		_scrollLayer->addChild(num);

		Label* price = Label::createWithTTF(String::createWithFormat("%d", _priceItem[i])->getCString(), GAME_FONT, 20);
		price->setColor(Color3B::BLACK);
		price->setPosition(Vec2(fish->getPositionX() + 40, fish->getPositionY() + 25));
		_scrollLayer->addChild(price);

		Menu* menu = Menu::create(left, right, NULL);
		menu->setPosition(Vec2());
		_scrollLayer->addChild(menu);
	}
	/////////////////////////////scroll end/////////////////////////////////////////

	_popupBack = Sprite::create("popup/openpopup.png");
	_popupBack->setPosition(Director::getInstance()->getWinSize() / 2);
	_popupLayer->addChild(_popupBack);

	_closeButton = MenuItemImage::create("popup/openpopupbutton.png", "popup/openpopupbutton2.png", CC_CALLBACK_1(Popup::menuCallBack, this));
	_closeButton->setPosition(Vec2(550, 640));
	_closeButton->setTag(1);

	Menu* menu = Menu::create(_closeButton, NULL);
	menu->setPosition(Vec2());
	_popupLayer->addChild(menu);

	_todayInfo = Label::createWithTTF("", GAME_FONT, 25);
	_todayInfo->setColor(Color3B::BLACK);
	_todayInfo->setPosition(Vec2(225, 920));
	_popupLayer->addChild(_todayInfo);

	_resultPrice = Label::createWithTTF("0", GAME_FONT, 50);
	_resultPrice->setAnchorPoint(Vec2(1, 0.5));
	_resultPrice->setPosition(Vec2(325, 640));
	_resultPrice->setColor(Color3B::BLACK);
	_popupLayer->addChild(_resultPrice);

	srand(time(NULL));
	setRandomLabel();
}

void Popup::setRandomLabel()
{
	int randd;
	if (GameData->getMonth() < 4 && GameData->getYear() == 1)
	{
		randd = rand() % 5;
		switch (randd)
		{
		case 0:
			GameData->setStringAtAll(_todayInfo, String::create("오늘도 반갑습니다. 모두 신선한 \n재료들 뿐이니 어서 골라 보십시오.")->getCString());
			break;
		case 1:
			GameData->setStringAtAll(_todayInfo, String::create("흐 음~ 하. 한번 맞아 보세요~ \n이 신선한 재료의 냄새를~ 골라 보십쇼.")->getCString());
			break;
		case 2:
			GameData->setStringAtAll(_todayInfo, String::create("매일 거래를 할 때 마다 \n즐거울 따름입니다. 골라 보세요.")->getCString());
			break;
		case 3:
			GameData->setStringAtAll(_todayInfo, String::create("휴~ 차가 막혀서 \n늦을 뻔 했네요. \n하하. 어서 골라 보세요.")->getCString());
			break;
		case 4:
			GameData->setStringAtAll(_todayInfo, String::create("거래를 많이 한 저나 \n그 재료로 많이 판 사장님이나 \n일석이조가 따로 없군요.\n어서 골라 보십쇼.")->getCString());
			break;
		case 5:
			GameData->setStringAtAll(_todayInfo, String::create("저와 꾸준히 거래를 해주시니 \n정말 감사드립니다. 나중에 식사 한번 대접하죠. \n자 어서 골라보세요.")->getCString());
			break;
		}
	}
	else
	{
		randd = rand() % 11;
		switch (randd)
		{
		case 0:
			GameData->setStringAtAll(_todayInfo, String::create("제 아들이 초밥을 정말 좋아하는데 \n나중에 한번 데리고 와도 될까요?")->getCString());
			break;
		case 1:
			GameData->setStringAtAll(_todayInfo, String::create("아이고 아들을 학교에 데려다 \n주느라 늦을 뻔 했네요.")->getCString());
			break;
		case 2:
			GameData->setStringAtAll(_todayInfo, String::create("오늘도 많이 파시고 건강하시길 바랍니다.")->getCString());
			break;
		case 3:
			GameData->setStringAtAll(_todayInfo, String::create("기분이 안 좋다가도 사장님의 \n밝은 얼굴을 보면 기운이 납니다.")->getCString());
			break;
		case 4:
			GameData->setStringAtAll(_todayInfo, String::create("혹시나 해서 말입니다만, \n저희 재료가 이상이 있다 싶으시면 \n부담없이 말씀 해주시길 바랍니다. \n바로 해결해 드리죠.")->getCString());
			break;
		case 5:
			GameData->setStringAtAll(_todayInfo, String::create("언제 한번 저희 작업장에 들리시는건 \n어떻겠습니까? 저희가 사장님께 배달하기 \n전까지의 과정을 보여드리고 싶습니다만.")->getCString());
			break;
		case 6:
			GameData->setStringAtAll(_todayInfo, String::create("전에 사장님이 초밥 만드시던걸 \n잠깐 엿봤습니다만. 캬~정말 현란 \n하시더군요. 놀랍습니다.")->getCString());
			break;
		case 7:
			GameData->setStringAtAll(_todayInfo, String::create("흠. 흠! 신선한 재료 엄선! \n깔끔한 손질! 빠른 배달! 이 삼박자가 \n잘 맞기에 저희 회사가 잘 돌아간답니다.")->getCString());
			break;
		case 8:
			GameData->setStringAtAll(_todayInfo, String::create("언제 한번은 저희 회사가 큰 위기를 \n겪은 적이 있었죠… 그 땐 참 힘든 시절 \n이였는데… 흑… 이런, 제 잡담이 길었네요.")->getCString());
			break;
		case 9:
			GameData->setStringAtAll(_todayInfo, String::create("버리는 재료는 어떻게 하는지 \n궁금하십니까? 죄송합니다만, 그건 영업상 \n비밀인 점 양해 부탁드립니다.")->getCString());
			break;
		case 10:
			GameData->setStringAtAll(_todayInfo, String::create("혹시 사장님께서 고민이 있으시다면 \n저희 쪽에서 될 수 있는 데로 도와 드릴 \n테니 꼭 말씀 해주시기 바랍니다.")->getCString());
			break;
		case 11:
			GameData->setStringAtAll(_todayInfo, String::create("지난번에 제 직원이 손질을 하다 \n그만 손가락을 베었지 뭡니까. 그래서 제가 쉬라고 \n했더니 괜찮다며 다시 일에 임하더군요.")->getCString());
			break;
		}

	}

	if (GameData->getYear() == 1 && GameData->getMonth() == 3 && GameData->getWeek() == 1)
		GameData->setStringAtAll(_todayInfo, String::create("저희와 거래를 맺어 주셔서 \n감사드립니다. 저희는 신선한 \n재료만 엄선해서 가져다 드리니 \n걱정 마시고 자 어서 골라 \n보십시오.")->getCString());

	if (GameData->getYear() == 1 && GameData->getMonth() == 4 && GameData->getWeek() == 1)
		GameData->setStringAtAll(_todayInfo, String::create("사장님과 계약 한지 금새 \n한달이 지났군요. \n앞으로도 잘 부탁드립니다.")->getCString());
}

void Popup::touchBegan(Touch* touch)
{
	Vec2 location = touch->getLocation();

	if (getPopupOpen() && _openclose)
	{
		if (_scrollBack->getBoundingBox().containsPoint(location))
		{
			_popupmove = true;
		}
		_touchPoint = location;
	}
}

void Popup::touchMoved(Touch* touch)
{
	if (getPopupOpen() && _openclose)
	{
		float location = _scrollLayer->getPosition().x;

		location += touch->getDelta().x;

		if (location > 0)
			location = 0;

		//log("popup : %f", location);
		if (location < -POPUPXLIMIT)
			location = -POPUPXLIMIT;

		if (_popupmove)
		{
			_scrollLayer->setPositionX(location);
		}

		//CCLOG("%f", _scrollLayer->getPositionX());
	}
}

void Popup::touchEnded(Touch* touch)
{
	if (getPopupOpen() && _openclose)
	{
		_popupmove = false;
	}
}

void Popup::closePopup(Node* parent)
{
	_parent = parent;

	_openclose = false;

	GuestMng::getInstance(NULL)->clearGuest();

	OpenMenu::getInstance()->close();

	Store::getInstance()->closeStore(false);

	Inventory::getInstance()->close();

	if (StaffMng::getInstance()->getIsStaffMenuOn())
		StaffMng::getInstance()->closeStaffMenu();

	Recipe::getInstance()->close();

	for (int i = 0; i < N_MATERIAL; i++)
	{
		GameData->setMaterial(i, 0);
	}

	for (int i = 0; i < 5; i++)
	{
		GameData->setSushi(i, 0);
	}

	if (!OpenMenu::getInstance()->getCurScene())
	{
		StaffMng::getInstance()->close();

		StaffMng::getInstance()->stopWorkAtAll();
	}
	StaffMng::getInstance()->resetSushi(parent);


	_popupLayer = Layer::create();
	_parent->addChild(_popupLayer);

	Inventory::getInstance()->close();

	_popupBack = Sprite::create("popup/closepopup.png");
	_popupBack->setPosition(Director::getInstance()->getWinSize() / 2);
	_popupLayer->addChild(_popupBack);

	_isPopupOpen = true;

	_closeButton = MenuItemImage::create("popup/closepopupbutton.png", "popup/closepopupbutton2.png", CC_CALLBACK_1(Popup::menuCallBack, this));

	_closeButton->setPosition(Vec2(360, 340));
	_closeButton->setTag(2);

	Menu* menu = Menu::create(_closeButton, NULL);
	menu->setPosition(Vec2());

	_popupLayer->addChild(menu);

	int result = 0;

	if (GameMng::getInstance()->getWeek() == 4)
	{
		int pay = StaffMng::getInstance()->getPay();

		if (!Status::getInstance()->subtractMoney(pay))
		{
			//파산.
		}
		else
		{
			Label* payLabel = Label::createWithTTF("", GAME_FONT, 50);
			payLabel->setPosition(Vec2(350, 740));
			payLabel->setColor(Color3B::BLACK);
			_popupLayer->addChild(payLabel, 99);
			GameData->setStringAtAll(payLabel, String::createWithFormat("월급            -%d", pay)->getCString());
			result -= pay;
		}
	}
	else
	{
		Label* payLabel = Label::createWithTTF("", GAME_FONT, 25);
		payLabel->setPosition(Vec2(350, 780));
		payLabel->setColor(Color3B::BLACK);
		_popupLayer->addChild(payLabel, 99);
		GameData->setStringAtAll(payLabel, String::createWithFormat("월급은 4주차에 계산됩니다.")->getCString());
	}

	{
		Label* willpayLabel = Label::createWithTTF("", GAME_FONT, 50);
		willpayLabel->setPosition(Vec2(350, 710));
		willpayLabel->setColor(Color3B::BLACK);
		_popupLayer->addChild(willpayLabel, 99);
		result -= GameMng::getInstance()->getWillPay();
		GameData->setStringAtAll(willpayLabel, String::createWithFormat("재료값         -%d", GameMng::getInstance()->getWillPay())->getCString());
		GameData->resetWillPay();
	}
	{
		Label* incomeLabel = Label::createWithTTF("", GAME_FONT, 50);
		incomeLabel->setPosition(Vec2(350, 640));
		incomeLabel->setColor(Color3B::BLACK);
		_popupLayer->addChild(incomeLabel, 99);
		result += GameData->getIncome();
		GameData->setStringAtAll(incomeLabel, String::createWithFormat("수입            +%d", GameData->getIncome())->getCString());
		GameData->setIncome(0);
	}
	Label* resultLabel = Label::createWithTTF("", GAME_FONT, 50);
	resultLabel->setPosition(Vec2(440, 500));
	resultLabel->setColor(Color3B::BLACK);
	_popupLayer->addChild(resultLabel, 99);
	GameData->setStringAtAll(resultLabel, String::createWithFormat("%d", result)->getCString());
}

void Popup::menuCallBack(Ref* sender)
{
	int tag = ((MenuItem*)sender)->getTag();

	int resultprice = 0;
	switch (tag)
	{
	case 1://buy material
		for (int i = 0; i < N_BUYITEM; i++)
		{
			int price = _buyArray[i] * _priceItem[i];
			int cmoney = GameMng::getInstance()->getMoney();

			if (cmoney < price)
			{
				return;//돈 부족.
			}
		}

		for (int i = 0; i < N_BUYITEM; i++)
		{
			int price = _buyArray[i] * _priceItem[i];
			int cmoney = GameMng::getInstance()->getMoney();

			GameMng::getInstance()->setMaterial(i, GameMng::getInstance()->getMaterial(i) + _buyArray[i]);

			resultprice += price;

			GameMng::getInstance()->setWillPay(price);
		}

		Status::getInstance()->subtractMoney(resultprice);
		_isPopupOpen = false;

		_parent->removeChildByTag(99);
		_popupLayer->removeAllChildrenWithCleanup(true);
		_scrollLayer->removeAllChildrenWithCleanup(true);
		break;
	case 2://close closepopup
		_isPopupOpen = false;

		_popupLayer->removeAllChildrenWithCleanup(true);
		break;
	default:
		if (tag >= 100 && tag < 200)
		{
			if (_buyArray[tag - 100] > 0)
			{
				_buyArray[tag - 100] -= 5;
			}
		}
		if (tag >= 200 && tag < 300)
		{
			_buyArray[tag - 200] += 5;
		}

		setNumLabel();
		break;
	}
}

void Popup::setNumLabel()
{
	int price = 0;

	for (int i = 0; i < N_BUYITEM; i++)
	{
		((Label*)_scrollLayer->getChildByTag(300 + i))->setString(String::createWithFormat("%d", _buyArray[i])->getCString());

		price += _buyArray[i] * _priceItem[i];
	}
	_resultPrice->setString(String::createWithFormat("%d", price)->getCString());
}

bool Popup::getPopupOpen()
{
	return _isPopupOpen;
}