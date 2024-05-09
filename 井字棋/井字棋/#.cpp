//可以依据此做一个五子棋（改一些数据，加一点算法）
//initgraph(
//	width,  宽
//	height,  高
//	flag   窗口样式
//);

#include<graphics.h>
#include<iostream>
//int i,j;
char board_data[3][3] =
{
	{ '-', '-', '-' },
	{ '-', '-', '-' },
	{ '-', '-', '-' },
};
//char board_data[3][3];
// void initialize_board(){
//	for (i = 0; i < 3; i++) {
//		for (j = 0; j < 3; j++) {
//			board_data[i][j] = '-';
//		}
//	}
//}
 char current_piece = 'O';//
//检测获胜
bool CheckWin(char c) {

	if (board_data[0][0] == c && board_data[0][1] == c && board_data[0][2] == c)
		return true;
	if (board_data[1][0] == c && board_data[1][1] == c && board_data[1][2] == c)
		return true;
	if (board_data[2][0] == c && board_data[2][1] == c && board_data[2][2] == c)
		return true;
	if (board_data[0][0] == c && board_data[1][0] == c && board_data[2][0] == c)
		return true;
	if (board_data[0][1] == c && board_data[1][1] == c && board_data[2][1] == c)
		return true;
	if (board_data[0][2] == c && board_data[1][2] == c && board_data[2][2] == c)
		return true;
	if (board_data[0][0] == c && board_data[1][1] == c && board_data[2][2] == c)
		return true;
	if (board_data[0][2] == c && board_data[1][1] == c && board_data[2][0] == c)
		return true;

	return false;
	/*for (i = 0; i < 3; i++) {
		 j = 0;
		 if (board_data[i][j] == c && board_data[i][j + 1] == c && board_data[i][j + 2] == c)
			 return true;
	}
	for (j = 0; j < 3; j++) {
		i = 0;
		if (board_data[i][j] == c && board_data[i+1][j] == c && board_data[i+2][j] == c)
			return true;
	}
	i = 0; j = 0;
	if (board_data[i][j] == c && board_data[i + 1][j + 1] == c && board_data[i + 2][j + 2] == c)
		return true;
		i = 0; j = 2;
		if (board_data[i][j] == c && board_data[i + 1][j - 1] == c && board_data[i + 2][j -2] == c)
			return true;
	return false;*/
}
//检测平局
bool CheckDraw()
{
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++) {
			if (board_data[i][j] == '-')
			{
				return false;
			}

		}

	}
	return true;

}
//绘制棋盘网格
void DrawBoard()
{
	line(0, 200, 600, 200);
	line(0, 400, 600, 400);
	line(200, 0, 200, 600);
	line(400, 0, 400, 600);
}
//绘制棋子
void DrawPiece()
{
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			switch (board_data[i][j])
			{
			case 'O':
				circle(200 * j + 100, 200 * i + 100, 100);
				break;
			case'X':
				line(200 * j, 200 * i, 200 * (j + 1), 200 * (i + 1));
				line(200 * (j+1), 200 * i, 200 * j , 200 * (i + 1));
				break;
			case'-':
				break;
			default:
				break;
			}

		}

	}
}
//绘制提示信息
void DrawTipText()
{
	static TCHAR str[64];//定义TCHAR类型字符数组作为格式化的缓冲区
	_stprintf_s(str, _T("当前棋子类型：%c"), current_piece);//字符串格式化函数
	settextcolor(RGB(225, 175, 45));//橙黄色
	outtextxy(0, 0, str);//在x，y，以字符串形式显示文本
}
int main()
{
	initgraph(600, 600);//绘制窗口，用后面的while卡住不让窗口消失
	/*initialize_board();*/
	bool running = true;

	const int fps = 60;

	ExMessage msg;

	BeginBatchDraw();

	/*
	初始化（）：

	while (true)
	{
		读取输入操作();
		处理数据（）；
		更新绘制画面();

	}
	释放资源（）；

	*/

	//solidcircle(x,y,r)


	while (running)
	{
		DWORD start_time = GetTickCount();//获取系统自启动以来经历的毫秒数   //减CPU
		while (peekmessage(&msg))
		{
			//在这里执行消息处理逻辑
		
			if (msg.message == WM_LBUTTONDOWN) //按下，在message那个表格里
			{//计算点击位置
				int x = msg.x;
				int y = msg.y;
				int index_x = x / 200;
				int index_y = y / 200;
				//尝试落子
				if (board_data[index_y][index_x] == '-') 
				{
					board_data[index_y][index_x] = current_piece;//这里多打了个“=”检查了好久

					if (current_piece == 'O')
						current_piece = 'X';
					else
						current_piece = 'O';
				}

			//Sleep(15);
			}

		}
		

		

		/*MessageBox(
			hWnd,  父窗口句柄 //GetHWnd() 获取窗口句柄
			text,    提示内容
			caption,   弹窗标题
			type        弹窗样式  //MB_OK  使弹出的提示窗口中只有OK一个确认按键
			);*/
		cleardevice();//是用当前背景色清空屏幕，并将当前点移至 (0, 0)//注释了好像也没影响？？

		DrawBoard();
		DrawPiece();
		DrawTipText();

		FlushBatchDraw();


		if (CheckWin('X'))
		{

			MessageBox(GetHWnd(), _T("X玩家赢"), _T("游戏结束"), MB_OK);
			running = false;
		}
		else if (CheckWin('O')) 
		{

			MessageBox(GetHWnd(), _T("O玩家赢"), _T("游戏结束"), MB_OK);
			running = false;
		}
		else if (CheckDraw()) 
		{

			MessageBox(GetHWnd(), _T("平局"), _T("游戏结束"), MB_OK);
			running = false;
		}
		DWORD end_time = GetTickCount();//
		DWORD delta_time = end_time - start_time;
		if (delta_time < 1000 / fps) 
		{
			Sleep(1000 / fps - delta_time);//用sleep延时减CPU占用率

		}
		

	

		
	}
	EndBatchDraw();


	return 0;
}