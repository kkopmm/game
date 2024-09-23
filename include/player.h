#ifndef _PLAYER_H
#define _PLAYER_H

#include "camera.h"
#include "vector2.h"
#include "animation.h"
#include "collision_box.h"
#include "collision_manager.h"
#include "bullet.h"
#include "game_object.h"

#include <graphics.h>

extern CollisionManager *collision_manager;

class Player : public GameObject
{
private:
    enum class Direction
    {
        Up,
        Down,
        Left,
        Right
    };

    bool is_walking = false;
    bool is_running = false;
    bool can_attack = true;
    bool is_invulnerable = false;
    bool can_run = true;
    bool has_flashlight = false;

    Timer timer_invulnerable;

    float speed = 100;
    int hp = 3;
    int bullet_count = 7;
    int sp = 1000;
    Timer attack_timer;
    Timer bullet_timer;
    Timer sp_timer;

    Vector2 velocity;
    Animation walk_up;
    Animation walk_down;
    Animation walk_left;
    Animation walk_right;
    Animation *current_animation;
    Direction direction = Direction::Down;
    Bullet *bullet;

public:
    Player();
    ~Player();
    void on_draw();
    void on_update(float delta);
    void on_input(const ExMessage &msg);
    const Vector2 &get_velocity() { return velocity; };
    void set_hp(int hp);
    int get_hp() const;
    int get_sp() const;
    float get_speed() const;
    void set_speed(float speed);
    void attack();
    int get_bullet_count() const;
    void set_bullet_count(int bullet_count);
    bool get_has_flashlight() const;
};
#endif // _PLAYER_H