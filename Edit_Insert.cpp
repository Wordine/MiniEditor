#include <iostream>
#include <conio.h>

#include "MiniWord.h"
#include "Edit.h"
#include "NetDataLog.h"
using namespace std;

struct buff {
	int size;
	char* data;
};
//extern int test_intial();
extern NetDataLog A;

int Edit_Insert()
{
   char word;///
   int num;
   char begin;
   buff buff_edit;
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
	}
	//backspace
	else if (word == 8) {
		Edit_Log.addLog("Backspace");
		Cursor_Move(LEFT);
		Data_Delete(File_Pos.Y, File_Pos.X);
		If_Change = 1;
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
			Edit_status = EDIT_MODE;
		}
	}
   }
   return 0;
}
