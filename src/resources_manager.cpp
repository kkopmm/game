#include "resources_manager.h"
#include "util.h"

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
// 图片信息列表
static const std::vector<ImageInfo> image_info_list = {
    // {"唯一id", _T(R"(路径)")}
    {"background", _T(R"(res\img\剧情背景.jpeg)")},
    {"player_walk_up", _T(R"(res\img\Character05_Walk_Up.png)")},

};
static const std::vector<AtlasInfo> atlas_info_list = {
    // {"唯一id", _T(R"(路径)",帧数)}
    // {"background", _T(R"(res\background.png)"), 3},

};

// 检测图片是否有效
static inline bool check_image_valid(IMAGE *image)
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
ResourcesManager::ResourcesManager() = default;
ResourcesManager::~ResourcesManager() = default;

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
    // filp_image();
    // flip_atlas();
    // load_audio();
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