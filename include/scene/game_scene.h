#ifndef _GAME_SCENE_H
#define _GAME_SCENE_H

#include "scene.h"

class GameScene : public Scene
{
public:
    GameScene() = default;
    ~GameScene() = default;
    virtual void on_enter() {};
    virtual void on_exit() {};
    virtual void on_update(float delta) {};
    virtual void on_draw() {};
    virtual void on_input(const ExMessage &msg) {};
};

#endif // _GAME_SCENE_H