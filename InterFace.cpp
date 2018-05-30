#include<tchar.h>
#include"Global.h"
#include"InterFace.h"
int LEFT = 0, RIGHT = 0, TOP = 0, BOTTOM = 0;   //������ļ�Ҫ�õ�
const int SCREEN_EIGHT_N = 18;
void Get_Screen()
{
	
	GetConsoleScreenBufferInfo(hOut, &bInfo);//��ȡ���ڻ�������Ϣ
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
	SetConsoleTitle(title);		//��������
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);//��Ļ���
	Get_Screen();

	WORD att = BACKGROUND_INTENSITY | FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;//���ñ���Ϊ��ɫ����ʾΪ��ɫ
	SetConsoleTextAttribute(hOut, att);
	BeiJing();	// ����������Ļ����Ϊ��Ҫ�����ӣ�		
	Navigation();
	Navigation_Search();
	//SMALL_RECT DaoHang_One = { LEFT, TOP + 3, RIGHT, TOP + 6 };
	//DrawBox(DaoHang_One);
	SMALL_RECT search = { LEFT + 80, TOP, RIGHT - 5, TOP + 2 };
	DrawBox(search);
	SMALL_RECT Search_One = { LEFT + 25, TOP + 3, RIGHT - 15, TOP + 5 };
	DrawBox(Search_One);
	SMALL_RECT WenBen = { LEFT, TOP + 6, RIGHT, BOTTOM - 5 };
	DrawBox(WenBen);//��ӡ���ı���
	SMALL_RECT  TiShi = { LEFT, BOTTOM - 5 , RIGHT, BOTTOM };
	DrawBox(TiShi);
	//system("pause>nul");//Ϊ�˲���ʾ���������������
}
void DrawBox(SMALL_RECT rc) 
{
	TCHAR chBox[6][3] = { _T("��"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��") };//�������ԣ�һ���������ַ�Ҫռ3���ֽڣ�TCHARΪͨ���ַ�
	COORD pos = { rc.Left, rc.Top };

	for (pos.X = rc.Left; pos.X < rc.Right; pos.X += 2) //��֪��ΪʲôҪ��2�����Ǹĳ������Ĳ���ȷ
	{
		pos.Y = rc.Top;
		//������ַ������ַ���������ʼλ�ã���д����
		WriteConsoleOutputCharacter(hOut, chBox[4], (int)_tcslen(chBox[4]), pos, &num_written);// ��
		pos.Y = rc.Bottom;
		WriteConsoleOutputCharacter(hOut, chBox[4], (int)_tcslen(chBox[4]), pos, &num_written);// ��
	}
	for (pos.Y = rc.Top; pos.Y < rc.Bottom; ++pos.Y)
	{
		pos.X = rc.Left;
		WriteConsoleOutputCharacter(hOut, chBox[5], (int)_tcslen(chBox[5]), pos,
			&num_written);// ��
		pos.X = rc.Right;
		WriteConsoleOutputCharacter(hOut, chBox[5], (int)_tcslen(chBox[5]), pos,
			&num_written);// ��
	}
	pos.X = rc.Left;
	pos.Y = rc.Top;
	WriteConsoleOutputCharacter(hOut, chBox[0], (int)_tcslen(chBox[0]), pos, &num_written);// ��
	pos.X = rc.Right;
	pos.Y = rc.Top;
	WriteConsoleOutputCharacter(hOut, chBox[1], (int)_tcslen(chBox[1]), pos, &num_written);// ��C/C++����̨������(V 4) (wyz5@163.com ����)
	pos.X = rc.Left;
	pos.Y = rc.Bottom;
	WriteConsoleOutputCharacter(hOut, chBox[2], (int)_tcslen(chBox[2]), pos, &num_written);// ��
	pos.X = rc.Right;
	pos.Y = rc.Bottom;
	WriteConsoleOutputCharacter(hOut, chBox[3], (int)_tcslen(chBox[3]), pos, &num_written);// ��
}



void Navigation()
{
	const char *CaiDan = "New    Open    Close    ReName    Save    Save_As    Quit";

	WORD  CaiDan_Color = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_BLUE;//�ı�����
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

	WORD  CaiDan_Color = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_BLUE;//�ı�����
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
	_tsystem(_T("cls"));//system(��cls�� )������������е�����
}