#ifndef _WALL_H
#define _WALL_H

#include "collision_box.h"
#include "collision_manager.h"
#include "resources_manager.h"
#include "collision_layer.h"
#include "vector2.h"
#include "animation.h"
#include "game_object.h"

extern CollisionManager *collision_manager;
extern ResourcesManager *res_manager;

class Wall : public GameObject
{
public:
    Wall(const Vector2 &pos)
    {
        position = pos;
        collision_box = collision_manager->create_collision_box();
        collision_box->set_position(position);
        collision_box->set_size(size);
        collision_box->set_layer_src(CollisionLayer::Wall);
        collision_box->set_layer_dst({CollisionLayer::Player});
        animation.add_frame(res_manager->get_image("wall"), 1);
        animation.set_position(position);
    };
    ~Wall() = default;
};

#endif // _WALL_H