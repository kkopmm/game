#ifndef _SCENE_H
#define _SCENE_H

#include "camera.h"

#include <graphics.h>

class Scene
{
public:
    Scene() = default;
    ~Scene() = default;

    virtual void on_enter() {};
    virtual void on_exit() {};
    virtual void on_update(float delta) {};
    virtual void on_draw(const Camera &camera) {};
    virtual void on_input(const ExMessage &msg) {};
};

#endif // _SCENE_H