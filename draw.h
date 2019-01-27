#include"macro.h"
#pragma once
class Cdraw
{
public:
	Cdraw();
	void writechar(COORD pos, HANDLE hStdOut, const char* pstr, WORD color);//print to window
	int waitkey();
	int getSign();//receive cmd from user
	void clearScreen();
	void printFrame();//print the border
	void writeSpace(COORD pos, int map[width][height], HANDLE hStdOut);//clean the map
	void referenceInfo(int hp, int mark, int level = 0);//prompt info
	void edittingMapPrompt();//while editting
	~Cdraw();
	
};