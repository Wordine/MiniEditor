#include<iostream>

#include "MiniWord.h"
#include "Edit.h"



void Edit_Update()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hStdout, &csbi);
	///
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(hStdout, &CursorInfo);//获取控制台光标信息  
	CursorInfo.bVisible = false; //隐藏控制台光标  
	SetConsoleCursorInfo(hStdout, &CursorInfo);//设置控制台光标状态 
	///
	COORD temp = Scrm.Edit_Pos;
	COORD data_pos = Update_Pos;
	char* update;
	int i, j;
	int ret;
	SetConsoleCursorPosition(hStdout, temp);
	for (i = 0; i < EDIT_LONG; i++) {
		ret = Line_Check(data_pos.Y, data_pos.X);
		if (ret == 2) {
			data_pos.X = 1;
			data_pos.Y++;
			ret = 0;
			i--;
			continue;
		}
		if (ret == 1) {
			for (j = 0; j < EDIT_WIDTH; j++)
				cout << " ";
			temp.X = Scrm.Edit_Pos.X;
			temp.Y++;
			SetConsoleCursorPosition(hStdout, temp);
			continue;
		}
		update = Data_Get(data_pos.Y, data_pos.X, EDIT_WIDTH);
		data_pos.X += EDIT_WIDTH;
		for (j = 0; j < EDIT_WIDTH; j++) {
			if ((update[j] > 31 && update[j] < 127) || update[j] == 13)
				cout << update[j];
			else if (update[j] == 0 || update[j] == '\t' || update[j] == '\n')
				cout << " ";
			else
				Edit_Log.addLog("WORING CHAR!");
			temp.X++;
			SetConsoleCursorPosition(hStdout, temp);
		}
		delete[] update;
		temp.X = Scrm.Edit_Pos.X;
		temp.Y++;
		SetConsoleCursorPosition(hStdout, temp);
	}
	temp.X = csbi.dwCursorPosition.X;
	temp.Y = csbi.dwCursorPosition.Y;

	CursorInfo.bVisible = true; //隐藏控制台光标  
	SetConsoleCursorInfo(hStdout, &CursorInfo);//设置控制台光标状态 
	SetConsoleCursorPosition(hStdout, temp);
}

void Edit_Update(int x)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hStdout, &csbi);
	///
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(hStdout, &CursorInfo);//获取控制台光标信息  
	CursorInfo.bVisible = false; //隐藏控制台光标  
	SetConsoleCursorInfo(hStdout, &CursorInfo);//设置控制台光标状态 
//	Edit_Log.addLog("Update start");
	COORD temp = Scrm.Edit_Pos;
	int i, j;
	SetConsoleCursorPosition(hStdout, temp);
	for (i = 0; i < EDIT_LONG; i++) {
		for (j = 1; j <= EDIT_WIDTH; j++) {
			cout << " ";
			temp.X++;
			SetConsoleCursorPosition(hStdout, temp);
		}
		temp.X = Scrm.Edit_Pos.X;
		temp.Y++;
		SetConsoleCursorPosition(hStdout, temp);
	}
	temp.X = csbi.dwCursorPosition.X;
	temp.Y = csbi.dwCursorPosition.Y;
	///
	CursorInfo.bVisible = true; //隐藏控制台光标  
	SetConsoleCursorInfo(hStdout, &CursorInfo);//设置控制台光标状态 
	///
	SetConsoleCursorPosition(hStdout, temp);
//	Edit_Log.addLog("Update clear complete");
}

void Edit_Update(int y, int x, int len)
{
	COORD temp = Update_Pos;
	Update_Pos.X = x + 1 - (x - 1) % EDIT_WIDTH;
	for (int i = 0; i < 5; i++) {
		Update_Pos.X -= EDIT_WIDTH;
		if (Update_Pos.X <= 0)
			break;
	}
	Update_Pos.Y = y;
	Update_Pos.X += EDIT_WIDTH;
	Edit_Update();
	COORD pos;
	pos.Y = (x - ((x - 1) % EDITWIDTH + 1)) / EDIT_WIDTH;
	pos.X = (x - 1) % EDITWIDTH + 1;
	Scrm.Cursor_Pos.X = Scrm.Edit_Pos.X + pos.X;
	Scrm.Cursor_Pos.Y = Scrm.Edit_Pos.Y + pos.Y;
	SetConsoleCursorPosition(hStdout, Scrm.Cursor_Pos);
	Update_Pos = temp;
}