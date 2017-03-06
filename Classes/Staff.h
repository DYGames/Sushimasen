#pragma once

class Staff : public Sprite
{
private:
	int _type;

	int _pos;

	int _remaintime;

	int _recipe;
public:
	static Staff* create(int type, int pos);

	int getType(){ return _type; }
	void setType(int type){ _type = type; }

	int getPos(){ return _pos; }
	void setPos(int pos){ _pos = pos; }

	int getRecipe(){ return _recipe; }

	int getRemaintime(){ return _remaintime; }

	void stopWork();

	bool subtractTime();

	void setWork(int recipe, int remaintime);
};