#ifndef _FLOOR_H
#define _FLOOR_H

#include "resources_manager.h"
#include "vector2.h"
#include "game_object.h"
#include "animation.h"

extern ResourcesManager *res_manager;
class Floor : public GameObject
{
public:
    Floor(const Vector2 &pos)
    {
        position = pos;
        animation.add_frame(res_manager->get_image("floor"), 1);
        animation.set_position(position);
    };
    ~Floor() = default;
};

#endif // _WALL_H