
#pragma once

#include "stdafx.h"

class MiniOutScene : public Layer
{
private:
	Layer* popupLayer;
	Layer* guestLayer;
	Layer* plusLayer;
	Layer* oxLayer;
	Point _Touch;
	Vector<MiniOutGuest*> g_guest;
	bool popupCheck;
	int		Answer[3];
	int		arr[9];
	int		qwe[9];
	int		checkanswer;
	bool    user[3];
	bool	firstsetting;
	bool	movecheck;
	int		answercount;
	int		showq[3];
	int		found;
	int		set[3];
	int		temp;
public:
	static Scene* createScene();

	virtual bool init();

	void update(float dt);

	virtual bool onTouchBegan(Touch* touch, Event* _event);
	virtual void onTouchMoved(Touch* touch, Event* _event);
	virtual void onTouchEnded(Touch* touch, Event* _event);

	void createguest(float dt);
	void selfremover(Node* sender);
	void setting();
	void popup();
	void drawing();
	void Checking(Ref* sender);
	void lastcheck();
	void speak(Ref* sender);
	void returncheck(Ref* sender);
	void speaking(int tag);
	void callcheck(Ref* sender);
	bool returnguest();

	CREATE_FUNC(MiniOutScene);
};