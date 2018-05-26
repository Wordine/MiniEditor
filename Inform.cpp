#include <iostream>
#include "MiniWord.h"
#include "Edit.h"


using namespace std;

void Inform(string message)
{
	COORD temp = cursorPos;
	cursorPos = Scrm.Inform_Pos;
	SetConsoleCursorPosition(hStdout, cursorPos);
	cout << message;
	cursorPos = temp;
	SetConsoleCursorPosition(hStdout, cursorPos);
}

void Inform()
{
	COORD temp = cursorPos;
	cursorPos = Scrm.Inform_Pos;
	cursorPos.Y += INFORM_LONG;
	cursorPos.Y --;
	SetConsoleCursorPosition(hStdout, cursorPos);
	for (int i = 0; i < INFORM_WIDTH; i++)
		cout << " ";
	SetConsoleCursorPosition(hStdout, cursorPos);
	if (Edit_status == INSERT_MODE)
		cout << "INSERT    ";
	else if (Edit_status == EDIT_MODE)
		cout << "EDIT      ";
	cout << temp.Y << "/" << temp.X;
	cursorPos = temp;
	SetConsoleCursorPosition(hStdout, cursorPos);
}