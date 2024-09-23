#ifndef _GAME_SCENE_H
#define _GAME_SCENE_H

#include "scene.h"
#include "util.h"
#include "camera.h"
#include "animation.h"

#include "progress_bar.h"
#include "scene_manager.h"
#include "collision_manager.h"
#include "collision_box.h"

// 实体类
#include "player.h"
#include "door.h"
#include "wall.h"
#include "floor.h"
#include "enemy.h"
#include "prop_flashlight.h"
#include "prop_bullet.h"

#include <vector>
#include <string>

extern ResourcesManager *res_manager;
extern CollisionManager *collision_manager;
extern SceneManager *scene_manager;
extern Camera *camera;

class Door;

class GameScene : public Scene
{
public:
    GameScene() = default;
    ~GameScene() = default;
    void on_enter()
    {
        camera->reset();
        player = new Player();
        player->set_position({100, 100});
        // 道具在这里添加

        // 随机选择地图
        int level = rand() % 2;
        if (level == 0)
        {
            load_map(this->map0);
            door = new Door({64 * 20, 64 * 20});
            game_object_loop = {
                new PropBullet({64 * 1, 64 * 3}),
                new Flashlight({64 * 1, 64 * 3}),
            };
        }
        else if (level == 1)
        {
            load_map(this->map1);
            door = new Door({64 * 20, 64 * 20});
        }
        // 随机生成怪物
        for (int i = 0; i < 10; i++)
        {
            enemy_loop.push_back(new Enemy({(float)(rand() % 1280), (float)(rand() % 720)}));
        }
        stop_all_audio();
        play_audio(L"游戏背景音乐", true);
    };
    void on_exit()
    {
        for (auto &wall : map)
            for (auto &w : wall)
                delete w;
        for (auto &enemy : enemy_loop)
            delete enemy;
        for (GameObject *game_object : game_object_loop)
            delete game_object;
        map.clear();
        enemy_loop.clear();
        game_object_loop.clear();
        delete door;
        delete player;
        stop_all_audio();
    };
    void on_update(float delta)
    {
        player->on_update(delta);
        // door->on_update(delta);
        for (GameObject *game_object : game_object_loop)
            game_object->on_update(delta);

        for (auto &enemy : enemy_loop)
        {
            Vector2 pos1 = player->get_position();
            Vector2 pos2 = enemy->get_position();
            enemy->set_velocity((pos1 - pos2).normalize() * 80.0f);
            enemy->on_update(delta);
        }
        camera->set_position(player->get_position() - Vector2(640, 350));
        sp_progress_bar.set_progress(player->get_sp() / 1000.0f);
        if (door->is_vctor)
        {
            scene_manager->switch_to(SceneType::Victory);
            return;
        }
        if (player->get_hp() <= 0)
        {
            scene_manager->switch_to(SceneType::Death);
            return;
        }
    };
    void on_draw()
    {
        if (is_stop)
        {
            int x = 550;
            int y = 300;
            int w = 150;
            int h = 50;
            int tx = x + (w - textwidth(_T("开启音乐"))) / 2;
            int ty = y + (h - textheight(_T("开启音乐"))) / 2;
            putimage(0, 0, res_manager->get_image("menu1"));
            setbkmode(TRANSPARENT);
            settextstyle(30, 0, _T("黑体")); // 设置字体
            setfillcolor(BROWN);             // 设置填充颜色
            settextcolor(WHITE);             // 设置文字颜色
            fillroundrect(x, y, x + w, y + h, 10, 10);
            fillroundrect(x, y + 100, x + w, y + h + 100, 10, 10);
            fillroundrect(x, y + 200, x + w, y + h + 200, 10, 10);
            outtextxy(tx, ty, _T("继续游戏"));
            outtextxy(tx, ty + 100, _T("重新开始"));
            outtextxy(tx, ty + 200, _T("返回菜单"));
            return;
        }

        for (auto &wall : map)
            for (auto &w : wall)
                if (w)
                    w->on_draw();

        bool surprise = false;
        for (auto &enemy : enemy_loop)
        {
            enemy->on_draw();
            if (enemy->surprise)
            {
                putimage(0, 0, res_manager->get_image("惊吓"));
                return;
            }
        }
        for (GameObject *game_object : game_object_loop)
            game_object->on_draw();

        player->on_draw();
        door->on_draw();

        setbkmode(TRANSPARENT);
        settextcolor(WHITE);
        settextstyle(30, 0, _T("楷体"));

        Rect r;
        // 绘制视野
        r = {0, 0, 1300, 720};
        if (!player->get_has_flashlight())
            putimage_ex(res_manager->get_image("z0"), &r);
        else
            putimage_ex(res_manager->get_image("z1"), &r);
        // 绘制爱心图标
        r = {0, 0, 64, 64};
        putimage_ex(res_manager->get_image("爱心"), &r);
        outtextxy(70, 20, std::to_wstring(player->get_hp()).c_str());
        // 绘制弹药图标
        r = {100, 0, 64, 64};
        putimage_ex(res_manager->get_image("弹药"), &r);
        outtextxy(180, 20, std::to_wstring(player->get_bullet_count()).c_str());
        // 绘制能量条
        sp_progress_bar.on_draw();
    };
    void on_input(const ExMessage &msg)
    {
        player->on_input(msg);
        if (msg.message == WM_KEYUP && msg.vkcode == VK_TAB)
            is_stop = !is_stop;
        if (msg.message == WM_LBUTTONDOWN && is_stop)
        {
            if (msg.x >= 550 && msg.x <= 700)
            {
                if (msg.y >= 300 && msg.y <= 350)
                    is_stop = false;
                if (msg.y >= 400 && msg.y <= 450)
                {
                    is_stop = false;    
                    scene_manager->switch_to(SceneType::Game);
                }
                if (msg.y >= 500 && msg.y <= 550) // 返回菜单
                {
                    is_stop = false;
                    scene_manager->switch_to(SceneType::Menu);
                }
            }
        }
    };

private:
    Player *player = nullptr;
    std::vector<std::vector<GameObject *>> map;
    std::vector<Enemy *> enemy_loop;
    ProgressBar sp_progress_bar = ProgressBar(10, 80, 150, 15);
    Door *door = nullptr;
    std::vector<GameObject *> game_object_loop;
    bool is_stop = false;

    // 加载地图
    void load_map(char (*select_map)[22])
    {
        for (int i = 0; i < 22; i++)
        {
            std::vector<GameObject *> m;
            char *row_ptr = *(select_map + i);
            for (int j = 0; j < 22; j++)
            {
                if (*(row_ptr + j) == '1')
                    m.push_back(new Wall({j * 64.0f, i * 64.0f}));
                else if (*(row_ptr + j) == '0')
                    m.push_back(new Floor({j * 64.0f, i * 64.0f}));
                else
                    m.push_back(nullptr);
            }
            map.push_back(m);
        }
    }
    char map0[22][22] = {
        '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
        '1', '0', '0', '0', '0', '0', '0', '0', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '1',
        '1', '0', '1', '1', '1', '1', '1', '0', '1', '0', '0', '1', '1', '1', '0', '1', '1', '1', '1', '1', '0', '1',
        '1', '0', '1', '0', '1', '0', '0', '0', '1', '1', '0', '1', '0', '1', '0', '0', '0', '0', '0', '0', '0', '1',
        '1', '0', '1', '0', '1', '1', '1', '0', '0', '1', '0', '1', '0', '1', '1', '1', '1', '1', '0', '1', '1', '1',
        '1', '0', '1', '0', '1', '0', '1', '1', '0', '1', '0', '1', '0', '0', '0', '0', '0', '1', '0', '0', '0', '1',
        '1', '0', '1', '0', '0', '0', '0', '1', '0', '1', '0', '1', '1', '1', '1', '1', '0', '1', '1', '1', '0', '1',
        '1', '0', '1', '1', '1', '1', '0', '1', '0', '1', '0', '1', '0', '0', '0', '1', '0', '1', '0', '0', '0', '1',
        '1', '0', '0', '0', '0', '1', '0', '1', '0', '1', '0', '0', '0', '1', '0', '1', '0', '1', '1', '1', '1', '1',
        '1', '0', '1', '1', '1', '1', '0', '1', '1', '1', '1', '1', '1', '1', '0', '1', '0', '0', '0', '1', '0', '1',
        '1', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '1', '1', '1', '0', '1',
        '1', '0', '1', '1', '1', '0', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1', '0', '1', '0', '0', '0', '1',
        '1', '0', '1', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '1', '0', '1', '1', '1',
        '1', '0', '1', '0', '1', '0', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1', '0', '0', '0', '1', '0', '1',
        '1', '0', '0', '0', '1', '0', '0', '0', '0', '1', '0', '0', '0', '1', '0', '1', '1', '1', '0', '1', '0', '1',
        '1', '0', '1', '0', '1', '1', '1', '1', '0', '1', '1', '1', '0', '0', '0', '0', '0', '1', '0', '1', '0', '1',
        '1', '0', '1', '0', '0', '0', '0', '1', '0', '0', '0', '1', '0', '1', '1', '1', '0', '0', '0', '1', '0', '1',
        '1', '1', '1', '1', '0', '1', '1', '1', '1', '1', '1', '1', '0', '1', '0', '1', '0', '1', '1', '1', '0', '1',
        '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '1', '0', '1', '0', '1', '0', '0', '0', '1',
        '1', '1', '1', '1', '0', '1', '1', '1', '1', '1', '1', '1', '0', '1', '0', '1', '1', '1', '0', '1', '1', '1',
        '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1',
        '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'};
    char map1[22][22] = {
        '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
        '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1',
        '1', '0', '1', '1', '1', '1', '1', '1', '0', '1', '1', '0', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1',
        '1', '0', '1', '0', '0', '0', '0', '0', '0', '1', '0', '0', '1', '1', '0', '0', '1', '1', '0', '1', '0', '1',
        '1', '0', '1', '1', '1', '1', '1', '0', '1', '0', '1', '1', '1', '0', '0', '0', '1', '1', '1', '1', '0', '1',
        '1', '0', '1', '0', '0', '0', '1', '0', '1', '0', '0', '1', '1', '1', '0', '1', '1', '0', '0', '0', '0', '1',
        '1', '0', '1', '0', '1', '0', '1', '0', '1', '0', '0', '1', '0', '0', '0', '1', '1', '0', '1', '1', '0', '1',
        '1', '0', '1', '0', '1', '0', '1', '0', '1', '1', '0', '0', '1', '0', '1', '0', '1', '1', '1', '1', '0', '1',
        '1', '0', '1', '1', '1', '1', '1', '0', '0', '0', '0', '1', '0', '0', '1', '1', '1', '1', '1', '0', '0', '1',
        '1', '0', '0', '0', '0', '0', '1', '1', '1', '1', '1', '0', '0', '0', '1', '0', '1', '0', '0', '0', '1', '1',
        '1', '0', '1', '1', '1', '1', '1', '0', '1', '1', '0', '0', '0', '1', '0', '1', '1', '0', '1', '1', '1', '1',
        '1', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '1', '0', '1', '1', '1', '0', '0', '0', '0', '0', '1',
        '1', '1', '1', '0', '0', '1', '1', '0', '0', '0', '1', '1', '0', '1', '1', '0', '0', '1', '1', '0', '1', '1',
        '1', '0', '0', '1', '1', '0', '1', '0', '1', '0', '0', '1', '1', '1', '1', '1', '0', '1', '1', '0', '1', '1',
        '1', '0', '1', '1', '1', '1', '1', '0', '1', '1', '0', '1', '1', '0', '0', '0', '0', '1', '0', '0', '1', '1',
        '1', '0', '1', '1', '1', '1', '1', '0', '1', '1', '0', '0', '1', '1', '1', '0', '1', '1', '0', '0', '0', '1',
        '1', '0', '0', '1', '1', '1', '1', '0', '1', '1', '1', '0', '1', '1', '1', '0', '1', '0', '0', '1', '1', '1',
        '1', '0', '1', '0', '1', '0', '1', '0', '1', '0', '1', '1', '1', '0', '0', '0', '1', '1', '0', '1', '1', '1',
        '1', '0', '1', '0', '1', '1', '1', '1', '1', '0', '0', '0', '1', '0', '1', '1', '1', '1', '0', '1', '0', '1',
        '1', '0', '0', '0', '1', '0', '1', '1', '1', '1', '1', '0', '0', '0', '0', '1', '0', '1', '1', '1', '1', '1',
        '1', '1', '1', '0', '1', '0', '1', '1', '1', '1', '1', '0', '1', '1', '1', '0', '1', '1', '0', '1', '0', '1',
        '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'};
};

#endif // _GAME_SCENE_H