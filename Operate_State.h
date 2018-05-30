#pragma once
#include<string>
using std::string;
#ifndef MAX_LINE
#define MAX_LINE 30
#endif

#ifndef MAX_COL
#define MAX_COL 600
#endif
extern void Operate_State(char *input);
extern bool Search(const char *target);
extern void Find_(char *str, const char *target, int Position[][MAX_COL + 1], int row);
extern void Get_Nextval(int *nextval, const char *target);
extern int Index_KMP(char *str, const char *target, int pos, int nextval[],int col_length);
extern int Position[MAX_LINE + 1][MAX_COL + 1];