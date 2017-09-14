#include "work4.h"

Match* match;
int n = -1, m = -1, w = -1;

err Initialize();
//������������Ƿ�Ϸ�
void cin_s(int &obj, 
    int min = MIN, 
    int max = MAX);
//��ӡ���˵�����ִ����������
bool confirm(string hint);
void main_menu();
void sub_exit(string filename);
void sub_input();
void sub_sort();
void sub_query();
//�ļ����ء����˵����ơ��˳�����
//�����ӳ���һ�ɲ��˳����򣬽�����״̬
int main()
{
	string filename = "Match.d";
	ifstream is;
	is.open(filename);
	err state;

	if (is.good() && confirm("���ҵ�" + filename + ",�Ƿ����? <Y|N>:"))
	{
		match = new Match(is);
		cout << "�ɹ�����" + filename << endl;
	}
	else
	{
		cout << "�����µı���......" << endl;
		state = Initialize();
		if (state == FINISHED)
			cout << "���������ɹ���" << endl;
		else
			exit(state);
	}
	is.close();
	int option = 1;
	while (option)
	{
		main_menu();
		cin_s(option);
		switch (option)
		{
		case 0:
			sub_exit(filename);
			exit(0);
		case 1:
			match->save(filename);
			break;
		case 2:
			sub_input();
			break;
		case 3:
			sub_sort();
			break;
		case 4:
			sub_query();
			break;
		default:
			cout << "������Ч,����������" << endl;
		}
	}
}
err Initialize()
{
	cout << "������ѧԺ����(1~20): " << endl;
	cin_s(n, 0, 20);
	cout << "������������Ŀ����(1~20): " << endl;
	cin_s(m, 0, 20);
	cout << "������Ů����Ŀ����(1~20): " << endl;
	cin_s(w, 0, 20);
	match = new Match();
	if (match == NULL)
		return NOT_ENOUGH_RAM;
	cout << "---����ѧԺ����---" << endl;
	string name;
	//����ѧԺ
	for (int i = 0; i < n; i++)
	{
		cout << "������ " << i+1 << " ��ѧԺ������:";
		cin >> name;
		match->SetAcademy(i+1, name);
		cout << "ѧԺ " << i+1 << " ����ɹ�" << endl;
	}
	cout << "---������Ŀ����---" << endl;
	//������Ŀ
	for (int i = 0; i < m + w; i ++)
	{
		cout << "������ " << i + 1 << " ����Ŀ������:";
		cin >> name;
		match->SetEvent(i+1, name);
		cout << "��Ŀ " << i+1 << " ����ɹ�" << endl;
	}
	return FINISHED;
}
void cin_s(int &obj, int min, int max)
{
	cin >> obj;
	while (cin.fail() || obj < min || obj > max)
	{
		cout << "������Ч������������" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> obj;
	}
}
bool confirm(string hint)
{
	cout << hint;
	string op;
	while (true)
	{
		cin >> op;
		if (op == "y" || op == "Y")
			return true;
		if (op == "n" || op == "N")
			return false;
		cout << "������Ч������������" << endl;
	}
}
void main_menu()
{
	cout << "-----------------���˵�------------------" << endl;
	cout << "0: �˳�" << endl;
	cout << "1: ����" << endl;
	cout << "2: ����ɼ�" << endl;
	cout << "3: ѧԺ����" << endl;
	cout << "4: ��ѯ" << endl;
}
void sub_exit(string filename)
{
	cout << "-----------------�˳�--------------------" << endl;
	if(confirm("�Ƿ񱣴�? <Y|N>:"))
		match->save(filename);
}
void sub_input()
{
	int option;
	while (true)
	{
		cout << "----------------����ɼ�-----------------" << endl;
		cout << "0: ����" << endl;
		cout << "1: ����������" << endl;
		cout << "2: ���������" << endl;
		cin_s(option);
		switch (option)
		{
		case 0:return;
		case 1:
		{
			string Academy_name, Event_name;
			int score;
			cout << "-----------------����������ɼ�-------------" << endl;
			cout << "�����Ϊ0��������" << endl;
			while (true)
			{
				cout << "������ѧԺ����:";
				cin >> Academy_name;
				cout << "��������Ŀ����:";
				cin >> Event_name;
				cout << "��������Ŀ�ɼ�:";
				cin_s(score, 0, MAXSCORE);
				if (Academy_name == "0" && Event_name == "0" && score == 0)
					break;
				if (!match->tellA(Academy_name) || !match->tellE(Event_name))
				{
					cout << "ѧԺ����Ŀ�����ڣ�" << endl;
					continue;
				}
				match->GetAcademy(Academy_name)->SetScore(Event_name, score);
				cout << "��ӳɹ�" << endl;
			}
			break;
		}
		case 2:
		{
			int Academy_id, Event_id;
			int score;
			cout << "-----------------���������ɼ�-------------" << endl;
			cout << "�����Ϊ0��������" << endl;
			while (true)
			{
				cout << "������ѧԺ���: ";
				cin_s(Academy_id, 0, n + 1);
				cout << "��������Ŀ���: ";
				cin_s(Event_id, 0, m + w + 1);
				cout << "������ɼ�: ";
				cin_s(score, 0, MAXSCORE);
				if (Academy_id == 0 && Event_id == 0 && score == 0)
					break;
				match->GetAcademy(Academy_id)->SetScore(Event_id, score);
				cout << "---��ӳɹ�---" << endl;
			}
		}
		}
	}
}
void sub_sort()
{
	cout << "---------------ѧԺ����----------------" << endl;
	cout << "0: ����" << endl;
	cout << "1: ��ѧԺ�������" << endl;
	cout << "2: ��ѧԺ��������" << endl;
	cout << "3: ��ѧԺ�ܷ�����" << endl;
	cout << "4: �����������ܷ�����" << endl;
	cout << "5: ��Ů�������ܷ�����" << endl;
	int option;
	while (true)
	{
		cin_s(option);
		if (!option)
			return;
		match->Academy_sort(option);
		cout << "������ɣ�" << endl;
	}
}
void sub_query()
{
	int option;
	int Academy_id;
	int Event_id;
	while (true)
	{
		cout << "---------------��ѯ---------------" << endl;
		cout << "0: ����" << endl;
		cout << "1: ��ѧԺ��Ų�ѯ��Ŀ�ɼ�" << endl;
		cout << "2: ����Ŀ��Ų�ѯѧԺ����" << endl;
		cin_s(option, 0, 2);
		if (!option)
			return;
		if (option == 1)
		{
			int score;
			cout << "������Ҫ��ѯ��ѧԺ���" << endl;
			cin_s(Academy_id, 1, n);
			cout << "������Ҫ��ѯ����Ŀ���" << endl;
			cin_s(Event_id, 1, m+w);
			score = match->GetAcademy(Academy_id)->GetScore(Event_id);
			cout << Academy_id << "ѧԺ" << Event_id << "��Ŀ�ĳɼ�Ϊ: " << score << endl;
		}
		else
		{
			int* rank;
			int num;
			cout << "������Ҫ��ѯ����Ŀ���" << endl;
			cin_s(Event_id, 1, m + w);
			rank = match->GetRank(Event_id);
			num = Event_id < m + 1 ? 5 : 3;
			for (int i = 0; i < 5; i++)
				cout << "��" << i + 1 << "��:" << match->GetAcademy(rank[i])->GetName() << endl;
		}
	}
}