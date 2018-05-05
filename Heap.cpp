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
	vector <vector <char*> > col;
};

Database::Database()
{
	col.resize(1);
	col[0].resize(0);
}

Database::~Database()
{
}

int main()
{
	Database A;
	A.col[0].push_back(NULL);
	A.col[0][0] = new char(10);
	A.col[0][0] = "1234567";
	cout << A.col[0][0][2];

}
