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
								函数实现
---------------------------------------------------------------------------*/
void ShowIndex()
{
	Output("------------------跳表demo--------------------");
	Output("0: 退出");
	Output("1: 插入");
	Output("2: 查询");
	Output("3: 删除");
	Output("4: 打印");
	Output("请输入选项序号:");
}

void Insert()
{
	int key;
	Output("-----------------插入-------------------");
	Output("请输入关键字: ");
	Input(key);
	list->Insert(key);
	Output("插入完成");
}

void Search()
{
	int key;
	Node<int>* node;
	Output("-----------------查询-------------------");
	Output("请输入关键字: ");
	Input(key);
	node = list->Find(key);
	if (node == NULL)
	{
		Output("未找到结果");
	}
	else
	{
		node->Print();
	}
}
void Delete()
{
	int key;
	Output("-----------------删除-------------------");
	Output("请输入关键字: ");
	Input(key);
	list->Delete(key);
	Output("删除完成");
}
void Print()
{
	Output("----------------打印------------------");
	list->Print();
}
void Exit()
{
	exit(0);
}