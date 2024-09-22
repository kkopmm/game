
#ifndef _DOOR_H
#define _DOOR_H

#include "game_object.h"
#include "collision_layer.h"
#include "collision_manager.h"
#include "resources_manager.h"
#include "scene_manager.h"

extern CollisionManager *collision_manager;
extern ResourcesManager *res_manager;
extern SceneManager *scene_manager;

class Door : public GameObject
{
public:
    bool is_vctor = false;
    Door(const Vector2 &position)
    {
        this->position = position;
        this->is_vctor = false;

        animation.add_frame(res_manager->get_image("大门"), 1);
        animation.set_position(position);

        collision_box = collision_manager->create_collision_box();
        collision_box->set_size({64, 64});
        collision_box->set_position(position);
        collision_box->set_layer_src(CollisionLayer::Door);
        collision_box->set_layer_dst({CollisionLayer::Player});
        collision_box->set_on_collide([&](CollisionBox *other)
                                      { is_vctor = true; });
    }
    ~Door() = default;
};

#endif // _DOOR_H