#ifndef _TIMER_H
#define _TIMER_H

#include <functional>

class Timer
{
private:
    float pass_time = 0;
    float wait_time = 0;
    bool shotted = false;
    bool paused = false;
    bool one_shot = false;
    std::function<void()> on_timeout;

public:
    Timer() = default;
    ~Timer() = default;

    void restart()
    {
        pass_time = 0;
        shotted = false;
    }
    void set_wait_time(float time)
    {
        wait_time = time;
    }
    void set_one_shot(bool one_shot)
    {
        this->one_shot = one_shot;
    }
    void set_on_timeout(std::function<void()> on_timeout)
    {
        this->on_timeout = on_timeout;
    }
    void pause()
    {
        paused = true;
    }
    void resume()
    {
        paused = false;
    }
    void on_update(float delta)
    {
        if (paused)
            return;
        pass_time += delta;
        if (pass_time >= wait_time)
        {
            bool can_shot = (!one_shot || (!shotted && one_shot));
            shotted = true;
            if (can_shot && on_timeout)
                on_timeout();
            pass_time -= wait_time;
        }
    }
};

#endif // _TIMER_H