#include"MiniWord.h"
#include"Global.h"
#include"KeyBoard.h"

#include"Operate_State.h"
#define REPLACE 0
#define INPUT 1
bool Operate_Error(char * input);
void Operate_Edit()
{
	//hIn = GetStdHandle(STD_INPUT_HANDLE);
//	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	screem.Cursor_Pos = screem.Operate_Pos;
	SetConsoleCursorPosition(hOut, screem.Cursor_Pos); // 设置光标位置
	INPUT_RECORD keyRec;
	DWORD state = 0, res = 0;
	TCHAR ch = NULL;
	char input[MAX_INPUT] = { '\0' };
	int num = 0, i = 0, bianjie = 0;
	while (true)
	{
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
				if (VK_ESCAPE == keyRec.Event.KeyEvent.wVirtualKeyCode)
					break;
				if (VK_LSHIFT == keyRec.Event.KeyEvent.wVirtualKeyCode)
					continue;
				ch = keyRec.Event.KeyEvent.uChar.AsciiChar;

				if (ch <= 127 && ch >= 32)
				{
					input[num] = ch;
					num++;
					CharWindow(ch);
				}
				if (VK_BACK == keyRec.Event.KeyEvent.wVirtualKeyCode && bianjie == 0 && num>0)
				{
					num--;
					input[num] = '\0';
					BackSpace_Delete(&bianjie, screem.Operate_Pos);
				}
				else if (VK_BACK == keyRec.Event.KeyEvent.wVirtualKeyCode && bianjie == 1)
				{
					continue;
				}
				//如果按下ENTER键
				if (VK_RETURN == keyRec.Event.KeyEvent.wVirtualKeyCode)
				{

					if (!Operate_Error(input))//如果输入没有错误,将输入的信息交给状态函数判断，进而执行下一步命令
					{
						Operate_State(input);
						for (i = 0; i < num; i++)
						{
							input[i] = '\0';
						}
						num = 0;
					}
					else
					{
						Warning();
					}

				}
			}
		}

	}
	//CloseHandle(hIn);
	//CloseHandle(hOut);
}
bool Operate_Error(char * input)
{
	if (_tcscmp(input, "Replace") == 0 || _tcscmp(input, "Search") == 0)
		return false;
	else
		return true;
}