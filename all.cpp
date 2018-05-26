#include <windows.h>
#include <winbase.h>
#include "MiniWord.h"
//#include "NetDataLog.h"

using namespace std;
//struct Screem Scrm;
COORD File_Pos;
COORD Update_Pos;
COORD  cursorPos;

int Edit_status;
//HANDLE hStdout;

//NetDataLog Edit_Log("log", "Edit_Log", 9999);