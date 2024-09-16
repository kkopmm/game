#ifndef _COLLISION_MANAGER_H
#define _COLLISION_MANAGER_H

#include "collision_box.h"

#include <vector>

class CollisionManager
{
public:
    static CollisionManager *instance();
    CollisionBox *create_collision_box();
    void destroy_collision_box(CollisionBox *collision_box);

    void process_collisions();
    void on_render();

private:
    CollisionManager() = default;
    ~CollisionManager() = default;
    static CollisionManager *manager;
    std::vector<CollisionBox *> collision_box_list;
};

#endif // _COLLISION_MANAGER_H