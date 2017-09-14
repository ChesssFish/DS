/*----------------------------------------------------------------
	文件名:test.cpp
	AVL.h的测试程序
	同时包含了对冒泡、选择、插入、快速四种排序算法的时间性能测试
	以及对整型序列的二分查找算法
----------------------------------------------------------------*/

#include"AVL.h"
#include"AVL.cpp"
#include<fstream>
#include<time.h>
#define MAXN 10
#define MAXNUM 10000007
using namespace std;
AVL<int> tree;
ofstream os;
ifstream is;
clock_t start;
clock_t endt;
int arr[MAXN] = { 0 };
void swap(int &a, int &b);
int select_min(int *a, int start, int end);
int Find(int* arr, int n, int key);
void bubble_sort(int* a, int start, int end);
void selection_sort(int* a, int start, int end);
void insertion_sort(int* a, int start, int end);
void q_sort(int* a, int low, int high);
void get_num();
void test_sort(char* name, int len, void(*f) (int*a, int start, int end));
void test_bst();
int main()
{
	srand(time(NULL));

	test_sort("bubble_sort", MAXN-1, bubble_sort);
	test_sort("selection_sort", MAXN-1, selection_sort);
	test_sort("insertion_sort", MAXN-1, insertion_sort);
	test_sort("quicksort", MAXN-1, q_sort);

	test_bst();
	return 0;
}
void swap(int &a, int &b)
{
	if (a != b)
		a ^= b ^= a ^= b;
}
int select_min(int *a, int start, int end)
{
	int min = numeric_limits<int>::max();
	int pos = -1;
	for (int i = start; i <= end; i++)
	{
		if (a[i] < min)
		{
			min = a[i];
			pos = i;
		}
	}
	return pos;
}
int Find(int* arr, int n, int key)
{
	int low = 0;
	int high = n - 1;
	long long mid;
	while (low <= high)
	{
		mid = (low + high) / 2;
		if (arr[mid] == key)
			return mid;
		else if (arr[mid] < key)
			low = mid + 1;
		else
			high = mid - 1;
	}
	return -1;
}
void bubble_sort(int* a, int start, int end)
{
	bool sorted = true;
	for (int i = start; i <= end; i++)
	{
		sorted = true;
		for (int j = start; j <= end - i - 1; j++)
		{
			if (a[j] > a[j + 1])
			{
				swap(a[j], a[j + 1]);
				sorted = false;
			}
		}
		if (sorted)break;
	}
}
void selection_sort(int* a, int start, int end)
{
	for (int i = start; i <= end - 1; i++)
	{
		/*--------------------------------------------------
			i之前的序列有序，之后无序
			每次在无序序列中选择最小的元素加入有序序列末尾
		--------------------------------------------------*/
		swap(a[i], a[select_min(a, i, end)]);
	}
}
void insertion_sort(int* a, int start, int end)
{
	int pos;
	int val;
	for (int i = start + 1; i <= end; i++)
	{
		/*--------------------------------------------------
			i之前的序列有序，之后无序
			每次将无序序列的第一个元素插入有序序列中
		--------------------------------------------------*/
		pos = numeric_limits<int>::max();
		val = a[i];
		for (int j = start; j < i; j++)
		{
			if (a[i] < a[j])
			{
				pos = j;
				break;
			}
		}
		for (int j = i - 1;j >= pos;j--)
		{
			a[j + 1] = a[j];
		}
		a[pos] = val;
	}
}
void q_sort(int* a, int low, int high)
{
	if (low >= high)return;
	//在有效范围内随机生成key
	int key = low + rand() % (high - low + 1);
	int i = low;
	int j = high;
	int val = a[key];//挖洞
	swap(a[key], a[low]);
	while (i < j)//划分
	{
		while (i < j && a[j] >= val)j--;
		a[i] = a[j];
		while (i < j && a[i] <= val)i++;
		a[j] = a[i];
	}
	a[i] = val;//填洞
	q_sort(a, low, i - 1);
	q_sort(a, i + 1, high);
}
void get_num()
{
	for (int i = 0; i < MAXN; i++)
		arr[i] = rand() % MAXNUM;
}
void test_sort(char* name, int len, void(*f) (int*a, int start, int end))
{
	cout << "test for time of function " << name << "(N = " << len+1 << ")"<<": ";
	start = clock();

	get_num();
	f(arr, 0, len);

	endt = clock();
	cout << endt - start << " ms" << endl;
}
void test_bst()
{
	cout << "------------二叉排序树测试-----------" << endl;
	cout << "i: 插入" << endl;
	cout << "d: 删除" << endl;
	cout << "f: 查询" << endl;
	char op;
	int val;
	while (true)
	{
		cin >> op;
		cin >> val;
		if (op == 'i')
			tree.ins(val);
		else if (op == 'd')
			tree.del(val);
		else if (op == 'f')
			cout << Find(tree.mInOrder, tree.mlen, val) << endl;
		cout << endl;
		cout << "中序序列:";tree.getInOrder();
	}
}