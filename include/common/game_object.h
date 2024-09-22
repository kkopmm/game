#ifndef _GAME_OBJECT_H
#define _GAME_OBJECT_H

#include "resources_manager.h"
#include "vector2.h"
#include "animation.h"

extern ResourcesManager *res_manager;
class GameObject
{
public:
    GameObject() = default;
    GameObject(const Vector2 &pos) : position(pos) {}
    ~GameObject() = default;

    void on_update(float delta)
    {
        animation.on_update(delta);
    };
    void on_draw()
    {
        animation.on_render();
    };
    void set_position(const Vector2 &pos)
    {
        position = pos;
    }
    const Vector2 &get_position() const
    {
        return position;
    }

protected:
    Animation animation;
    Vector2 position;
    Vector2 size = Vector2(64, 64);
};

#endif // _GAME_OBJECT_H
