#include "util.h"
#include "resources_manager.h"
#include "animation.h"

#include "menu_scene.h"
#include "scene_manager.h"

#include <chrono>
#include <thread>
#include <graphics.h>

ResourcesManager *res_manager = ResourcesManager::instance();
SceneManager *scene_manager = new SceneManager();

int main(int argc, char const *argv[])
{
    using namespace std::chrono;

    HWND hwnd = initgraph(1280, 720, EW_SHOWCONSOLE);
    SetWindowText(hwnd, _T("EasyX"));

    // TODO: 初始化
    try
    {
        res_manager->load();
    }
    catch (const LPCTSTR id)
    {
        TCHAR error_msg[256];
        wsprintf(error_msg, _T("资源加载失败: %s"), id);
        MessageBox(hwnd, error_msg, _T("错误"), MB_OK | MB_ICONERROR);
        return -1;
    }

    const nanoseconds frame_duration(1000000000 / 120);
    steady_clock::time_point last_tick = steady_clock::now();

    BeginBatchDraw();

    ExMessage msg;
    Scene *scene = new MenuScene();
    scene_manager->set_current_scene(scene);
    bool is_quit = false;

    // 动画测试代码
    // Animation *anim = new Animation();
    // anim->add_frame(res_manager->get_image("player_walk_up"), 4);
    // anim->set_position({100, 100});
    // anim->set_interval(0.1f);
    IMAGE *img = res_manager->get_image("player_walk_up");
    while (!is_quit)
    {
        while (peekmessage(&msg))
        {
            // TODO: 处理消息
            scene_manager->on_input(msg);
        }

        steady_clock::time_point frame_start = steady_clock::now();
        duration<float> delta = duration<float>(frame_start - last_tick);

        // TODO: 处理更新
        // anim->on_update(delta.count());
        scene_manager->on_update(delta.count());
        setbkcolor(RGB(0, 0, 0));
        cleardevice();

        // TODO: 处理绘图
        scene_manager->on_draw();
        // putimage(100, 100, img);
        // anim->on_render();

        FlushBatchDraw();

        // 稳定帧数
        last_tick = frame_start;
        nanoseconds sleep_duration = frame_duration - (steady_clock::now() - frame_start);
        if (sleep_duration > nanoseconds(0))
            std::this_thread::sleep_for(sleep_duration);
    }
    EndBatchDraw();
    return 0;
}
