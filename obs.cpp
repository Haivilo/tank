#include "obs.h"

Cdraw obs::draw;

int (*obs::map)[height];
obs::obs(COORD position, int tpe, int hh)
{//init
	pos = position;
	type = tpe;
	hp = hh;
}


void obs::writeObs(){
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	switch (type)
	{//if obs, print regarding hp
	case WOOD:draw.writechar(pos, hStdOut, "¡ö", 0xc - hp); break;
	case RIVER:	draw.writechar(pos, hStdOut, "¢£", 0x9); break;
	default:
		break;
	}
	
	
}

bool obs::reduceHpDie(COORD bpos){
	
	if (pos.X == bpos.X&&pos.Y == bpos.Y)
	{
		hp -= 1;

		if (hp)
		{
			writeObs();
			return 0;
		}
		else{
			HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
			draw.writeSpace(pos, map, hStdOut);
			return 1;
		}
	}return 0;
}
void obs::inputObs(){
	//input to map
	map[pos.X][pos.Y] = type;
}
obs::~obs()
{
}
