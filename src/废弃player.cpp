#include"player.h"

void initplayer(Player* p1)
{
	p1->x = 20; p1->y = 1; p1->blood = 150; p1->dir = 's'; p1->bullet = BUNUMS;
	p1->show_x = p1->show_y = 0;
	p1->speed = 0.7;
	p1->view = 0;
	p1->invincible = false;
}