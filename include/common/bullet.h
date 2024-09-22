#ifndef _BULLET_H
#define _BULLET_H

#include "game_object.h"
#include "vector2.h"
#include "collision_box.h"
#include "collision_layer.h"
#include "collision_manager.h"

#include <iostream>

extern CollisionManager *collision_manager;

class Bullet : public GameObject
{
private:
    Vector2 velocity;
    CollisionBox *collision_box = nullptr;
    bool is_active = false;

public:
    Bullet(const Vector2 &position, const Vector2 &velocity)
    {
        this->velocity = velocity;
        this->position = position;
        animation.add_frame(res_manager->get_image("bullet"), 1);
        collision_box = collision_manager->create_collision_box();
        collision_box->set_position(position);
        collision_box->set_size({16, 16});
        collision_box->set_layer_src({CollisionLayer::Bullet});
        collision_box->set_layer_dst({CollisionLayer::Wall, CollisionLayer::Enemy});
        collision_box->set_on_collide([&](CollisionBox *other)
                                      { 
                                        if(other->get_layer_src() == CollisionLayer::Wall)
                                            set_enable(false);
                                        set_active(false); 
                                        });
    };
    ~Bullet()
    {
        if (collision_box != NULL)
            collision_manager->destroy_collision_box(collision_box);
        collision_box = nullptr;
    }
    void on_update(float delta)
    {
        animation.on_update(delta);
        position += velocity * delta;
        collision_box->set_position(position);
        animation.set_position(position);
    };
    void on_draw()
    {
        if (is_active)
            animation.on_render();
    };
    void set_velocity(const Vector2 &velocity)
    {
        this->velocity = velocity;
    }
    void set_active(bool active)
    {
        is_active = active;
    }
    void set_enable(bool enable)
    {
        if (collision_box != NULL)
            collision_box->set_enable(enable);
    }
};

#endif // _BULLET_H