#include "stdafx.h"

Scene* MiniOutScene::createScene()
{
	auto scene = Scene::create();

	auto layer = MiniOutScene::create();

	scene->addChild(layer);

	return scene;
}

bool MiniOutScene::init()
{
	if (!Layer::init())
		return false;
	srand(time(NULL));

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(MiniOutScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(MiniOutScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(MiniOutScene::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	//팝업레이어
	popupLayer = Layer::create();
	this->addChild(popupLayer, G_Z_ORDER::INTER);

	//손님레이어
	guestLayer = Layer::create();
	this->addChild(guestLayer, G_Z_ORDER::UNIT);

	//글자레이어
	plusLayer = Layer::create();
	this->addChild(plusLayer, G_Z_ORDER::INTER);

	//OX레이어
	oxLayer = Layer::create();
	this->addChild(oxLayer, 5);

	schedule(schedule_selector(MiniOutScene::update));
	schedule(schedule_selector(MiniOutScene::createguest), 1);

	popupCheck = false;

	checkanswer = 0;

	firstsetting = false;

	answercount = 0;

	movecheck = false;

	return true;
}
void MiniOutScene::update(float dt)
{

}

bool MiniOutScene::onTouchBegan(Touch* touch, Event* _event)
{
	/*
	for (auto it : g_guest)
	{
		if (it->body->getBoundingBox().containsPoint(_Touch))
		{
			if (it->type == LIFE)
				it->type = DIE;
			temp = it->randomselect;
			popup();
		}
	}
	*/
	log("touch");
	if (!popupCheck)
	{
		_Touch = touch->getLocation();

		MiniOutGuest* g = NULL;
		for (auto it = g_guest.begin(); it != g_guest.end(); it++)
		{
			MiniOutGuest* g = (MiniOutGuest*)*it;
			if (g->body->getBoundingBox().containsPoint(_Touch))
			{
				temp = g->randomselect;
				popup();
			}
		}
	}
	return true;
}

void MiniOutScene::onTouchMoved(Touch* touch, Event* _event)
{

}

void MiniOutScene::onTouchEnded(Touch* touch, Event* _event)
{

}

void MiniOutScene::createguest(float dt)
{
	Size winSize = Director::getInstance()->getWinSize();

	int random = rand() % 5 + 1;
	int randombody = rand() % 6 + 1;

	MiniOutGuest* m_guest = new MiniOutGuest();

	m_guest->body = Sprite::create(String::createWithFormat("mini/g%d.png", randombody)->getCString());
	m_guest->randomselect = randombody;
	m_guest->posX = rand() % 620 + 50;
	m_guest->posY = rand() % 668 + 150;
	m_guest->body->setPosition(Point(m_guest->posX, m_guest->posY));
	m_guest->type = LIFE;

	DelayTime* delaytime = DelayTime::create(random);
	CallFuncN* callfucn = CallFuncN::create(CC_CALLBACK_1(MiniOutScene::selfremover, this));
	Sequence* sequence = Sequence::create(delaytime, callfucn, NULL);
	m_guest->body->runAction(sequence);

	guestLayer->addChild(m_guest->body);
	g_guest.pushBack(m_guest);
}

void MiniOutScene::selfremover(Node* sender)
{
	MiniOutGuest* guest = NULL;
	for (auto it = g_guest.begin(); it != g_guest.end(); it++)
	{
		guest = (MiniOutGuest*)*it;
		if (guest->type == LIFE)
		{
			guest->Release();
			it = g_guest.erase(it);
			break;
		}
	}
}

void MiniOutScene::popup()
{
	Size winSize = Director::getInstance()->getWinSize();

	if (!popupCheck)
	{
		popupCheck = true;

		Sprite* seletpopup = Sprite::create("mini/outsceneback.png");
		seletpopup->setPosition(Point(winSize / 2));
		seletpopup->setTag(3333);
		popupLayer->addChild(seletpopup);

		//직원
		Sprite* staff = Sprite::create("mini/harpoon.png");
		staff->setPosition(Point(0, winSize.height * 0.8));
		seletpopup->addChild(staff);

		CallFuncN* call = CallFuncN::create(CC_CALLBACK_1(MiniOutScene::callcheck, this));
		MoveTo* moveto = MoveTo::create(1, Point(winSize.width * 0.45, winSize.height * 0.8));
		Sequence* sequence = Sequence::create(moveto, call, NULL);
		staff->runAction(sequence);

		//손님
		Sprite* guest = Sprite::create(String::createWithFormat("mini/g%d.png", temp)->getCString());
		guest->setPosition(Point(winSize.width * 0.8, winSize.height * 0.8));
		seletpopup->addChild(guest);

		//체크박스
		Sprite* box1 = Sprite::create("mini/box.png");
		box1->setPosition(Point(winSize.width * 0.2, winSize.height * 0.6));
		seletpopup->addChild(box1);

		Sprite* box2 = Sprite::create("mini/box.png");
		box2->setPosition(Point(winSize.width * 0.5, winSize.height * 0.6));
		seletpopup->addChild(box2);

		Sprite* box3 = Sprite::create("mini/box.png");
		box3->setPosition(Point(winSize.width * 0.8, winSize.height * 0.6));
		seletpopup->addChild(box3);
	}
}

void MiniOutScene::setting()
{
	Size winSize = Director::getInstance()->getWinSize();

	bool answercheck[10] = { false, };
	bool acheck[10] = { false, };

	if (!firstsetting)
	{
		for (int j = 0; j < 3;)
		{
			int randomanswer = rand() % 3;
			if (answercheck[randomanswer] == false)
			{
				answercheck[randomanswer] = true;
				Answer[j] = randomanswer + 1;
				log("%d", Answer[j]);
				j++;
			}
		}
	}

	switch (checkanswer)
	{
	case 0:
		arr[0] = Answer[0];
		break;
	case 1:
		arr[0] = Answer[1];
		break;
	case 2:
		arr[0] = Answer[2];
		break;
	}

	found = 0;
	for (int i = found + 1; i < 12; ++i)
	{
		while (1)
		{
			arr[i] = rand() % 12 + 4;
			int qwe = 0;
			for (int j = found; j < i; ++j)
			{
				if (arr[j] == arr[i])
				{
					qwe = 1;
					break;
				}
			}
			if (!qwe)
			{
				break;
			}
		}
	}

	for (int i = 0; i < 3; ++i)
	{
		while (1)
		{
			set[i] = rand() % 3;
			int qwe = 0;
			for (int j = 0; j < i; ++j)
			{
				if (set[j] == set[i])
				{
					qwe = 1;
					break;
				}
			}
			if (!qwe)
			{
				break;
			}
		}
	}


	for (int i = 0; i < 3; i++)
	{
		Label* question = Label::createWithTTF("", GAME_FONT, 40);
		question->setColor(Color3B::BLACK);
		switch (arr[i])
		{
		case 1:
			GameData->setStringAtAll(question, String::createWithFormat("초밥 좋아하세요?")->getCString());
			break;
		case 2:
			GameData->setStringAtAll(question, String::createWithFormat("연어 초밥 어때요?")->getCString());
			break;
		case 3:
			GameData->setStringAtAll(question, String::createWithFormat("저희 초밥 가게에서 식사 어떠세요?")->getCString());
			break;
		case 4:
			GameData->setStringAtAll(question, String::createWithFormat("치킨 좋아하세요?")->getCString());
			break;
		case 5:
			GameData->setStringAtAll(question, String::createWithFormat("간장 양념 중에 뭐가 더 좋아요?")->getCString());
			break;
		case 6:
			GameData->setStringAtAll(question, String::createWithFormat("오늘 날씨가 좋네요.")->getCString());
			break;
		case 7:
			GameData->setStringAtAll(question, String::createWithFormat("저기 사진 좀 찍어주세요.")->getCString());
			break;
		case 8:
			GameData->setStringAtAll(question, String::createWithFormat("아몰랑")->getCString());
			break;
		case 9:
			GameData->setStringAtAll(question, String::createWithFormat("오늘 아침 뭐 먹었어요?")->getCString());
			break;
		case 10:
			GameData->setStringAtAll(question, String::createWithFormat("도를 아십니까?")->getCString());
			break;
		case 11:
			GameData->setStringAtAll(question, String::createWithFormat("저희 가게 물 좋아요.")->getCString());
			break;
		case 12:
			GameData->setStringAtAll(question, String::createWithFormat("저희 가게 주차장 없어요.")->getCString());
			break;
		case 13:
			GameData->setStringAtAll(question, String::createWithFormat("몇 살이에요?")->getCString());
			break;
		case 14:
			GameData->setStringAtAll(question, String::createWithFormat("아버지 뭐 하시노")->getCString());
			break;
		case 15:
			GameData->setStringAtAll(question, String::createWithFormat("유단잔가?")->getCString());
			break;
		}
		MenuItemLabel* menuitemlabel = MenuItemLabel::create(question, CC_CALLBACK_1(MiniOutScene::Checking, this));
		menuitemlabel->setTag(arr[i]);
		Menu* menu = Menu::create(menuitemlabel, NULL);
		menu->setPosition(Point(winSize.width / 2, winSize.height * 0.4 - set[i] * 150));
		plusLayer->addChild(menu, 3);
	}
}

void MiniOutScene::Checking(Ref* sender)
{
	Size winSize = Director::getInstance()->getWinSize();

	log("Checking");
	found++;
	firstsetting = true;
	arr[3] = { NULL, };

	//글자지우기
	plusLayer->removeAllChildrenWithCleanup(true);

	for (; checkanswer < 3;)
	{
		if (Answer[checkanswer] == ((MenuItem*)sender)->getTag())
		{
			user[checkanswer] = true;
			break;
		}
		else
		{
			user[checkanswer] = false;
			break;
		}
		break;
	}

	if (checkanswer < 3)
	{
		speaking(((MenuItem*)sender)->getTag());
		drawing();
		checkanswer++;
		setting();
	}

	if (checkanswer == 3)
	{
		lastcheck();
	}

}

void MiniOutScene::speaking(int tag)
{
	Size winSize = Director::getInstance()->getWinSize();

	Label* question = Label::create("", GAME_FONT, 25);
	question->setColor(Color3B::WHITE);
	question->setPosition(Point(winSize.width * 0.35, winSize.height * 0.85));
	plusLayer->addChild(question, 3);

	switch (tag)
	{
	case 1:
		GameData->setStringAtAll(question, String::create("초밥 좋아하세요?")->getCString());
		break;
	case 2:
		GameData->setStringAtAll(question, String::create("연어 초밥 어때요?")->getCString());
		break;
	case 3:
		GameData->setStringAtAll(question, String::create("저희 초밥 가게에서 식사 어떠세요?")->getCString());
		break;
	case 4:
		GameData->setStringAtAll(question, String::create("치킨 좋아하세요?")->getCString());
		break;
	case 5:
		GameData->setStringAtAll(question, String::create("간장 양념 중에 뭐가 더 좋아요?")->getCString());
		break;
	case 6:
		GameData->setStringAtAll(question, String::create("오늘 날씨가 좋네요.")->getCString());
		break;
	case 7:
		GameData->setStringAtAll(question, String::create("저기 사진 좀 찍어주세요.")->getCString());
		break;
	case 8:
		GameData->setStringAtAll(question, String::create("아몰랑")->getCString());
		break;
	case 9:
		GameData->setStringAtAll(question, String::create("오늘 아침 뭐 먹었어요?")->getCString());
		break;
	case 10:
		GameData->setStringAtAll(question, String::create("도를 아십니까?")->getCString());
		break;
	case 11:
		GameData->setStringAtAll(question, String::create("저희 가게 물 좋아요.")->getCString());
		break;
	case 12:
		GameData->setStringAtAll(question, String::create("저희 가게 주차장 없어요.")->getCString());
		break;
	case 13:
		GameData->setStringAtAll(question, String::create("몇 살이에요?")->getCString());
		break;
	case 14:
		GameData->setStringAtAll(question, String::create("아버지 뭐 하시노")->getCString());
		break;
	case 15:
		GameData->setStringAtAll(question, String::create("유단잔가?")->getCString());
		break;
	}

	Label* answer = Label::create("", GAME_FONT, 25);
	answer->setPosition(Point(winSize.width * 0.8, winSize.height * 0.85));
	GameData->setStringAtAll(answer, String::create("네 좋아요.")->getCString());
	Label* Incorrect = Label::create("", GAME_FONT, 30);
	Incorrect->setPosition(Point(winSize.width * 0.8, winSize.height * 0.85));
	GameData->setStringAtAll(Incorrect, String::create("엥 뭐라는거야")->getCString());


	switch (checkanswer)
	{
	case 0:
		if (user[0] == true)
		{
			plusLayer->addChild(answer, 4);
		}
		else
		{
			plusLayer->addChild(Incorrect, 4);
		}
		break;
	case 1:
		if (user[1] == true)
		{
			plusLayer->addChild(answer, 4);
		}
		else
		{
			plusLayer->addChild(Incorrect, 4);
		}
		break;
	case 2:
		if (user[2] == true)
		{
			plusLayer->addChild(answer, 4);
		}
		else
		{
			plusLayer->addChild(Incorrect, 4);
		}
		break;
	}
}


void MiniOutScene::drawing()
{
	Size winSize = Director::getInstance()->getWinSize();

	Sprite* circle = Sprite::create("mini/circle.png");
	Sprite* Incorrect = Sprite::create("mini/incorrect.png");

	switch (checkanswer)
	{
	case 0:
		if (user[0] == true)
		{
			circle->setPosition(Point(winSize.width * 0.2, winSize.height * 0.6));
			oxLayer->addChild(circle, 4);
		}
		else
		{
			Incorrect->setPosition(Point(winSize.width * 0.2, winSize.height * 0.6));
			oxLayer->addChild(Incorrect, 4);
		}
		break;
	case 1:
		if (user[1] == true)
		{
			circle->setPosition(Point(winSize.width * 0.5, winSize.height * 0.6));
			oxLayer->addChild(circle, 4);
		}
		else
		{
			Incorrect->setPosition(Point(winSize.width * 0.5, winSize.height * 0.6));
			oxLayer->addChild(Incorrect, 4);
		}
		break;
	case 2:
		if (user[2] == true)
		{
			circle->setPosition(Point(winSize.width * 0.8, winSize.height * 0.6));
			oxLayer->addChild(circle, 4);
		}
		else
		{
			Incorrect->setPosition(Point(winSize.width * 0.8, winSize.height * 0.6));
			oxLayer->addChild(Incorrect, 4);
		}
		break;
	}
}

void MiniOutScene::lastcheck()
{
	Size winSize = Director::getInstance()->getWinSize();

	plusLayer->removeAllChildrenWithCleanup(true);

	Sprite* back = Sprite::create("mini/outsceneback.png");
	back->setPosition(winSize / 2);
	popupLayer->addChild(back, 6);

	MenuItemImage* check = MenuItemImage::create("mini/barrier.png", "mini/barrier.png", CC_CALLBACK_1(MiniOutScene::returncheck, this));
	Menu* menu = Menu::create(check, NULL);
	menu->setPosition(Point(winSize / 2));
	back->addChild(menu);

	char g[256];
	sprintf(g, "mini/g%d.png", temp);
	Sprite* guest = Sprite::create(g);
	guest->setPosition(Point(winSize.width / 2, winSize.height * 0.8));
	back->addChild(guest);

	int temp = 0;
	for (int i = 0; i < 3; i++)
	{
		if (user[i] == true)
		{
			temp++;
		}
	}

	Label* label = Label::create("", GAME_FONT, 40);
	label->setPosition(Point(winSize.width / 2, winSize.height * 0.7));
	plusLayer->addChild(label);
	switch (temp)
	{
	case 0:
		GameData->setStringAtAll(label, String::create("허맛 지금 장난치는거에욧?!")->getCString());
		break;
	case 1:
		GameData->setStringAtAll(label, String::create("초밥은 좋지만 갈지는 모르겠네요.")->getCString());
		break;
	case 2:
		GameData->setStringAtAll(label, String::create("시간이 되면 가보겠습니다.")->getCString());
		break;
	case 3:
		GameData->setStringAtAll(label, String::create("꼭 가봐야겠네요!")->getCString());
		break;
	}

	returnguest();
}

void MiniOutScene::returncheck(Ref* sender)
{
	log("returncheck");
	for (int i = 0; i < 3; i++)
	{
		Answer[i] = NULL;
		user[i] = NULL;
	}

	firstsetting = false;
	popupLayer->removeAllChildrenWithCleanup(true);
	oxLayer->removeAllChildrenWithCleanup(true);
	plusLayer->removeAllChildrenWithCleanup(true);
	popupCheck = false;
	checkanswer = 0;
	movecheck = false;
}
void MiniOutScene::callcheck(Ref* sender)
{
	setting();
}

bool MiniOutScene::returnguest()
{
	int success = 0;
	int _success = 0;

	for (int i = 0; i < 3; i++)
	{
		if (user[i] == true)
		{
			_success++;
		}
	}

	log("%d", _success);

	switch (_success)
	{
	case 0:
		return false;
		break;
	case 1:
		success = rand() % 10 + 1;
		if (success == 1 || success == 2)
		{
			return true;
		}
		break;
	case 2:
		success = rand() % 2 + 1;
		if (success == 1)
		{
			return true;
		}
		break;
	case 3:
		success = rand() % 10 + 1;
		if (success != 10 || success != 9)
		{
			return true;
		}
		break;
	}
	return false;
}