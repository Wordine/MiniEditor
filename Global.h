#pragma once
#include<Windows.h>
#define FILE 0
#define EDIT 1
#define OPERATE 2
#define INFORM 3
extern unsigned long num_written;
extern HANDLE hOut;
extern HANDLE hIn;
extern int BLEFT, BRIGHT, BTOP, BBOTTOM, BWIDTH, BHEIGHT, INFOHEIGHT;
extern int Inform_Long;
extern CONSOLE_SCREEN_BUFFER_INFO bInfo;//用于储存窗口缓冲区信息
struct Screem
{
	COORD Cursor_Pos;   //目前光标在屏幕上的位置X，Y
	COORD File_Pos;      //文件区位置
	COORD Edit_Pos;      //编辑区位置
	COORD Operate_Pos;  //操作区位置
	COORD Inform_Pos;   //通知区位置
};
extern struct Screem screem;
#ifndef MAX_INPUT
#define MAX_INPUT 50
#endif
extern int If_Change;//记录编辑区是否对文件进行了修改，若没有修改可直接关闭文件，否则需要进行保存操作
extern int IF_HAS_SAVE;//文件已经保存过了置为1，此时不需要重新输入文件名字，直接保存即可。否则置为0