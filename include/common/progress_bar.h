#ifndef _PROGRESS_BAR_H
#define _PROGRESS_BAR_H

#include <graphics.h>

class ProgressBar
{
public:
    ProgressBar(int x, int y, int w, int h)
    {
        this->x = x;
        this->y = y;
        this->w = w;
        this->h = h;
    }
    void on_draw()
    {
        // 绘制背景
        setfillcolor(LIGHTGRAY);
        fillrectangle(x, y, x + w, y + h);
        // 绘制进度条
        setfillcolor(YELLOW);
        fillrectangle(x, y, x + (int)(w * progress), y + h);
    }
    void set_progress(float progress)
    {
        this->progress = progress;
    }

private:
    float progress = 1.0;
    int x, y, w, h;
};

#endif // _PROGRESS_BAR_H