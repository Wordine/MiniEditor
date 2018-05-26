#pragma once
#include<tchar.h>
#include <Windows.h>
extern void CharWindow(TCHAR ch);
//void Alert();
extern void Warning();
extern void File_State(char input[]);
extern char *KeyBoard_Name(COORD WeiZhi);
extern void BackSpace_Delete(int* flag, COORD WeiZhi);
extern void ChaChu(char input[], COORD WeiZhi);