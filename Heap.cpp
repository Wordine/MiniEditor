class Heap_Linked_List//�����Ϊ100�ַ��Ķ�������ʽ����
{
public:
	Heap_Linked_List();
	Add_Heap();
	~Heap_Linked_List();
private:
	char* heap;
	int length;//�˶����Ѵ��ַ�����
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
