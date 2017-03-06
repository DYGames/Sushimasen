#include "stdafx.h"

Monster::Monster() : body(NULL), type(0), Xspeed(0), Yspeed(0), life(false)
{

}
Monster::~Monster()
{
	Release();
}

void Monster::Release()
{
	if (body != NULL)
	{
		body->removeFromParentAndCleanup(true);
		body = NULL;
	}
}