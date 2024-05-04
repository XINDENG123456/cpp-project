#include<graphics.h>
int i,j;
char board_data[3][3];
 void initialize_board(){
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			board_data[i][j] = '-';
		}
		}
	}
 char current_piece = 'O';
//检测获胜
bool CheckWin(char c) {
	if ();
	return true;

	return false;
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


}
//绘制棋盘网格
void DrawBoard()
{
	line(0, 200, 600, 200);
	line(0, 400, 600, 400);
	line(200, 0, 200, 400);
	line(400, 0, 400, 600);
}
//绘制棋子
void DrawPiece()
{
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			switch (board_data[i][j]) {
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
	static TCHAR str[64];
	_stprintf_s(str, _T("当前棋子类型：%c"), current_piece);
	settextcolor(RGB(225, 175, 45));
	outtextxy(0, 0, str);
}
int main()
{
	initgraph(600, 600);
	initialize_board();
	bool running = true;

	ExMessage msg;

	BeginBatchDraw();
	while (running) 
	{
		DWORD start_time = GetTickCount();
		while (peekmessage(&msg)) {
			if (msg.message == WM_LBUTTONDOWN)
			{//计算点击位置
				int x = msg.x;
				int y = msg.y;
				int index_x = x / 200;
				int index_y = y / 200;
				//尝试落子
				if (board_data[index_y][index_x] == '-') {
					board_data[index_y][index_x] == current_piece;
				}
				if (current_piece == 'O')
					current_piece = 'X';
				else
					current_piece = 'O';

				//Sleep(15);
			}

		}
		cleardevice();
		DrawBoard();
		DrawPiece();
		DrawTipText();

		FlushBatchDraw();
		if (CheckWin('X')) {

			MessageBox(GetHWnd(), _T("X玩家赢"), _T("游戏结束"), MB_OK);
			running = false;
		}
		else if (CheckWin('O')) {

			MessageBox(GetHWnd(), _T("O玩家赢"), _T("游戏结束"), MB_OK);
			running = false;
		}
		else if (CheckDraw()) {

			MessageBox(GetHWnd(), _T("平局"), _T("游戏结束"), MB_OK);
			running = false;
		}
		DWORD end_time = GetTickCount();
		DWORD delta_time = end_time - start_time;
		if (delta_time < 1000 / 60) {
			Sleep(1000 / 60 - delta_time);
		}
	}
	EndBatchDraw();

}