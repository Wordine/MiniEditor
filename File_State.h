#pragma once
extern void File_State(char input[]);
extern void Close_File();
extern void New();
extern char *File_Name;
extern int FILE_STATE;
#ifndef OPEN
#define OPEN 1
#endif