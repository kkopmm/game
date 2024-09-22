#ifndef _SCENE_MANAGER_H
#define _SCENE_MANAGER_H

#include "scene.h"

#include <iostream>

extern Scene *setting_scene;
extern Scene *menu_scene;
extern Scene *game_scene;
extern Scene *introduce_scene;
extern Scene *death_scene;
extern Scene *victory_scene;

enum class SceneType
{
	Menu,
	Game,
	Setting,
	Introduce,
	Death,
	Victory,
	Exit
};

class SceneManager
{
public:
	SceneManager() = default;
	~SceneManager() = default;
	void set_current_scene(Scene *scene)
	{
		current_scene = scene;
		current_scene->on_enter();
	};
	void on_update(float delta)
	{
		current_scene->on_update(delta);
	}
	void on_draw()
	{
		current_scene->on_draw();
	}
	void on_input(const ExMessage &msg)
	{
		current_scene->on_input(msg);
	}

	void switch_to(SceneType type)
	{
		current_scene->on_exit();
		switch (type)
		{
		case SceneType::Menu:
			std::cout << "进入Menu场景";
			current_scene = menu_scene;
			break;
		case SceneType::Game:
			std::cout << "进入Game场景";
			current_scene = game_scene;
			break;
		case SceneType::Setting:
			std::cout << "进入Setting场景";
			current_scene = setting_scene;
			break;
		case SceneType::Introduce:
			std::cout << "进入Setting场景";
			current_scene = introduce_scene;
			break;
		case SceneType::Death:
			std::cout << "进入Death场景";
			current_scene = death_scene;
			break;
		case SceneType::Victory:
			std::cout << "进入Victory场景";
			current_scene = victory_scene;
			break;
		case SceneType::Exit:
			std::cout << "进入Exit场景";
			exit(0);
			break;
		}
		current_scene->on_enter();
	}

private:
	Scene *current_scene = nullptr;
};

#endif // _SCENE_MANAGER_H