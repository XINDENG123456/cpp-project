//initgraph(
//	width,  宽
//	height,  高
//	flag   窗口样式
//);


#include <graphics.h>
#include<iostream>
int main()
{
	initgraph(1280, 720);//绘制窗口，用后面的while卡住不让窗口消失
	int x = 300;
	int y = 300;
	BeginBatchDraw();///////////双缓冲优化

	/*while (true)
	{
		读取输入();
		更新画面();

	}*/

	//solidcircle(x,y,r)


	while (true) 
	{
		ExMessage msg; //这个结构体用于保存鼠标消息
		while (peekmessage(&msg))
		{
			if(msg.message == WM_MOUSEMOVE)//赋值改坐标
			{
				x = msg.x;
				y = msg.y;


			}
		}
		cleardevice();//清空原来的⚪
		solidcircle(x, y, 100);//绘制⚪
		FlushBatchDraw();////////////双缓冲优化
	}
	EndBatchDraw();/////////双缓冲优化
	return 0;
}