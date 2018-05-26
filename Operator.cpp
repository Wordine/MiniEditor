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
	SetConsoleCursorPosition(hOut, screem.Cursor_Pos); // ���ù��λ��
	INPUT_RECORD keyRec;
	DWORD state = 0, res = 0;
	TCHAR ch = NULL;
	char input[MAX_INPUT] = { '\0' };
	int num = 0, i = 0, bianjie = 0;
	while (true)
	{
		ReadConsoleInput(hIn, &keyRec, 1, &res);
		if (keyRec.EventType == KEY_EVENT)//�����ǰ�¼��Ǽ����¼�
		{
			//ֻ�ڰ���ʱ�жϣ�����ʽ���ж�
			if (keyRec.Event.KeyEvent.bKeyDown)
			{
				//��ȡ���Ƽ��Ĳ���
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
				//�������ENTER��
				if (VK_RETURN == keyRec.Event.KeyEvent.wVirtualKeyCode)
				{

					if (!Operate_Error(input))//�������û�д���,���������Ϣ����״̬�����жϣ�����ִ����һ������
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