#include<graphics.h>
#include<string>
int idx_current_anim = 0;//存储当前动画的帧索引  没搞懂？？？/

const int PLAYER_ANIM_NUM = 6;//动画帧总数常量
const int PLAYER_SPEED = 3;

IMAGE img_player_left[PLAYER_ANIM_NUM];
IMAGE img_player_right[PLAYER_ANIM_NUM];

POINT player_pos = { 500,500 };

#pragma comment(lib,"MSIMG32.LIB")

inline void putimage_alpha(int x,int y,IMAGE* img)//实现透明通道混叠
{
	int w = img->getwidth();
	int h = img->getheight();
	AlphaBlend(GetImageHDC(NULL), x, y, w, h,
		GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });

}

void LoadAnimation()//循环加载图片
{
	for (size_t i = 0; i < PLAYER_ANIM_NUM; i++)
	{
		std::wstring path = L"img/player_left_" + std::to_wstring(i) + L".png";
		loadimage(&img_player_left[i], path.c_str());
	}
	for (size_t i = 0; i < PLAYER_ANIM_NUM; i++)
	{
		std::wstring path = L"img/player_right_" + std::to_wstring(i) + L".png";
		loadimage(&img_player_right[i], path.c_str());
	}
}

int main()
{
	initgraph(1280, 720);

	bool running = true;

	ExMessage msg;
	IMAGE img_background;

	bool is_move_up = false;
	bool is_move_down = false;//优化移动手感
	bool is_move_left = false;
	bool is_move_right = false;

	LoadAnimation();
	loadimage(&img_background, _T("img/background.png"));

	BeginBatchDraw();

	while (running)
	{
		DWORD start_time = GetTickCount();

		while (peekmessage(&msg)) 
		{
			if (msg.message == WM_KEYDOWN)
			{
				switch (msg.vkcode)
				{
				case VK_UP:
					is_move_up = true;
					player_pos.y -= PLAYER_SPEED;
					break;
				case VK_DOWN:
					is_move_down = true;
					player_pos.y += PLAYER_SPEED;
					break;
				case VK_LEFT:
					is_move_left = true;
					player_pos.x -= PLAYER_SPEED;
					break;
				case VK_RIGHT:
					is_move_right = true;
					player_pos.x += PLAYER_SPEED;
					break;
				}

			}
			else if (msg.message == WM_KEYUP)
			{
				switch (msg.vkcode)
				{
				case VK_UP:
					is_move_up = false;
					break;
				case VK_DOWN:
					is_move_down = false;
					break;
				case VK_LEFT:
					is_move_left = false;
					break;
				case VK_RIGHT:
					is_move_right = false;
					break;



				}


			}

		}
		
		if (is_move_up) player_pos.y -= PLAYER_SPEED;
		if (is_move_down) player_pos.y += PLAYER_SPEED;
		if (is_move_left) player_pos.x -= PLAYER_SPEED;
		if (is_move_right) player_pos.x += PLAYER_SPEED;


		static int counter = 0;//记录当前动画帧一共播放了几个游戏帧  static确保计数器只在第一个游戏帧时被初始化为0
		if (++counter % 5 == 0)//每5个游戏帧切换一个动画帧
			idx_current_anim++;

		//使动画循环播放
		idx_current_anim = idx_current_anim % PLAYER_ANIM_NUM;

		cleardevice();

		putimage(0, 0, &img_background);
		putimage_alpha(player_pos.x, player_pos.y, &img_player_left[idx_current_anim]);//原本是putimage函数

		FlushBatchDraw();

		DWORD end_time = GetTickCount();
		DWORD delta_time = end_time - start_time;
		if (delta_time < 1000 / 144)
		{
			Sleep(1000 / 144 - delta_time);
		}


	}
	EndBatchDraw();
	return 0;
}