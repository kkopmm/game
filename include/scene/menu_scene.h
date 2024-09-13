#ifndef _MENU_SCENE_H
#define _MENU_SCENE_H

#include "scene.h"
#include "resources_manager.h"

extern ResourcesManager *res_manager;

class MenuScene : public Scene
{
public:
    MenuScene() = default;
    ~MenuScene() = default;

    void on_enter() {

    };
    void on_exit() {};
    void on_update(float delta) {};
    void on_draw()
    {
        putimage(0, 0, res_manager->get_image("menu"));
    };
    void on_input(const ExMessage &msg) {};
};

#endif // _MENU_SCENE_H