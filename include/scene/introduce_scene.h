

#ifndef _INTRODUCE_SCENE_H_
#define _INTRODUCE_SCENE_H_

#include "scene.h"
#include "scene_manager.h"

extern SceneManager *scene_manager;

class IntroduceScene : public Scene
{
public:
    IntroduceScene() = default;
    ~IntroduceScene() = default;

    void on_enter() {};
    void on_exit() {};
    void on_update(float delta) {};
    void on_draw()
    {
        setbkcolor(BLACK);
        settextcolor(WHITE);
        settextstyle(50, 0, _T("楷体"));
        outtextxy(300, 70, _T("W上"));
        outtextxy(300, 170, _T("S下"));
        outtextxy(200, 170, _T("A左"));
        outtextxy(400, 170, _T("D右"));
        outtextxy(700, 170, _T("【空格】发射子弹"));
        outtextxy(700, 70, _T("R奔跑"));
        outtextxy(70, 300, _T("用七发子弹的枪逃离迷宫，地上的道具会帮助你！！！"));
        settextcolor(RED);
        outtextxy(200, 450, _T("【警告】不要被怪物碰到三次【警告】"));
        rectangle(600, 550, 700, 600);
        outtextxy(600, 550, _T("离开"));
    };
    void on_input(const ExMessage &msg)
    {
        if (msg.message != WM_LBUTTONDOWN)
            return;
        if (msg.x > 600 && msg.x < 700 && msg.y > 550 && msg.y < 600)
            scene_manager->switch_to(SceneType::Menu);
    };
};

#endif // !_INTRODUCE_SCENE_H_