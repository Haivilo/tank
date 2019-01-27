#include"macro.h"
#include"draw.h"
#pragma once
 class basic
{
protected:
	int (*map)[height];//map array
	static Cdraw draw;//drawing class
public:
	const bool player;//1 is player, 2 is enemy
	clock_t time;//to control frequency
	COORD pos; 
	int dir;//dirction
	basic(int x, int y, const bool z, int mm[width][height]);
	~basic();
};

