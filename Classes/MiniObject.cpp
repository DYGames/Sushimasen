#include "stdafx.h"

MiniObject::MiniObject() :body(NULL), o_speed(0), hitpoint(NULL), type(0), direction(0), sectype(0)
{

}

MiniObject::~MiniObject()
{

}

void MiniObject::Release()
{
	if (body != NULL)
	{
		body->removeFromParentAndCleanup(true);
		body = NULL;
	}
}