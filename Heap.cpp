#include <vector>
#include <cstdlib>
#include <iostream>

using namespace std;

class Database//整体数据结构
{
public:
	Database();
	~Database();
	
private:
	vector <vector <char*> > col;//二维容器
};

Database::Database()
{
	col.resize(2);
	col[1].resize(0);
}

Database::~Database()
{
}
