#include "draw.h"
#pragma once
class obs
{
	static Cdraw draw;
	COORD pos;
	int hp;
	int type = 0;
public:
	static int(*map)[height];
	obs(COORD position, int tpe=WOOD,int hh=0);
	void inputObs();//obs = obstacles
	void writeObs();//print to map
	bool reduceHpDie(COORD bpos);//reduce hp while being hit
	~obs();
};

