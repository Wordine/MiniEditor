class Heap_Linked_List//将规格为100字符的堆以链表方式连接
{
public:
	Heap_Linked_List();
	Add_Heap();
	~Heap_Linked_List();
private:
	char* heap;
	int length;//此堆中已存字符长度
	Heap_Linked_List* next;
};

class Line_Linked_List
{
public:
	Line_Linked_List();
	Add_line();
	~Line_Linked_List();
private:
	Heap_linked_List* heap = NULL;
	Line_Linked_List* next = NULL; 
};
