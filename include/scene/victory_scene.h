#ifndef _VICTORY_SCENE_H
#define _VICTORY_SCENE_H

#include "scene.h"
#include "resources_manager.h"

extern ResourcesManager *res_manager;

class VictoryScene : public Scene
{
public:
    void on_enter() {};
    void on_exit() {};
    void on_update(float delta) {};
    void on_draw() {
        putimage(0, 0, res_manager->get_image("通关画面"));
    };
    void on_input(const ExMessage &msg) {};
};

#endif // _VICTORY_SCENE_H