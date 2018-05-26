#include<cstring>
#include<string>
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
void Operate_State(char *input)
{
	ChaChu(input, screem.Operate_Pos);
	char *Source = nullptr, *Target = nullptr;
	int i;
	if (_tcscmp(input, "Replace") == 0)
	{
		Input_Status = REPLACE;

		MessageBox(NULL, _T("�������滻ǰ���ַ���"), _T("��ʾ"), MB_OK);
		Source = KeyBoard_Name(screem.Operate_Pos);
		Search(Source);
		MessageBox(NULL, _T("�������滻����ַ���"), _T("��ʾ"), MB_OK);
		Target = KeyBoard_Name(screem.Operate_Pos);
	}
	if (_tcscmp(input, "Search") == 0)
	{
		Input_Status = SEARCH;
		MessageBox(NULL, _T("����������ҵ��ַ���"), _T("��ʾ"), MB_OK);
		Target = KeyBoard_Name(screem.Operate_Pos);
		for (i = strlen(Target); i >= 0; i--)
		{
			Target[i + 1] = Target[i];
		}
		Search(Target);
	}
}
void Search(const char *target)
{
	int i, j;
	int line, len, col;
	//char receiver[MAX_COL];
	char *text;
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
		//WriteConsoleOutputCharacter(hOut, receiver, strlen(receiver), out_put, &num_written);
		Find_(text, target, Position, line);
	
		out_put.X = screem.Inform_Pos.X;
		for (col = 1; col <= Count_Col; col++)
		{
			if (Position[line][col] > 0)
			{
				Edit_Update(line, Position[line][col], 9);
				a[0] = text[Position[line][col]];
				WriteConsoleOutputCharacter(hOut, a,1, out_put, &num_written);
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
	if (Count_Find_Num == 0)
	{
		MessageBox(NULL, _T("�Ҳ������ַ�����"), _T("����"), MB_OK | MB_ICONEXCLAMATION);
	}
}
//Ѱ�����滻��Ӧ�ַ���

void Find_(char *str, const char *target, int Position[][MAX_COL + 1], int row)
{
	int len = strlen(target);
	int nextval[MAX_INPUT];
	int pos = 1, i = 0, ans = 0, flag = 0;
	Get_Nextval(nextval, target);

	while (pos<strlen(str) && (ans != 0 || flag == 0))
	{
		flag = 1;
		ans = Index_KMP(str, target, pos, nextval);
		if (ans != 0)
		{
			i++;
			pos = ans + strlen(target) - 1;
			Position[row][i] = ans + 1;
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
int Index_KMP(char *str, const char *target, int pos, int nextval[])
{
	int i = pos, j = 1;
	while ((i < strlen(str)) && (j < strlen(target)))
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
		return i - strlen(target);
	else
		return 0;
}
void Replace()
{
	//Line_Replace(int row, int col, char* oldline, char* newline, int old_len, int new_len)
}