#ifndef _GAME_OBJECT_H
#define _GAME_OBJECT_H

#include "resources_manager.h"
#include "vector2.h"
#include "animation.h"
#include "collision_box.h"

extern ResourcesManager *res_manager;
extern CollisionManager *collision_manager;

class GameObject
{
public:
    GameObject() = default;
    GameObject(const Vector2 &pos) : position(pos) {}
    ~GameObject()
    {
        if (collision_box)
            collision_manager->destroy_collision_box(collision_box);
        collision_box = nullptr;
    };
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
    void set_size(const Vector2 &size)
    {
        this->size = size;
    }
    const Vector2 &get_size() const
    {
        return size;
    }

protected:
    Animation animation;
    Vector2 position;
    CollisionBox *collision_box = nullptr;
    Vector2 size = Vector2(64, 64);
};

#endif // _GAME_OBJECT_H
