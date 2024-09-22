#ifndef _CAMERA_H
#define _CAMERA_H

#include "vector2.h"

class Camera
{
public:
    Camera() = default;
    ~Camera() = default;
    const Vector2 &get_position() const
    {
        return position;
    }
    void set_position(const Vector2 &pos)
    {
        position = pos;
    }
    void reset()
    {
        position.x = 0;
        position.y = 0;
    }
    void on_update(float delta)
    {
    }

private:
    Vector2 position = {0, 0};
};

#endif // _CAMERA_H