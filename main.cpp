#include "Heap.h"
#include"InterFace.h"
#include "MiniWord.h"
#include"File_Edit.h"
#include"Operator.h"
#include"Global.h"
#include"Edit.h"
#include"NetDataLog.h"

NetDataLog A("log", "record", 9999);
using namespace std;
Database Mini;
int main()
{
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);//这里的参数为标准输出的句柄
	hIn = GetStdHandle(STD_INPUT_HANDLE);
	int File_Status = FILE;
	Initial();
	string informa;
	while (1)
	{
		switch (File_Status)
		{
		case FILE:
			File_Edit();
			File_Status = EDIT;
			break;
		case EDIT:
			File_Status = Edit_Insert();
			break;
		case OPERATE:
			Operate_Edit();
			File_Status = EDIT;
			break;
		}
	}
}



