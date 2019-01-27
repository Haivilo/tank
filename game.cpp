#include "game.h"


game::game()
{
	obs::map = map;
}

bool game::easyGame(){
	Cmap _map(map);
	Cdraw draw;
	_map.createMap();
	vector<tank*> enetk;
	tank* ptk = new tank(map, 0, 20, 20);
	tank* ptk2 = new tank(map, 0, 30, 20);
	enetk.push_back(ptk);
	enetk.push_back(ptk2);
	vector<obs*> Aobs;
	vector<bullet*> bul;
	
	tank tk(map,1,10,10);
	tk.writeTank();
	tk.inputTank();
	for (int i = 0; i < enetk.size(); i++)
	{
		enetk[i]->writeTank();
		enetk[i]->inputTank();
	}
	while (true)
	{
		clock_t now = clock();
		for (int i = 0; i < enetk.size(); i++)
		{
			enetk[i]->randomMove(bul);
		}
		int a = draw.getSign();
		if (a == up || a == down || a == left || a == right){
			tk.dir = a;
			tk.move();
		}
		else if (a == shoot&&now - tk.time > 2 * bulletSpeed){
			tk.addBullet(bul);
			tk.time = now;
		}	
		if(allBullets(bul, enetk, tk, Aobs)) break;
	}
	return 1;
}

int game::allBullets(vector<bullet*>& bAry,  vector<tank*>& tk, tank& player, vector<obs*>& obss){
	//move all bullets
	for (int i = 0; i < bAry.size(); i++)
	{
		bAry[i]->moveBulletOut();//every one needs to be moved
		switch (bAry[i]->dir)
		{//if dir is tanks or obs -> disapear+reduce hp
			//if grass/ border -> only disappear

		case TANK:
			if (!bAry[i]->player)
			{
				player.hp -= 1;
				draw.referenceInfo(player.hp, mark);//refresh score and hp
				if (!player.hp)//no hp, dead
				{
					return 1;
				}
			}
			delete bAry[i];
			bAry.erase(bAry.begin() + i);
			break;
		case ENEMY:
			if (bAry[i]->player)
			{
				for (int t = 0; t < tk.size(); t++)
				{
					if (tk[t]->checkCollision(bAry[i]->pos)){//return 1£¬ if dead
				
						mark += 1;
						draw.referenceInfo(player.hp, mark);//refresh prompt
						delete tk[t];
						tk.erase(tk.begin() + t);
						if (tk.size()==0)
						{
							return 1;
						}
						break;
					}
				}
			}
			delete bAry[i];
			bAry.erase(bAry.begin() + i);
			
			break;
		case WOOD:
			for (int t = 0; t < obss.size(); t++)
			{
				if (obss[t]->reduceHpDie(bAry[i]->pos)){//collided with obs
					delete obss[t];
					obss.erase(obss.begin() + t);
					break;
				}
			}
			delete bAry[i];
			bAry.erase(bAry.begin() + i);
			break;
		case BASE:
			player.hp = 0;
			return 1;
		case IRON: case BULLET: case GRASSTANK:case GRASSENEMY:case wall:
			delete bAry[i];
			bAry.erase(bAry.begin() + i);
			break;
		default:
			break;
		}
	}
	return 0;
}


bool game::readInfo(char* link){
	//func to read into buffer
	FILE *p = NULL;
	fopen_s(&p, link, "r");
	if (p == NULL){
		printf("readinfo failed\nAnykey to exit\n");
		return 1;
	}
	memset(map, 0, sizeof(int)*width*height);
	fread(map,  sizeof(int), height*width , p);
	
	fclose(p);
	return 0;
}

int game::mapPlay(char* abc, int hp, int lev){

	if (readInfo(abc)){
		_getch();//if failed read£¬-1
		return -1;
	}
	draw.printFrame();
	readInToMap();
	//input to vars
	tank tk(map, 1, tankX, tankY);
	tk.hp = hp;
	level = lev;
	tk.writeTank();
	/*for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++){
			if (map[j][i]>WOOD&&map[j][i]<WOOD+10)
			{
				obs* pobs = new obs({ j, i }, WOOD, map[j][i]-WOOD);
				map[j][i] = WOOD;
				pobs->writeObs();
				Aobs.push_back(pobs);

			}
			else if (map[j][i]==wall)
			{
				HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
				draw.writechar({ j, i }, hStdOut, "¡ö", 0xc);
			}
			else if ((map[j][i] == left || map[j][i] == right || map[j][i] == up || map[j][i] == down)&&map[j-1][i]==ENEMY)
			{
				tank* ptk = new tank(map, 0, j, i);
				ptk->writeTank();
				enetk.push_back(ptk);
			}
			else if (map[j][i] == BASE){
				HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
				draw.writechar({ j, i }, hStdOut, "¡ö", 0xd);
			}
		}
	}*/
	play(tk, enetk, bul, Aobs);
	return tk.hp;
}
void game::readInToMap(){
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++){
			//hp for obs
			if (map[j][i]>WOOD&&map[j][i]<WOOD + 10)
			{
				obs* pobs = new obs({ j, i }, WOOD, map[j][i] - WOOD);
				map[j][i] = WOOD;
				pobs->writeObs();
				Aobs.push_back(pobs);
			}
			else if (map[j][i] == wall)
			{
				//wall
				draw.writechar({ j, i }, hStdOut, "¡ö", 0xc);
			}
			else if (map[j][i]<4&& map[j][i]>0)
			{
				//enemy tank and their hp
				tank* ptk = new tank(map, 0, j, i);
				ptk->hp = map[j][i];
				map[j][i] = up;
				ptk->writeTank();
				enetk.push_back(ptk);
			}
			//print others without operation
			else if (map[j][i] == BASE){
				draw.writechar({ j, i }, hStdOut, "¡ö", 0xd);
			}
			else if (map[j][i] == RIVER){
				draw.writechar({ j, i }, hStdOut, "¢£", 0x9);
			}
			else if (map[j][i] == IRON){
				draw.writechar({ j, i }, hStdOut, "¡ö", 0xc);
			}
			else if (map[j][i] == GRASS){
				draw.writechar({ j, i }, hStdOut, "¢£", 0xa);
			}
		}
	}
}
int game::mapMode(){
	//input by user
	draw.clearScreen();
	char abc[100];
	cout << "input file name: " << endl;
	cin >> abc;

	return mapPlay(abc);
}
int game::twoPlayerMode(){
	
	draw.clearScreen();
	char abc[100];
	cout << "input file name: " << endl;
	cin >> abc;
	if (readInfo(abc)){
		_getch();
		return -1;
	}
	draw.printFrame();
	readInToMap();
	tank tk(map, 1, tankX, tankY);
	tk.writeTank();
	tk.hp = 4;
	tank tk2(map, 1, 2*tankX, tankY);
	tk2.inputTank();
	tk2.writeTank();//create object
	draw.referenceInfo(tk.hp, mark, level);//start to prompt
	play2(tk, tk2, enetk, bul, Aobs);
	return tk.hp;
}
void game::play(tank &tk, vector<tank*> enetk, vector<bullet*>& bul, vector<obs*>& Aobs){
	draw.referenceInfo(tk.hp, mark,level);
	while (true)
	{
		clock_t now = clock();//timer
		for (int i = 0; i < enetk.size(); i++)
		{
			enetk[i]->randomMove(bul);//move tank
		}
		Cdraw draw;
		int a = draw.getSign();//receive key events
		if (a == up || a == down || a == left || a == right){
			tk.dir = a;
			tk.move();
		}
		else if (a == shoot&&now - tk.time > 2 * bulletSpeed){
			tk.addBullet(bul);
			tk.time = now;
		}
		else if (a == PAUSE){
			char b;
			do
			{
				b = _getch();
			} while (b != 'p'&&b!='b');
			if (b == 'b')
			{
				save(tk, enetk, bul, Aobs, now, "save");
				return;
			}

		}
		if (allBullets(bul, enetk, tk, Aobs)) break;//move bullets, end game if return true
	}

}
void game::play2(tank &tk, tank &tk2, vector<tank*> enetk, vector<bullet*>& bul, vector<obs*>& Aobs){
	while (true)
	{//simipar to player 1
		clock_t now = clock();
		for (int i = 0; i < enetk.size(); i++)
		{
			enetk[i]->randomMove(bul);
		}
		Cdraw draw;
		int a = draw.getSign();
		if (a == up || a == down || a == left || a == right){
			tk.dir = a;
			tk.move();
		}
		else if (a == shoot&&now - tk.time > 2 * bulletSpeed){
			tk.addBullet(bul);
			tk.time = now;
		}
		else if (a == up2 || a == down2 || a == left2|| a == right2 ){
			tk2.dir = a / 3;//additional check for 2nd player
			tk2.move();
		}
		else if (a == shoot2&&now - tk2.time > 2 * bulletSpeed){
			tk2.addBullet(bul);
			tk2.time = now;
		}

		if (allBullets(bul, enetk, tk, Aobs)) break;
	}
	
}
int game::continuePlay(){
	draw.clearScreen();
	char abc[100];
	cout << "input file name: " << endl;
	cin >> abc;

	tank tk(map, 1, tankX, tankY);
	clock_t now;
	if (read(tk,now,abc)){
		_getch();
		return -1;
	}
	draw.printFrame();
	tk.writeTank();
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < enetk.size(); i++)
	{
		enetk[i]->writeTank();
	}
	for (int i = 0; i < Aobs.size(); i++)
	{
		Aobs[i]->writeObs();
	}
	for (int i = 0; i < bul.size(); i++)
	{
		if (bul[i]->previous == GRASS){
			draw.writechar(bul[i]->pos, out, "¡ï", bul[i]->player ? 0xf : 0xe);
		}
		else
		{
			draw.writechar(bul[i]->pos, out, "¡ï", bul[i]->player ? 0xf : 0xe);
		}
	}
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++){
			if (map[x][y]==GRASS)
			{
				draw.writechar({ x, y }, out, "¢£", 0xa);
			}
			else if (map[x][y] == RIVER){
				draw.writechar({ x, y }, out, "¢£", 0x9);
			}
		}
	}
	play(tk, enetk, bul, Aobs);
	return tk.hp;
}
void game::save(tank &tk, vector<tank*> enetk, vector<bullet*>& bul, vector<obs*>& Aobs, clock_t& timer, char link[]){
	FILE *p = NULL;
	fopen_s(&p, link, "w");

	if (p == NULL){
		printf("readinfo failed");
		return;
	}
	
	fwrite(map, sizeof(int), width*height, p);
	int a = enetk.size();
	fwrite(&a, sizeof(int), 1, p);
	for (int i = 0; i < enetk.size(); i++)
	{
		fwrite(enetk[i], sizeof(tank), 1, p);
		delete enetk[i];
	}
	a = bul.size();
	fwrite(&a, sizeof(int), 1, p);
	for (int i = 0; i < bul.size(); i++)
	{
		fwrite(bul[i], sizeof(bullet), 1, p);
		delete bul[i];
	}
	a = Aobs.size();
	fwrite(&a, sizeof(int), 1, p);
	for (int i = 0; i < Aobs.size(); i++)
	{
		fwrite(Aobs[i], sizeof(obs), 1, p);
		delete Aobs[i];
	}
	fwrite(&tk, sizeof(tank), 1, p);
	fwrite(&timer, sizeof(clock_t), 1, p);
	//write
	fclose(p);
}

bool game::read(tank &tk, clock_t& timer, char link[]){
	FILE *p = NULL;
	fopen_s(&p, link, "r");
	if (p == NULL){
		printf("readinfo failed\nAnykey to exit\n");
		return 0;
	}
	memset(map, 0, sizeof(int)*width*height);
	fread(map, sizeof(int), height*width, p);
	int a = 0;
	fread(&a, sizeof(int), 1, p);
	enetk.resize(a);
	for (int i = 0; i < enetk.size(); i++)
	{
		enetk[i] = new tank(tk);
		fread(enetk[i], sizeof(tank), 1, p);
	}
	fread(&a, sizeof(int), 1, p);
	bul.resize(a);
	for (int i = 0; i < bul.size(); i++)
	{
		bul[i] = new bullet(map, 1, 2, 2);
		fread(bul[i], sizeof(bullet), 1, p);
	}
	fread(&a, sizeof(int), 1, p);
	Aobs.resize(a); 
	for (int i = 0; i < Aobs.size(); i++)
	{
		Aobs[i] = new obs({ 1, 1 },100,3);
		fread(Aobs[i], sizeof(obs), 1, p);
	}
	fread(&tk, sizeof(tank), 1, p);
	fread(&timer, sizeof(clock_t), 1, p);
	fclose(p);
}
game::~game()
{
}
