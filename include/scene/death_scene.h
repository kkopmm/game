#ifndef _DEATH_SCENE_H_
#define _DEATH_SCENE_H_

#include "scene.h"
#include "scene_manager.h"
#include "resources_manager.h"
#include "timer.h"

extern SceneManager *scene_manager;
extern ResourcesManager *res_manager;

class DeathScene : public Scene
{
public:
    DeathScene() = default;
    ~DeathScene() = default;

    void on_enter() {

    };
    void on_exit() {};
    void on_update(float delta) {};
    void on_draw()
    {
        putimage(0, 0, res_manager->get_image("女鬼"));
        
    };
    void on_input(const ExMessage &msg) {

    };

private:
    Timer timer;
    bool is_timeout = false;
};

#endif // _DEATH_SCENE_H_
