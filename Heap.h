#pragma once
#include <vector>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <fstream>
#define EDITWIDTH BWIDTH
extern int BWIDTH;

using namespace std;

class Database	//�������ݽṹ
{
public:
	Database();
	~Database();
	void File_Open();
	void File_Open(const char*);
	int Get_Row();
	int Get_Col(int);
	char* Get_Line(int);
	char* Data_Get(unsigned int, unsigned int, unsigned int);
	void Data_Replace(unsigned int, unsigned int, const char*, unsigned int, unsigned int);
	void Data_Insert(unsigned int, unsigned int, const char);
	void Data_Delete(unsigned int, unsigned int);
	void File_Save(const char*);
	int Line_Check(int, int);

private:
	vector <vector <char*> > data;	//��ά����
	vector <int> line_num;//��¼ÿ���ַ�������0�Ž���¼����
};
