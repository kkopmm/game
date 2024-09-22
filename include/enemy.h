#ifndef _ENEMY_H
#define _ENEMY_H

#include "game_object.h"
#include "resources_manager.h"
#include "collision_box.h"
#include "collision_manager.h"
#include "vector2.h"

#include <iostream>

extern ResourcesManager *res_manager;
extern CollisionManager *collision_manager;

class Enemy : public GameObject
{
public:
    int hp = 2;
    Enemy(const Vector2 &pos)
    {
        this->position = pos;
        animation.add_frame(res_manager->get_image("enemy"), 1);
        animation.set_position(position);
        collision_box = collision_manager->create_collision_box();
        collision_box->set_position(position);
        collision_box->set_size({32, 32});
        collision_box->set_layer_src({CollisionLayer::Enemy});
        collision_box->set_layer_dst({CollisionLayer::Bullet, CollisionLayer::Player, CollisionLayer::Wall});
        collision_box->set_on_collide([&](CollisionBox *other_box)
                                      {
            if (other_box->get_layer_src() == CollisionLayer::Bullet)
            {
                this->hp--;
                other_box->set_enable(false);
            }
            if (other_box->get_layer_src() == CollisionLayer::Wall)
            {
                Vector2 pos1 = collision_box->get_position();
                Vector2 pos2 = other_box->get_position();
                Vector2 size1 = collision_box->get_size();
                Vector2 size2 = other_box->get_size();
                float overlap_x = (size1.x + size2.x) / 2 - abs(pos1.x - pos2.x);
                float overlap_y = (size1.y + size2.y) / 2 - abs(pos1.y - pos2.y);
                if (overlap_x > overlap_y)
                    set_position({position.x, position.y - (pos1.y < pos2.y ? overlap_y : -overlap_y)});
                else
                    set_position({position.x - (pos1.x < pos2.x ? overlap_x : -overlap_x), position.y});
            } });
    }
    ~Enemy() = default;
    void on_update(float delta)
    {
        this->position += velocity * delta;
        animation.set_position(position);
        collision_box->set_position(position);
    }
    void on_draw()
    {
        if (hp > 0)
            animation.on_render();
    }
    void dead()
    {
        collision_box->set_enable(false);
        set_position({-1000, -1000});
    }
    void set_velocity(const Vector2 &vel)
    {
        this->velocity = vel;
    }

private:
    Vector2 velocity = Vector2(0, 0);
};

#endif // _ENEMY_H