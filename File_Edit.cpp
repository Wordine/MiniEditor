#include"MiniWord.h"
#include"File_Edit.h"
#include"Global.h"
#include"KeyBoard.h"

void File_Edit()
{
	screem.Cursor_Pos = screem.File_Pos;
	SetConsoleCursorPosition(hOut, screem.Cursor_Pos); // 设置光标位置
	INPUT_RECORD keyRec;
	DWORD state = 0, res = 0;
	TCHAR ch = NULL;
	int num = 0, i = 0, bianjie = 0;
	 static char input[MAX_INPUT] = { '\0' };
	 for (i = 0; i < MAX_INPUT; i++)
	 {
		 input[i] = '\0';
	 }
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
				{
					break;
				}
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
					BackSpace_Delete(&bianjie, screem.File_Pos);
				}
				else if (VK_BACK == keyRec.Event.KeyEvent.wVirtualKeyCode && bianjie == 1)
				{
					continue;
				}
				//如果按下ENTER键
				if (VK_RETURN == keyRec.Event.KeyEvent.wVirtualKeyCode)
				{

					if (!File_Error(input))//如果输入没有错误,将输入的信息交给状态函数判断，进而执行下一步命令
					{
						File_State(input);
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
//	CloseHandle(hOut);
}
int File_Error(char input[])
{
	if (_tcscmp(input, "Open") == 0 || _tcscmp(input, "Close") == 0 || _tcscmp(input, "ReName") == 0 || _tcscmp(input, "Save") == 0 ||
		_tcscmp(input, "Save_As") == 0 || _tcscmp(input, "Enter_Edit") == 0 || _tcscmp(input, "Help") == 0 || _tcscmp(input, "Quit") == 0)
		return 0;
	else
		return 1;
}