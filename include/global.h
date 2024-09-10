#pragma once
#include<graphics.h>
#include<easyx.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<Windows.h>
#include<mmsystem.h>          //多媒体设备接口头文件
#include<vector>
#include "TimerClock.h"
#include"player.h"
#pragma comment(lib,"winmm.lib")    //加载静态库
using namespace std;

#define width 1300//窗口宽度
#define height 760 //窗口高度
#define W 22  //宽行数 
#define H  22  //高行数 
#define SIZE 100//100  //格子边长
#define X 6
#define Y 3
#define NUMS 4  //怪物数
#define BUNUMS 7 //子弹数


//全局变量
extern char map[22][22];
extern Player p;

struct Bullet {
	double show_x;
	double show_y;
	double speed;

	int x;
	int y;
	char dir;
	int power;
};
struct Monster {
	double show_x;
	double show_y;
	double speed;

	char dir;
	int x;
	int y;
	int blood;
	int power;
};
struct Props {
	int x;
	int y;
	int sign;
};

int Menu(void);  //菜单界面
int introduce(void);      //游戏玩法介绍界面
void setmusic(int music_sign);        //游戏音乐设置函数
void musicbutton(int x, int y, int w, int h, const char* text);    //游戏音乐设置界面按钮
int setmusicface(void);         //游戏音乐设置界面
int deadface(void);       //游戏死亡界面
void winbutton(int x, int y, int w, int h, const char* text);//通关界面按钮
int winface(void);//通关界面
void gamebk(void); //游戏故事背景界面
void loadimage1();   //加载图片资源
void input();                //键盘输入????

void show_photo(void); //播放恐怖照片
void is_getprops(void);      //判断是否get道具
void initprops(int x, int y, int sign);  //初始化道具
void initmonster(int x, int y);  //初始化怪物
void move();
void change_show();          //???????
bool is_wall(double x, double y);       //判断是否为墙

int gameface();
void move_bullet(void);
void print();