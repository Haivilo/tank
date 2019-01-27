#include "Cmap.h"

Cdraw Cmap::draw;
Cmap::Cmap(int(*mm)[height]) :map(mm)
{
}


Cmap::~Cmap()
{
}
void Cmap::createMap(){
	//init
	draw.printFrame();//create border
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			if (i == width - 1 || i == 0 || j == 0 || j == height - 1){
				map[i][j] = wall;
				COORD pt = { i, j };//determine if it is space or wall
				Cmap:: draw.writechar(pt, hStdOut, "¡ö", 0xc);
			}
			else
			{
				map[i][j] = space;
			}

		}
	}
}

void Cmap::save(char* link){
	
	FILE *p = NULL;
	fopen_s(&p, link, "w");

	if (p == NULL){
		printf("readinfo failed");
		return;
	}
	fwrite(map, sizeof(int), width*height, p);
	
	fclose(p);


}
void Cmap::editMap(){
	char a = 0;
	draw.edittingMapPrompt();//hint 
	tank tk(map, 1, tankX,tankY);
	tk.writeTank();
	tk.inputTank();
	tank tk2(map, 1, tankX*2,tankY);
	tk2.writeTank();
	tk2.inputTank();//print tank on the map so that pos could not be drawn.

	while (true)
	{
		HANDLE hstdin = GetStdHandle(STD_INPUT_HANDLE);
		HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
		INPUT_RECORD stc = { 0 };
		DWORD dwread;
		SetConsoleMode(hstdin, ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);
		ReadConsoleInput(hstdin, &stc, 1, &dwread);
		if (stc.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED){//left click
			int x = stc.Event.MouseEvent.dwMousePosition.X / 2;
			int y = stc.Event.MouseEvent.dwMousePosition.Y;//save pos
			if (x<width - 1 &&y<height - 1 &&x>0 && y >0)//check if out of border
			{
				if (map[x][y] == space)
				{
					if (a > '0'&&a < 10 + '0' || a == 'b'){//obstacles
						Cmap::draw.writechar({ x, y }, hstdout, "¡ö", a != 'b' ? 0xc - a + '0' : 0xd);
						a != 'b' ? map[x][y] = WOOD + a - '0' : map[x][y] = BASE;
					}
					else if (a=='r'){//river
						map[x][y] = RIVER;
						draw.writechar({ x, y }, hstdout, "¢£", 0x9);
					}

					else if (a > 's'&&a<'w')
					{//tank with hp
						tank tk(map, 0, x, y);
						bool covered = 1;
						//tk.dir = up;
						tk.createAry();
						for (int i = 0; i < 8; i++)
						{
							if (map[tk.tkAry[i].X][tk.tkAry[i].Y] != space){
								covered = 0;//make sure tank is on space
							}
						}
						if (covered)//if space
						{
							tk.inputTank();
							tk.hp = a - 's';
							tk.writeTank();
							map[tk.tkAry[4].X][tk.tkAry[4].Y] = tk.hp;
						}
					}
					else if (a == 'i'){//iron
						map[x][y] = IRON;
						draw.writechar({ x, y }, hstdout, "¡ö", 0xc);
					}
					else if (a == 'g'){//grass
						map[x][y] = GRASS;
						draw.writechar({ x, y }, hstdout, "¢£", 0xa);
					}
				}
				else if (a=='c')//erase
				{
					if (map[x][y] > 0 && map[x][y] < 4)
					{//if enemy

						draw.writeSpace({ x, y }, map, hstdout);
						draw.writeSpace({ x - 1, y }, map, hstdout);
						draw.writeSpace({ x + 1, y }, map, hstdout);
						draw.writeSpace({ x - 1, y - 1 }, map, hstdout);
						draw.writeSpace({ x, y - 1 }, map, hstdout);
						draw.writeSpace({ x + 1, y - 1 }, map, hstdout);
						draw.writeSpace({ x - 1, y + 1 }, map, hstdout);
						draw.writeSpace({ x, y + 1 }, map, hstdout);
						draw.writeSpace({ x + 1, y + 1 }, map, hstdout);

					}
					else if (map[x][y] != ENEMY&&map[x][y] != TANK&&map[x][y] != up)
					{//if not tank
						draw.writeSpace({ x, y }, map, hstdout);
					}
				}
				
			}
		}
		else if (stc.EventType == KEY_EVENT&&stc.Event.KeyEvent.bKeyDown)
		{//keyborad event
		
			char temp  = stc.Event.KeyEvent.uChar.AsciiChar;
			if (temp - '0'< 10 && temp - '0'>0 || temp == 't' || temp == 'b' || temp == 'r' || temp == 'i' || temp == 'g' || temp == 'c' || temp > 's'&&temp<'w')
			{//input OK
				a = temp;
			}
			else if (temp == 'q'){//quit
				tk2.cleanTank();
				break;
			}
		
		}

	}
	draw.clearScreen();
	char abc[100];
	cout << "input file name: "<<endl;
	cin >> abc;
	save(abc);

}