#ifndef _COLLISION_BOX_H
#define _COLLISION_BOX_H

#include "vector2.h"
#include "collision_layer.h"

#include <functional>

class CollisionManager;

class CollisionBox
{
    friend class CollisionManager;

private:
    Vector2 size;
    Vector2 position;
    CollisionLayer layer;
    bool enable;
    std::function<void()> on_collide;
    CollisionLayer layer_src = CollisionLayer::None;
    CollisionLayer layer_dst = CollisionLayer::None;

public:
    CollisionBox() = default;
    ~CollisionBox() = default;

public:
    void set_size(const Vector2 &size)
    {
        this->size = size;
    };
    void set_position(const Vector2 &position)
    {
        this->position = position;
    };
    void set_layer(CollisionLayer layer)
    {
        this->layer = layer;
    };
    void set_enable(bool enable)
    {
        this->enable = enable;
    };
    void set_on_collide(std::function<void()> on_collide)
    {
        this->on_collide = on_collide;
    };
    void set_layer_src(CollisionLayer layer)
    {
        this->layer_src = layer;
    };
    void set_layer_dst(CollisionLayer layer)
    {
        this->layer_dst = layer;
    };
    const Vector2 &get_size() const
    {
        return this->size;
    };
};

#endif // _COLLISION_BOX_H