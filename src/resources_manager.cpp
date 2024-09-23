#include "resources_manager.h"
#include "util.h"

extern bool music_on;

struct ImageInfo
{
    std::string id;
    LPTSTR path;
};
struct AtlasInfo
{
    std::string id;
    LPTSTR path;
    int num_frame = 0;
};
struct AudioInfo
{
    std::string id;
    LPTSTR path;
};

// 图片信息列表
static const std::vector<ImageInfo> image_info_list = {
    {"background", _T("res/img/剧情背景.jpeg")},
    {"menu", _T("res/img/menu.png")},
    {"menu1", _T("res/img/menu1.png")},
    {"player_walk_down", _T("res/img/player/walk_down.png")},
    {"player_walk_left", _T("res/img/player/walk_left.png")},
    {"player_walk_right", _T("res/img/player/walk_right.png")},
    {"player_walk_up", _T("res/img/player/walk_up.png")},
    {"wall", _T("res/img/wall.png")},
    {"floor", _T("res/img/floor.png")},
    {"bullet", _T("res/img/bullet.png")},
    {"enemy", _T("res/img/enemy.png")},
    {"爱心", _T("res/img/爱心.png")},
    {"女鬼", _T("res/img/女鬼.png")},
    {"逃脱失败", _T("res/img/逃脱失败.jpg")},
    {"弹药", _T("res/img/弹药.png")},
    {"通关画面", _T("res/img/通关画面.jpg")},
    {"大门", _T("res/img/大门.png")},
    {"z0", _T("res/img/z0.png")},
    {"惊吓", _T("res/img/惊吓.jpg")},
    {"手电筒", _T("res/img/手电筒.png")},
};

static const std::vector<AtlasInfo> atlas_info_list = {

};

static const std::vector<AudioInfo> audio_info_list = {
    {"菜单背景音乐", _T("res/sound/菜单背景音乐.mp3")},
    {"游戏背景音乐", _T("res/sound/游戏背景音乐.mp3")},
    {"剧情背景音乐", _T("res/sound/剧情背景音乐.mp3")},
    {"尖叫声", _T("res/sound/尖叫声.mp3")},
    {"胜利音乐", _T("res/sound/胜利音乐.mp3")},
    {"受击", _T("res/sound/受击.mp3")},
    {"手枪", _T("res/sound/手枪.mp3")},
    {"弹药耗尽", _T("res/sound/弹药耗尽.mp3")},
};

// 检测图片是否有效
static inline bool
check_image_valid(IMAGE *image)
{
    return image->getwidth() > 0 && image->getheight() > 0;
}

ResourcesManager *ResourcesManager::manager = nullptr;
ResourcesManager *ResourcesManager::instance()
{
    if (!manager)
        manager = new ResourcesManager();
    return manager;
}

Atlas *ResourcesManager::get_atlas(const std::string &id) const
{
    const auto &it = atlas_pool.find(id);
    if (it == atlas_pool.end())
        return nullptr;
    return it->second;
}
IMAGE *ResourcesManager::get_image(const std::string &id) const
{
    const auto &it = image_pool.find(id);
    if (it == image_pool.end())
        return nullptr;
    return it->second;
}
void ResourcesManager::flip_image(IMAGE *src_image, IMAGE *dst_image, int num_h)
{
    int w = src_image->getwidth();
    int h = src_image->getheight();
    int w_frame = w / num_h;
    Resize(dst_image, w, h);
    DWORD *src_buffer = GetImageBuffer(src_image);
    DWORD *dst_buffer = GetImageBuffer(dst_image);
    for (int i = 0; i < num_h; i++)
    {
        int x_left = i * w_frame;
        int x_right = (i + 1) * w_frame;
        for (int y = 0; y < h; y++)
        {
            for (int x = x_left; x < x_right; x++)
            {
                int idx_src = y * w + x;
                int idx_dst = y * w + x_right - (x - x_left);
                dst_buffer[idx_dst] = src_buffer[idx_src];
            }
        }
    }
}
void ResourcesManager::flip_image(const std::string &src_id, const std::string &dst_id, int num_h)
{
    IMAGE *src_image = image_pool[src_id];
    IMAGE *dst_image = new IMAGE();
    flip_image(src_image, dst_image, num_h);
    image_pool[dst_id] = dst_image;
}
void ResourcesManager::flip_atlas(const std::string &src_id, const std::string &dst_id)
{
    Atlas *src_atlas = atlas_pool[src_id];
    Atlas *dst_atlas = new Atlas();
    for (int i = 0; i < src_atlas->get_size(); i++)
    {
        IMAGE img_flipped;
        flip_image(src_atlas->get_image(i), &img_flipped);
        dst_atlas->add_image(img_flipped);
    }
    atlas_pool[dst_id] = dst_atlas;
}

void ResourcesManager::load()
{
    for (const auto &info : image_info_list)
    {
        IMAGE *image = new IMAGE();
        loadimage(image, info.path);
        if (!check_image_valid(image))
            throw info.path;
        image_pool[info.id] = image;
    }
    for (const auto &info : atlas_info_list)
    {
        Atlas *atlas = new Atlas();
        atlas->load(info.path, info.num_frame);
        for (int i = 0; i < info.num_frame; i++)
        {
            IMAGE *image = atlas->get_image(i);
            if (!check_image_valid(image))
                throw info.path;
        }
        atlas_pool[info.id] = atlas;
    }
    for (const auto &info : audio_info_list)
    {
        int wideLength = MultiByteToWideChar(CP_UTF8, 0, info.id.c_str(), -1, nullptr, 0);
        std::wstring wstr(wideLength, 0);
        MultiByteToWideChar(CP_UTF8, 0, info.id.c_str(), -1, &wstr[0], wideLength);
        load_audio(info.path, wstr.c_str());
    }
    // flip_image("enemy_right", "enemy_left", 1);
    // flip_atlas();
}
