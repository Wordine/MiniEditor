#pragma once

#include <windows.h>
#include <winbase.h>
#include <string>
#include "Heap.h"
#define Scrm screem
extern COORD File_Pos;		//Ŀǰ������ļ��е�λ�� X��Y
extern COORD Update_Pos;		//����λ��
//string Buff_Inform;//֪ͨ�Ĵ���
/*struct Screem {
	COORD Cursor_Pos;   //Ŀǰ�������Ļ�ϵ�λ��X��Y
	COORD File_Pos;      //�ļ���λ��
	COORD Edit_Pos;      //�༭��λ��
	COORD Operate_Pos;  //������λ��
	COORD Inform_Pos;   //֪ͨ��λ��
};*/

using namespace std;

extern struct Screem Scrm;

extern Database Mini;

//���File_Pos�Ƿ��ںϷ���λ�ã�//1 end of file// 2 line change
//extern int Line_Check(int row, int col);
#define Line_Check Mini.Line_Check

//�ӵ�row�еĵ�col���ַ���ʼ��õĳ���Ϊn���ַ���
//extern char* Data_Get(int row, int col, unsigned int n);
#define Data_Get Mini.Data_Get

//�ӵ�row�еĵ�col���ַ���ʼ������Ϊold_len���ַ����滻Ϊ����Ϊnew_len���ַ���new_ch
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

