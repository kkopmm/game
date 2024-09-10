#ifndef _RESOURCES_MANAGER_H
#define _RESOURCES_MANAGER_H

#include "atlas.h"

#include <string>
#include <unordered_map>
#include <graphics.h>

// 单例资源管理类
class ResourcesManager
{
private:
    static ResourcesManager *manager;
    std::unordered_map<std::string, Atlas *> atlas_pool;
    std::unordered_map<std::string, IMAGE *> image_pool;
    void filp_image(IMAGE *src_image, IMAGE *dst_image, int num_h = 1);
    void filp_image(const std::string &src_id, const std::string &dst_id, int num_h = 1);
    void flip_atlas(const std::string &src_id, const std::string &dst_id);
    ResourcesManager();
    ~ResourcesManager();

public:
    static ResourcesManager *instance();
    // 加载资源
    void load();
    // 获取图集
    Atlas *getAtlas(const std::string &id) const;
    // 获取图片
    IMAGE *getImage(const std::string &id) const;
};

#endif // _RESOURCES_MANAGER_H