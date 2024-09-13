#ifndef ATLAS_H
#define ATLAS_H

#include <graphics.h>
#include <vector>

// 用于保存多个图片
class Atlas
{
private:
    std::vector<IMAGE> img_list;

public:
    Atlas() = default;
    ~Atlas() = default;
    void load(const LPTCH path_template, const int num_frame)
    {
        img_list.clear();
        img_list.resize(num_frame);
        TCHAR path[256];
        for (int i = 0; i < num_frame; i++)
        {
            _stprintf_s(path, path_template, path, i);
            loadimage(&img_list[i], path);
        }
    };
    void clear()
    {
        img_list.clear();
    }
    IMAGE *get_image(const int index)
    {
        if (index < 0 || index >= (int)img_list.size())
            return nullptr;
        return &img_list[index];
    };
    int get_size() const
    {
        return (int)img_list.size();
    };
    void add_image(const IMAGE &image)
    {
        img_list.push_back(image);
    };
};

#endif