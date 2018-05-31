#include<io.h>
#include<cstdio>
#include "MiniWord.h"
#include"File_State.h"
#include"Global.h"
#include"KeyBoard.h"

#include "Edit_Intial.h"
extern void Clear_Inform();
extern void Edit_Update(int);
static char *File_Name = nullptr;
int FILE_STATE = 0;
static int HAS_FILE_OPEN_NEW = 0;
void File_State(char input[])
{
	ChaChu(input, screem.File_Pos);
	if (_tcscmp(input, "New") == 0)
	{
		if (HAS_FILE_OPEN_NEW == 1)//����Ѿ����й��ļ��½���򿪲������ȹرյ�ǰ�ļ��ٽ��в���
		{
			Close_File();
		}
		IF_HAS_SAVE = 0;
		Mini.File_Open();
		FILE_STATE = OPEN;
		HAS_FILE_OPEN_NEW = 1;
	}
	else if (_tcscmp(input, "Open") == 0)
	{
		if (HAS_FILE_OPEN_NEW == 1)//����Ѿ����й��ļ��½���򿪲������ȹرյ�ǰ�ļ��ٽ��в���
		{
			Close_File();
		}
		MessageBox(NULL, _T("��������Ҫ�򿪵��ļ���"), _T("��ʾ"), MB_OK);
		File_Name = KeyBoard_Name(screem.File_Pos);
		if (_access(File_Name, 0) != 0)
		{
			int result = MessageBox(NULL, _T("���ļ������ڣ����Ƿ�Ҫ�½����ļ���"), _T("����"), MB_YESNO);
			switch (result)
			{
			case IDYES:
				IF_HAS_SAVE = 0;
				Mini.File_Open();
				FILE_STATE = OPEN;
				HAS_FILE_OPEN_NEW = 1;
				break;
			case IDNO:
				break;
			}
		}
		else
		{
			Open(File_Name);
			FILE_STATE = OPEN;
			IF_HAS_SAVE = 1;
			HAS_FILE_OPEN_NEW = 1;
		}
	}
	else if (_tcscmp(input, "Close") == 0)
	{
		Close_File();
	}
	else if (_tcscmp(input, "ReName") == 0)
	{
		remove(File_Name);
		File_Name = KeyBoard_Name(screem.File_Pos);
		Save(File_Name);
		IF_HAS_SAVE = 1;
		FILE_STATE = OPEN;
	}
	else if (_tcscmp(input, "Save") == 0)
	{
		if (IF_HAS_SAVE == 0)
		{
			MessageBox(NULL, _T("��������Ҫ������ļ���"), _T("��ʾ"), MB_OK);
			File_Name = KeyBoard_Name(screem.File_Pos);
		}
		Save(File_Name);
		If_Change = 0;
		IF_HAS_SAVE = 1;
		FILE_STATE = OPEN;
	}
	else if (_tcscmp(input, "Save_As") == 0)
	{
		File_Name = KeyBoard_Name(screem.File_Pos);
		Save(File_Name);
		If_Change = 0;
		IF_HAS_SAVE = 1;
		FILE_STATE = OPEN;
	}
	else if (_tcscmp(input, "Quit") == 0)
	{
		FILE_STATE = 0;
		exit(0);
	}
}
void Close_File()
{
	int result;
	FILE_STATE = 0;
	if (If_Change == 1)
	{
		if (IF_HAS_SAVE == 1)
		{
			result = MessageBox(NULL, _T("�Ƿ񱣴浱ǰ����?"), _T("��ʾ"), MB_YESNO);
			switch (result)
			{
			case IDYES:
				Save(File_Name);
				break;
			case IDNO:
				break;
			}
		}
		else
		{
			result = MessageBox(NULL, _T("�Ƿ�Ҫ���浱ǰ�ĵ�?"), _T("��ʾ"), MB_YESNO);
			switch (result)
			{
			case IDYES:
				MessageBox(NULL, _T("�����Ҫ������ļ�������"), _T("��ʾ"), MB_OK);
				File_Name = KeyBoard_Name(screem.File_Pos);
				Save(File_Name);
				break;
			case IDNO:
				break;
			}
		}
	}
	If_Change = 0;
	IF_HAS_SAVE = 0;
	HAS_FILE_OPEN_NEW = 0;

	Edit_Close();
	Edit_Update(0);
	screem.Cursor_Pos = screem.File_Pos;
	SetConsoleCursorPosition(hOut, screem.Cursor_Pos);
}

