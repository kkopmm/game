#ifndef _PLAYER_H
#define _PLAYER_H

#include "camera.h"
#include "vector2.h"
#include "animation.h"
#include "collision_box.h"
#include "collision_manager.h"
#include "bullet.h"

#include <graphics.h>

extern CollisionManager *collision_manager;

class _Player
{
private:
    enum class Direction
    {
        Up,
        Down,
        Left,
        Right
    };

    bool is_walking;
    bool is_running;
    bool can_attack = true;
    bool is_invulnerable = false;
    bool can_run = true;

    Timer timer_invulnerable;

    float speed = 100;
    int hp = 3;
    int bullet_count = 7;
    int sp = 1000;
    Timer attack_timer;
    Timer bullet_timer;
    Timer sp_timer;

    Vector2 position;
    Vector2 velocity;
    Animation walk_up;
    Animation walk_down;
    Animation walk_left;
    Animation walk_right;
    Animation *current_animation;
    Direction direction = Direction::Down;
    CollisionBox *collision_box = nullptr;
    Bullet *bullet;

public:
    _Player();
    ~_Player();
    void on_draw();
    void on_update(float delta);
    void on_input(const ExMessage &msg);
    void set_position(const Vector2 &position);
    const Vector2 &get_velocity() { return velocity; };
    const Vector2 &get_position();
    void set_hp(int hp);
    int get_hp() const;
    int get_sp() const;
    float get_speed() const;
    void set_speed(float speed);
    void attack();
    int get_bullet_count() const;
};
#endif // _PLAYER_H