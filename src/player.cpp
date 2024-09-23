#include "player.h"
#include "resources_manager.h"
#include "collision_layer.h"

#include <iostream>

extern ResourcesManager *res_manager;

Player::Player()
{
    walk_down.add_frame(res_manager->get_image("player_walk_down"), 4);
    walk_left.add_frame(res_manager->get_image("player_walk_left"), 4);
    walk_right.add_frame(res_manager->get_image("player_walk_right"), 4);
    walk_up.add_frame(res_manager->get_image("player_walk_up"), 4);
    walk_down.set_interval(0.1f);
    walk_left.set_interval(0.1f);
    walk_right.set_interval(0.1f);
    walk_up.set_interval(0.1f);
    current_animation = &walk_down;

    timer_invulnerable.set_wait_time(1.0f);
    timer_invulnerable.set_one_shot(true);
    timer_invulnerable.set_on_timeout([&]()
                                      { is_invulnerable = false; });

    sp_timer.set_wait_time(1.0f);
    sp_timer.set_one_shot(true);
    sp_timer.set_on_timeout([&]
                            { can_run = true; });

    bullet = new Bullet(position, {0, 0});
    bullet->set_active(false);

    attack_timer.set_one_shot(true);
    attack_timer.set_wait_time(1.0f);
    attack_timer.set_on_timeout([&]
                                { can_attack = true; });

    collision_box = collision_manager->create_collision_box(position);
    collision_box->set_size({32, 32});
    collision_box->set_layer_src(CollisionLayer::Player);
    collision_box->set_layer_dst({CollisionLayer::Wall, CollisionLayer::Enemy});
    collision_box->set_on_collide([&](CollisionBox *other_box)
                                  {
                                    if (other_box->get_layer_src() == CollisionLayer::Wall)
        {Vector2 pos1 = collision_box->get_position();
        Vector2 pos2 = other_box->get_position();
        Vector2 size1 = collision_box->get_size();
        Vector2 size2 = other_box->get_size();
        float overlap_x = (size1.x+size2.x)/2 - abs(pos1.x-pos2.x);
        float overlap_y = (size1.y+size2.y)/2 - abs(pos1.y-pos2.y);
        if(overlap_x>overlap_y) 
            set_position({position.x, position.y-(pos1.y<pos2.y?overlap_y:-overlap_y)});
        else
            set_position({position.x-(pos1.x<pos2.x?overlap_x:-overlap_x), position.y});}
        if(other_box->get_layer_src() == CollisionLayer::Enemy&&!is_invulnerable)
            {hp--;
            std::cout << "is_invulnerable: " << is_invulnerable << std::endl;
            is_invulnerable = true;
            timer_invulnerable.restart();
            } });
}
Player::~Player()
{
    delete bullet;
};
void Player::set_hp(int hp)
{
    this->hp = hp;
}
int Player::get_hp() const
{
    return hp;
}
int Player::get_sp() const
{
    return sp;
}
void Player::set_speed(float speed)
{
    this->speed = speed;
}
void Player::attack()
{
    if (!can_attack || bullet_count <= 0)
    {
        play_audio(L"子弹耗尽", false);
        return;
    }

    can_attack = false;
    bullet_count--;
    bullet->set_enable(true);
    bullet->set_position(position);
    bullet->set_active(true);

    play_audio(L"手枪", false);

    attack_timer.restart();
    if (direction == Direction::Up)
        bullet->set_velocity({0, -1000});
    else if (direction == Direction::Down)
        bullet->set_velocity({0, 1000});
    else if (direction == Direction::Left)
        bullet->set_velocity({-1000, 0});
    else if (direction == Direction::Right)
        bullet->set_velocity({1000, 0});
}
int Player::get_bullet_count() const
{
    return bullet_count;
}
void Player::set_bullet_count(int bullet_count)
{
    this->bullet_count = bullet_count;
}
float Player::get_speed() const
{
    return speed;
}
void Player::on_input(const ExMessage &msg)
{
    if (msg.message == WM_KEYDOWN)
    {       
        if (msg.vkcode == 0x52)
            is_running = true;
        if (msg.vkcode == VK_SPACE)
            attack();
        switch (msg.vkcode)
        {
        case 0x57:
            velocity.y = -speed;
            break;
        case 0x53:
            velocity.y = speed;
            break;
        case 0x41:
            velocity.x = -speed;
            break;
        case 0x44:
            velocity.x = speed;
            break;
        }
    }
    else if (msg.message == WM_KEYUP)
    {
        if (msg.vkcode == 0x52)
            is_running = false;
        switch (msg.vkcode)
        {
        case 0x57:
        case 0x53:
            velocity.y = 0;
            break;
        case 0x41:
        case 0x44:
            velocity.x = 0;
            break;
        }
    };
};
void Player::on_update(float delta)
{
    if (velocity.y < 0)
    {
        direction = Direction::Up;
        current_animation = &walk_up;
    }
    else if (velocity.y > 0)
    {
        direction = Direction::Down;
        current_animation = &walk_down;
    }
    else if (velocity.x < 0)
    {
        direction = Direction::Left;
        current_animation = &walk_left;
    }
    else if (velocity.x > 0)
    {
        direction = Direction::Right;
        current_animation = &walk_right;
    }
    else
    {
        current_animation->reset();
    }
    is_walking = velocity.length() != 0;
    if (is_walking)
    {
        if (is_running && can_run)
        {
            set_position(position + velocity.normalize() * speed * delta * 2);
            sp -= 5;
            if (sp <= 0)
            {
                can_run = false;
                sp_timer.restart();
            }
        }
        else
        {
            set_position(position + velocity.normalize() * speed * delta);
            sp = min(1000, sp + 1);
        }
    }
    // 体力恢复
    if (!is_running && !is_walking)
        sp = min(1000, sp + 3);

    sp_timer.on_update(delta);
    bullet->on_update(delta);
    attack_timer.on_update(delta);
    collision_box->set_position(position);
    current_animation->set_position(position);
    current_animation->on_update(delta);
    timer_invulnerable.on_update(delta);
};
void Player::on_draw()
{
    current_animation->on_render();
    bullet->on_draw();
    
};