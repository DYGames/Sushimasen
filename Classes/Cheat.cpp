#include "stdafx.h"

Cheat* Cheat::_cheatInstance = NULL;
Cheat* Cheat::getInstance()
{
	if (!_cheatInstance)
		_cheatInstance = new Cheat;
	return _cheatInstance;
}

void Cheat::getInput()
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	if (GetAsyncKeyState(0x70) & 1)//F1 �ð� ����
	{
		if (GameData->getFast())
			GameData->setFast(false);
		else
			GameData->setFast(true);
	}
	if (GetAsyncKeyState(0x71) & 1)//F2 �մ� �߰�
	{
		if (OpenMenu::getInstance()->getCurScene())
			GuestMng::getInstance(NULL)->addGuest();
	}
	if (GetAsyncKeyState(0x72) & 1)//F3 �ð� ����������
	{
		GameMng::getInstance()->setHour(21);
		GameMng::getInstance()->setMinute(50);
	}
#endif
}

void Cheat::getMiniInput()
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	if (GetAsyncKeyState(0x74) & 1)//F4 �̴ϰ��� ����
	{
		if (GameData->getMiniOverPower())
			GameData->setMiniOverPower(false);
		else
			GameData->setMiniOverPower(true);
	}
#endif
}