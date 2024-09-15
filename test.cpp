#include "util.h"
#include "resources_manager.h"
#include "animation.h"

#include "menu_scene.h"
#include "setting_scene.h"
#include "game_scene.h"
#include "scene_manager.h"

#include <chrono>
#include <thread>
#include <graphics.h>

ResourcesManager *res_manager = ResourcesManager::instance();
SceneManager *scene_manager = new SceneManager();
Scene *menu_scene = nullptr;
Scene *setting_scene = nullptr;
Scene *game_scene = nullptr;

bool music_on = true;

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

    // 场景初始化
    menu_scene = new MenuScene();
    setting_scene = new SettingScene();
    game_scene = new GameScene();

    scene_manager->set_current_scene(menu_scene);

    const nanoseconds frame_duration(1000000000 / 120);
    steady_clock::time_point last_tick = steady_clock::now();

    BeginBatchDraw();

    ExMessage msg;
    bool is_quit = false;

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
        scene_manager->on_update(delta.count());
        setbkcolor(RGB(0, 0, 0));
        cleardevice();

        // TODO: 处理绘图
        scene_manager->on_draw();

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
