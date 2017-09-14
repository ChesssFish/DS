#include"skiplist.h"
#include"valid.h"
#include<iostream>
#include<ctime>
using namespace std;

Skiplist<int>* list;

void ShowIndex();
void Insert();
void Search();
void Delete();
void Print();
void Exit();

//#define DEBUG
int main()
{
#ifndef DEBUG
	srand(time((time_t)NULL));
#endif
	list = new Skiplist<int>;
	int op;

	while (true)
	{
		ShowIndex();
		Input(op, 0, 4);
		switch (op)
		{
		case 0:
			Exit();
			break;
		case 1:
			Insert();
			break;
		case 2:
			Search();
			break;
		case 3:
			Delete();
			break;
		case 4:
			Print();
			break;
		default:
			break;
		}
	}

	return 0;
}

/*---------------------------------------------------------------------------
								����ʵ��
---------------------------------------------------------------------------*/
void ShowIndex()
{
	Output("------------------����demo--------------------");
	Output("0: �˳�");
	Output("1: ����");
	Output("2: ��ѯ");
	Output("3: ɾ��");
	Output("4: ��ӡ");
	Output("������ѡ�����:");
}

void Insert()
{
	int key;
	Output("-----------------����-------------------");
	Output("������ؼ���: ");
	Input(key);
	list->Insert(key);
	Output("�������");
}

void Search()
{
	int key;
	Node<int>* node;
	Output("-----------------��ѯ-------------------");
	Output("������ؼ���: ");
	Input(key);
	node = list->Find(key);
	if (node == NULL)
	{
		Output("δ�ҵ����");
	}
	else
	{
		node->Print();
	}
}
void Delete()
{
	int key;
	Output("-----------------ɾ��-------------------");
	Output("������ؼ���: ");
	Input(key);
	list->Delete(key);
	Output("ɾ�����");
}
void Print()
{
	Output("----------------��ӡ------------------");
	list->Print();
}
void Exit()
{
	exit(0);
}