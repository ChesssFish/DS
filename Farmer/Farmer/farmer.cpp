/*--------------------------------------------------------------------
	农夫过河问题：
	有一农夫带着一条狼,一只羊和一筐菜,想从河的左岸乘船到右岸.
	但由于船太小,农夫每次只能带一样东西过河,而且如果没有农夫看管,
	则狼会吃羊,羊会吃菜.
	问:农夫怎样过河才能把每个东西安全地送过河?

	用一个四位二进制向量表示当前过河的状态(state)
	1111 分别代表农夫、菜、羊、狼在当前岸边
	0000 分别代表农夫、菜、羊、狼在对岸

	定义四种操作(method)：
	1000(8) ：农夫自己过河
	1100(12)：农夫带菜过河
	1010(10)：农夫带羊过河
	1001(9) ：农夫带狼过河

	从初始状态进行广搜，用四种操作对状态进行改变，
	保留合法状态，直至找到目标状态 0000
---------------------------------------------------------------------*/

#include<iostream>
#include<iomanip>
#define MAXSTATES 16
using namespace std;

//队列节点
class node
{
public:
	char state;            //当前状态
	int pre;               //前一状态在队列中的位置
	int method;            //由那种方式转移得到
	bool vis[MAXSTATES];   //当前节点路径访问过的节点
};
node q[MAXSTATES * 2];
//农夫、菜、羊、狼 = 1111 = 15
int m[4] = {8,12,10,9 };//m[0]:农夫 m[1]:农夫带菜 m[2]:农夫带羊 m[3]:农夫带狼
int head = 0;
int tail = 0;
//检查状态是否合法，合法则返回转移后的状态，否则返回-1
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
	//判断当前状态是否可以执行当前操作
	if ((state & 8) == 0)
	{
		if((state & method) != 0)
			return -1;
	}
	else if ((state & method) != method)
	{
		return -1;
	}
	state ^= method;//执行当前操作
	//判断转移后的状态是否合法
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
		cout << "农夫过河";
		break;
	case 12:
		cout << "农夫带菜过河";
		break;
	case 10:
		cout << "农夫带羊过河";
		break;
	case 9:
		cout << "农夫带狼过河";
		break;
	case -1:
		cout << "开始过河";
	default:
		break;
	}
}
void print_state(char state)
{
	char name[4][3] = { "农","菜","羊","狼" };
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