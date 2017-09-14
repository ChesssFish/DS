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
	if (is.good() && confirm("���ҵ����ݣ��Ƿ����<Y|n>")) {
		list->load(is);
		is.close();
	}
	int op;
	while (true)//�����������ѭ��
	{
		Menu();//��ӡ���˵�
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
	cout << "-----------���˵�------------" << endl;
	cout << "0: ֹͣӪҵ" << endl;
	cout << "1: ��ѯ" << endl;
	cout << "2: ���" << endl;
	cout << "3: �޸�" << endl;
	cout << "4: �Ƴ�" << endl;
	cout << "5: ����" << endl;
}
void Exit()
{
	cout << "----------�˳�-----------" << endl;
	if (confirm("�Ƿ񱣴�<Y|n>"))
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
		cout << "----------��ѯ-----------" << endl;
		cout << "0: ����" << endl;
		cout << "1: ��ѯ������Ʒ" << endl;
		cout << "2: ��ѯȫ����Ʒ" << endl;
		input(op, 0, 2);
		switch (op)
		{
		case 0:
			return;
		case 1:
			cout << "��������Ʒ����" << endl;
			cin >> name;
			tmp = (*list)[name];
			if (list->exist(tmp))
				tmp.show();
			else
				cout << "��Ʒ������" << endl;
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
		cout << "------------���-----------" << endl;
		cout << "0: ����" << endl;
		cout << "1: �������Ʒ" << endl;
		input(op, 0, 1);
		switch (op)
		{
		case 0:
			return;
		case 1:
			cout << "��������Ʒ����" << endl;
			cin >> name;
			cout << "��������Ʒ�̱�" << endl;
			cin >> logo;
			cout << "��������Ʒ�۸�" << endl;
			input(price, 0.0);
			cout << "��������Ʒ����" << endl;
			input(amount, 0);
			newNode = new Node(name,logo,price,amount);
			list->ins(newNode);
			cout << "��Ʒ��ӳɹ�" << endl;
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
		cout << "--------�޸�---------" << endl;
		cout << "0:����" << endl;
		cout << "1:�޸�" << endl;
		input(op, 0, 1);
		switch (op)
		{
		case 0:
			return;
		case 1:
			cout << "������Ҫ�޸ĵ���Ʒ����" << endl;
			cin >> name;
			tmp = (*list)[name];
			if (!list->exist(tmp))
				cout << "��Ʒ������" << endl;
			else
			{
				cout << "��Ʒ��Ϣ:" << endl;
				tmp.show();
				cout << "--------------------" << endl;
				cout << "�������µ���Ʒ����" << endl;
				cin >> Nname;
				cout << "�������µ���Ʒ�̱�" << endl;
				cin >> Nlogo;
				cout << "�������µ���Ʒ�۸�" << endl;
				input(Nprice, 0.0);
				cout << "�������µ���Ʒ����" << endl;
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
		cout << "----------ɾ��----------" << endl;
		cout << "0: ����" << endl;
		cout << "1: ɾ��" << endl;
		input(op);
		switch (op)
		{
		case 0:
			return;
		case 1:
			cout << "������Ҫɾ������Ʒ���" << endl;
			input(pos, 0);
			list->del(pos-1);
			cout << "��ɾ���� " << pos << " ����Ʒ" << endl;
		}
	}
}