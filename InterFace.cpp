#include<tchar.h>
#include"Global.h"
#include"InterFace.h"
int LEFT = 0, RIGHT = 0, TOP = 0, BOTTOM = 0;   //我这个文件要用的
const int SCREEN_EIGHT_N = 18;
void Get_Screen()
{
	
	GetConsoleScreenBufferInfo(hOut, &bInfo);//获取窗口缓冲区信息
	LEFT = bInfo.srWindow.Left + 21, RIGHT = LEFT + SCREEN_EIGHT_N * 8 + 4, TOP = bInfo.srWindow.Top, BOTTOM = bInfo.srWindow.Bottom;
	BLEFT = LEFT + 2;
	BRIGHT = RIGHT - 2;
	BTOP = TOP + 4;
	BBOTTOM = BOTTOM - 6;
	BWIDTH = BRIGHT - BLEFT;
	BHEIGHT = BBOTTOM - BTOP - 2;
	INFOHEIGHT = BOTTOM - BBOTTOM + 1;

	screem.Cursor_Pos.X = LEFT + 82;
	screem.Cursor_Pos.Y = TOP + 1;

	screem.File_Pos.X = LEFT + 82;
	screem.File_Pos.Y = TOP + 1;

	screem.Operate_Pos.X = LEFT + 27;
	screem.Operate_Pos.Y =TOP + 4;

	screem.Edit_Pos.X = LEFT + 2;
	screem.Edit_Pos.Y = TOP + 7;

	screem.Inform_Pos.X = LEFT + 2;
	screem.Inform_Pos.Y = BOTTOM - 4;
}
void Initial()
{
	LPCTSTR title = "MiniWord";
	SetConsoleTitle(title);		//窗口命名
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);//屏幕最大化
	Get_Screen();

	WORD att = BACKGROUND_INTENSITY | FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;//设置背景为白色，显示为黑色
	SetConsoleTextAttribute(hOut, att);
	BeiJing();	// 清屏（将屏幕设置为想要的样子）		
	Navigation();
	Navigation_Search();
	//SMALL_RECT DaoHang_One = { LEFT, TOP + 3, RIGHT, TOP + 6 };
	//DrawBox(DaoHang_One);
	SMALL_RECT search = { LEFT + 80, TOP, RIGHT - 5, TOP + 2 };
	DrawBox(search);
	SMALL_RECT Search_One = { LEFT + 25, TOP + 3, RIGHT - 15, TOP + 5 };
	DrawBox(Search_One);
	SMALL_RECT WenBen = { LEFT, TOP + 6, RIGHT, BOTTOM - 5 };
	DrawBox(WenBen);//打印出文本框
	SMALL_RECT  TiShi = { LEFT, BOTTOM - 5 , RIGHT, BOTTOM };
	DrawBox(TiShi);
	//system("pause>nul");//为了不显示“按任意键继续”
}
void DrawBox(SMALL_RECT rc) 
{
	TCHAR chBox[6][3] = { _T("┌"), _T("┐"), _T("└"), _T("┘"), _T("─"), _T("│") };//经过测试，一个这样的字符要占3个字节，TCHAR为通用字符
	COORD pos = { rc.Left, rc.Top };

	for (pos.X = rc.Left; pos.X < rc.Right; pos.X += 2) //不知道为什么要增2，但是改成其他的不正确
	{
		pos.Y = rc.Top;
		//句柄，字符串，字符个数，起始位置，已写个数
		WriteConsoleOutputCharacter(hOut, chBox[4], (int)_tcslen(chBox[4]), pos, &num_written);// 顶
		pos.Y = rc.Bottom;
		WriteConsoleOutputCharacter(hOut, chBox[4], (int)_tcslen(chBox[4]), pos, &num_written);// 底
	}
	for (pos.Y = rc.Top; pos.Y < rc.Bottom; ++pos.Y)
	{
		pos.X = rc.Left;
		WriteConsoleOutputCharacter(hOut, chBox[5], (int)_tcslen(chBox[5]), pos,
			&num_written);// 左
		pos.X = rc.Right;
		WriteConsoleOutputCharacter(hOut, chBox[5], (int)_tcslen(chBox[5]), pos,
			&num_written);// 右
	}
	pos.X = rc.Left;
	pos.Y = rc.Top;
	WriteConsoleOutputCharacter(hOut, chBox[0], (int)_tcslen(chBox[0]), pos, &num_written);// 左
	pos.X = rc.Right;
	pos.Y = rc.Top;
	WriteConsoleOutputCharacter(hOut, chBox[1], (int)_tcslen(chBox[1]), pos, &num_written);// 右C/C++控制台界面编程(V 4) (wyz5@163.com 整理)
	pos.X = rc.Left;
	pos.Y = rc.Bottom;
	WriteConsoleOutputCharacter(hOut, chBox[2], (int)_tcslen(chBox[2]), pos, &num_written);// 左
	pos.X = rc.Right;
	pos.Y = rc.Bottom;
	WriteConsoleOutputCharacter(hOut, chBox[3], (int)_tcslen(chBox[3]), pos, &num_written);// 右
}



void Navigation()
{
	const char *CaiDan = "New    Open    Close    ReName    Save    Save_As    Quit";

	WORD  CaiDan_Color = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_BLUE;//文本属性
	COORD Show_CaiDan = { LEFT + 1, TOP };
	int i;
	for (i = 0; i < 3; i++)
	{
		FillConsoleOutputAttribute(hOut, CaiDan_Color, RIGHT - LEFT, Show_CaiDan, &num_written);
		Show_CaiDan.Y++;
	}
	Show_CaiDan.X += 1;
	Show_CaiDan.Y -= 2;
	WriteConsoleOutputCharacter(hOut, CaiDan, _tcslen(CaiDan), Show_CaiDan, &num_written);
}
void Navigation_Search()
{
	const char *CaiDan = "Search    Replace";

	WORD  CaiDan_Color = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_BLUE;//文本属性
	COORD Show_CaiDan = { LEFT + 1, TOP + 3 };
	int i;
	for (i = 0; i < 4; i++)
	{
		FillConsoleOutputAttribute(hOut, CaiDan_Color, RIGHT - LEFT, Show_CaiDan, &num_written);
		Show_CaiDan.Y++;
	}
	Show_CaiDan.X += 1;
	Show_CaiDan.Y -= 3;
	WriteConsoleOutputCharacter(hOut, CaiDan, _tcslen(CaiDan), Show_CaiDan, &num_written);
}
void BeiJing(void)
{
	_tsystem(_T("cls"));//system(“cls” )用于清除窗口中的文字
}