#include "Heap.h"

Database::Database()
{

}

void Database::File_Open()
{
	vector <char*> _data;
	data.push_back(_data);
	data.push_back(_data);
	data[1].push_back(new char[102]());
	line_num.push_back(1);
	line_num.push_back(0);
}

void Database::File_Open(const char* filename)
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
		if (line_num[line_num[0]] == 0)
			data[line_num[0]].push_back(new char[102]());
	}
}

int Database::Get_Row()	//返回行数
{
	return line_num[0];
}

int Database::Get_Col(int row)	//返回第row行字符数 ////wording edited;
{
	if (line_num[row] == 1) {
		return 1;
	}
	else
		return line_num[row] - 1;
}

char* Database::Get_Line(int row)
{
	char* line = new char[line_num[row] + 1]();
	int i;

	for (i = 0; i < line_num[row]; i++)
	{
		line[i] = data[row][(i) / 100 + 1][(i) % 100 + 1];
	}

	return line;

}

char* Database::Data_Get(unsigned int row, unsigned int col, unsigned int n)
//从第row行的第col个字符开始获得的长度为n的字符串
{
	char* line = new char[n + 1]();

	for (int i = 0; col <= line_num[row] && i < n; col++, i++)
	{
		line[i] = data[row][(col - 1) / 100 + 1][(col - 1) % 100 + 1];
	}

	return line;
}

void Database::Data_Replace(unsigned int row, unsigned int col, const char* new_ch, unsigned int old_len, unsigned int new_len)
//从第row行的第col个字符开始将长度为old_len的字符串替换为长度为new_len的字符串new_ch
{
	char *temp = NULL;
	int i, t;
	int intercept = old_len - new_len;
	temp = new char[line_num[row] - col - old_len + 10]();
	if (intercept == 0)
	{
		for (i = 0; i < old_len; i++, col++)
		{
			data[row][(col - 1) / 100 + 1][(col - 1) % 100 + 1] = new_ch[i];
		}
	}
	else
	{
		t = 0;
		if (abs(intercept) % 8 != 0)
		{
			char c;
			for (i = 0; col + old_len + i <= line_num[row]; i++)
			{
				c = data[row][(col + old_len + i - 1) / 100 + 1][(col + old_len + i - 1) % 100 + 1];
				if (t == 0 && (c == '\0' || c == '\t'))
				{
					int old_zero = 8 - (col + old_len + i) % 8;
					int new_zero = 8 - (col + old_len + i - intercept) % 8;
					t = old_zero - new_zero;
					if (t > 0)
						temp[i] = data[row][(col + old_len + i + t - 1) / 100 + 1][(col + old_len + i + t - 1) % 100 + 1];
					else if (t < 0)
						temp[i + t] = c;
				}
				else
				{
					if (t >= 0)
						temp[i] = data[row][(col + old_len + i + t - 1) / 100 + 1][(col + old_len + i + t - 1) % 100 + 1];
					else
						temp[i + t] = c;
				}

			}
		}
		else
		{
			for(i = 0; col + old_len + i <= line_num[row]; i++)
				temp[i] = data[row][(col + old_len + i - 1) / 100 + 1][(col + old_len + i - 1) % 100 + 1];
		}

		if (intercept > 0 && line_num[row] % 100 <= intercept + t)
		{
			data[row].pop_back();
		}
		else if(intercept  < 0 && (100 - line_num[row] % 100) < -intercept - t)
		{
			data[row].push_back(new char[102]());
		}
		
		if(line_num[row] == 0)
			line_num[row]++;
		line_num[row] = line_num[row] - intercept - t;
		
		for (i = 0; i < new_len; i++)
			data[row][(col + i - 1) / 100 + 1][(col + i - 1) % 100 + 1] = new_ch[i];
		for (i = 0; i < line_num[row] - col - new_len + 1; i++)
		{
			data[row][(col + new_len + i - 1) / 100 + 1][(col + new_len + i - 1) % 100 + 1] = temp[i];
		}
	}
	free(temp);
}

void Database::Data_Insert(unsigned int row, unsigned int col, const char c)
{
	if (c == '\t')
	{
		int zero = 8 - (col % 8);
		char *temp = new char(zero + 2);
		temp[zero] = '\t';
		Data_Replace(row, col, temp, 0, zero + 1);
		free(temp);
	}
	else if (c == '\n')
	{
		char *temp = new char(line_num[row] - col + 2);
		int len = line_num[row] - col + 1;
		for (int i = col; i <= line_num[row]; i++)
			temp[i - col] = data[row][(i - 1) / 100 + 1][(i - 1) % 100 + 1];
		Data_Replace(row, col, temp, len, 0);
		Data_Replace(row, col, "\n", 0, 1);
		vector< vector<char*> >::iterator it1 = data.begin() + row + 1;
		vector <char*> _data;
		data.insert(it1, _data);
		line_num[0]++;
		vector<int>::iterator it2 = line_num.begin() + row + 1;
		line_num.insert(it2, 0);
		data[row + 1].push_back(NULL);
		data[row + 1].push_back(new char[102]());
	//	data[row + 1][1][1] = '\n';
	//	line_num[row + 1] = 1;
		Data_Replace(row + 1, 1, temp, 1, len);
		free(temp);
	}
	else
	{
		char a[2];
		a[0] = c;
		Data_Replace(row, col, a, 0, 1);
	}

}

void Database::Data_Delete(unsigned int row, unsigned int col)
{
	if (col == 0)
	{
		char *temp = Get_Line(row);
		Data_Replace(row - 1, line_num[row - 1], temp, 1, line_num[row]);
		vector< vector<char*> >::iterator it1 = data.begin() + row;
		data.erase(it1);
		vector<int>::iterator it2 = line_num.begin() + row;
		line_num.erase(it2);
		line_num[0]--;

	}
	else
	{
		char c = data[row][(col - 1) / 100 + 1][(col - 1) % 100 + 1];
		if (c == '\t')
		{
			int i;
			for (i = 1; data[row][(col - i - 1) / 100 + 1][(col - i - 1) % 100 + 1] == 0; i++) {}
			Data_Replace(row, col - i + 1, "", i, 0);
		}
		else
			Data_Replace(row, col, "", 1, 0);
	}
}

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

int Database::Line_Check(int row, int col)
{
	char c;
	if(row <= line_num[0] && col <= line_num[row])
		c = data[row][(col - 1) / 100 + 1][(col - 1) % 100 + 1];
	if (row > line_num[0])
		return 1;
	else if (col - line_num[row] + 1 > EDITWIDTH - ((line_num[row] - 1) % EDITWIDTH))
		return 2;
	else if (line_num[0] > row && col > line_num[row] - 1)
		return -(col - line_num[row] + 1);
	else if (col > line_num[row])
		return -(col - line_num[row]);
	else if (col <= line_num[row] && c != '\n' && c != '\0' && c != '\t')
		return 0;
	else
	{
		if (col == EDITWIDTH)
			return -1;
		else
		{
			int i;
			for (i = 1; data[row][(col - i - 1) / 100 + 1][(col - i - 1) % 100 + 1] != '\0'; i++){}
			return -i;
		}
	}
}
Database::~Database()
{
}


