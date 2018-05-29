#pragma once
#ifndef NETDATALOG_H  
#define NETDATALOG_H  
#include <iostream>  
#include <fstream>  
#include <stdio.h>  
#include <direct.h>  
#include <string>  
#include <io.h>  
#include <stdlib.h>  
#include <time.h>  
#include <fcntl.h>  

using namespace std;
enum TIMEFORMAT
{
	NETLOG = 0, //  [yyyy\mm\dd hh.MM.ss]  
	LOGINLOG = 1, //  mm-dd hh:MM:ss  
};

class NetDataLog
{
public:
	NetDataLog(string strDir = "log", string filename = "record", int maxfilesize = 0, int filecount = 0, int timeformat = 0);
	~NetDataLog();

	void addLog(string log);    //�����־��¼����־�ļ�  
	void fileSizeLimit();       //�ж��ļ���С�Ƿ�ﵽ�޶�ֵ  
	int getCurrentLogFileSize();//��ȡ��ǰ��־�ļ��Ĵ�С  
	string getLogFileName();    //��ȡ��־�ļ�����  
	void setMaxFileSize(int);//�����ļ�����С  
	void setFileName(string); //������־�ļ���  
	void setFileCount(int); //������־�ļ��ĸ���  
	void setLogDir(string strDir);      //������־�ļ�Ŀ¼  
private:
	void fileOffset();      //�ļ����ƽ���ƫ��  
	bool checkFolderExist(const string &strPath);


private:
	string m_LogFileName;   //�ļ���  
	int m_MaxFileSize;      //�ļ���С  
	int m_FileCount;        //�ļ�����  
	fstream *m_outputFile;  //����ļ���  
	string m_strDir;        //Ŀ¼  
	int m_timeFormat;


};
#endif