#pragma once
#include<Windows.h>
extern int LEFT, RIGHT, TOP, BOTTOM;
extern void Initial();
extern void BeiJing(void);
extern void DrawBox(SMALL_RECT rc);
//extern void DeleteTopLine(SMALL_RECT rc);
extern void Navigation();
extern void Get_Screen();
extern void Navigation_Search();
extern void Clear_Inform();