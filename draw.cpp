#include "draw.h"


Cdraw::Cdraw()
{
}

void Cdraw::writechar(COORD pos, HANDLE hStdOut, const char* pstr, WORD color)
{
	//the function for format printing 
	pos.X *= 2;
	SetConsoleCursorPosition(hStdOut, pos);
	SetConsoleTextAttribute(hStdOut, color);
	printf("%s", pstr);
}
int Cdraw::waitkey(){
	if (_kbhit())
	{
		return _getch();
	}
	return 0;

}

int Cdraw::getSign(){
	char a = waitkey();
	switch (a)
	{//return specific value
	case'w':case'W':return up; break;
	case's':case'S':return down; break;
	case'd':case'D':return right; break;
	case'a':case'A':return left; break;
	case'j':case'J':return shoot; break;
	case 'o':return up2; break;
	case 'l':return down2; break;
	case 'k':return left2; break;
	case ';':return right2; break;
	case '[':return shoot2; break;
	case 'p':return PAUSE; break;
	default:
		break;
	}
	return 0;
}
void Cdraw::printFrame(){
	
	char gameFrame[100] = { '\0' };
	sprintf_s(gameFrame, 100, "mode con cols=%d lines=%d", width * 2, height+6);
	system(gameFrame);
}

void Cdraw::writeSpace(COORD pos, int map[width][height], HANDLE hStdOut){
	//input space for specified coord
	map[pos.X][pos.Y] = space;
	writechar(pos, hStdOut, "  ", 0xf);
}

void Cdraw::clearScreen(){
	//return to init size
	char gameFrame[100] = { '\0' };
	sprintf_s(gameFrame, 100, "mode con cols=%d lines=%d", 20, 10);
	system(gameFrame);
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, 0xf);
}

void Cdraw::referenceInfo(int hp, int mark, int level){
	//prompt while playing
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(out, {0,height});
	SetConsoleTextAttribute(out, 0xf);
	cout << "wasd move; j atk ko;l move; [ atk" << endl << "HP: " << hp << endl << "Score: " << mark << endl;
	if (level)
	{
		cout <<"level :"<< level << endl;
	}
}
void Cdraw::edittingMapPrompt(){
	//prompt while drawing map
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(out, { 0, height });
	SetConsoleTextAttribute(out, 0xf);
	cout << "0-9: set hp" << endl << "t-v: set Tank  " << "b: set Base  " << endl << "r : set river  " <<  "i : IRON  " <<"g : GRASS" <<endl << "q : finish";
}

Cdraw::~Cdraw()
{
}
