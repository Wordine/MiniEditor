#include"MiniWord.h"
#include"Edit.h"


bool Edit_Initial()
{
	//update FilePos
	File_Pos.X = 1;
	File_Pos.Y = 1;
	//update UpdatePos
	Update_Pos = File_Pos;
	//set handle
	//hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	//set cursor pos
	cursorPos.X = 1;
	cursorPos.Y = 1;
	Scrm.Cursor_Pos.X = Scrm.Edit_Pos.X + cursorPos.X - 1;
	Scrm.Cursor_Pos.Y = Scrm.Edit_Pos.Y + cursorPos.Y - 1;
	SetConsoleCursorPosition(hStdout, Scrm.Cursor_Pos);
//	Edit_Log.addLog("a new file open");
	return true;
}

bool Edit_Turn()
{
	//update FilePos check
	if (File_Pos.X <= 0 || File_Pos.Y <= 0) {
//		Edit_Log.addLog("Edit turned FilePos WORING");
		return false;
	}
	//update UpdatePos check
	if (Update_Pos.X <= 0 || Update_Pos.Y <= 0) {
//		Edit_Log.addLog("Edit turned UpdatePos WORING");
		return false;
	}
		
	//set cursor pos
	cursorPos.X = Scrm.Cursor_Pos.X - Scrm.Edit_Pos.X + 1;
	cursorPos.Y = Scrm.Cursor_Pos.Y - Scrm.Edit_Pos.Y + 1;
	SetConsoleCursorPosition(hStdout, cursorPos);
//	Edit_Log.addLog("Edit turned");
}

bool Edit_Break()
{
	Scrm.Cursor_Pos.X = Scrm.Edit_Pos.X + cursorPos.X - 1;
	Scrm.Cursor_Pos.Y = Scrm.Edit_Pos.Y + cursorPos.Y - 1;
///	Edit_Log.addLog("Edit break");
	return true;
}

bool Edit_Close()
{
	File_Pos.X = 0;
	File_Pos.Y = 0;
	cursorPos = File_Pos;
	Update_Pos = File_Pos;
	Scrm.Cursor_Pos = File_Pos;
//	Edit_Log.addLog("a file close");
	return true;
}