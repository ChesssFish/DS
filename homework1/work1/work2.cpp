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
	//�����б��ҵ����Ԫ��
	for (int i = 0; i < n; i++)
	{
		if (num[i] > max_num)
			max_num = num[i];
	}
	//�ٴα����ҵ����е����Ԫ�ؼ�λ��
	for (int i = 0; i < n; i++)
	{
		if (fabs(num[i] - max_num) < EPS)
			positions[num_of_max_num++] = i;
	}
	/*------------------------------------------------------------------------
		������O(n)���㷨��ѭ��ִ��2n��.
		�������Ԫ�ص�λ�ã�ʹ�õ�����洢���Խ�Լ�ռ�
		������÷��εĲ�����Ѱ�����Ԫ�أ�������΢���Ч�ʣ�����ķ�
		����Ŀռ䣬��������������ζ�Ҫ��������Ԫ�أ�ʱ�临�Ӷ��޷�ͻ��O(n)
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