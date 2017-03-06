#pragma once

#include "stdafx.h"

class MiniGame : public Layer
{
private:
	Layer* enemyLayer;
	Layer* interfaceLayer;
	Sprite* Hero;
	Sprite* background;
	Sprite* monster;
	Sprite* button;
	Sprite* b_pause;
	Sprite* s_number;
	Sprite* popup;
	Sprite* Barrieritem;
	Sprite* Boomitem;
	Sprite* h_button;
	Sprite* b_button;
	Sprite* hitobj;
	Sprite* _harpoon;
	int Direction;
	int B_movespeed;
	int H_movespeed;
	int O_movespeed;
	int M_movespeed;
	int B_Count;
	int _i;
	int _t;
	bool T_Check;
	bool B_Check;
	bool G_Start;
	bool G_over;
	bool M_Check;
	bool BoomCheck;
	bool barrierCheck;
	bool buttonCheck;
	bool firstobjCheck;
	bool hitobjCheck;
	bool harpoonCheck;

	bool isClear = false;

	Point objposition;
	Scene* scene;
	Point _Touch;
	Vector<Monster*> m_monster;
	Vector<MiniObject*>  g_obstacle;
	Vector<Sprite*>  m_missile;
	Vector<MiniItem*>    g_item;
	bool test;
public:
	static Scene* createScene();

	virtual bool init();

	void update(float dt);

	virtual bool onTouchBegan(Touch* touch, Event* _event);
	virtual void onTouchMoved(Touch* touch, Event* _event);
	virtual void onTouchEnded(Touch* touch, Event* _event);

	void addMonster(int type, bool under);
	void create(float dt);
	void Gameover();
	void Call(Ref* sender);
	void pause(Ref* sender);
	void Clear();
	void callstart(Node* sender);
	void selfremover(Node* sender);
	void addobject(float dt);
	void shootting();
	void boom();
	void createitem();
	void barrier();
	void callbarrier(Node* sender);
	CREATE_FUNC(MiniGame);
};