#include<io.h>
#include<cstdio>
#include "MiniWord.h"
#include"File_State.h"
#include"Global.h"
#include"KeyBoard.h"

#include "Edit_Intial.h"

char *File_Name = nullptr;
int FILE_STATE = 0;
void File_State(char input[])
{
	ChaChu(input, screem.File_Pos);
	if (_tcscmp(input, "New") == 0)
	{
		New();
		FILE_STATE = OPEN;
	}
	else if (_tcscmp(input, "Open") == 0)
	{
		MessageBox(NULL, _T("��������Ҫ�򿪵��ļ���"), _T("��ʾ"), MB_OK);
		File_Name = KeyBoard_Name(screem.File_Pos);
		if (_access(File_Name, 0) != 0)
		{
			int result = MessageBox(NULL, _T("���ļ������ڣ����Ƿ�Ҫ�½����ļ���"), _T("����"), MB_YESNO);
			switch (result)
			{
			case IDYES:
				New();
				FILE_STATE = OPEN;
				break;
			case IDNO:
				break;
			}
		}
		else
		{
			Open(File_Name);
			FILE_STATE = OPEN;
		}
	}
	else if (_tcscmp(input, "Close") == 0)
	{
		Close_File();
		Edit_Close();
	}
	else if (_tcscmp(input, "ReName") == 0)
	{
		remove(File_Name);
		File_Name = KeyBoard_Name(screem.File_Pos);
		Save(File_Name);
	}
	else if (_tcscmp(input, "Save") == 0)
	{
		File_Name = KeyBoard_Name(screem.File_Pos);
		Save(File_Name);
		If_Change = 0;
		IF_HAS_SAVE = 1;
	}
	else if (_tcscmp(input, "Save_As") == 0)
	{
		File_Name = KeyBoard_Name(screem.File_Pos);
		Save(File_Name);
		If_Change = 0;
		IF_HAS_SAVE = 1;
	}
}
void Close_File()
{
	int result;
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
}

void New()
{
	Close_File();
}