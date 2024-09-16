#include "global.h"
#include "resources_manager.h"

ResourcesManager *res_manager = ResourcesManager::instance();
bool music_on = true;
int main()
{
	loadimage1();
	srand((unsigned)time(NULL));
	HWND hwnd = initgraph(width, height);
	int a = 1;
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