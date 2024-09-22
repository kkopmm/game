#ifndef _UTIL_H
#define _UTIL_H

#include <graphics.h>
#include <stdio.h>

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "MSIMG32.lib")

extern bool music_on;

struct Rect
{
    int x, y, w, h;
};

inline void putimage_ex(IMAGE *img, const Rect *rect_dst, const Rect *rect_src = nullptr)
{
    static BLENDFUNCTION blend_func = {AC_SRC_OVER, 0, 255, AC_SRC_ALPHA};
    AlphaBlend(GetImageHDC(GetWorkingImage()), rect_dst->x, rect_dst->y, rect_dst->w, rect_dst->h,
               GetImageHDC(img), rect_src ? rect_src->x : 0, rect_src ? rect_src->y : 0, rect_src ? rect_src->w : img->getwidth(), rect_src ? rect_src->h : img->getheight(), blend_func);
}

inline void load_audio(const LPCTSTR &path, const LPCTSTR &id)
{
    static TCHAR str_cmd[512];
    _stprintf_s(str_cmd, _T("open %s alias %s"), path, id);
    if (mciSendString(str_cmd, NULL, 0, NULL))
        throw path;
}

inline void play_audio(const LPCTSTR &id, bool is_loop = true)
{
    if (!music_on)
        return;
    static TCHAR str_cmd[512];
    _stprintf_s(str_cmd, _T("play %s %s"), id, is_loop ? _T("repeat") : _T(""));
    mciSendString(str_cmd, NULL, 0, NULL);
}

inline void stop_audio(const LPCTSTR &id)
{
    static TCHAR str_cmd[512];
    _stprintf_s(str_cmd, _T("stop %s"), id);
    mciSendString(str_cmd, NULL, 0, NULL);
}
inline void stop_all_audio()
{
    mciSendString(_T("stop all"), NULL, 0, NULL);
}

inline void sketch_image(IMAGE *src, IMAGE *dst)
{
    int w = src->getwidth(), h = src->getheight();
    Resize(dst, w, h);
    DWORD *src_buffer = GetImageBuffer(src);
    DWORD *dst_buffer = GetImageBuffer(dst);
    for (int y = 0; y < w * h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            int idx = y * w + x;
            dst_buffer[idx] = BGR(RGB(255, 255, 255)) | (src_buffer[idx] & 0xFF000000);
        }
    }
}

#endif // _UTIL_H