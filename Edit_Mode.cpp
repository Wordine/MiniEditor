#include <iostream>
#include <conio.h>

#include "MiniWord.h"
#include "Edit.h"

int Edit_Mode()
{
	Edit_status = EDIT_MODE;
	char word;
	char* buff;
	char begin;
	int num;
	while (1) {
		word = _getch();
		//direction
		if (word == -32) {
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
			default:
//				Edit_Log.addLog("unknow command");
				//unknow command 
				break;
			}
		}
		else if (word == 'p') {

		}
		else if (word <= '9' && word >= '1') {
			num = (int)word - '0';
		}
		else if (word == 'd') {
			if (begin == 0) {
				begin = 'd';
				break;
			}
			else if (begin == 'd') {
				///
			}
			else {
				begin = 'd';
				num = 1;
			}
			Edit_Update();
			Inform();
		}
		else if (word == 'y') {
			if (begin == 0) {
				begin = 'y';
				break;
			}
			else if (begin == 'y') {
				///
			}
			else {
				begin = 'y';
				num = 1;
			}
			Edit_Update();
			Inform();
		}
		else if (word >= 'a' && word <= 'z') {
			break;
		}
		//esc // Edit_Mode out
		else if (word == 27) {
			Inform();
//			Edit_Log.addLog("esc detected Edit mode out");
			return 0;
		}
	}
}