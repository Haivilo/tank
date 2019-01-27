
#pragma once
#include "tank.h"
#include"obs.h"
#include "Cmap.h"
class game
{
	int allBullets(vector<bullet*>& bAry, vector<tank*>& tk, tank& player, vector<obs*>& obss);
	int map[width][height];
	Cdraw draw;
	vector<tank*> enetk;//enymy vector
	vector<obs*> Aobs;//obs vector
	vector<bullet*> bul;//bullet vector
	void play(tank &tk, vector<tank*> enetk, vector<bullet*>& bul, vector<obs*>& Aobs);//single player
	void play2(tank &tk, tank &tk2, vector<tank*> enetk, vector<bullet*>& bul, vector<obs*>& Aobs);//dual 
	void save(tank &tk, vector<tank*> enetk, vector<bullet*>& bul, vector<obs*>& Aobs, clock_t& timer, char link[]);
	
	bool game::read(tank &tk, clock_t& timer, char link[]);//read from file
	void readInToMap();
	bool readInfo(char* link);//read into a ptr buffer
public:
	int mark=0;
	int level = 0;
	game();
	bool easyGame();
	int mapPlay(char* abc, int hp = 4, int lev = 0);//defualt game 
	int mapMode();//single
	int twoPlayerMode();//dual player
	int continuePlay();
	~game();
};

