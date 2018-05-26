#pragma once
#include "Global.h"
#define LEFT	75
#define UP		72
#define RIGHT	77
#define DOWN	80
#define EDIT_WIDTH BWIDTH
#define EDIT_LONG BHEIGHT
#define INFORM_WIDTH BWIDTH
#define INFORM_LONG 5
#define EDIT_MODE 1
#define INSERT_MODE 0
#define hStdout hOut

#include <windows.h>
#include <winbase.h>
#include <string>

using namespace std;
//#include "NetDataLog.h"
extern int Edit_Insert();
extern void Cursor_Move(int direct);
extern void Edit_Update();
extern void Edit_Update(int y, int x, int len);
extern void Edit_Update(int y);
extern bool Edit_Initial();
extern void Inform(string message);
extern void Inform();

//extern NetDataLog Edit_Log;




extern COORD  cursorPos;	// ‰≥ˆŒª÷√
extern HANDLE hStdout;		

extern int Edit_status;