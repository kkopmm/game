#ifndef _SETTING_SCENE_H_
#define _SETTING_SCENE_H_

#include <easyx.h>

#include "scene.h"
#include "util.h"

extern bool music_on;
extern SceneManager *scene_manager;

class SettingScene : public Scene
{
public:
    void on_enter() {
        // play_audio(L"菜单背景音乐", true);
    };
    void on_exit() {
        // stop_audio(L"菜单背景音乐");
    };
    void on_update(float delta) {};
    void on_draw()
    {
        setbkmode(TRANSPARENT);
        settextstyle(30, 0, _T("黑体")); // 设置字体
        setfillcolor(BROWN);             // 设置填充颜色
        int x = 550;
        int y = 300;
        int w = 150;
        int h = 50;
        int tx = x + (w - textwidth("开启音乐")) / 2;
        int ty = y + (h - textheight("开启音乐")) / 2;
        fillroundrect(x, y, x + w, y + h, 10, 10);
        fillroundrect(x, y + 100, x + w, y + h + 100, 10, 10);
        fillroundrect(x, y + 200, x + w, y + h + 200, 10, 10);
        outtextxy(tx, ty, "开启音乐");
        outtextxy(tx, ty + 100, "关闭音乐");
        outtextxy(tx, ty + 200, "返回菜单");
    };
    void on_input(const ExMessage &msg)
    {
        if (msg.message != WM_LBUTTONDOWN)
            return;
        if (msg.x >= 550 && msg.x <= 700)
        {
            if (msg.y >= 300 && msg.y <= 350)
            { // 开启音乐
                music_on = true;
                play_audio("菜单背景音乐");
            }
            if (msg.y >= 400 && msg.y <= 450)
            {
                music_on = false;
                stop_all_audio();
            }
            if (msg.y >= 500 && msg.y <= 550) // 返回菜单
                scene_manager->switch_to(SceneType::Menu);
        }
    };
};

#endif // _SETTING_SCENE_H_