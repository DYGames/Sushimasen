#include "stdafx.h"

Scene* MiniGame::createScene()
{
	auto scene = Scene::create();

	auto layer = MiniGame::create();

	scene->addChild(layer);

	return scene;
}

bool MiniGame::init()
{
	if (!Layer::init())
		return false;

	Size winSize = Director::getInstance()->getWinSize();

	if (GameData->getMusic())
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("mini.mp3", true);
	}

	Director::getInstance()->resume();

	srand(time(NULL));

	schedule(schedule_selector(MiniGame::update));
	schedule(schedule_selector(MiniGame::create), 2.7);
	schedule(schedule_selector(MiniGame::addobject), 3.2);

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(MiniGame::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(MiniGame::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(MiniGame::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	//레이어추가
	enemyLayer = Layer::create();
	this->addChild(enemyLayer, G_Z_ORDER::UNIT);

	interfaceLayer = Layer::create();
	this->addChild(interfaceLayer, G_Z_ORDER::INTER);

	//배경
	background = Sprite::create("mini/back.jpg");
	background->setPosition(Point(winSize.width / 2, winSize.height));
	background->setAnchorPoint(Point(0.5, 1));
	this->addChild(background, G_Z_ORDER::BACKGROUND);

	//공격버튼
	h_button = Sprite::create("mini/hbutton.png");
	h_button->setPosition(Point(winSize.width * 0.2, winSize.height * 0.15));
	this->addChild(h_button, G_Z_ORDER::INTER);

	//폭탄버튼
	b_button = Sprite::create("mini/bbutton.png");
	b_button->setPosition(Point(winSize.width * 0.8, winSize.height * 0.15));
	this->addChild(b_button, G_Z_ORDER::INTER);

	//일시정지
	MenuItemImage* b_pause = MenuItemImage::create("mini/pause.png", "mini/pause.png", CC_CALLBACK_1(MiniGame::pause, this));
	Menu* menu = Menu::create(b_pause, NULL);
	menu->setPosition(Point(winSize.width * 0.88, winSize.height * 0.93));
	this->addChild(menu,G_Z_ORDER::INTER);

	B_movespeed = 20;

	H_movespeed = 5.3;

	T_Check = false;

	G_Start = false;

	G_over = false;

	M_Check = false;

	BoomCheck = false;

	O_movespeed = 4;

	barrierCheck = false;

	buttonCheck = false;

	hitobjCheck = false;

	firstobjCheck = false;

	harpoonCheck = false;

	_i = 0;
	_t = 0;

	//폭탄 개수
	B_Count = 5;

	//시작 카운트
	s_number = Sprite::create("mini/three.png");
	s_number->setPosition(winSize/2);
	this->addChild(s_number, G_Z_ORDER::INTER);
	Animation* animation = Animation::create();
	animation->setDelayPerUnit(0.75f);
	animation->addSpriteFrameWithFileName("mini/three.png");
	animation->addSpriteFrameWithFileName("mini/two.png");
	animation->addSpriteFrameWithFileName("mini/one.png");
	animation->addSpriteFrameWithFileName("mini/start.png");
	Animate* animate = Animate::create(animation);
	CallFuncN* callfucn = CallFuncN::create(CC_CALLBACK_1(MiniGame::callstart, this));
	CallFuncN* callremover = CallFuncN::create(CC_CALLBACK_1(MiniGame::selfremover, this));
	Sequence* sequence = Sequence::create(animate, callremover, callfucn, NULL);
	s_number->runAction(sequence);

	test = true;

	return true;
}

bool MiniGame::onTouchBegan(Touch* touch, Event* _event)
{
	Size winSize = Director::getInstance()->getWinSize();

	_Touch = touch->getLocation();

	if (G_Start)
	{
		T_Check = true;

		if (!h_button->getBoundingBox().containsPoint(_Touch) && !b_button->getBoundingBox().containsPoint(_Touch))
		{
			if (_Touch.x < winSize.width * 0.5)
			{
				buttonCheck = false;
				Direction = B_LEFT;
			}
			else
			{
				buttonCheck = false;
				Direction = B_RIGHT;
			}
		}

		if (h_button->getBoundingBox().containsPoint(_Touch))
		{
			buttonCheck = true;
			boom();
		}

		if (b_button->getBoundingBox().containsPoint(_Touch))
		{
			buttonCheck = true;
			shootting();
		}
	}
	return true;
}

void MiniGame::onTouchMoved(Touch* touch, Event* _event)
{
	Size winSize = Director::getInstance()->getWinSize();

	_Touch = touch->getLocation();

	if (!h_button->getBoundingBox().containsPoint(_Touch) && !b_button->getBoundingBox().containsPoint(_Touch))
	{
		if (_Touch.x < winSize.width * 0.5)
		{
			Direction = B_LEFT;
		}
		else
		{
			Direction = B_RIGHT;
		}
	}
}

void MiniGame::onTouchEnded(Touch* touch, Event* _event)
{
	Size winSize = Director::getInstance()->getWinSize();

	_Touch = touch->getLocation();

	T_Check = false;

}


void MiniGame::update(float dt)
{
	Size winSize = Director::getInstance()->getWinSize();

	Cheat::getInstance()->getMiniInput();

	if (G_Start)
	{
		//배경 움직임
		background->setPositionY(background->getPosition().y + B_movespeed);


		if (background->getPosition().y > 12385)
		{
			B_movespeed = 0;
			Hero->setPositionY(Hero->getPosition().y - 4);
			M_Check = true;
		}


		//주인공 움직임
		if (T_Check)
		{
			if (!buttonCheck)
			{
				if (Direction == B_LEFT)
				{
					Hero->setPositionX(Hero->getPosition().x - H_movespeed);
				}
				if (Direction == B_RIGHT)
				{
					Hero->setPositionX(Hero->getPosition().x + H_movespeed);
				}
				if (Hero->getPosition().x >= winSize.width)
				{
					Hero->setPositionX(Hero->getPosition().x - H_movespeed);
				}
				if (Hero->getPosition().x <= 0)
				{
					Hero->setPositionX(Hero->getPosition().x + H_movespeed);
				}

			}

		}
		//클리어
		if (Hero->getPosition().y <= 0)
		{
			if (!isClear)
				Clear();
		}

		//작살
		if (harpoonCheck)
		{
			_harpoon->setPositionY(_harpoon->getPosition().y - 8);
			if (_harpoon->getPosition().y <= 0)
			{
				harpoonCheck = false;
				removeChild(_harpoon);
			}
		}

		//물고기
		Monster* monster = NULL;

		for (auto it = m_monster.begin(); it != m_monster.end(); it++)
		{
			monster = (Monster*)*it;

			if (monster->type == M_LEFT)
			{
				monster->body->setPositionX(monster->body->getPosition().x - monster->Xspeed);
				monster->body->setPositionY(monster->body->getPosition().y + monster->Yspeed);

				if (monster->body->getPosition().x < 0)
				{
					monster->Release();
					it = m_monster.erase(it);
					break;
				}
				if (harpoonCheck)
				{
					if (_harpoon->getBoundingBox().intersectsRect(monster->body->getBoundingBox()))
					{
						if (_harpoon != NULL)
						{
							removeChild(_harpoon);
							harpoonCheck = false;
						}
						monster->Release();
						it = m_monster.erase(it);
						break;
					}
				}

			}

			if (monster->type == M_RIGHT)
			{
				monster->body->setPositionX(monster->body->getPosition().x + monster->Xspeed);
				monster->body->setPositionY(monster->body->getPosition().y + monster->Yspeed);

				if (monster->body->getPosition().x > winSize.width)
				{
					monster->Release();
					it = m_monster.erase(it);
					break;
				}
				if (harpoonCheck)
				{
					if (_harpoon->getBoundingBox().intersectsRect(monster->body->getBoundingBox()))
					{
						if (_harpoon != NULL)
						{
							removeChild(_harpoon);
							harpoonCheck = false;
						}
						monster->Release();
						it = m_monster.erase(it);
						break;
					}

				}

			}
			
			if (!GameData->getMiniOverPower())
			{
				if (monster->body->getBoundingBox().intersectsRect(Hero->getBoundingBox()))
				{
					Hero->setPosition(Point(5000, 5000));
					Gameover();
				}
			}

			if (barrierCheck)
			{
				if (getChildByTag(BARRIERITEM)->getBoundingBox().intersectsRect(monster->body->getBoundingBox()))
				{
					monster->setPosition(Point(5000, 5000));
					monster->Release();
					it = m_monster.erase(it);
					removeChildByTag(TIMER);
					removeChildByTag(BARRIERITEM);
					barrierCheck = false;
					break;
				}
			}
		}
		//바위
			MiniObject* obj = NULL;

			for (auto obj_it = g_obstacle.begin(); obj_it != g_obstacle.end(); obj_it++)
			{

				obj = (MiniObject*)*obj_it;

				obj->body->setPositionY(obj->body->getPosition().y + obj->o_speed);

				if (obj->body->getPosition().y >= winSize.height)
				{
					obj->Release();
					obj_it = g_obstacle.erase(obj_it);
					break;
				}

				if (!GameData->getMiniOverPower())
				{
					if (obj->body->getBoundingBox().intersectsRect(Hero->getBoundingBox()))
					{
						obj->body->setPosition(Point(5000, 5000));
						Gameover();
					}
				}
			}
			
			//폭탄
			Sprite* _boom = NULL;

			if (hitobjCheck)
			{
				hitobj->setPositionY(hitobj->getPosition().y + 4);
				if (hitobj->getPosition().y >= winSize.height)
				{
					hitobjCheck = false;
					removeChild(hitobj);
				}
			}

			for (auto m_it = m_missile.begin(); m_it != m_missile.end(); m_it++)
			{
				_boom = (Sprite*)* m_it;
				_boom->setPositionY(_boom->getPosition().y - 4);

				if (hitobjCheck)
				{

					Rect box2 = _boom->getBoundingBox();
					Rect box1 = hitobj->getBoundingBox();

					if (box2.intersectsRect(box1))
					{
						BoomCheck = false;
						hitobjCheck = false;
						objposition = hitobj->getPosition();
						removeChild(_boom);
						removeChild(hitobj);
						m_it = m_missile.erase(m_it);
						createitem();
						break;

					}

					if (_boom->getPosition().y <= 0)
					{
						BoomCheck = false;
						removeChild(_boom);
						m_it = m_missile.erase(m_it);
						break;
					}
				}
			}

			
		//아이템
		MiniItem* Item = NULL;
		for (auto it = g_item.begin(); it != g_item.end(); it++)
		{
			Item = (MiniItem*)*it;
			if (Item->direction == RIGHT_UP)
			{
				Item->body->setPositionX(Item->body->getPosition().x + 3);
				Item->body->setPositionY(Item->body->getPosition().y + 3);
			}
			if (Item->direction == RIGHT_DOWN)
			{
				Item->body->setPositionX(Item->body->getPosition().x + 3);
				Item->body->setPositionY(Item->body->getPosition().y - 3);
			}
			if (Item->direction == LEFT_UP)
			{
				Item->body->setPositionX(Item->body->getPosition().x - 3);
				Item->body->setPositionY(Item->body->getPosition().y + 3);
			}
			if (Item->direction == LEFT_DOWN)
			{
				Item->body->setPositionX(Item->body->getPosition().x - 3);
				Item->body->setPositionY(Item->body->getPosition().y - 3);
			}
			if (Item->body->getPosition().x <0 || Item->body->getPosition().y < 0 || Item->body->getPosition().x > D_DESIGN_WIDTH || Item->body->getPosition().y > D_DESIGN_HEIGHT)
			{
				if (Item->direction == RIGHT_UP)
					Item->direction = LEFT_UP;
				else if (Item->direction == LEFT_UP)
					Item->direction = LEFT_DOWN;
				else if (Item->direction == LEFT_DOWN)
					Item->direction = RIGHT_DOWN;
				else if (Item->direction == RIGHT_DOWN)
					Item->direction = RIGHT_UP;
			}
			Rect item = Item->body->getBoundingBox();
			Rect herobox = Hero->getBoundingBox();

			if (herobox.intersectsRect(item))
			{
				if (Item->type == BOOM)
				{
					Item->Release();
					it = g_item.erase(it);
					B_Count++;
					break;
				}
				if (Item->type == BARRIER)
				{
					Item->Release();
					it = g_item.erase(it);
					barrier();
					break;
				}

			}
		}
		if (barrierCheck)
		{
			getChildByTag(BARRIERITEM)->setPosition(Point(Hero->getPosition()));
			getChildByTag(TIMER)->setPosition(getChildByTag(BARRIERITEM)->getPosition().x, getChildByTag(BARRIERITEM)->getPosition().y + 80);
		}
	}
}


void MiniGame::addMonster(int type, bool under)
{
	Size winSize = Director::getInstance()->getWinSize();

	if (!M_Check)
	{
		Monster* monster = new Monster();

		switch (type)
		{
		case M_LEFT:
		{
					   int random = rand() % 2 + 1;
					   int pos = rand() % 432 + 216;

					   switch (random)
					   {
					   case 1:
						   monster->body = Sprite::create("mini/fish_1.png");
						   break;
					   case 2:
						   monster->body = Sprite::create("mini/fish_5.png");
						   break;
					   }
					   monster->body->setPosition(Point(winSize.width + 4, pos));
					   monster->Yspeed = rand() % 4 + 3;
					   monster->Xspeed = rand() % 4 + 3;
					   monster->type = M_LEFT;
					   break;
		}
		case M_RIGHT:
		{
						int random = rand() % 2 + 1;
						switch (random)
						{
						case 1:
							monster->body = Sprite::create("mini/fish_2.png");
							break;
						case 2:
							monster->body = Sprite::create("mini/fish_5.png");
							monster->body->setFlipX(true);
							break;
						}

						monster->body->setPosition(Point(-4, rand() % 432 + 216));
						monster->Yspeed = rand() % 4 + 3;
						monster->Xspeed = rand() % 4 + 3;
						monster->type = M_RIGHT;
						break;
		}
		}
		enemyLayer->addChild(monster->body);

		m_monster.pushBack(monster);
	}
}

void MiniGame::create(float dt)
{
	if (G_Start && test)
	{
		int random = rand() % 4 + 1;

		switch (random)
		{
		case 1:
			addMonster(M_LEFT, false);
			break;
		case 2:
			addMonster(M_RIGHT, false);
			break;
		case 3:
			addMonster(M_LEFT, true);
			break;
		case 4:
			addMonster(M_RIGHT, true);
			break;
		}
	}
}

void MiniGame::Gameover()
{
	Size winSize = Director::getInstance()->getWinSize();

	if (!G_over && G_Start)
	{
		Director::getInstance()->pause();
		popup = Sprite::create("mini/popup.png");
		popup->setPosition(Point(winSize / 2));
		popup->setTag(1000);
		interfaceLayer->addChild(popup);

		MenuItemImage* retry = MenuItemImage::create("mini/retry.png", "mini/retry.png", CC_CALLBACK_1(MiniGame::Call, this));
		retry->setPosition(Point(popup->getContentSize().width/2,popup->getContentSize().height * 0.6));
		retry->setTag(1);

		MenuItemImage* end = MenuItemImage::create("mini/out.png", "mini/out.png", CC_CALLBACK_1(MiniGame::Call, this));
		end->setPosition(Point(popup->getContentSize().width / 2, popup->getContentSize().height * 0.3));
		end->setTag(2);

		Menu* menu = Menu::create(retry, end, NULL);
		menu->setPosition(Point::ZERO);
		popup->addChild(menu);

	}
}

void MiniGame::Call(Ref* sender)
{
	switch (((MenuItem*)sender)->getTag())
	{
	case 1:
		scene = MiniGame::createScene();
		Director::getInstance()->replaceScene(scene);
		break;
	case 2:
		if (GameData->getMusic())
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
			CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("main.mp3", true);
		}
		Director::getInstance()->resume();
		MOVESCENE(0.15f, Hall::createScene());
		break;
	case 3:
		interfaceLayer->removeAllChildrenWithCleanup(true);
		Director::getInstance()->resume();
		break;
	}
}

void MiniGame::Clear()
{
	Size winSize = Director::getInstance()->getWinSize();

	isClear = true;

	enemyLayer->removeAllChildrenWithCleanup(true);
	m_monster.clear();
	g_obstacle.clear();
	
	int randd = rand() % 22;
	while (GameData->getRecipeOn(randd) || (randd < 9 && randd > 6) || randd < 2 || randd > 21 || (randd == 11 || randd == 12 || randd == 13|| randd == 14))
	{
		randd = rand() % 22;
	}

	GameData->setRecipeOn(randd, true);

	Sprite* result = Sprite::create("mini/result.png");
	result->setPosition(winSize / 2);
	interfaceLayer->addChild(result);

	Sprite* recipe = Sprite::create(String::createWithFormat("recipe/recipe (%d).png", randd)->getCString());
	recipe->setPosition(winSize / 2);
	interfaceLayer->addChild(recipe);

	MenuItemImage* back = MenuItemImage::create("mini/back.png", "mini/back2.png", CC_CALLBACK_1(MiniGame::Call, this));
	back->setTag(2);
	back->setPosition(Vec2(winSize.width / 2, 480));

	Menu* menu = Menu::create(back, NULL);
	menu->setPosition(Vec2());
	interfaceLayer->addChild(menu);

}


void MiniGame::pause(Ref* sender)
{
	Size winSize = Director::getInstance()->getWinSize();

	if (!G_over && G_Start)
	{
		Director::getInstance()->pause();
		popup = Sprite::create("mini/popup.png");
		popup->setPosition(Point(winSize / 2));
		popup->setTag(1000);
		interfaceLayer->addChild(popup);

		MenuItemImage* retry = MenuItemImage::create("mini/retry.png", "mini/retry.png", CC_CALLBACK_1(MiniGame::Call, this));
		retry->setPosition(Point(popup->getContentSize().width/2,popup->getContentSize().height * 0.5));
		retry->setTag(1);

		MenuItemImage* resume = MenuItemImage::create("mini/resume.png", "mini/resume.png", CC_CALLBACK_1(MiniGame::Call, this));
		resume->setPosition(Point(popup->getContentSize().width / 2, popup->getContentSize().height * 0.75));
		resume->setTag(3);

		MenuItemImage* end = MenuItemImage::create("mini/out.png", "mini/out.png", CC_CALLBACK_1(MiniGame::Call, this));
		end->setPosition(Point(popup->getContentSize().width / 2, popup->getContentSize().height * 0.25));
		end->setTag(2);

		Menu* menu = Menu::create(retry, resume,end, NULL);
		menu->setPosition(Point::ZERO);
		popup->addChild(menu);

	}
}

void MiniGame::callstart(Node* sender)
{
	G_Start = true;

	Size winSize = Director::getInstance()->getWinSize();

	Hero = Sprite::create("mini/character_1.png");
	Hero->setPosition(Point(winSize.width * 0.5, winSize.height * 0.8));
	this->addChild(Hero, G_Z_ORDER::UNIT);
	Animation* Hero_animation = Animation::create();
	Hero_animation->addSpriteFrameWithFile("mini/character_1.png");
	Hero_animation->addSpriteFrameWithFile("mini/character_2.png");
	Hero_animation->addSpriteFrameWithFile("mini/character_3.png");
	Hero_animation->setDelayPerUnit(0.3f);
	Animate* Hero_animate = Animate::create(Hero_animation);
	RepeatForever* forever = RepeatForever::create(Hero_animate);
	Hero->runAction(forever);
}

void MiniGame::selfremover(Node* sender)
{
	sender->removeFromParentAndCleanup(true);
}

void MiniGame::addobject(float dt)
{
	Size winSize = Director::getInstance()->getWinSize();

	if (G_Start)
	{

		if (!M_Check)
		{
			MiniObject* obj = new MiniObject();
			
			
			int random = rand() % 6 + 1;

			if (random == 6 && firstobjCheck == false)
			{
				firstobjCheck = true;
				random = rand() % 5 + 1;
			}
			
			if (firstobjCheck)
			{
				if (_i == 2 || _i == 6)
				{
					random = 6;
				}
				
			}

			switch (random)
				{
				case 1:
					_i++;
					firstobjCheck = true;
					obj->body = Sprite::create("mini/rock_1.png");
					obj->body->setPosition(Point(0, -4));
					obj->body->setAnchorPoint(Point(0, 0.5));
					break;
				case 2:
					_i++;
					firstobjCheck = true;
					obj->body = Sprite::create("mini/rock_2.png");
					obj->body->setPosition(Point(winSize.width, -4));
					obj->body->setAnchorPoint(Point(1, 0.5));
					break;
				case 3:
					_i++;
					firstobjCheck = true;
					obj->body = Sprite::create("mini/rock_3.png");
					obj->body->setPosition(Point(0, -4));
					obj->body->setAnchorPoint(Point(0, 0.5));
					break;
				case 4:
					_i++;
					firstobjCheck = true;
					obj->body = Sprite::create("mini/rock_4.png");
					obj->body->setPosition(Point(winSize.width, -4));
					obj->body->setAnchorPoint(Point(1, 0.5));
					break;
				case 5:
					_i++;
					firstobjCheck = true;
					obj->body = Sprite::create("mini/rock_5.png");
					obj->body->setPosition(Point(0, -4));
					obj->body->setAnchorPoint(Point(0, 0.5));
					break;
				case 6:
					if (!hitobjCheck)
					{
						_i++;
						firstobjCheck = true;
						hitobj = Sprite::create("mini/rock_6.png");
						hitobj->setPosition(Point(winSize.width / 2, -4));
						this->addChild(hitobj, G_Z_ORDER::HIT);
						hitobjCheck = true;

						break;
					}

					break;
				}
			
			if (!hitobjCheck)
			{
				obj->o_speed = B_movespeed / 3 * 2;
				this->addChild(obj->body, G_Z_ORDER::HIT);

				g_obstacle.pushBack(obj);
			}
			
		}
	}
}

void MiniGame::shootting()
{
	if (B_Count >= 1)
	{
		BoomCheck = true;
		B_Count--;

		Sprite* missile = Sprite::create("mini/boomitem.png");
		missile->setPosition(Hero->getPosition());
		this->addChild(missile,G_Z_ORDER::HIT);

		m_missile.pushBack(missile);
	}
}

void MiniGame::boom()
{
	if (G_Start)
	{
		if (!harpoonCheck)
		{
		
		harpoonCheck = true;

		_harpoon = Sprite::create("mini/harpoon.png");
		_harpoon->setPosition(Hero->getPosition());
		this->addChild(_harpoon,G_Z_ORDER::HIT);
		}
	}

}

void MiniGame::createitem()
{
	MiniItem* Item = new MiniItem();
	int random = rand() % 2 + 1;
	int direction = rand() % 3 + 0;
	int itempos;
	
	switch (direction)
	{
	case 0:
		itempos = Direction::RIGHT_UP;
		break;
	case 1:
		itempos = Direction::RIGHT_DOWN;
		break;
	case 2:
		itempos = Direction::LEFT_UP;
		break;
	case 3:
		itempos = Direction::LEFT_DOWN;
		break;
	}

	if (_t == 0)
	{
		_t = 1;
	}
	if (_t == 3)
	{
		_t = 1;
	}

	switch (_t)
	{
	case 1:
		_t++;
		Item->body = Sprite::create("mini/barrieritem.png");
		Item->body->setPosition(Point(objposition));
		Item->type = BARRIER;
		Item->direction = itempos;
		break;
	case 2:
		_t++;
		Item->body = Sprite::create("mini/boomitem.png");
		Item->body->setPosition(Point(objposition));
		Item->type = BOOM;
		Item->direction = itempos;
		break;
	}
	this->addChild(Item->body);
	g_item.pushBack(Item);
}
void MiniGame::barrier()
{
	if (!barrierCheck)
	{
		Size winSize = Director::getInstance()->getWinSize();

		barrierCheck = true;
		Sprite* barrier = Sprite::create("mini/barrier.png");
		barrier->setPosition(Point(Hero->getPosition()));
		barrier->setOpacity(200);
		barrier->setTag(BARRIERITEM);
		this->addChild(barrier);

		Sprite* timer_gaze = Sprite::create("mini/timer.png");
		ProgressTimer* m_progress = ProgressTimer::create(timer_gaze);
		m_progress->setPosition(barrier->getPosition().x, barrier->getPosition().y + 220);
		m_progress->setPercentage(100);
		m_progress->setMidpoint(ccp(0, 0.5));
		m_progress->setBarChangeRate(ccp(1, 0));
		m_progress->setType(kCCProgressTimerTypeBar);
		m_progress->setTag(TIMER);
		this->addChild(m_progress, 3);

		ProgressFromTo* progresstozero = ProgressFromTo::create(3, 100, 0);
		CallFuncN* callFucnn = CallFuncN::create(CC_CALLBACK_1(MiniGame::callbarrier, this));
		Sequence* sequence = Sequence::create(progresstozero, callFucnn, NULL);
		m_progress->runAction(sequence);

	}

}
void MiniGame::callbarrier(Node* sender)
{
	barrierCheck = false;
	removeChildByTag(BARRIERITEM);
	removeChildByTag(TIMER);
}