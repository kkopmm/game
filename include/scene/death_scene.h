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

    void on_enter()
    {
        is_timeout = false;
        timer.set_wait_time(1.0f);
        timer.set_one_shot(true);
        timer.set_on_timeout(
            [&]()
            { is_timeout = true; });
        timer.restart();
        timer.pause();
    };
    void on_exit() {};
    void on_update(float delta) {
        timer.on_update(delta);
    };
    void on_draw()
    {
        if (!is_timeout) {
            play_audio(L"尖叫声",false);
            putimage(0, 0, res_manager->get_image("女鬼"));
            timer.resume();
        }else{
            putimage(0, 0, res_manager->get_image("逃脱失败"));
        }
    };
    void on_input(const ExMessage &msg) {
        if (msg.message == WM_LBUTTONDOWN) {
            if (msg.x >= 510 && msg.x <= 755 && msg.y >= 500 && msg.y <= 590) {
                scene_manager->switch_to(SceneType::Game);
            }
            if (msg.x >= 510 && msg.x <= 755 && msg.y >= 620 && msg.y <= 700) {
                scene_manager->switch_to(SceneType::Menu);
            }
        }
    };

private:
    Timer timer;
    bool is_timeout;
};

#endif // _DEATH_SCENE_H_
