﻿#pragma once

#include "stdafx.h"

class Kitchen : public Layer
{
private:
	CookSushi* _cookSushi;
public:
	static Scene* createScene();

	virtual bool init();
	
	void updateStatus(float dt);
	void getInput(float dt);

	virtual bool onTouchBegan(Touch* touch, Event* unused_event);
	virtual void onTouchMoved(Touch* touch, Event* unused_event);
	virtual void onTouchEnded(Touch* touch, Event* unused_event);

	CREATE_FUNC(Kitchen);
};