#include <vector>
#include <cstdlib>
#include <iostream>
#include <fstream>

using namespace std;

class Database	//整体数据结构
{
public:
	Database();
	Database(const char*);
	~Database();
	int Get_Row();
	int Get_Col(int);
	char* Get_Line(int);
	char* Data_Get(unsigned int, unsigned int, unsigned int);
	void Data_Replace(unsigned int, unsigned int, const char*, unsigned int, unsigned int);
	void File_Save(const char*);

private:
	vector <vector <char*> > data;	//二维容器
	vector <int> line_num;//记录每行字符个数，0号结点记录行数
};

Database::Database()
{
	vector <char*> _data;
	data.push_back(_data);
	line_num.push_back(0);
}

Database::Database(const char* filename)
//打开文件并写入结构中
{
	ifstream file(filename);
	vector <char*> _data;
	data.push_back(_data);
	line_num.push_back(0);
	char c;	//单个读取字符
	int i = 0;	//\t处理需要补位个数
	while (!file.eof())
	{
		vector <char*> _data;
		data.push_back(_data);
		line_num.push_back(0);
		line_num[0]++;
		data[line_num[0]].push_back(NULL);
		for (file.get(c); c != '\n' && !file.eof(); file.get(c))
		{
			if (line_num[line_num[0]] % 100 == 0)
			{
				data[line_num[0]].push_back(new char[102]());
				if (i != 0)	//跨跃两个堆的\t处理
				{
					line_num[line_num[0]] += i;
					data[line_num[0]][line_num[line_num[0]] / 100 + 1][line_num[line_num[0]] % 100] = '\t';
					i = 0;
				}
			}
			if (c != '\t' || line_num[line_num[0]] % 8 == 7)
			{
				data[line_num[0]][line_num[line_num[0]] / 100 + 1][line_num[line_num[0]] % 100 + 1] = c;
				line_num[line_num[0]]++;
			}
			else
			{	//跨跃两个堆的\t处理
				if((100 - (line_num[line_num[0]] % 100)) < (8 - (line_num[line_num[0]] % 8)))
				{
					i = (8 - (line_num[line_num[0]] % 8)) - (100 - (line_num[line_num[0]] % 100));
					line_num[line_num[0]] += 100 - (line_num[line_num[0]] % 100);
				}
				else
				{
					line_num[line_num[0]] += 8 - (line_num[line_num[0]] % 8) - 1;
					data[line_num[0]][line_num[line_num[0]] / 100 + 1][line_num[line_num[0]] % 100 + 1] = '\t';
					line_num[line_num[0]]++;
				}
			}
		}
		if (c == '\n' && !file.eof())	//行尾\n的保存
		{
			if (line_num[line_num[0]] % 100 == 0)
			{
				data[line_num[0]].push_back(new char[102]());
				if (i != 0)
				{
					line_num[line_num[0]] += i;
					data[line_num[0]][line_num[line_num[0]] / 100 + 1][line_num[line_num[0]] % 100] = '\t';
				}
			}
			data[line_num[0]][line_num[line_num[0]] / 100 + 1][line_num[line_num[0]] % 100 + 1] = '\n';
			line_num[line_num[0]]++;
		}
	}
}

int Database::Get_Row()	//返回行数
{
	return line_num[0];
}

int Database::Get_Col(int row)	//返回第row行字符数
{
	return line_num[row];
}

char* Database::Get_Line(int row)
{
	char* line = new char(line_num[row] + 2);
	int col;

	for (col = 1; col <= line_num[row]; col++)
	{
		line[col] = data[row][(col - 1) / 100 + 1][(col - 1) % 100 + 1];
	}

	return line;

}

char* Data_Get(unsigned int row, unsigned int col, unsigned int n)
//从第row行的第col个字符开始获得的长度为n的字符串
{

}

void Data_Replace(unsigned int row, unsigned int col, const char* new_ch, unsigned int old_len, unsigned int new_len);
//从第row行的第col个字符开始将长度为old_len的字符串替换为长度为new_len的字符串new_ch

void Database::File_Save(const char* filename)
{
	ofstream file(filename);
	int row, col;
	char c;
	for (row = 1; row <= line_num[0]; row++)
	{
		for (col = 1; col <= line_num[row]; col++)
		{
			c = data[row][(col - 1) / 100 + 1][(col - 1) % 100 + 1];
			if(c != '\0')
			{
				file.put(c);
			}
		}
	}
}

Database::~Database()
{
}
