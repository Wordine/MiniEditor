#include"Global.h"
unsigned long num_written;
HANDLE hOut;
HANDLE hIn;
int BLEFT = 0, BRIGHT = 0, BTOP = 0, BBOTTOM = 0, BWIDTH = 0, BHEIGHT = 0, INFOHEIGHT = 0;
CONSOLE_SCREEN_BUFFER_INFO bInfo;//���ڴ��洰�ڻ�������Ϣ
struct Screem screem;
int If_Change = 0;
int IF_HAS_SAVE = 0;