#ifndef _FLASHLIGHT_H
#define _FLASHLIGHT_H

#include "game_object.h"
#include "vector2.h"
#include "collision_layer.h"

class Flashlight : public GameObject
{
public:
    Flashlight(const Vector2 &pos)
    {
        this->position = pos;
        animation.set_position(pos);
        animation.add_frame(res_manager->get_image("手电筒"), 1);
        animation.set_scale(0.5f);
        collision_box = collision_manager->create_collision_box(pos);
        collision_box->set_size({32, 32});
        collision_box->set_layer_src(CollisionLayer::Prop);
        collision_box->set_layer_src({CollisionLayer::Player});
    };
    ~Flashlight() = default;
};

#endif // _FLASHLIGHT_H