#pragma once
#include"bullet.h"
class tank :
	public basic
{
public:
	int hp=4;
	COORD tkAry[9];
	tank(int(*map)[height], const bool z,int x=0, int y=0 );
	void createAry();
	void writeTank();
	void cleanTank();
	void inputTank();
	void change();//move
	void randomMove(vector<bullet*> &bul);
	int blockedMove();//determine if move is blocked by others 
	void move();
	void addBullet(vector<bullet*> &bAry);
	bool checkCollision(COORD bpos);
	~tank();
};

