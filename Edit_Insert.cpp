#include <iostream>
#include <conio.h>

#include "MiniWord.h"
#include "Edit.h"
#include "NetDataLog.h"
using namespace std;

//extern int test_intial();
extern NetDataLog A;

int Edit_Insert()
{
   char word;///
  // test_intial();///
   Edit_Initial();///
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
				//delete///problem!
				Data_Delete(File_Pos.Y, File_Pos.X);
//				Edit_Log.addLog("Delete");
				Inform();
				break;
	   		default:
//				Edit_Log.addLog("unknow command");
				//unknow command 
				break;
	   }
	}
	//normal char
	else if ((word > 31 && word < 127) || word == 13){
//		Edit_Log.addLog("Insert one char!");
//		Edit_Log.addLog(&word);
		string informa = "dbg:";
		informa.push_back(char('0' + File_Pos.X));
		informa.push_back(char('0' + File_Pos.Y));
		A.addLog(informa);
		Data_Insert(File_Pos.Y, File_Pos.X, word);
		Cursor_Move(RIGHT);
		Edit_Update();
		If_Change = 1;
		Inform();
	}
	//backspace
	else if (word == 8) {
//		Edit_Log.addLog("Backspace");
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
//		Edit_Log.addLog("esc detected Edit mode out");
		return 0;
	}
	else if (word == 0) {
		word = _getch();
		//f1 // enter search mode
		if (word == 59) {
			Inform();
//			Edit_Log.addLog("f1 detected enter search mode");
			//enter search mode
			return 1;
		}
		//f2 //enter Edit_Mode
		else if (word == 60) {

		}
	}
   }
   return 0;
}
