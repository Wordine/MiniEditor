#pragma once

#include <windows.h>
#include <winbase.h>
#include <string>
#include "Heap.h"
#define Scrm screem
extern COORD File_Pos;		//目前光标在文件中的位置 X，Y
extern COORD Update_Pos;		//更新位置
//string Buff_Inform;//通知寄存器
/*struct Screem {
	COORD Cursor_Pos;   //目前光标在屏幕上的位置X，Y
	COORD File_Pos;      //文件区位置
	COORD Edit_Pos;      //编辑区位置
	COORD Operate_Pos;  //操作区位置
	COORD Inform_Pos;   //通知区位置
};*/

using namespace std;

extern struct Screem Scrm;

extern Database Mini;

//检查File_Pos是否在合法的位置，//1 end of file// 2 line change
//extern int Line_Check(int row, int col);
#define Line_Check Mini.Line_Check

//从第row行的第col个字符开始获得的长度为n的字符串
//extern char* Data_Get(int row, int col, unsigned int n);
#define Data_Get Mini.Data_Get

//从第row行的第col个字符开始将长度为old_len的字符串替换为长度为new_len的字符串new_ch
//extern void Data_Replace(int row, int col, char* new_ch, unsigned int old_len, unsigned int new_len);
#define Data_Replace Mini.Data_Replace


//extern void Data_Insert(int row, int col, char x);
#define Data_Insert Mini.Data_Insert

//extern void Data_Delete(int row, int col);
#define Data_Delete Mini.Data_Delete

//extern int Get_Col(int y);
#define Get_Col Mini.Get_Col

//extern int Get_Row();
#define Get_Row Mini.Get_Row

//extern char* Get_Line(int);
#define Get_Line Mini.Get_Line

//extern void Save(string);
#define Save Mini.File_Save

//extern void Open(string);
#define Open Mini.File_Open

