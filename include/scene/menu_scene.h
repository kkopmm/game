#ifndef _MENU_SCENE_H
#define _MENU_SCENE_H

#include "scene.h"
#include "resources_manager.h"
#include "scene_manager.h"

extern ResourcesManager *res_manager;
extern SceneManager *scene_manager;

class MenuScene : public Scene
{
public:
    MenuScene() = default;
    ~MenuScene() = default;

    void on_enter() {};
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
        if (msg.x > 150 && msg.x < 450)
        {
            if (msg.y > 250 && msg.y < 350)
                scene_manager->switch_to(SceneType::Game);
            else if (msg.y > 360 && msg.y < 460)
                scene_manager->switch_to(SceneType::Setting);
            else if (msg.y > 470 && msg.y < 570)
                scene_manager->switch_to(SceneType::Setting);
            else if (msg.y > 580 && msg.y < 690)
                scene_manager->switch_to(SceneType::Exit);
        }
    };
};

#endif // _MENU_SCENE_H