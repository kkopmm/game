#ifndef _VICTORY_SCENE_H
#define _VICTORY_SCENE_H

#include "scene.h"
#include "util.h"
#include "resources_manager.h"
#include "scene_manager.h"

extern ResourcesManager *res_manager;
extern SceneManager *scene_manager;

class VictoryScene : public Scene
{
public:
    void on_enter()
    {
        play_audio(L"胜利音乐");
    };
    void on_exit() {
        stop_audio(L"胜利音乐");
    };
    void on_update(float delta) {};
    void on_draw()
    {
        int x = 550;
        int y = 300;
        int w = 150;
        int h = 50;
        int tx = x + (w - textwidth(_T("返回菜单"))) / 2;
        int ty = y + (h - textheight(_T("返回菜单"))) / 2;
        putimage(0, 0, res_manager->get_image("通关画面"));
        setbkmode(TRANSPARENT);
        settextstyle(30, 0, _T("黑体")); // 设置字体
        setfillcolor(BROWN);             // 设置填充颜色
        settextcolor(WHITE);             // 设置文字颜色
        fillroundrect(x, y, x + w, y + h, 10, 10);
        fillroundrect(x, y + 100, x + w, y + h + 100, 10, 10);
        outtextxy(tx, ty, _T("返回菜单"));
        outtextxy(tx, ty + 100, _T("重新开始"));
    };
    void on_input(const ExMessage &msg) {

        if (msg.message == WM_LBUTTONDOWN) {
            if (msg.x >= 550 && msg.x <= 700 && msg.y >= 300 && msg.y <= 350) {
                scene_manager->switch_to(SceneType::Menu);
            }
            if (msg.x >= 550 && msg.x <= 700 && msg.y >= 400 && msg.y <= 450) {
                scene_manager->switch_to(SceneType::Game);
            }
        }

    };
};

#endif // _VICTORY_SCENE_H