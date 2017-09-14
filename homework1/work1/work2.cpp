#include <iostream>
#include <fstream>
#include <cmath>
#include <Windows.h>
#define PAUSE system("pause")
#define MIN -1e90
#define EPS 1e-6
using namespace std;

int n;
double* num;
void loadfile(char* filename);
int main()
{
	loadfile("sample.txt");
	double max_num = MIN;
	int num_of_max_num = 0;
	int *positions = new int[n];
	//遍历列表找到最大元素
	for (int i = 0; i < n; i++)
	{
		if (num[i] > max_num)
			max_num = num[i];
	}
	//再次遍历找到所有的最大元素及位置
	for (int i = 0; i < n; i++)
	{
		if (fabs(num[i] - max_num) < EPS)
			positions[num_of_max_num++] = i;
	}
	/*------------------------------------------------------------------------
		采用了O(n)的算法，循环执行2n次.
		对于最大元素的位置，使用单链表存储可以节约空间
		如果采用分治的策略来寻找最大元素，可以略微提高效率，但会耗费
		更多的空间，而且由于无论如何都要遍历所有元素，时间复杂度无法突破O(n)
	--------------------------------------------------------------------------*/
	cout << "There is(are) " << num_of_max_num << "max number(s)" << endl;
	cout << "The max number is " << max_num << endl;
	cout << "Positions:" << endl;
	for (int i = 0; i < num_of_max_num; i++)
		cout << positions[i] << " ";
	cout << endl;
	PAUSE;
	return 0;
}
void loadfile(char* filename)
{
	ifstream is(filename);
	is >> n;
	num = new double[n];
	for (int i = 0;i < n; i++)
		is >> num[i];

}