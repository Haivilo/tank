#include "tank.h"


tank::tank(int(*map)[height], const bool z, int x , int y ) :basic(x, y, z, map)
{
	createAry();//create array
}

void tank::createAry(){
	int index = 0;
	for (int y = -1; y < 2; y++)
	{
		for (int x = -1; x < 2; x++, index++){
			tkAry[index] = { pos.X + x, pos.Y + y };//9 ptr are all tank pos
		}
	}
}

void tank::writeTank(){
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (player)//if player-> print if enemy-> print regarding their hp
	{
		switch (dir)
			//print on different locations depending on the direction
		{
		case up:
			draw.writechar(tkAry[1], hStdOut, "¡ö", 0xf);
			draw.writechar(tkAry[3], hStdOut, "¡ö", 0xf  );
			draw.writechar(tkAry[4], hStdOut, "¡ö", 0xf  );
			draw.writechar(tkAry[5], hStdOut, "¡ö", 0xf  );
			draw.writechar(tkAry[6], hStdOut, "¡ö", 0xf  );
			draw.writechar(tkAry[8], hStdOut, "¡ö", 0xf  );
			break;

		case down:
			draw.writechar(tkAry[0], hStdOut, "¡ö", 0xf  );
			draw.writechar(tkAry[2], hStdOut, "¡ö", 0xf  );
			draw.writechar(tkAry[3], hStdOut, "¡ö", 0xf  );
			draw.writechar(tkAry[4], hStdOut, "¡ö", 0xf  );
			draw.writechar(tkAry[5], hStdOut, "¡ö", 0xf  );
			draw.writechar(tkAry[7], hStdOut, "¡ö", 0xf  );
			break;
		case left:
			draw.writechar(tkAry[1], hStdOut, "¡ö", 0xf  );
			draw.writechar(tkAry[2], hStdOut, "¡ö", 0xf  );
			draw.writechar(tkAry[3], hStdOut, "¡ö", 0xf  );
			draw.writechar(tkAry[4], hStdOut, "¡ö", 0xf  );
			draw.writechar(tkAry[7], hStdOut, "¡ö", 0xf  );

			draw.writechar(tkAry[8], hStdOut, "¡ö", 0xf  );
			break;
		case right:
			draw.writechar(tkAry[0], hStdOut, "¡ö", 0xf  );
			draw.writechar(tkAry[1], hStdOut, "¡ö", 0xf  );
			draw.writechar(tkAry[4], hStdOut, "¡ö", 0xf  );
			draw.writechar(tkAry[5], hStdOut, "¡ö", 0xf  );
			draw.writechar(tkAry[6], hStdOut, "¡ö", 0xf  );
			draw.writechar(tkAry[7], hStdOut, "¡ö", 0xf  );
			break;
		default:
			break;
		}
	}
	else
	{
		switch (dir)
			//print on different locations depending on the direction
		{
		case up:
			draw.writechar(tkAry[1], hStdOut, "¡ö", 0xf-hp);
			draw.writechar(tkAry[3], hStdOut, "¡ö", 0xf-hp);
			draw.writechar(tkAry[4], hStdOut, "¡ö", 0xf-hp);
			draw.writechar(tkAry[5], hStdOut, "¡ö", 0xf-hp);
			draw.writechar(tkAry[6], hStdOut, "¡ö", 0xf-hp);
			draw.writechar(tkAry[8], hStdOut, "¡ö", 0xf-hp);
			break;

		case down:
			draw.writechar(tkAry[0], hStdOut, "¡ö", 0xf-hp);
			draw.writechar(tkAry[2], hStdOut, "¡ö", 0xf-hp);
			draw.writechar(tkAry[3], hStdOut, "¡ö", 0xf-hp);
			draw.writechar(tkAry[4], hStdOut, "¡ö", 0xf-hp);
			draw.writechar(tkAry[5], hStdOut, "¡ö", 0xf-hp);
			draw.writechar(tkAry[7], hStdOut, "¡ö", 0xf-hp);
			break;
		case left:
			draw.writechar(tkAry[1], hStdOut, "¡ö", 0xf-hp);
			draw.writechar(tkAry[2], hStdOut, "¡ö", 0xf-hp);
			draw.writechar(tkAry[3], hStdOut, "¡ö", 0xf-hp);
			draw.writechar(tkAry[4], hStdOut, "¡ö", 0xf-hp);
			draw.writechar(tkAry[7], hStdOut, "¡ö", 0xf-hp);

			draw.writechar(tkAry[8], hStdOut, "¡ö", 0xf-hp);
			break;
		case right:
			draw.writechar(tkAry[0], hStdOut, "¡ö", 0xf-hp);
			draw.writechar(tkAry[1], hStdOut, "¡ö", 0xf-hp);
			draw.writechar(tkAry[4], hStdOut, "¡ö", 0xf-hp);
			draw.writechar(tkAry[5], hStdOut, "¡ö", 0xf-hp);
			draw.writechar(tkAry[6], hStdOut, "¡ö", 0xf-hp);
			draw.writechar(tkAry[7], hStdOut, "¡ö", 0xf-hp);
			break;
		default:
			break;
		}
	}
	
}

void tank::cleanTank(){//clean previous tank while moving
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < 9; i++)
	{//if prev is grass, draw grass
		if (map[tkAry[i].X][tkAry[i].Y] == GRASSTANK || map[tkAry[i].X][tkAry[i].Y] == GRASSENEMY || map[tkAry[i].X][tkAry[i].Y] == GrassDown || map[tkAry[i].X][tkAry[i].Y] == GrassLeft || map[tkAry[i].X][tkAry[i].Y] == GrassRight || map[tkAry[i].X][tkAry[i].Y] == GrassUp)
		{
			draw.writechar(tkAry[i], hStdOut, "¢£", 0xa);
			map[tkAry[i].X][tkAry[i].Y] = GRASS;
		} 
		else{ //draw space otherwise
			draw.writeSpace(tkAry[i], map, hStdOut);
		}
	}
}

void tank::inputTank(){
	//write into map var
	for (int i = 0; i < 9; i++)
	{
		//if in grass
		if (map[tkAry[i].X][tkAry[i].Y] == GRASS){

			if (i == 4)
			{
				map[tkAry[i].X][tkAry[i].Y] = dir*2;//map poses becomes 2* its dir, for center
			}
			else
			{
				player == 1 ? map[tkAry[i].X][tkAry[i].Y] = GRASSTANK : map[tkAry[i].X][tkAry[i].Y] = GRASSENEMY;
			}

		}
		else
		{//not grass
			if (i == 4)
			{
				map[tkAry[i].X][tkAry[i].Y] = dir;
			}
			else
			{
				player == 1 ? map[tkAry[i].X][tkAry[i].Y] = TANK : map[tkAry[i].X][tkAry[i].Y] = ENEMY;
			}
		}

	}
}

void tank::change(){
	//change regarding directions
	switch (dir)
	{
	case up:
		for (int i = 0; i < 9; i++)
		{
			tkAry[i].Y -= 1;
		}
		break;
	case down:
		for (int i = 0; i < 9; i++)
		{
			tkAry[i].Y += 1;
		}
		break;
	case left:
		for (int i = 0; i < 9; i++)
		{
			tkAry[i].X -= 1;
		}
		break;
	case right:
		for (int i = 0; i < 9; i++)
		{
			tkAry[i].X += 1;
		}
		break;
	default:
		break;
	}


}
int tank::blockedMove(){
	//check if blocked by forward stuff
	switch (dir)
	{//grass and space will not return0
	case up:
		for (int i = 0; i < 3; i++)
		{
			if (map[tkAry[i].X][tkAry[i].Y - 1] != space && map[tkAry[i].X][tkAry[i].Y - 1] != GRASS){
				return 0;
			}
		}
		break;
	case down:
		for (int i = 6; i < 9; i++)
		{
			if (map[tkAry[i].X][tkAry[i].Y + 1] != space && map[tkAry[i].X][tkAry[i].Y + 1] != GRASS){
				return 0;
			}
		}
		break;
	case left:
		for (int i = 0; i < 9; i += 3)
		{
			if (map[tkAry[i].X-1][tkAry[i].Y] != space && map[tkAry[i].X-1][tkAry[i].Y] != GRASS){
				return 0;
			}
		}
		break;
	case right:
		for (int i = 2; i < 9; i += 3)
		{
			if (map[tkAry[i].X+1][tkAry[i].Y] != space && map[tkAry[i].X+1][tkAry[i].Y] != GRASS){
				return 0;
			}
		}
		break;
	default:
		break;
	}
	return 1;
}

void tank::move(){
	if (blockedMove())
	{//if no obstacles in front

		cleanTank();
		change();
		inputTank();
		writeTank();
	}
	else
	{//blocked by something
		//do not change pos, only dir
		cleanTank();
		inputTank();
		writeTank();
	}

}

bool tank::checkCollision(COORD bpos){
	for (int i = 0; i < 9; i++)
	{
		if (tkAry[i].X==bpos.X&&tkAry[i].Y==bpos.Y)
		{
			hp -= 1;
			if (!hp)
			{
			cleanTank();
			return 1;
			}
			else{
				writeTank();
				return 0;
			}
		}
	}
	return 0;
}
void tank::randomMove(vector<bullet*> &bul){
	clock_t now = clock();
	//tk.dir = down;
	int option = 0;
	option = rand() % (5);
	if (now - time > enemyFrequency)
	{

		
		time = now;
		//char a[2];
		int chance[5] = { up, down, left, right, shoot };
		if (option != 4)
		{
			dir = chance[option];
			move();
		}
		else
		{
			addBullet(bul);
		}
	}
}
void tank::addBullet(vector<bullet*> &bAry){
	//add a bullet on the tank head
	bullet* bp = new bullet(map, player);
	bp->dir = dir;
	switch (dir)
	{
	case up: bp->pos = tkAry[1]; break;
	case down:bp->pos = tkAry[7]; break;
	case left:bp->pos = tkAry[3]; break;
	case right:bp->pos = tkAry[5]; break;
	default:
		break;
	}

	bAry.push_back(bp);
}
tank::~tank()
{
}
