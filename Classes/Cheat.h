#include "stdafx.h"

class Cheat
{
private:
	static Cheat* _cheatInstance;
public:
	void getInput();
	void getMiniInput();
	static Cheat* getInstance();
};