#pragma once
#include<Windows.h>
#define FILE 0
#define EDIT 1
#define OPERATE 2
#define INFORM 3
extern unsigned long num_written;
extern HANDLE hOut;
extern HANDLE hIn;
extern int BLEFT, BRIGHT, BTOP, BBOTTOM, BWIDTH, BHEIGHT, INFOHEIGHT;
extern int Inform_Long;
extern CONSOLE_SCREEN_BUFFER_INFO bInfo;//���ڴ��洰�ڻ�������Ϣ
struct Screem
{
	COORD Cursor_Pos;   //Ŀǰ�������Ļ�ϵ�λ��X��Y
	COORD File_Pos;      //�ļ���λ��
	COORD Edit_Pos;      //�༭��λ��
	COORD Operate_Pos;  //������λ��
	COORD Inform_Pos;   //֪ͨ��λ��
};
extern struct Screem screem;
#ifndef MAX_INPUT
#define MAX_INPUT 50
#endif
extern int If_Change;//��¼�༭���Ƿ���ļ��������޸ģ���û���޸Ŀ�ֱ�ӹر��ļ���������Ҫ���б������
extern int IF_HAS_SAVE;//�ļ��Ѿ����������Ϊ1����ʱ����Ҫ���������ļ����֣�ֱ�ӱ��漴�ɡ�������Ϊ0