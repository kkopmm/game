#pragma once

#define BUNUMS 7

struct Player {
	double show_x;
	double show_y;
	double speed;

	int x; //横坐标
	int y; //纵坐标
	int blood; //玩家血条
	char dir;
	int bullet; //子弹数
	bool invincible;
	int view;  //视野
};

void initplayer(Player* p1);     //初始化玩家