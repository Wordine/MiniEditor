#include "Heap.h"
#include"InterFace.h"
#include "MiniWord.h"
#include"File_Edit.h"
#include"Operator.h"
#include"Global.h"
#include"Edit.h"

using namespace std;
Database Mini;
extern int FILE_STATE;
int main()
{
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);//这里的参数为标准输出的句柄
	hIn = GetStdHandle(STD_INPUT_HANDLE);
	int File_Status = FILE;
	Initial();

	while (1)
	{
		switch (File_Status)
		{
		case FILE:
			File_Edit();
			FILE_STATE = 0;
			File_Status = EDIT;
			break;
		case EDIT:
			Edit_Insert();
			File_Status = FILE;
		case OPERATE:
			Operate_Edit();
			File_Status = INFORM;
			break;
		}
	}
}



