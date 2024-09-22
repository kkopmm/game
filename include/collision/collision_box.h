#ifndef _COLLISION_BOX_H
#define _COLLISION_BOX_H

#include "vector2.h"
#include "collision_box.h"
#include "collision_layer.h"

#include <unordered_set>
#include <functional>

class CollisionManager;

class CollisionBox
{
    friend class CollisionManager;

private:
    bool enable = true;
    Vector2 size;
    Vector2 position;
    std::function<void(CollisionBox *)> on_collide;
    CollisionLayer layer_src = CollisionLayer::None;
    std::unordered_set<CollisionLayer> layer_dst = {};

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
    void set_enable(bool enable)
    {
        this->enable = enable;
    };
    void set_on_collide(std::function<void(CollisionBox *)> on_collide)
    {
        this->on_collide = on_collide;
    };
    void set_layer_src(CollisionLayer layer)
    {
        this->layer_src = layer;
    };
    CollisionLayer get_layer_src() const
    {
        return this->layer_src;
    }
    void set_layer_dst(std::unordered_set<CollisionLayer> layer)
    {
        this->layer_dst = layer;
    };

    const Vector2 &get_size() const
    {
        return this->size;
    };
    const Vector2 &get_position() const
    {
        return this->position;
    }
};

#endif // _COLLISION_BOX_H