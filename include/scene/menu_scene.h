#ifndef _MENU_SCENE_H
#define _MENU_SCENE_H

#include "scene.h"
#include "util.h"
#include "camera.h"
#include "resources_manager.h"
#include "scene_manager.h"

extern ResourcesManager *res_manager;
extern SceneManager *scene_manager;

class MenuScene : public Scene
{
public:
    MenuScene() = default;
    ~MenuScene() = default;

    void on_enter()
    {
        play_audio(L"菜单背景音乐", true);
    };
    void on_exit() {};
    void on_update(float delta) {};
    void on_draw()
    {
        putimage(0, 0, res_manager->get_image("menu"));
    };
    void on_input(const ExMessage &msg)
    {
        if (msg.message != WM_LBUTTONDOWN)
            return;
        if (msg.x > 130 && msg.x < 385)
        {
            if (msg.y > 240 && msg.y < 330)
                scene_manager->switch_to(SceneType::Game);
            else if (msg.y > 340 && msg.y < 430)
                scene_manager->switch_to(SceneType::Setting);
            else if (msg.y > 450 && msg.y < 540)
                scene_manager->switch_to(SceneType::Introduce);
            else if (msg.y > 550 && msg.y < 640)
                scene_manager->switch_to(SceneType::Exit);
        }
    };
};

#endif // _MENU_SCENE_H