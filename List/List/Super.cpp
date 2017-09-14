#include "List.h"
#include "Valid.h"
#include <iostream>
#include <fstream>
using namespace std;
List* list;
ifstream is;
ofstream os;
char* filename = "data.dat";
void Init();
void Menu();
void Exit();
void Show();
void Add();
void Modify();
void Remove();
int main()
{
	list = new List;
	is.open(filename, ios::in | ios::binary);
	if (is.good() && confirm("已找到数据，是否加载<Y|n>")) {
		list->load(is);
		is.close();
	}
	int op;
	while (true)//处理输入的主循环
	{
		Menu();//打印主菜单
		input(op, 0, 5);
		switch (op)
		{
		case 0:
			Exit();
			return 0;
			break;
		case 1:
			Show();
			break;
		case 2:
			Add();
			break;
		case 3:
			Modify();
			break;
		case 4:
			Remove();
			break;
		case 5:
			os.open(filename, 'b');
			list->save(os);
			os.close();
		}
	}
	return 0;
}
void Menu()
{
	cout << "-----------主菜单------------" << endl;
	cout << "0: 停止营业" << endl;
	cout << "1: 查询" << endl;
	cout << "2: 添加" << endl;
	cout << "3: 修改" << endl;
	cout << "4: 移除" << endl;
	cout << "5: 保存" << endl;
}
void Exit()
{
	cout << "----------退出-----------" << endl;
	if (confirm("是否保存<Y|n>"))
	{
		os.open(filename,ios::out|ios::binary);
		list->save(os);
		os.close();
	}
}
void Show()
{
	int op;
	char *name = new char[MAXLEN];
	Node tmp;
	while (true)
	{
		cout << "----------查询-----------" << endl;
		cout << "0: 返回" << endl;
		cout << "1: 查询单个商品" << endl;
		cout << "2: 查询全部商品" << endl;
		input(op, 0, 2);
		switch (op)
		{
		case 0:
			return;
		case 1:
			cout << "请输入商品名称" << endl;
			cin >> name;
			tmp = (*list)[name];
			if (list->exist(tmp))
				tmp.show();
			else
				cout << "商品不存在" << endl;
			break;
		case 2:
			list->show();
		}
	}
	delete[]name;
}
void Add()
{
	Node* newNode;
	char name[MAXLEN];
	char logo[MAXLEN];
	double price;
	int amount;
	int op;
	while (true)
	{
		cout << "------------添加-----------" << endl;
		cout << "0: 返回" << endl;
		cout << "1: 添加新商品" << endl;
		input(op, 0, 1);
		switch (op)
		{
		case 0:
			return;
		case 1:
			cout << "请输入商品名称" << endl;
			cin >> name;
			cout << "请输入商品商标" << endl;
			cin >> logo;
			cout << "请输入商品价格" << endl;
			input(price, 0.0);
			cout << "请输入商品数量" << endl;
			input(amount, 0);
			newNode = new Node(name,logo,price,amount);
			list->ins(newNode);
			cout << "商品添加成功" << endl;
			break;
		}
	}
}
void Modify()
{
	int op;
	char name[MAXLEN];
	char Nname[MAXLEN];
	char Nlogo[MAXLEN];
	double Nprice;
	int Namount;
	Node tmp;
	Node* newNode;
	while (true)
	{
		cout << "--------修改---------" << endl;
		cout << "0:返回" << endl;
		cout << "1:修改" << endl;
		input(op, 0, 1);
		switch (op)
		{
		case 0:
			return;
		case 1:
			cout << "请输入要修改的商品名称" << endl;
			cin >> name;
			tmp = (*list)[name];
			if (!list->exist(tmp))
				cout << "商品不存在" << endl;
			else
			{
				cout << "商品信息:" << endl;
				tmp.show();
				cout << "--------------------" << endl;
				cout << "请输入新的商品名称" << endl;
				cin >> Nname;
				cout << "请输入新的商品商标" << endl;
				cin >> Nlogo;
				cout << "请输入新的商品价格" << endl;
				input(Nprice, 0.0);
				cout << "请输入新的商品数量" << endl;
				input(Namount, 0);
				newNode = new Node(Nname, Nlogo, Nprice, Namount);
				list->del(tmp)->ins(newNode);
			}
		}
	}
}
void Remove()
{
	int op;
	int pos;
	while (true)
	{
		cout << "----------删除----------" << endl;
		cout << "0: 返回" << endl;
		cout << "1: 删除" << endl;
		input(op);
		switch (op)
		{
		case 0:
			return;
		case 1:
			cout << "请输入要删除的商品编号" << endl;
			input(pos, 0);
			list->del(pos-1);
			cout << "已删除第 " << pos << " 号商品" << endl;
		}
	}
}