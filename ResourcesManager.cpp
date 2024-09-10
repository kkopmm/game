#include "resources_manager.h"

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
    {"background", _T(R"(res\background.png)")},
};
static const std::vector<AtlasInfo> atlas_info_list = {
    // {"唯一id", _T(R"(路径)",帧数)}
    {"background", _T(R"(res\background.png)"), 3},
};

// 检测图片是否有效
static inline bool check_image_valid(IMAGE *image)
{
    return GetImageBuffer(image);
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
    
}