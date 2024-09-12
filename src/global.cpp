#include "global.h"
#include <graphics.h>
#include <cstdio>
Player p;
vector<Bullet> bulls;
vector<Monster> mons;
vector<Props> pros;

TimerClock t1, t2, t3, t4, t6, t5; // 时间变量_计时器
IMAGE character[8];
IMAGE wall;
IMAGE road;
IMAGE bullet[2];
IMAGE monster[2];
IMAGE mask0;
IMAGE mask4;
IMAGE menu_face;
IMAGE pblood[2];
IMAGE pbullet[2];
IMAGE photo[2];
IMAGE view[2];

int flag = 1;		// 控制全局音乐
int menu_music = 0; // 控制菜单音乐

char map[22][22] = {
	'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
	'1', '0', '0', '0', '0', '0', '0', '0', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '1',
	'1', '0', '1', '1', '1', '1', '1', '0', '1', '0', '0', '1', '1', '1', '0', '1', '1', '1', '1', '1', '0', '1',
	'1', '0', '1', '0', '1', '0', '0', '0', '1', '1', '0', '1', '0', '1', '0', '0', '0', '0', '0', '0', '0', '1',
	'1', '0', '1', '0', '1', '1', '1', '0', '0', '1', '0', '1', '0', '1', '1', '1', '1', '1', '0', '1', '1', '1',
	'1', '0', '1', '0', '1', '0', '1', '1', '0', '1', '0', '1', '0', '0', '0', '0', '0', '1', '0', '0', '0', '1',
	'1', '0', '1', '0', '0', '0', '0', '1', '0', '1', '0', '1', '1', '1', '1', '1', '0', '1', '1', '1', '0', '1',
	'1', '0', '1', '1', '1', '1', '0', '1', '0', '1', '0', '1', '0', '0', '0', '1', '0', '1', '0', '0', '0', '1',
	'1', '0', '0', '0', '0', '1', '0', '1', '0', '1', '0', '0', '0', '1', '0', '1', '0', '1', '1', '1', '1', '1',
	'1', '0', '1', '1', '1', '1', '0', '1', '1', '1', '1', '1', '1', '1', '0', '1', '0', '0', '0', '1', '0', '1',
	'1', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '1', '1', '1', '0', '1',
	'1', '0', '1', '1', '1', '0', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1', '0', '1', '0', '0', '0', '1',
	'1', '0', '1', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '1', '0', '1', '1', '1',
	'1', '0', '1', '0', '1', '0', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1', '0', '0', '0', '1', '0', '1',
	'1', '0', '0', '0', '1', '0', '0', '0', '0', '1', '0', '0', '0', '1', '0', '1', '1', '1', '0', '1', '0', '1',
	'1', '0', '1', '0', '1', '1', '1', '1', '0', '1', '1', '1', '0', '0', '0', '0', '0', '1', '0', '1', '0', '1',
	'1', '0', '1', '0', '0', '0', '0', '1', '0', '0', '0', '1', '0', '1', '1', '1', '0', '0', '0', '1', '0', '1',
	'1', '1', '1', '1', '0', '1', '1', '1', '1', '1', '1', '1', '0', '1', '0', '1', '0', '1', '1', '1', '0', '1',
	'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '1', '0', '1', '0', '1', '0', '0', '0', '1',
	'1', '1', '1', '1', '0', '1', '1', '1', '1', '1', '1', '1', '0', '1', '0', '1', '1', '1', '0', '1', '1', '1',
	'0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1',
	'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'};

// 菜单界面
void loadimage1()
{
	for (int i = 1; i <= 8; ++i)
	{
		char s[20];
		sprintf_s(s, "./res/man/%d.png", i, 19);
		loadimage(&character[i - 1], s, SIZE, SIZE);
	}
	loadimage(&menu_face, "./res/img/menu.jpg");
	loadimage(&wall, "./res/img/walk.png", SIZE, SIZE);
	loadimage(&road, "./res/img/floor.png", SIZE, SIZE);
	loadimage(&monster[1], "./res/img/monster1.png", SIZE, SIZE);
	loadimage(&monster[0], "./res/img/monster2.png", SIZE, SIZE);
	loadimage(&bullet[1], "./res/img/子弹1.png", SIZE, SIZE);
	loadimage(&bullet[0], "./res/img/子弹2.png", SIZE, SIZE);
	loadimage(&mask0, "./res/img/z0.png", width, height);
	loadimage(&mask4, "./res/img/z4.png", width, height);
	loadimage(&pbullet[1], "./res/img/弹药1.png", SIZE, SIZE);
	loadimage(&pbullet[0], "./res/img/弹药2.png", SIZE, SIZE);
	loadimage(&pblood[1], "./res/img/血包1.png", SIZE, SIZE);
	loadimage(&pblood[0], "./res/img/血包2.png", SIZE, SIZE);
	loadimage(&view[1], "./res/img/视野1.png", SIZE, SIZE);
	loadimage(&view[0], "./res/img/视野2.png", SIZE, SIZE);
	loadimage(&photo[1], "./res/img/惊喜1.png", SIZE, SIZE);
	loadimage(&photo[0], "./res/img/惊喜2.png", SIZE, SIZE);
}

// 函数功能:清屏, 打印菜单界面:包括开始游戏, 游戏设置, 游戏介绍, 退出游戏,并且返回点击结果
int Menu(void)
{
	setbkcolor(BLACK);
	cleardevice(); // 清屏
	ExMessage m;
	putimage(0, 0, &menu_face); // 加载背景图片
	if (flag == 1)
	{
		if (menu_music == 0)
		{
			setmusic(0);
			setmusic(1); // 这里是菜单背景音乐，如果flag是1的话则播放菜单背景音乐
		}
	}
	while (true)
	{
		m = getmessage(EX_MOUSE);
		switch (m.message)
		{
		case WM_LBUTTONDOWN:

			if (m.x > 150 && m.x < 450 && m.y > 250 && m.y < 350)
				return 2;
			else if (m.x > 150 && m.x < 450 && m.y > 360 && m.y < 460)
				return 3;
			else if (m.x > 150 && m.x < 450 && m.y > 470 && m.y < 570)
				return 4;
			else if (m.x > 150 && m.x < 450 && m.y > 580 && m.y < 690)
				return 5;
			break;
		}
	}
}

// 函数功能:
// 跳出界面 介绍游戏玩法,可通过鼠标点击离开该界面,返回菜单界面
int introduce(void)
{
	setbkcolor(BLACK);
	cleardevice();
	settextcolor(WHITE);
	settextstyle(50, 0, "楷体");
	outtextxy(300, 70, "W上");
	outtextxy(300, 170, "S下");
	outtextxy(200, 170, "A左");
	outtextxy(400, 170, "D右");
	outtextxy(700, 170, "【空格】发射子弹");
	outtextxy(70, 300, "用七发子弹的枪逃离迷宫，地上的道具会帮助你！！！");
	settextcolor(RED);
	outtextxy(200, 450, "【警告】不要被怪物碰到三次【警告】");
	rectangle(600, 550, 700, 600);
	outtextxy(600, 550, "离开");
	ExMessage m; // 定义消息变量
	while (true)
	{
		m = getmessage(EX_MOUSE | EX_KEY);

		switch (m.message)
		{
		case WM_LBUTTONDOWN:
			if (m.x > 600 && m.x < 700 && m.y > 550 && m.y < 600)
				return 1;
			break;
		}
	}
	return 0;
}

// 设置音乐根据不同参数播放音乐
void setmusic(int music_sign)
{
	switch (music_sign)
	{
	case 1:
	{
		menu_music = 1;
		mciSendString("open ./res/sound/菜单背景音乐.mp3", 0, 0, 0);
		mciSendString("play ./res/sound/菜单背景音乐.mp3 repeat", 0, 0, 0);
		break;
	}

	case 0:
	{
		menu_music = 0;
		mciSendString("stop ./res/sound/菜单背景音乐.mp3", 0, 0, 0);
		mciSendString("close ./res/sound/菜单背景音乐.mp3", 0, 0, 0);
		mciSendString("stop  ./res/sound/剧情背景音乐.mp3", 0, 0, 0);
		mciSendString("close ./res/sound/剧情背景音乐.mp3", 0, 0, 0);
		mciSendString("stop ./res/sound/胜利音乐.mp3", 0, 0, 0);
		mciSendString("close ./res/sound/胜利音乐.mp3", 0, 0, 0);
		mciSendString("stop  ./res/sound/游戏背景音乐.mp3", 0, 0, 0);
		mciSendString("close ./res/sound/游戏背景音乐.mp3", 0, 0, 0);
		break;
	}
	case 2:
		mciSendString("open ./res/sound/剧情背景音乐.mp3", 0, 0, 0);
		mciSendString("play ./res/sound/剧情背景音乐.mp3 repeat", 0, 0, 0);
		break;
	case 3:
	{
		mciSendString("open ./res/sound/游戏背景音乐.mp3", 0, 0, 0);
		mciSendString("play ./res/sound/游戏背景音乐.mp3 repeat", 0, 0, 0);
		break;
	}
	case 4:
	{
		mciSendString("open ./res/sound/胜利音乐.mp3", 0, 0, 0);
		mciSendString("play ./res/sound/胜利音乐.mp3 repeat", 0, 0, 0);
		break;
	}
	}
}

// 游戏音乐设置界面按钮
void musicbutton(int x, int y, int w, int h, const char *text)
{
	setbkmode(TRANSPARENT);					   // 设置窗口背景色
	setfillcolor(BROWN);					   // 设置窗口填充色
	fillroundrect(x, y, x + w, y + h, 10, 10); // 设置圆角矩形

	settextstyle(30, 0, "黑体"); // 设置字体

	// 使字体在矩形中间
	int tx = x + (w - textwidth(text)) / 2;
	int ty = y + (h - textheight(text)) / 2;

	outtextxy(tx, ty, text); // 在指定位置输出字符串
}

int setmusicface() // 游戏音乐设置界面
{
	cleardevice(); // 清屏
	IMAGE img;
	loadimage(&img, "111.jpg");
	putimage(0, -250, &img);

	musicbutton(550, 300, 150, 50, "开启音乐");
	musicbutton(550, 400, 150, 50, "关闭音乐");
	musicbutton(550, 500, 150, 50, "返回菜单");

	ExMessage msg;
	while (1)
	{
		if (peekmessage(&msg, EM_MOUSE))
		{
			switch (msg.message)
			{
			case WM_LBUTTONDOWN:												  // 左键点击
				if (msg.x >= 550 && msg.x <= 700 && msg.y >= 300 && msg.y <= 350) // 开启音乐
				{
					flag = 1;
					setmusic(0);
					setmusic(1);
				}

				if (msg.x >= 550 && msg.x <= 700 && msg.y >= 400 && msg.y <= 450) // 关闭音乐
				{
					flag = 0;
					setmusic(0);
				}
				if (msg.x >= 550 && msg.x <= 700 && msg.y >= 500 && msg.y <= 550) // 返回菜单
				{
					return 1;
				}
				break;
			}
		}
	}
}

int deadface() // 死亡界面
{

	cleardevice();
	time_t start_t, end_t;
	double diff_t = 0.0;
	double a = 5.0;
	time(&start_t);
	if (flag == 1)
	{
		setmusic(0); // 这里是处理游戏背景音乐，如果有音乐的话先关掉音乐先再播放尖叫声
	}
	mciSendString("close 尖叫", 0, 0, 0);
	mciSendString("open ./res/sound/尖叫声.mp3 alias 尖叫", 0, 0, 0); // 把音乐地址放入
	mciSendString("play 尖叫", 0, 0, 0);
	IMAGE img;
	loadimage(&img, "./res/img/女鬼.png", 1300, 760); // 加入恐怖图片
	putimage(0, 0, &img);

	for (a; diff_t < a;)
	{
		time(&end_t);
		diff_t = difftime(end_t, start_t);
	}
	mciSendString("close 尖叫", 0, 0, 0);
	cleardevice();
	loadimage(&img, "./res/img/qaz.jpg"); // 加入失败界面
	putimage(0, 0, &img);
	ExMessage m;

	while (true)
	{
		m = getmessage(EX_MOUSE | EX_KEY);
		switch (m.message)
		{

		case WM_LBUTTONDOWN:

			if ((522 < m.x) && (m.x < 764) && (518 < m.y) && (m.y < 607))
			{

				return 2;
				break;
			}
			if ((522 < m.x) && (m.x < 764) && (639 < m.y) && (m.y < 719))
			{
				return 1;
				break;
			}
		}
	}
}

void winbutton(int x, int y, int w, int h, const char *text) // 游戏胜利界面按钮

{
	setbkmode(TRANSPARENT);					 // 去除文字的黑色背景
	setfillcolor(BROWN);					 // 图框的颜色
	fillroundrect(x, y, x + w, y + h, 5, 5); // 图框的形状和大小
	settextstyle(30, 0, "黑体");			 // 字体
	char word1[50] = {" text"};
	// 使文字居中
	strcpy_s(word1, text);
	int tx1 = x + (w - textwidth(text)) / 2;
	int ty1 = y + (h - textheight(text)) / 2;
	outtextxy(tx1, ty1, text);
}

int winface(void) // 游戏胜利界面

{
	IMAGE img;
	cleardevice();
	loadimage(&img, "./res/img/通关画面.jpg", 1300, 760);
	putimage(0, 0, &img);
	winbutton(1000, 580, 200, 70, "返回菜单");
	winbutton(150, 580, 200, 70, "重新开始");
	if (flag == 1)
	{
		setmusic(0); // 这里是胜利音乐，如果flag是1的话则播放胜利音乐
		setmusic(4);
	}
	// 判断玩家鼠标选择
	ExMessage msg;
	while (true)
	{
		if (peekmessage(&msg, EM_MOUSE))
		{
			switch (msg.message)
			{
			case WM_LBUTTONDOWN:
				if (msg.x > 150 && msg.x < 150 + 200 && msg.y > 580 && msg.y < 580 + 70)
				{
					return 2; // 重新开始游戏
				}
				else
				{
					if (msg.x > 1000 && msg.x < 1000 + 200 && msg.y > 580 && msg.y < 580 + 70)
					{
						return 1; // 返回菜单
					}
				}
				break;
			default:
				break;
			}
		}
	}
}

void gamebk() // 游戏故事背景界面
{
	IMAGE GAMEBK;
	int x, y;
	x = 290;
	y = 500;
	int c = 0;
	setbkcolor(BLACK);
	settextcolor(WHITE);
	settextstyle(20, 0, "宋体");
	loadimage(&GAMEBK, "./res/img/剧情背景.jpeg", 666, 363);
	if (flag == 1)
	{
		setmusic(0); // 这里是剧情背景音乐，如果flag是1则播放剧情背景音乐
		setmusic(2);
	}
	TimerClock t;
	while (1)
	{
		if (GetAsyncKeyState(VK_ESCAPE))
		{
			break;
		}
		BeginBatchDraw();
		cleardevice();
		outtextxy(x, y, "铁蛋是一个普通的社畜，一天晚上，在回家途中，看见一位老人躺在地上，铁蛋上");
		outtextxy(x, y + 20, "去扶起老人。");
		outtextxy(x, y + 40, "铁蛋：老人家，你没事吧，我帮你打120.");
		outtextxy(x, y + 60, "老头：我没事。小伙子，你能送我回家吗？我家里有药。");
		outtextxy(x, y + 80, "于是，铁蛋将老人送回了家。");
		outtextxy(x, y + 100, "老头：药在地下室，小伙子陪我去拿药好吗？");
		outtextxy(x, y + 120, "来到地下室，老头走进一个小房间，找着什么东西。时间一分一秒的过去，铁蛋感");
		outtextxy(x, y + 140, "到很无聊，于是就拿起旁边的一张报纸读了起来……");
		outtextxy(x, y + 160, "铁蛋：疯狂科学家？生化实验？难道这个地下室真的是……?");
		outtextxy(x, y + 180, "就在铁蛋思考期间，老头已经出现在铁蛋身后，手中的铁棒将铁蛋打晕了过去。");
		outtextxy(x, y + 200, "……");
		outtextxy(x, y + 220, "铁蛋睁开眼睛，发现自己被捆在乐椅子上，老头正在手术台边调整工具。");
		outtextxy(x, y + 240, "铁蛋：你在做什么？快……快放开我!");
		outtextxy(x, y + 260, "老头：桀桀桀，给我老实点，不然我现在就把你的嘴缝上……我的外卖到了，等我");
		outtextxy(x, y + 280, "出去拿个外卖。");
		outtextxy(x, y + 300, "老头离开了地下室，铁蛋环顾四周，发现地上掉落了一把手术刀，于是，铁蛋模仿");
		outtextxy(x, y + 320, "着电影中的情景，用刀割开了绳子。在货架上寻找着有用的东西，很快铁蛋找到了");
		outtextxy(x, y + 340, "一把枪和一个手电筒，正当他准备离开时，老头回来了。");
		outtextxy(x, y + 360, "老头：想跑？没这么容易！看我废了你！");
		outtextxy(x, y + 380, "只见老头拿起大砍刀就向铁蛋砍来。铁蛋很快冷静下来，对着老头的腿打了一枪，");
		outtextxy(x, y + 400, "老头倒下，铁蛋大步向出口跑去。老头爬到墙边，按下了牢房的控制按钮，顿时地");
		outtextxy(x, y + 420, "下室的牢房被打开了，怪物们冲了出来。");
		outtextxy(x, y + 440, "怪物：吼吼~！");
		outtextxy(x, y + 460, "……");
		putimage(330, y + 500, &GAMEBK); // 调用图片
		EndBatchDraw();
		y -= 0.8;
		while (t.getMilliSec() < 10)
			;
		t.update();
		c++;
		if (c == 3450)
		{
			outtextxy(520, 690, "――――按ESC进入游戏――――");
			while (1)
			{
				if (GetAsyncKeyState(VK_ESCAPE))
				{
					break;
				}
			}
			break;
		}
	}
}

void input() // 输入
{
	if (GetAsyncKeyState('A') & 0x8000 || GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		p.dir = 'a';
		p.show_x -= p.speed;
	}
	if (GetAsyncKeyState('D') & 0x8000 || GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		p.show_x += p.speed;
		p.dir = 'd';
	}
	if (GetAsyncKeyState('W') & 0x8000 || GetAsyncKeyState(VK_UP) & 0x8000)
	{
		p.show_y -= p.speed;
		p.dir = 'w';
	}
	if (GetAsyncKeyState('S') & 0x8000 || GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		p.show_y += p.speed;
		p.dir = 's';
	}
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		if (t1.getMilliSec() > 1000) // 发射子弹时间间隔
		{

			if (p.bullet > 0)
			{
				if (flag == 1)
				{
					mciSendString("close ./res/sound/手枪.mp3", 0, 0, 0);
					mciSendString("open ./res/sound/手枪.mp3", 0, 0, 0);
					mciSendString("play ./res/sound/手枪.mp3", 0, 0, 0);
				}
				struct Bullet b;
				b.dir = p.dir;
				b.x = p.x;
				b.y = p.y;
				b.power = 50;
				b.speed = 10;
				b.show_x = b.show_y = 0;
				bulls.push_back(b);
				p.bullet--;
				t1.update();
			}
			else
			{
				if (flag == 1)
				{
					mciSendString("close ./res/sound/弹药耗尽.mp3", 0, 0, 0);
					mciSendString("open ./res/sound/弹药耗尽.mp3", 0, 0, 0);
					mciSendString("play ./res/sound/弹药耗尽.mp3", 0, 0, 0);
				}
			}
		}
	}
}

void move()
{
	char move_map[H][W];
	memcpy(move_map, map, sizeof(char) * H * W);
	vector<pair<int, int>> v;
	v.push_back(make_pair(p.x, p.y));
	while (v.size() != 0)
	{
		int x = v[0].first, y = v[0].second;
		v.erase(v.begin());
		if (move_map[y][x + 1] == '0')
		{
			move_map[y][x + 1] = 'a';
			v.push_back(make_pair(x + 1, y));
		}
		if (move_map[y][x - 1] == '0')
		{
			move_map[y][x - 1] = 'd';
			v.push_back(make_pair(x - 1, y));
		}
		if (move_map[y + 1][x] == '0')
		{
			move_map[y + 1][x] = 'w';
			v.push_back(make_pair(x, y + 1));
		}
		if (move_map[y - 1][x] == '0')
		{
			move_map[y - 1][x] = 's';
			v.push_back(make_pair(x, y - 1));
		}
	}
	int x = 0;
	if (t3.getMilliSec() > 2000) // 怪物移动方向更改
	{
		x = 1;
		t3.update();
	}
	for (int i = 0; i < mons.size(); ++i)
	{
		if ((p.x - mons[i].x) * (p.x - mons[i].x) + (p.y - mons[i].y) * (p.y - mons[i].y) < 18)
		{
			switch (move_map[mons[i].y][mons[i].x])
			{
			case 'w':
				mons[i].show_y -= mons[i].speed;
				break;
			case 's':
				mons[i].show_y += mons[i].speed;
				break;
			case 'a':
				mons[i].show_x -= mons[i].speed;
				break;
			case 'd':
				mons[i].show_x += mons[i].speed;
				break;
			}
		}
		else
		{
			if (x)
			{
				vector<char> arr;
				if (map[mons[i].y][mons[i].x + 1] == '0')
					arr.push_back('d');
				if (map[mons[i].y][mons[i].x - 1] == '0')
					arr.push_back('a');
				if (map[mons[i].y + 1][mons[i].x] == '0')
					arr.push_back('s');
				if (map[mons[i].y - 1][mons[i].x] == '0')
					arr.push_back('w');
				mons[i].dir = arr[rand() % arr.size()];
			}
			switch (mons[i].dir)
			{
			case 'w':
				mons[i].show_y -= mons[i].speed;
				break;
			case 's':
				mons[i].show_y += mons[i].speed;
				break;
			case 'a':
				mons[i].show_x -= mons[i].speed;
				break;
			case 'd':
				mons[i].show_x += mons[i].speed;
				break;
			}
		}
		if (p.x == mons[i].x && p.y == mons[i].y && p.invincible == false)
		{
			p.blood -= mons[i].power;
			if (flag == 1)
			{
				mciSendString("close ./res/sound/受击.mp3", 0, 0, 0);
				mciSendString("open ./res/sound/受击.mp3", 0, 0, 0);
				mciSendString("play ./res/sound/受击.mp3", 0, 0, 0);
			}
			t4.update();
			p.invincible = true;
		}
	}
}

void show_photo(void)
{
	if (flag == 1)
	{
		mciSendString("close 尖叫", 0, 0, 0);
		mciSendString("open ./res/sound/尖叫声.mp3 alias 尖叫", 0, 0, 0); // 把音乐地址放入
		mciSendString("play 尖叫", 0, 0, 0);
	}
	IMAGE img;
	loadimage(&img, "./res/img/道具_照片.jpg", 1300, 760); // 加入恐怖图片
	putimage(0, 0, &img);
	t5.update();
	while (t5.getMilliSec() < 2500)
		;
}

void is_getprops(void)
{
	for (int i = 0; i < pros.size(); i++)
	{
		if (pros[i].x == p.x && p.y == pros[i].y)
		{
			switch (pros[i].sign)
			{
			case 0:
				p.bullet += BUNUMS;
				break;
			case 1:
				p.blood += 2;
				break;
			case 2:
				p.view = 4;
				break;
			case 3:
				show_photo();
				break;
			}
			pros.erase(pros.begin() + i--);
		}
	}
}

void initprops(int x, int y, int sign)
{
	Props pr;
	pr.x = x;
	pr.y = y;
	pr.sign = sign;
	pros.push_back(pr);
}

void initmonster(int x, int y)
{
	Monster m;
	m.x = x;
	m.y = y;
	m.blood = 150;
	m.power = 50;
	m.show_x = m.show_y = 0;
	m.speed = 0.6;
	mons.push_back(m);
}

void change_show()
{
	double w = SIZE / 5;
	double h = SIZE / 2.5;
	double x = p.x * SIZE + p.show_x + SIZE / 2;
	double y = p.y * SIZE + p.show_y + SIZE / 2;
	if (is_wall(x - w, y - h))
	{
		p.show_x += p.speed;
		p.show_y += p.speed;
	}
	if (is_wall(x - w, y + h))
	{
		p.show_x += p.speed;
		p.show_y -= p.speed;
	}
	if (is_wall(x + w, y - h))
	{
		p.show_x -= p.speed;
		p.show_y += p.speed;
	}
	if (is_wall(x + w, y + h))
	{
		p.show_x -= p.speed;
		p.show_y -= p.speed;
	}
	if (p.show_x > SIZE / 2)
	{
		p.show_x = -SIZE / 2;
		p.x++;
	}
	if (p.show_x < -SIZE / 2)
	{
		p.show_x = SIZE / 2;
		p.x--;
	}
	if (p.show_y > SIZE / 2)
	{
		p.show_y = -SIZE / 2;
		p.y++;
	}
	if (p.show_y < -SIZE / 2)
	{
		p.show_y = SIZE / 2;
		p.y--;
	}

	for (int i = 0; i < mons.size(); ++i)
	{
		w = SIZE / 2.2;
		h = SIZE / 2.2;
		x = mons[i].x * SIZE + mons[i].show_x + SIZE / 2;
		y = mons[i].y * SIZE + mons[i].show_y + SIZE / 2;
		if (is_wall(x - w, y - h))
		{
			mons[i].show_x += mons[i].speed;
			mons[i].show_y += mons[i].speed;
		}
		if (is_wall(x - w, y + h))
		{
			mons[i].show_x += mons[i].speed;
			mons[i].show_y -= mons[i].speed;
		}
		if (is_wall(x + w, y - h))
		{
			mons[i].show_x -= mons[i].speed;
			mons[i].show_y += mons[i].speed;
		}
		if (is_wall(x + w, y + h))
		{
			mons[i].show_x -= mons[i].speed;
			mons[i].show_y -= mons[i].speed;
		}
		if (mons[i].show_x > SIZE / 2)
		{
			mons[i].show_x = -SIZE / 2;
			mons[i].x++;
		}
		if (mons[i].show_x < -SIZE / 2)
		{
			mons[i].show_x = SIZE / 2;
			mons[i].x--;
		}
		if (mons[i].show_y > SIZE / 2)
		{
			mons[i].show_y = -SIZE / 2;
			mons[i].y++;
		}
		if (mons[i].show_y < -SIZE / 2)
		{
			mons[i].show_y = SIZE / 2;
			mons[i].y--;
		}
	}

	for (int i = 0; i < bulls.size(); ++i)
	{
		if (bulls[i].show_x > SIZE / 2)
		{
			bulls[i].show_x = -SIZE / 2;
			bulls[i].x++;
		}
		if (bulls[i].show_x < -SIZE / 2)
		{
			bulls[i].show_x = SIZE / 2;
			bulls[i].x--;
		}
		if (bulls[i].show_y > SIZE / 2)
		{
			bulls[i].show_y = -SIZE / 2;
			bulls[i].y++;
		}
		if (bulls[i].show_y < -SIZE / 2)
		{
			bulls[i].show_y = SIZE / 2;
			bulls[i].y--;
		}
	}
}

// 判断是否为墙
bool is_wall(double x, double y)
{
	return map[(int)y / SIZE][(int)x / SIZE] - '0';
}

int gameface()
{
	initplayer(&p);
	mons.clear();
	initmonster(20, 10); // 改
	initmonster(3, 9);	 // 改
	initmonster(4, 16);
	initmonster(14, 9);
	initprops(16, 6, 0);  // 子弹
	initprops(3, 3, 1);	  // 血量
	initprops(20, 14, 2); // 视野
	initprops(18, 4, 3);  // 照片x,y坐标
	if (flag == 1)
	{
		setmusic(0);
		setmusic(3);
	}
	while (1)
	{
		change_show();
		is_getprops();
		print();
		if (p.invincible)
		{
			if (t4.getMilliSec() > 2500) // 无敌时间
			{
				p.invincible = false;
				t4.update();
			}
		}

		move();

		if (mons.size() < NUMS) // 怪物复活
		{
			while (1)
			{
				int x = rand() % W;
				int y = rand() % H;
				if (map[y][x] == '0')
				{
					if ((p.x - x) * (p.x - x) + (p.y - y) * (p.y - y) < 25)
					{
						initmonster(x, y);
						break;
					}
				}
			}
		}
		input();
		if (p.x == 0 && p.y == 20)
		{
			int flag = winface();
			if (flag == 1)
			{
				return 1;
			}
			else if (flag == 2)
			{
				return 2;
			}
		}
		if (p.blood <= 0)
		{
			int flag = deadface();
			if (flag == 1)
			{
				return 1;
			}
			else if (flag == 2)
			{
				return 2;
			}
		}
		while (t2.getMilliSec() < 10)
			;
		t2.update();
	}
}

void move_bullet(void)
{
	setfillcolor(BLACK);
	for (int t = 0; t < bulls.size(); t++)
	{
		switch (bulls[t].dir)
		{
		case 'w':
			if (map[bulls[t].y][bulls[t].x] == '0')
				bulls[t].show_y -= bulls[t].speed;
			break;
		case 's':
			if (map[bulls[t].y][bulls[t].x] == '0')
				bulls[t].show_y += bulls[t].speed;
			break;
		case 'a':
			if (map[bulls[t].y][bulls[t].x] == '0')
				bulls[t].show_x -= bulls[t].speed;
			break;
		case 'd':
			if (map[bulls[t].y][bulls[t].x] == '0')
				bulls[t].show_x += bulls[t].speed;
			break;
		}

		int x = 0;
		if (map[bulls[t].y][bulls[t].x] == '0')
		{
			for (int i = 0; i < mons.size(); i++)
			{
				if (mons[i].x == bulls[t].x && mons[i].y == bulls[t].y)
				{
					mons[i].blood -= bulls[t].power;
					x = 1;
					break;
				}
			}
			if (x == 0)
				putimage((bulls[t].x - p.x + X) * SIZE - p.show_x + bulls[t].show_x, (bulls[t].y - p.y + Y) * SIZE - p.show_y + bulls[t].show_y, &bullet[0], SRCAND);
			putimage((bulls[t].x - p.x + X) * SIZE - p.show_x + bulls[t].show_x, (bulls[t].y - p.y + Y) * SIZE - p.show_y + bulls[t].show_y, &bullet[1], SRCPAINT);
		}
		else
		{
			x = 1;
		}
		if (x)
			bulls.erase(bulls.begin() + t--);
	}
}

void print() // 打印地图
{
	BeginBatchDraw();
	setbkcolor(BLACK);
	cleardevice();
	setlinecolor(WHITE);
	for (int i = 0; i < H; i++)
	{
		for (int j = 0; j < W; j++)
		{
			if (map[i][j] == '1')
			{
				// putimage((j - p.x + X) * SIZE, (i - p.y + Y) * SIZE, &wall);
				putimage((j - p.x + X) * SIZE - p.show_x, (i - p.y + Y) * SIZE - p.show_y, &wall);
			}
			if (map[i][j] == '0')
			{
				// putimage((j - p.x + X) * SIZE, (i - p.y + Y) * SIZE, &road);
				putimage((j - p.x + X) * SIZE - p.show_x, (i - p.y + Y) * SIZE - p.show_y, &road);
			}
		}
	}
	move_bullet();
	// putimage(p.x * SIZE, p.y * SIZE, &character);
	switch (p.dir)
	{
	case 'w':
		putimage(X * SIZE, Y * SIZE, SIZE - 1, SIZE - 1, &character[1], 0, 0, SRCAND);
		putimage(X * SIZE, Y * SIZE, SIZE - 1, SIZE - 1, &character[0], 0, 0, SRCPAINT);
		break;
	case 'a':
		putimage(X * SIZE, Y * SIZE, SIZE - 1, SIZE - 1, &character[7], 0, 0, SRCAND);
		putimage(X * SIZE, Y * SIZE, SIZE - 1, SIZE - 1, &character[6], 0, 0, SRCPAINT);
		break;
	case 'd':
		putimage(X * SIZE, Y * SIZE, SIZE - 1, SIZE - 1, &character[5], 0, 0, SRCAND);
		putimage(X * SIZE, Y * SIZE, SIZE - 1, SIZE - 1, &character[4], 0, 0, SRCPAINT);
		break;
	default:
		putimage(X * SIZE, Y * SIZE, SIZE - 1, SIZE - 1, &character[3], 0, 0, SRCAND);
		putimage(X * SIZE, Y * SIZE, SIZE - 1, SIZE - 1, &character[2], 0, 0, SRCPAINT);
		break;
	}

	for (int i = 0; i < mons.size(); ++i)
	{
		if (mons[i].blood > 0)
		{
			putimage((mons[i].x - p.x + X) * SIZE - p.show_x + mons[i].show_x, (mons[i].y - p.y + Y) * SIZE - p.show_y + mons[i].show_y, &monster[0], SRCAND);
			putimage((mons[i].x - p.x + X) * SIZE - p.show_x + mons[i].show_x, (mons[i].y - p.y + Y) * SIZE - p.show_y + mons[i].show_y, &monster[1], SRCPAINT);
		}
		else
			mons.erase(mons.begin() + i--);
	}
	for (int i = 0; i < pros.size(); i++)
	{
		switch (pros[i].sign)
		{
		case 0:
			putimage((pros[i].x - p.x + X) * SIZE - p.show_x, (pros[i].y - p.y + Y) * SIZE - p.show_y, &pbullet[0], SRCAND);
			putimage((pros[i].x - p.x + X) * SIZE - p.show_x, (pros[i].y - p.y + Y) * SIZE - p.show_y, &pbullet[1], SRCPAINT);
			break;
		case 1:
			putimage((pros[i].x - p.x + X) * SIZE - p.show_x, (pros[i].y - p.y + Y) * SIZE - p.show_y, &pblood[0], SRCAND);
			putimage((pros[i].x - p.x + X) * SIZE - p.show_x, (pros[i].y - p.y + Y) * SIZE - p.show_y, &pblood[1], SRCPAINT);
			break;
		case 2:
			putimage((pros[i].x - p.x + X) * SIZE - p.show_x, (pros[i].y - p.y + Y) * SIZE - p.show_y, &view[0], SRCAND);
			putimage((pros[i].x - p.x + X) * SIZE - p.show_x, (pros[i].y - p.y + Y) * SIZE - p.show_y, &view[1], SRCPAINT);
			break;
		case 3:
			putimage((pros[i].x - p.x + X) * SIZE - p.show_x, (pros[i].y - p.y + Y) * SIZE - p.show_y, &photo[0], SRCAND);
			putimage((pros[i].x - p.x + X) * SIZE - p.show_x, (pros[i].y - p.y + Y) * SIZE - p.show_y, &photo[1], SRCPAINT);
			break;
		}
	}
	switch (p.view)
	{
	case 0:
		putimage(0, 0, &mask0, SRCAND);
		break;
	case 4:
		putimage(0, 0, &mask4, SRCAND);
		break;
	}
	EndBatchDraw();
}