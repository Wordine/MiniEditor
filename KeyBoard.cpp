#include<iostream>
#include"KeyBoard.h"
#include"Global.h"
#include"InterFace.h"

using namespace std;
extern struct Screem screem;

void CharWindow(TCHAR ch)//////////////////当搜索的字符长度比搜索框长时，应该进行处理。
{ // 将字符输入到指定的窗口中
	//int x = screem.Cursor_Pos.X;
	WriteConsoleOutputCharacter(hOut, &ch, 1, screem.Cursor_Pos, &num_written);
	screem.Cursor_Pos.X++;
	SetConsoleCursorPosition(hOut, screem.Cursor_Pos); // 设置光标位置
}

char *KeyBoard_Name(COORD WeiZhi)
{
	INPUT_RECORD keyRec;
	DWORD res = 0;
	TCHAR ch = NULL;
	static char key_input[MAX_INPUT];
	int num = 0, i = 0, bianjie = 0, state = 0;
	screem.Cursor_Pos = WeiZhi;
	SetConsoleCursorPosition(hOut, screem.Cursor_Pos);
	for (i = 0; i < MAX_INPUT; i++)
	{
		key_input[i] = '\0';
	}
	while (true)
	{
		ReadConsoleInput(hIn, &keyRec, 1, &res);
		if (keyRec.EventType == KEY_EVENT)//如果当前事件是键盘事件
		{
			//只在按下时判断，弹起式不判断
			if (keyRec.Event.KeyEvent.bKeyDown)
			{
				if (state != keyRec.Event.KeyEvent.dwControlKeyState)
				{
					state = keyRec.Event.KeyEvent.dwControlKeyState;
				}
				if (keyRec.Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE)
					break;
				if (VK_LSHIFT == keyRec.Event.KeyEvent.wVirtualKeyCode)//如果按下左shift键，表示切换输入法，不响应
					continue;
				// 按键事件响应代码
				ch = keyRec.Event.KeyEvent.uChar.AsciiChar;
				if (ch <= 127 && ch >= 32)
				{
					CharWindow(ch);
					key_input[num] = ch;
					num++;
				}
				if (VK_BACK == keyRec.Event.KeyEvent.wVirtualKeyCode && bianjie == 0&&num>0)
				{
					num--;
					key_input[num] = '\0';
					BackSpace_Delete(&bianjie, WeiZhi);
				}
				else if(VK_BACK == keyRec.Event.KeyEvent.wVirtualKeyCode && bianjie == 1)
				{
					continue;
				}
				//如果按下ENTER键
				if (VK_RETURN == keyRec.Event.KeyEvent.wVirtualKeyCode)
				{
					ChaChu(key_input, WeiZhi);
				//	a[0] = strlen(key_input) + '0';
					//WriteConsoleOutputCharacter(hOut, key_input, strlen(key_input), screem.Inform_Pos, &num_written);
				//	WriteConsoleOutputCharacter(hOut, a, 1, screem.Inform_Pos, &num_written);
					return key_input;
				}
			}
		}
	}
}
void BackSpace_Delete(int* flag, COORD WeiZhi)
{ // 按回车键删除字符
	COORD letterPos;
	if (screem.Cursor_Pos.X >= (WeiZhi.X))
	{
		// 边框线的宽为两个字符，为一个字符
		letterPos = screem.Cursor_Pos;
		letterPos.X--;
		WriteConsoleOutputCharacter(hOut, " ", 1, letterPos, &num_written);
		screem.Cursor_Pos.X--;
		SetConsoleCursorPosition(hOut, screem.Cursor_Pos); // 设置光标位置
	}
	else
	{
		*flag = 1;
	}
}
void ChaChu(char input[], COORD WeiZhi)
{
	int num = _tcslen(input);
	COORD Recover_curPoi = screem.Cursor_Pos;
	while (Recover_curPoi.X >= WeiZhi.X)
	{
		WriteConsoleOutputCharacter(hOut, " ", 1, Recover_curPoi, &num_written);
		Recover_curPoi.X--;
	}
	screem.Cursor_Pos = WeiZhi;
	SetConsoleCursorPosition(hOut, WeiZhi);
}
void Warning()
{
	MessageBox(NULL, _T("你的输入有误！"), _T("警告"), MB_OK | MB_ICONEXCLAMATION);
}