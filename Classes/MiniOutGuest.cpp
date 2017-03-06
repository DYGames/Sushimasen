#pragma once

#include "stdafx.h"

MiniOutGuest::MiniOutGuest() : body(NULL), type(0), speed(0), randomselect(0), posX(0), posY(0)
{

}
MiniOutGuest::~MiniOutGuest()
{
	Release();
}
void MiniOutGuest::Release()
{
	if (body != NULL)
	{
		body->removeFromParentAndCleanup(true);
		body = NULL;
	}
}