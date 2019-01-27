#include "bullet.h"


bullet::bullet(int(*map)[height], const bool z, int x, int y) :basic(x, y, z, map)
{

}


bullet::~bullet()
{
}
void bullet::moveBullet(){
	switch (dir)
	{
	case up:pos.Y -= 1;  break;
	case down:pos.Y += 1; break;
	case left:pos.X -= 1;  break;
	case right:pos.X += 1; break;
	default:
		break;
	}

}
void bullet::moveBulletOut(){
	clock_t current = clock();
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	if (current - time > bulletSpeed || map[pos.X][pos.Y] == TANK || map[pos.X][pos.Y] == ENEMY){
		//if frequency is slow enough or first time shot
		 time = current;

		// if (map[pos.X][pos.Y] != TANK && map[pos.X][pos.Y] != ENEMY&&!previous)
		//	
		//{
		//	draw.writeSpace(pos, map, out);
		//}
		 
		 switch (previous)
		 {//determine previous unit type to recover the original image.
		 case RIVER:
			 map[pos.X][pos.Y] = RIVER;
			 draw.writechar(pos, out, "¢£", 0x9);
			 break;
		 case GRASS:
			 map[pos.X][pos.Y] = GRASS;
			 draw.writechar(pos, out, "¢£", 0xa);
			 break;
		 case space: draw.writeSpace(pos, map, out);
			 break;
		 default:
			 break;
		 }

		moveBullet();
		
		switch (map[pos.X][pos.Y])
		{//check collision, if so change direction to a special type, to record collision target
		case wall:
			 dir = wall; break;
		case TANK:
			 dir = TANK;
			break;
		case ENEMY:
			 dir = ENEMY; break;
		case WOOD:
			 dir = WOOD; break;
		case BASE:
			 dir = BASE; break;	
		case IRON:
			dir = IRON; break;
		case BULLET:
			dir = BULLET; break;
		case GRASSENEMY:
			dir = GRASSENEMY; break;
		case GRASSTANK:
			dir = GRASSTANK; break;
		case RIVER:
			draw.writechar(pos, out, "¡ï", player ? 0xf : 0xe);
			map[pos.X][pos.Y] = BULLET;
			previous = RIVER;
			break;
		case space: 
			draw.writechar(pos, out, "¡ï",  player ? 0xf : 0xe);
			map[pos.X][pos.Y] = BULLET;
			previous = space;
			break;
		case GRASS:
			map[pos.X][pos.Y] = BULLET;
			draw.writechar(pos, out, "¡î", player ? 0xf : 0xe);
			previous = GRASS;
			break;
			//dir won't change if running on river, grass or space
		default:
			break;
		}
	}
}

