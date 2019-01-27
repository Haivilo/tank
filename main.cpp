#include"game.h"

void clearScreen(){
	char gameFrame[100] = { '\0' };
	sprintf_s(gameFrame, 100, "mode con cols=%d lines=%d", 20, 10);
	system(gameFrame);
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, 0xf);
}//clean screen to iniitial size

void showScore(int hp, int score){
	clearScreen();
	hp ? cout << "congrats" : cout << "good luck next time";
	cout << endl;
	cout << "your score: " << score << endl;
	cout << "press y to exit " << score << endl;
	while (_getch() != 'y');
	clearScreen();
}
int main(){
	PlaySoundA("sound\\yaya.wav", NULL, SND_ASYNC | SND_NODEFAULT | SND_LOOP);

	int sign = 0;
	clearScreen();
	while (sign != 7){
		cout << "1. adventure" << endl << "2. 2p" << endl << "3. normal" << endl << "4. read map" << endl << "5. create map" << endl<<"6. read Archive"<<endl;
		cin >> sign;
		cin.clear();
		if (getchar()!='\n')
		{	//wrong input
			while (getchar() != '\n');
			system("cls");
			clearScreen();
			cout << "wrong input"<<endl;
			continue;
		}
		switch (sign)
		{
		case 1:{
			//adventure mod, b is hp 
			game a;
			int b=9;
			int score = 0;
			char* maps[4] = { "2", "3", "4", "5" };
			for (int i = 0; i < 4; i++)
			{
				if (b)//if b = 0, end game
				{
					game a;
					a.mark = score;
					b = a.mapPlay(maps[i], b, i+1);
					score = a.mark;
				}
			}
			showScore(b,score);
			break;
			
			
		}
		case 2:{
			game a;//dual ,mode
			int b = a.twoPlayerMode();
			clearScreen();
			if (b == -1) break;//not success map
			showScore(b, a.mark);
			break;
		}
		case 3:{game a; a.easyGame(); clearScreen(); break; }
		case 4:{game a;
			//choose map
			int b = a.mapMode(); //hp
			clearScreen();
			if (b == -1) break;
			showScore(b, a.mark);
			break; 
		}
		case 5:{int map[width][height]; Cmap mm(map); mm.createMap(); mm.editMap(); clearScreen();  break; }//»­µØÍ¼
		case 6:{
			game a;
			a.continuePlay();
		}
		default:
			clearScreen();
			cout << "wrong input"<<endl;
			break;
		}
	}

}
