#include<iostream>

#include "MiniWord.h"
#include "Edit.h"



void Edit_Update()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hStdout, &csbi);
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
			break;
		}
		update = Data_Get(data_pos.Y, data_pos.X, EDIT_WIDTH);
		data_pos.X += EDIT_WIDTH;
		for (j = 0; j < EDIT_WIDTH; j++) {
			if ((update[j] > 31 && update[j] < 127) || update[j] == 13)
				cout << update[j];
			else if (update[j] == 0 || update[j] == '\t')
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
	SetConsoleCursorPosition(hStdout, temp);
}

void Edit_Update(int x)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hStdout, &csbi);
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
	SetConsoleCursorPosition(hStdout, temp);
//	Edit_Log.addLog("Update clear complete");
}

void Edit_Update(int y, int x, int len)
{
	COORD temp = Update_Pos;
	for (int i = 0; i < 5; i++) {
		Update_Pos.X -= EDIT_WIDTH;
		if (Update_Pos.X <= 0)
			break;
	}
	Update_Pos.X += EDIT_WIDTH;
	Edit_Update();
	Update_Pos = temp;
}