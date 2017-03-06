#pragma once

#include "stdafx.h"

class Start : public Layer
{
private:
public:
	static Scene* createScene();

	virtual bool init();

	void menucallback(Ref* sender);

	bool onTouchBegan(Touch* touch, Event* unused_event);

	CREATE_FUNC(Start);
};