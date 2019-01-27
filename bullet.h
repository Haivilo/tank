#pragma once
#include "basic.h"
class bullet :
	public basic
{
public:
	int previous = 0;//to record previous pos not in river or grass
	void moveBullet();
	void moveBulletOut();//use prev func to move bullet Array
	bullet(int(*map)[height], const bool z, int x = 0, int y = 0);
	~bullet();
};

