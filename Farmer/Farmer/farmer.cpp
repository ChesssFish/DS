/*--------------------------------------------------------------------
	ũ��������⣺
	��һũ�����һ����,һֻ���һ���,��Ӻӵ��󰶳˴����Ұ�.
	�����ڴ�̫С,ũ��ÿ��ֻ�ܴ�һ����������,�������û��ũ�򿴹�,
	���ǻ����,���Բ�.
	��:ũ���������Ӳ��ܰ�ÿ��������ȫ���͹���?

	��һ����λ������������ʾ��ǰ���ӵ�״̬(state)
	1111 �ֱ����ũ�򡢲ˡ������ڵ�ǰ����
	0000 �ֱ����ũ�򡢲ˡ������ڶ԰�

	�������ֲ���(method)��
	1000(8) ��ũ���Լ�����
	1100(12)��ũ����˹���
	1010(10)��ũ��������
	1001(9) ��ũ����ǹ���

	�ӳ�ʼ״̬���й��ѣ������ֲ�����״̬���иı䣬
	�����Ϸ�״̬��ֱ���ҵ�Ŀ��״̬ 0000
---------------------------------------------------------------------*/

#include<iostream>
#include<iomanip>
#define MAXSTATES 16
using namespace std;

//���нڵ�
class node
{
public:
	char state;            //��ǰ״̬
	int pre;               //ǰһ״̬�ڶ����е�λ��
	int method;            //�����ַ�ʽת�Ƶõ�
	bool vis[MAXSTATES];   //��ǰ�ڵ�·�����ʹ��Ľڵ�
};
node q[MAXSTATES * 2];
//ũ�򡢲ˡ����� = 1111 = 15
int m[4] = {8,12,10,9 };//m[0]:ũ�� m[1]:ũ����� m[2]:ũ����� m[3]:ũ�����
int head = 0;
int tail = 0;
//���״̬�Ƿ�Ϸ����Ϸ��򷵻�ת�ƺ��״̬�����򷵻�-1
int check(int state, int method);
void print(int head, int method);
void print_method(int method);
void print_state(char state);

int main()
{
	q[tail].state = 15;
	q[tail].pre = -1;
	q[tail].method = -1;
	q[tail].vis[15] = true;
	tail++;
	int next;
	while (head < tail)
	{
		for (int i = 0; i < 4;i++)
		{
			next = check(q[head].state, m[i]);
			if (next == 0)
			{
				print(head, m[i]);
			}
			else if (next != -1 && !q[head].vis[next])
			{
				q[tail].state = next;
				q[tail].pre = head;
				q[tail].method = m[i];
				memcpy(q[tail].vis, q[q[tail].pre].vis, MAXSTATES);
				q[tail].vis[next] = true;
				tail++;
			}
		}
		head++;
	}
	return 0;
}
int check(int state, int method)
{
	//�жϵ�ǰ״̬�Ƿ����ִ�е�ǰ����
	if ((state & 8) == 0)
	{
		if((state & method) != 0)
			return -1;
	}
	else if ((state & method) != method)
	{
		return -1;
	}
	state ^= method;//ִ�е�ǰ����
	//�ж�ת�ƺ��״̬�Ƿ�Ϸ�
	if ((state & 8) == 0)
	{
		if ((state & 6) == 6 || (state & 3) == 3)
			return -1;
	}
	else if((state & 6) == 0 || (state & 3) == 0)
	{
		return -1;
	}
	return state;
}
void print(int head, int method)
{
	int way[MAXSTATES] = { 0 };
	int len = 0;
	
	while (head != -1)
	{
		way[len++] = head;
		head = q[head].pre;
	}
	for (int i = len - 1; i >= 0; i--)
	{
		print_method(q[way[i]].method);
		cout << ": ";
		print_state(q[way[i]].state);
		cout << endl;
	}
	print_method(method);
	cout << ": ";
	print_state(0);
	cout << endl << endl;
}
void print_method(int method)
{
	cout << setw(15);
	switch (method)
	{
	case 8:
		cout << "ũ�����";
		break;
	case 12:
		cout << "ũ����˹���";
		break;
	case 10:
		cout << "ũ��������";
		break;
	case 9:
		cout << "ũ����ǹ���";
		break;
	case -1:
		cout << "��ʼ����";
	default:
		break;
	}
}
void print_state(char state)
{
	char name[4][3] = { "ũ","��","��","��" };
	char t[4] = { 8,4,2,1 };
	for (int i = 0; i < 4; i++)
	{
		if ((state & t[i]) != 0)
			cout << name[i] << " ";
	}
	cout << "|";
	for (int i = 0; i < 4; i++)
	{
		if ((state& t[i]) == 0)
			cout << name[i] << " ";
	}
}