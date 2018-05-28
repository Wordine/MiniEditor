#include <iostream>
#include "MiniWord.h"
#include "Edit.h"


using namespace std;

void Inform(string message)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hStdout, &csbi);
	COORD temp = Scrm.Inform_Pos;
	SetConsoleCursorPosition(hStdout, temp);
	cout << message;
	temp.X = csbi.dwCursorPosition.X;
	temp.Y = csbi.dwCursorPosition.Y;
	SetConsoleCursorPosition(hStdout, temp);
}

void Inform()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hStdout, &csbi);

	COORD temp = Scrm.Inform_Pos;
	temp.Y += INFORM_LONG;
	temp.Y --;
	SetConsoleCursorPosition(hStdout, temp);
	for (int i = 0; i < INFORM_WIDTH; i++)
		cout << " ";
	SetConsoleCursorPosition(hStdout, temp);
	if (Edit_status == INSERT_MODE)
		cout << "INSERT    ";
	else if (Edit_status == EDIT_MODE)
		cout << "EDIT      ";
	cout << File_Pos.Y << "/" << File_Pos.X;
	
	temp.X = csbi.dwCursorPosition.X;
	temp.Y = csbi.dwCursorPosition.Y;
	SetConsoleCursorPosition(hStdout, temp);
}

void Inform(int)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hStdout, &csbi);

	COORD temp = Scrm.Inform_Pos;
	SetConsoleCursorPosition(hStdout, temp);
	for (int i = 0; i < INFORM_LONG; i++) {
		for (int j = 0; i < INFORM_WIDTH; i++)
			cout << " ";
		temp.X = Scrm.Edit_Pos.X;
		SetConsoleCursorPosition(hStdout, temp);
	}

	temp.X = csbi.dwCursorPosition.X;
	temp.Y = csbi.dwCursorPosition.Y;
	SetConsoleCursorPosition(hStdout, temp);
}