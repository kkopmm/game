#include "collision_manager.h"

#include <graphics.h>

CollisionManager *CollisionManager::manager = nullptr;

CollisionManager *CollisionManager::instance()
{
    if (!manager)
        manager = new CollisionManager();
    return manager;
}

CollisionBox *CollisionManager::create_collision_box()
{
    CollisionBox *box = new CollisionBox();
    collision_box_list.push_back(box);
    return box;
}

void CollisionManager::destroy_collision_box(CollisionBox *collision_box)
{
    collision_box_list.erase(std::remove(collision_box_list.begin(),
                                         collision_box_list.end(), collision_box),
                             collision_box_list.end());
    delete collision_box;
}

void CollisionManager::process_collisions()
{
    for (CollisionBox *box : collision_box_list)
    {
        if (!box->enable || box->layer_dst == CollisionLayer::None)
            continue;
        for (CollisionBox *other_box : collision_box_list)
        {
            if (box == other_box)
                continue;
            if (!other_box->enable || box->layer_dst != other_box->layer_src)
                continue;

            bool is_collide_x = (max(box->position.x + box->size.x / 2,
                                     other_box->position.x + other_box->size.x / 2) -
                                     min(
                                         box->position.x - box->size.x / 2,
                                         other_box->position.x - other_box->size.x / 2) <=
                                 box->size.x + other_box->size.x);
            bool is_collide_y = (max(box->position.y + box->size.y / 2,
                                     other_box->position.y + other_box->size.y / 2) -
                                     min(
                                         box->position.y - box->size.y / 2,
                                         other_box->position.y - other_box->size.y / 2) <=
                                 box->size.y + other_box->size.y);
            if (is_collide_x && is_collide_y && box->on_collide)
            {
                box->on_collide();
            }
        }
    }
}

void CollisionManager::on_render()
{
    for (CollisionBox *box : collision_box_list)
    {
        setlinecolor(box->enable ? RGB(0, 255, 0) : RGB(255, 0, 0));
        rectangle((int)(box->position.x - box->size.x / 2),
                  (int)(box->position.y - box->size.y / 2),
                  (int)(box->position.x + box->size.x / 2),
                  (int)(box->position.y + box->size.y / 2));
    }
}
