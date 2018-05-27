#include<iostream>

#include "MiniWord.h"
#include "Edit.h"



void Edit_Update()
{
	//sting 0 start.
//	Edit_Log.addLog("Update start");
	COORD temp = cursorPos;
	COORD data_pos = Update_Pos;
	cursorPos = Scrm.Edit_Pos;
	char* update;
	int i, j;
	int ret;
	SetConsoleCursorPosition(hStdout, cursorPos);
	for (i = 0; i < EDIT_LONG; i++) {
		ret = Line_Check(data_pos.Y, data_pos.X);
		if (ret == 1) {
			data_pos.X = 1;
			data_pos.Y++;
		}
		update = Data_Get(data_pos.Y, data_pos.X, EDIT_WIDTH);
		data_pos.X += EDIT_LONG;
		for (j = 1; j <= EDIT_WIDTH; j++) {
			if (update[j] > 31 || update[j] < 127)
				cout << update[j];
			else if (update[j] == 0 || update[j] == '\t')
				cout << " ";
			else
//				Edit_Log.addLog("WORING CHAR!");
			cursorPos.X++;
			SetConsoleCursorPosition(hStdout, cursorPos);
		}
		delete[] update;
		cursorPos.X = Scrm.Edit_Pos.X;
		cursorPos.Y++;
		SetConsoleCursorPosition(hStdout, cursorPos);
	}
	cursorPos = temp;
	temp.X = cursorPos.X + Scrm.Edit_Pos.X - 1;
	temp.Y = cursorPos.Y + Scrm.Edit_Pos.Y - 1;
	SetConsoleCursorPosition(hStdout, temp);
//	Edit_Log.addLog("Update complete");
}

void Edit_Update(int x)
{
	//sting 0 start.
//	Edit_Log.addLog("Update start");
	COORD temp = cursorPos;
	cursorPos = Scrm.Edit_Pos;
	int i, j;
	SetConsoleCursorPosition(hStdout, cursorPos);
	for (i = 0; i < EDIT_LONG; i++) {
		for (j = 1; j <= EDIT_WIDTH; j++) {
			cout << " ";
			cursorPos.X++;
			SetConsoleCursorPosition(hStdout, cursorPos);
		}
		cursorPos.X = Scrm.Edit_Pos.X;
		cursorPos.Y++;
		SetConsoleCursorPosition(hStdout, cursorPos);
	}
	cursorPos = temp;
	SetConsoleCursorPosition(hStdout, cursorPos);
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
	Edit_Update();
	Update_Pos = temp;
}