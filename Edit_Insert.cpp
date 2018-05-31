#include <iostream>
#include <conio.h>

#include "MiniWord.h"
#include "Edit.h"
#include "NetDataLog.h"
using namespace std;
extern void Update_Move(int);

struct buff {
	int size;
	char* data;
};
//extern int test_intial();
extern NetDataLog A;

void Edit_Mode(char word, char* begin, int *num, struct buff* buff_edit)
{
	if (word <= '9' && word >= '1') {
		*num = word - '0';
		if (*begin == 'd' || *begin == 'y' || *begin == 0) {
			return;
		}
		else {
			*begin = 0;
		}
	}
	switch (word)
	{
	case 'd':
		if (*begin == 'd') {
			buff_edit->size = *num;
			if (buff_edit->data != NULL) {
				delete[] buff_edit->data;
			}
			while (File_Pos.X % EDIT_WIDTH != 1) {
				Cursor_Move(LEFT);
			}
			buff_edit->size = *num * EDIT_WIDTH;
			buff_edit->data = Data_Get(File_Pos.Y, File_Pos.X, *num * EDIT_WIDTH);
			Cursor_Move(UP);
			for (int i = 0; i < *num * EDIT_WIDTH; i++)
				Data_Delete(File_Pos.Y, File_Pos.X + EDIT_WIDTH);
			
			Edit_Update();
			*begin = 0;
			*num = 1;
		}
		else if (*begin == 0) {
			*begin = 'd';
		}
		else {
			*begin = 'd';
			*num = 1;
		}
		break;
	case 'y':
		if (*begin == 'y') {
			buff_edit->size = *num;
			if (buff_edit->data != NULL) {
				delete[] buff_edit->data;
			}
			while (File_Pos.X % EDIT_WIDTH != 1) {
				Cursor_Move(LEFT);
			}
			buff_edit->size = *num * EDIT_WIDTH;
			buff_edit->data = Data_Get(File_Pos.Y, File_Pos.X, *num * EDIT_WIDTH);
			*begin = 0;
			*num = 1;
		}
		else if (*begin == 0) {
			*begin = 'y';
		}
		else {
			*begin = 'y';
			*num = 1;
		}
		break;
	case 'p':
		if (buff_edit->data == NULL || buff_edit->size == 0)
			break;
		while (File_Pos.X % EDIT_WIDTH != 1) {
			Cursor_Move(LEFT);
		}
		for (int i = buff_edit->size; i >= 0; i--) {
			if (buff_edit->data[i] != 0)
				Data_Insert(File_Pos.Y, File_Pos.X, buff_edit->data[i]);
		}
		*begin = 0;
		*num = 1;
		break;
	case 'h':
		Cursor_Move(LEFT);
		Edit_Update();
		Inform();
		*begin = 0;
		*num = 1;
		break;
	case 'j':
		Cursor_Move(UP);
		Edit_Update();
		Inform();
		*begin = 0;
		*num = 1;
		break;
	case 'l':
		Cursor_Move(RIGHT);
		Edit_Update();
		Inform();
		*begin = 0;
		*num = 1;
		break;
	case 'k':
		Cursor_Move(DOWN);
		Edit_Update();
		Inform();
		*begin = 0;
		*num = 1;
		break;
	default:
		break;
	}
}

int Edit_Insert()
{
   char word;///
   int num;
   char begin;
   buff buff_edit;
   buff_edit.size = 0;
   buff_edit.data = NULL;
  // test_intial();///
   Edit_Turn();///
   Edit_status = INSERT_MODE;
   Edit_Update();
   Inform();
   while (1){
   	word = _getch();
	//direction
   	if(word == -32){
   		word = _getch();
   		switch (word)
	   {
	   		case LEFT:
				Cursor_Move(LEFT);
				Edit_Update();
				Inform();
	   		break;
	   		case UP:
				Cursor_Move(UP);
				Edit_Update();
				Inform();
	   		break;
	   		case RIGHT:
				Cursor_Move(RIGHT);
				Edit_Update();
				Inform();
	   		break;
	   		case DOWN:
				Cursor_Move(DOWN);
				Edit_Update();
				Inform();
	   		break;
			case 71:
				//home
				while (File_Pos.X != 1)
					Cursor_Move(LEFT);
				Edit_Update();
				Inform();
				break;
			case 73:
				//page up
				for (int i = 0; i < EDIT_LONG; i++) {
					Update_Move(UP);
				}
				File_Pos = Update_Pos;
				cursorPos.X = 1;
				cursorPos.Y = 1;
				Scrm.Cursor_Pos.X = Scrm.Edit_Pos.X + cursorPos.X - 1;
				Scrm.Cursor_Pos.Y = Scrm.Edit_Pos.Y + cursorPos.Y - 1;
				SetConsoleCursorPosition(hStdout, Scrm.Cursor_Pos);
				Edit_Update();
				Inform();
				break;
			case 79:
				//end
				while (File_Pos.X != Get_Col(File_Pos.Y))
					Cursor_Move(RIGHT);
				Edit_Update();
				Inform();
				break;
			case 81:
				//page down
				for (int i = 0; i < EDIT_LONG; i++) {
					Update_Move(DOWN);
				}
				File_Pos = Update_Pos;
				cursorPos.X = 1;
				cursorPos.Y = 1;
				Scrm.Cursor_Pos.X = Scrm.Edit_Pos.X + cursorPos.X - 1;
				Scrm.Cursor_Pos.Y = Scrm.Edit_Pos.Y + cursorPos.Y - 1;
				SetConsoleCursorPosition(hStdout, Scrm.Cursor_Pos);
				Edit_Update();
				Inform();
				break;
			case 83:
				//delete
				Data_Delete(File_Pos.Y, File_Pos.X);
				Edit_Update();
				Edit_Log.addLog("Delete");
				Inform();
				break;
	   		default:
				Edit_Log.addLog("unknow command");
				//unknow command 
				break;
	   }
	}
	//normal char
	else if ((word > 31 && word < 127) || word == '\n' || word == '\t' || word == '\r'){
		if (word == '\r')
			word = '\n';
		if (Edit_status == INSERT_MODE) {
			Data_Insert(File_Pos.Y, File_Pos.X, word);
			Cursor_Move(RIGHT);
			Edit_Update();
			If_Change = 1;
			Inform();
		}
		else {
			Edit_Mode(word, &begin, &num, &buff_edit);
		}
	}
	//backspace
	else if (word == 8) {
		if (Edit_status == EDIT_MODE)
			continue;
		if (File_Pos.X == 1 && File_Pos.Y == 1)
			continue;
		Edit_Log.addLog("Backspace");
		if (File_Pos.X == 1) {
			Cursor_Move(LEFT);
			Data_Delete(File_Pos.Y + 1, 0);
			If_Change = 1;
		}
		else {
			Cursor_Move(LEFT);
			Data_Delete(File_Pos.Y, File_Pos.X);
			If_Change = 1;
		}
		Edit_Update();
		Inform();
	}
	//esc // Edit out
	else if (word == 27) {
		///
		Inform();
		Edit_Log.addLog("esc detected Edit mode out");
		return FILE;
	}
	else if (word == 0) {
		word = _getch();
		//f1 // enter search mode
		if (word == 59) {
			Edit_Log.addLog("f1 detected enter search mode");
			//enter search mode
			return OPERATE;
		}
		//f2 //enter Edit_Mode
		else if (word == 60) {
			if (Edit_status == EDIT_MODE) {
				Edit_status = INSERT_MODE;
				Inform();
			}
			else if (Edit_status == INSERT_MODE) {
				Edit_status = EDIT_MODE;
				Inform();
			}
		}
	}
   }
   return 0;
}
