#include "stdafx.h"

Hero::Hero() : body(NULL), type(0)
{

}
Hero::~Hero()
{
	Release();
}
void Hero::Release()
{
	if (body != NULL)
	{
		body->removeFromParentAndCleanup(true);
		body = NULL;
	}
}