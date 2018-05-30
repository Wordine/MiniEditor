#include<cstring>
#include<string>
#include<conio.h>
#include"MiniWord.h"
#include"Operate_State.h"
#include"Global.h"
#include"KeyBoard.h"
#include"Edit.h"

using namespace std;
#define REPLACE 0
#define SEARCH 1
int Input_Status;
static int Position[MAX_LINE + 1][MAX_COL + 1];
extern void Clear_Inform();
void Operate_State(char *input)
{
	ChaChu(input, screem.Operate_Pos);
	char *Source = nullptr, *Target = nullptr;
	int i, len_old = 0;
	if (_tcscmp(input, "Replace") == 0)
	{

		MessageBox(NULL, _T("请输入替换前的字符串"), _T("提示"), MB_OK);
		Source = KeyBoard_Name(screem.Operate_Pos);
		len_old = strlen(Source);
		for (i = strlen(Source); i >= 0; i--)
		{
			Source[i + 1] = Source[i];
		}
		if (Search_Replace(Source) == true)
		{
			RePlace(len_old);
			MessageBox(NULL, _T("替换完成"), _T("提示"), MB_OK);
		}
		SetConsoleCursorPosition(hOut, screem.Operate_Pos);
	}
	if (_tcscmp(input, "Search") == 0)
	{
		Input_Status = SEARCH;
		MessageBox(NULL, _T("请输入待查找的字符串"), _T("提示"), MB_OK);
		Target = KeyBoard_Name(screem.Operate_Pos);
		for (i = strlen(Target); i >= 0; i--)
		{
			Target[i + 1] = Target[i];
		}
		Search(Target);
		SetConsoleCursorPosition(hOut, screem.Operate_Pos);
	}
}
bool Search_Replace(const char *target)
{
	int i, j;
	int line, len, col;
	//char receiver[MAX_COL];
	char *text = nullptr;
	int  Count_Row, Count_Col, Count_Find_Num = 0;
	Count_Row = Get_Row();
	char a[1];
	COORD out_put = screem.Inform_Pos;

	for (i = 0; i <= MAX_LINE; i++)
	{
		for (j = 0; j <= MAX_COL; j++)
		{
			Position[i][j] = 0;
		}
	}
	for (line = 1; line <= Count_Row; line++)
	{
		Count_Col = Get_Col(line);
		text = Get_Line(line);
		Find_(text, target, Position, line);

		out_put.X = screem.Inform_Pos.X;
		for (col = 1; col <= Count_Col; col++)
		{
			if (Position[line][col] > 0)
			{
				Count_Find_Num++;
			}
			else
			{
				break;
			}
		}

		out_put.Y++;
	}
	if (Count_Find_Num == 0)
	{
		MessageBox(NULL, _T("找不到该字符串！"), _T("警告"), MB_OK | MB_ICONEXCLAMATION);
		return false;
	}
	return true;
}
bool Search(const char *target)
{
	int i, j;
	int line, len, col;
	//char receiver[MAX_COL];
	char *text = nullptr;
	int  Count_Row, Count_Col, Count_Find_Num = 0;
	Count_Row = Get_Row();
	char a[1];
	COORD out_put = screem.Inform_Pos;

	for (i = 0; i <= MAX_LINE; i++)
	{
		for (j = 0; j <= MAX_COL; j++)
		{
			Position[i][j] = 0;
		}
	}
	for (line = 1; line <= Count_Row; line++)
	{
		Count_Col = Get_Col(line);
		text = Get_Line(line);
		Find_(text, target, Position, line);
	
		out_put.X = screem.Inform_Pos.X;
		for (col = 1; col <= Count_Col; col++)
		{
			if (Position[line][col] > 0)
			{
				Edit_Update(line, Position[line][col], 9);
 				_getch();
			//	a[0] = text[Position[line][col]];
			//	WriteConsoleOutputCharacter(hOut, a,1, out_put, &num_written);
				out_put.X += 2;
				Count_Find_Num++;
			}
			else
			{
				break;
			}
		}

		out_put.Y++;
	}
	SetConsoleCursorPosition(hOut, screem.Operate_Pos);
	if (Count_Find_Num == 0)
	{
		MessageBox(NULL, _T("找不到该字符串！"), _T("警告"), MB_OK | MB_ICONEXCLAMATION);
		return false;
	}
	return true;
}
//寻找与替换对应字符串

void Find_(char *str, const char *target, int Position[][MAX_COL + 1], int row)
{
	int len = strlen(target);
	int nextval[MAX_INPUT];
	int pos = 1, i = 0, ans = 0, flag = 0;
	Get_Nextval(nextval, target);
	int col_length = Get_Col(row);
	while (pos<col_length && (ans != 0 || flag == 0))
	{
		flag = 1;
		ans = Index_KMP(str, target, pos, nextval, col_length);
		if (ans != 0)
		{
			i++;
			pos = ans + strlen(target) - 1;
			Position[row][i] = ans;
		}
	}
}
void Get_Nextval(int *nextval, const char *target)
{
	int j = 1, k = 0;
	nextval[1] = 0;
	while (j<strlen(target) - 1)
	{
		if (k == 0 || target[j] == target[k])
		{
			j++;
			k++;
			if (target[j] != target[k])
				nextval[j] = k;
			else
				nextval[j] = nextval[k];
		}
		else
			k = nextval[k];
	}
}
int Index_KMP(char *str, const char *target, int pos, int nextval[], int col_length)
{
	int i = pos, j = 1;
	while ((i < col_length) && (j < strlen(target)))
	{
		if (j == 0 || str[i] == target[j])
		{
			++i;
			++j;
		}
		else
		{
			j = nextval[j];
		}
	}
	if (j > (strlen(target) - 1))
		return i - strlen(target) + 1;
	else
		return 0;
}
void RePlace(int len_old)
{
	int  Count_Row, Count_Col, line, col;
	COORD out_put = screem.Inform_Pos;
	out_put.X = screem.Inform_Pos.X + 1;
	Count_Row = Get_Row();
	char a[50] = "Do you want to replace the string?(y or n)?";
	int flag = 1;
	Input_Status = REPLACE;
	INPUT_RECORD keyRec;
	DWORD state = 0, res = 0;
	TCHAR ch = NULL;
	char b[1];
	char *Target = nullptr;
	MessageBox(NULL, _T("请输入替换后的字符串"), _T("提示"), MB_OK);
	Target = KeyBoard_Name(screem.Operate_Pos);
	for (line = 1; line <= Count_Row; line++)
	{
		Count_Col = Get_Col(line);
		for (col = 1; col <= Count_Col; col++)
		{
			if (Position[line][col] > 0)
			{
				WriteConsoleOutputCharacter(hOut, " ", 1, out_put, &num_written);
				Edit_Update(line, Position[line][col], 9);
				WriteConsoleOutputCharacter(hOut, a, strlen(a), out_put, &num_written);
				WriteConsoleOutputCharacter(hOut, b, 1, out_put, &num_written);
				ReadConsoleInput(hIn, &keyRec, 1, &res);
				if (keyRec.EventType == KEY_EVENT)//如果当前事件是键盘事件
				{
					//只在按下时判断，弹起式不判断
					if (keyRec.Event.KeyEvent.bKeyDown)
					{
						//获取控制键的操作
						if (state != keyRec.Event.KeyEvent.dwControlKeyState)
						{
							state = keyRec.Event.KeyEvent.dwControlKeyState;
						}
						if (VK_RETURN == keyRec.Event.KeyEvent.wVirtualKeyCode)
						{
							Data_Replace(line, Position[line][col], Target, len_old, strlen(Target));
							out_put.X = out_put.X - strlen(a) - 1;
						}
						else
						{
							ch = keyRec.Event.KeyEvent.uChar.AsciiChar;
							while (ch != 'y'&&ch != 'n'&&(ch <= 127 && ch >= 32))
							{
								MessageBox(NULL, _T("你的输入有误！请重新选择："), _T("警告"), MB_OK | MB_ICONEXCLAMATION);
								ReadConsoleInput(hIn, &keyRec, 1, &res);
								ch = keyRec.Event.KeyEvent.uChar.AsciiChar;
							}
							out_put.X = out_put.X + strlen(a) + 1;
							b[0] = ch;
							WriteConsoleOutputCharacter(hOut, b, 1, out_put, &num_written);
							if (ch == 'y')
							{
								Data_Replace(line, Position[line][col], Target, len_old, strlen(Target));
								out_put.X = out_put.X - strlen(a) - 1;
							}
							else if (ch == 'n')
							{
								out_put.X = out_put.X - strlen(a) - 1;
								continue;
							}
						}
					}
				}
			}
		}
	}
	Clear_Inform();
}