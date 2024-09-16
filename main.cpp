#include "global.h"
#include "resources_manager.h"

ResourcesManager *res_manager = ResourcesManager::instance();

int main()
{
	loadimage1();
	srand((unsigned)time(NULL));
	initgraph(width, height);
	int a = 1;

	while (1)
	{
		switch (a)
		{
		case 1:
			a = Menu();
			break;
		case 2:
			gamebk();
			a = gameface();
			break;
		case 3:
			a = setmusicface();
			break;
		case 4:
			a = introduce();
			break;
		default:
			closegraph();
			setmusic(0);
			break;
		}
	}
}