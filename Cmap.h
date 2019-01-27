#include "draw.h"
#include"tank.h"
#pragma once
class Cmap
{
	static Cdraw draw;
public:	
	int (*map)[height];
	void createMap();
	void editMap();
	void save(char* link);
	Cmap(int (*mm)[height]);
	~Cmap();
};

