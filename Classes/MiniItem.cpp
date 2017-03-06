#include "stdafx.h"

MiniItem::MiniItem() : body(NULL), type(0), direction(0)
{

}
MiniItem::~MiniItem()
{
	Release();
}
void MiniItem::Release()
{
	if (body != NULL)
	{
		body->removeFromParentAndCleanup(true);
		body = NULL;
	}
}