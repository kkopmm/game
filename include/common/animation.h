#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include "util.h"
#include "timer.h"
#include "atlas.h"
#include "vector2.h"
#include "camera.h"

#include <vector>
#include <functional>

extern Camera *camera;

class Animation
{

public:
    enum class AnchorMode
    {
        Centered,
        BottomCentered
    };

private:
    struct Frame
    {
        Rect rect_src;
        IMAGE *image = nullptr;
        Frame() = default;
        ~Frame() = default;
        Frame(IMAGE *image, const Rect &rect_src) : rect_src(rect_src), image(image) {};
    };
    Timer timer;
    Vector2 position;
    bool is_loop = true;
    size_t idx_frame = 0;
    AnchorMode anchor_mode = AnchorMode::Centered;
    std::vector<Frame> frame_list;
    std::function<void()> on_finished;
    float scale = 1.0f;

public:
    Animation()
    {
        timer.set_one_shot(false);
        timer.set_on_timeout(
            [&]()
            {
                idx_frame++;
                if (idx_frame >= frame_list.size())
                {
                    idx_frame = is_loop ? 0 : frame_list.size() - 1;
                    if (!is_loop && on_finished)
                        on_finished();
                }
            });
    };
    ~Animation() = default;
    void reset()
    {
        timer.restart();
        idx_frame = 0;
    }
    void set_loop(bool is_loop) { this->is_loop = is_loop; }
    void set_anchor_mode(AnchorMode anchor_mode) { this->anchor_mode = anchor_mode; }
    void set_on_finished(std::function<void()> on_finished) { this->on_finished = on_finished; }
    void set_interval(float interval) { timer.set_wait_time(interval); }
    void set_position(const Vector2 &position) { this->position = position; }
    void set_scale(float scale) { this->scale = scale; };

    void add_frame(IMAGE *image, int num_h)
    {
        int width = image->getwidth();
        int height = image->getheight();
        int width_frame = width / num_h;
        for (int i = 0; i < num_h; i++)
        {
            Rect rect_src = {i * width_frame, 0, width_frame, height};
            frame_list.emplace_back(image, rect_src);
        }
    }
    void add_frame(Atlas *atlas)
    {
        for (int i = 0; i < atlas->get_size(); i++)
        {
            IMAGE *image = atlas->get_image(i);
            int width = image->getwidth();
            int height = image->getheight();
            Rect rect_src = {0, 0, width, height};
            frame_list.emplace_back(image, rect_src);
        }
    }
    // 更新
    void on_update(float delta)
    {
        timer.on_update(delta);
    }
    // 进行绘制
    void on_render()
    {
        const Frame &frame = frame_list[idx_frame];
        Rect rect_dst;
        rect_dst.x = (int)(position.x - scale * frame.rect_src.w / 2);
        rect_dst.y = (anchor_mode == AnchorMode::Centered)
                         ? (int)(position.y - scale * frame.rect_src.h / 2)
                         : (int)(position.y - scale * frame.rect_src.h);
        rect_dst.x -= (int)camera->get_position().x;
        rect_dst.y -= (int)camera->get_position().y;
        rect_dst.w = (int)(frame.rect_src.w * scale);
        rect_dst.h = (int)(frame.rect_src.h * scale);
        putimage_ex(frame.image, &rect_dst, &frame.rect_src);
    }
};

#endif // _ANIMATION_H_