#ifndef _PROP_BULLET_H_
#define _PROP_BULLET_H_

#include "game_object.h"

class PropBullet : public GameObject
{
public:
    PropBullet(const Vector2& pos)
    {
        this->position = pos;
        animation.set_position(pos);
        animation.add_frame(res_manager->get_image("弹药"), 1);
        animation.set_scale(0.5f);
        collision_box = collision_manager->create_collision_box(pos);
        collision_box->set_size({32, 32});
        collision_box->set_layer_src(CollisionLayer::Prop_bullet);
        collision_box->set_layer_dst({CollisionLayer::Player});
        
    }
    ~PropBullet() = default;
    
};

#endif // _PROP_BULLET_H_
