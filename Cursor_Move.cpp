#include <iostream>
#include <conio.h>
#include "MiniWord.h"
#include "Edit.h"


void Update_Move(int direct)
{
	int ret;
	if (direct == UP) {
		if (Update_Pos.X <= EDIT_WIDTH) {
			//处于非第一行，前width字符
			if (Update_Pos.Y > 1) {
				Update_Pos.X = (Get_Col(Update_Pos.Y - 1) - 1) % EDIT_WIDTH + 1;
				Update_Pos.Y--;
				return;
			}
			else return;	//处于第一行前width字符
		}
		else {
			Update_Pos.X = Update_Pos.X - EDIT_WIDTH;
		}
	}
	else if (direct == DOWN) {
		ret = Line_Check(Update_Pos.Y, Update_Pos.X + EDIT_WIDTH);
		if (ret == 2|| ret < 0) {
			Update_Pos.X = 1;
			Update_Pos.Y++;
		}
		else {
			Update_Pos.X = Update_Pos.X + EDIT_WIDTH;
		}
	}
}

void Cursor_Move(int direct)
{
	int ret;
	switch (direct)
	{
	case LEFT:
		//first line//first char
		if (File_Pos.Y == 1 && File_Pos.X == 1) {
			break;
		}
		//first char
		if (File_Pos.X == 1) {
			File_Pos.Y--;
			ret = Get_Col(File_Pos.Y);
			File_Pos.X = ret;
			cursorPos.X = (ret - 1) % EDIT_WIDTH + 1;
			//upper bound
			if (cursorPos.Y == 1) 
				Update_Move(UP);
			else 
				cursorPos.Y--;
			Scrm.Cursor_Pos.X = Scrm.Edit_Pos.X + cursorPos.X - 1;
			Scrm.Cursor_Pos.Y = Scrm.Edit_Pos.Y + cursorPos.Y - 1;
			SetConsoleCursorPosition(hStdout, Scrm.Cursor_Pos);
			break;
		}
		//left char
		if (cursorPos.X == 1) {
			//upper bound
			if (cursorPos.Y == 1) {
				File_Pos.X--;
				cursorPos.X = EDIT_WIDTH;
				Scrm.Cursor_Pos.X = Scrm.Edit_Pos.X + cursorPos.X - 1;
				Scrm.Cursor_Pos.Y = Scrm.Edit_Pos.Y + cursorPos.Y - 1;
				Update_Move(UP);
				SetConsoleCursorPosition(hStdout, Scrm.Cursor_Pos);
				break;
			}
			else {
				File_Pos.X--;
				cursorPos.Y--;
				cursorPos.X = EDIT_WIDTH;
				Scrm.Cursor_Pos.X = Scrm.Edit_Pos.X + cursorPos.X - 1;
				Scrm.Cursor_Pos.Y = Scrm.Edit_Pos.Y + cursorPos.Y - 1;
				SetConsoleCursorPosition(hStdout, Scrm.Cursor_Pos);
				break;
			}
		}
		//normal
		cursorPos.X--;
		File_Pos.X--;
		Scrm.Cursor_Pos.X = Scrm.Edit_Pos.X + cursorPos.X - 1;
		Scrm.Cursor_Pos.Y = Scrm.Edit_Pos.Y + cursorPos.Y - 1;
		SetConsoleCursorPosition(hStdout, Scrm.Cursor_Pos);
		break;
	case UP:
		// first line
		if (File_Pos.Y == 1) {
			//first row
			if (File_Pos.X <= EDIT_WIDTH)
				break;
			else {
				File_Pos.X -= EDIT_WIDTH;
				//upper bound
				if (cursorPos.Y == 1) {
					Update_Move(UP);
				}
				else {
					cursorPos.Y--;
				}
				Scrm.Cursor_Pos.X = Scrm.Edit_Pos.X + cursorPos.X - 1;
				Scrm.Cursor_Pos.Y = Scrm.Edit_Pos.Y + cursorPos.Y - 1;
				SetConsoleCursorPosition(hStdout, Scrm.Cursor_Pos);
				break;
			}
		}
		//first row
		if (File_Pos.X <= EDIT_WIDTH) {
			File_Pos.Y--;
			ret = Get_Col(File_Pos.Y);
			File_Pos.X = ret + Line_Check(File_Pos.Y, ret - ((ret - 1) % EDIT_WIDTH + 1) + cursorPos.X);
			cursorPos.X = (File_Pos.X - 1) % EDIT_WIDTH + 1;
			//upper bound
			if (cursorPos.Y == 1) {
				Update_Move(UP);
			}
			else {
				cursorPos.Y--;
			}
			Scrm.Cursor_Pos.X = Scrm.Edit_Pos.X + cursorPos.X - 1;
			Scrm.Cursor_Pos.Y = Scrm.Edit_Pos.Y + cursorPos.Y - 1;
			SetConsoleCursorPosition(hStdout, Scrm.Cursor_Pos);
			break;
		}
		//normal
		File_Pos.X -= EDIT_WIDTH;
		//upper bound
		if (cursorPos.Y == 1) {
			Update_Move(UP);
		}
		else {
			cursorPos.Y--;
		}
		Scrm.Cursor_Pos.X = Scrm.Edit_Pos.X + cursorPos.X - 1;
		Scrm.Cursor_Pos.Y = Scrm.Edit_Pos.Y + cursorPos.Y - 1;
		SetConsoleCursorPosition(hStdout, Scrm.Cursor_Pos);
		break;
	case RIGHT:
		ret = Line_Check(File_Pos.Y, File_Pos.X + 1);

		//last char
		if (ret == 2 || ret == -1) {
			//end od file
			if (Line_Check(File_Pos.Y + 1, 1) == 1) {
				break;
			}
			File_Pos.Y++;
			File_Pos.X = 1;
			cursorPos.X = 1;
			//lower bound
			if (cursorPos.Y == EDIT_LONG) {
				Update_Move(DOWN);
			}
			else {
				cursorPos.Y++;
			}
			Scrm.Cursor_Pos.X = Scrm.Edit_Pos.X + cursorPos.X - 1;
			Scrm.Cursor_Pos.Y = Scrm.Edit_Pos.Y + cursorPos.Y - 1;
			SetConsoleCursorPosition(hStdout, Scrm.Cursor_Pos);
			break;
		}
		if (ret == 0) {
			//right char
			if (cursorPos.X == EDIT_WIDTH) {
				File_Pos.X++;
				cursorPos.X = 1;
				//lower bound
				if (cursorPos.Y == EDIT_LONG) {
					Update_Move(DOWN);
				}
				else {
					cursorPos.Y++;
				}
				Scrm.Cursor_Pos.X = Scrm.Edit_Pos.X + cursorPos.X - 1;
				Scrm.Cursor_Pos.Y = Scrm.Edit_Pos.Y + cursorPos.Y - 1;
				SetConsoleCursorPosition(hStdout, Scrm.Cursor_Pos);
				break;
			}
			//normal
			cursorPos.X++;
			File_Pos.X++;
			Scrm.Cursor_Pos.X = Scrm.Edit_Pos.X + cursorPos.X - 1;
			Scrm.Cursor_Pos.Y = Scrm.Edit_Pos.Y + cursorPos.Y - 1;
			SetConsoleCursorPosition(hStdout, Scrm.Cursor_Pos);
		}
//		Edit_Log.addLog("WORING RIGHT RET");
		break;
	case DOWN:
		ret = Line_Check(File_Pos.Y, File_Pos.X + EDIT_WIDTH);
		//last row
		if (ret == 2) {
			//eof
			if (Line_Check(File_Pos.Y + 1, File_Pos.X) == 1) {
				break;
			}
			File_Pos.X = cursorPos.X;
			File_Pos.Y++;

			if (cursorPos.Y == EDIT_LONG) {
				Update_Move(DOWN);
			}
			else {
				cursorPos.Y++;
			}
			Scrm.Cursor_Pos.X = Scrm.Edit_Pos.X + cursorPos.X - 1;
			Scrm.Cursor_Pos.Y = Scrm.Edit_Pos.Y + cursorPos.Y - 1;
			SetConsoleCursorPosition(hStdout, Scrm.Cursor_Pos);
			break;
		}
		//last row but one and normal
		if (ret <= 0) {
			File_Pos.X += (EDIT_WIDTH + ret);
			cursorPos.X += ret;
			if (cursorPos.Y == EDIT_LONG) {
				Update_Move(DOWN);
			}
			else {
				cursorPos.Y++;
			}
			Scrm.Cursor_Pos.X = Scrm.Edit_Pos.X + cursorPos.X - 1;
			Scrm.Cursor_Pos.Y = Scrm.Edit_Pos.Y + cursorPos.Y - 1;
			SetConsoleCursorPosition(hStdout, Scrm.Cursor_Pos);
			break;
		}
//		Edit_Log.addLog("WORING DOWN RET");
		break;
	default:
//		Edit_Log.addLog("WORING CURSOR MOVE DIRECTION!");
		break;
	}
}