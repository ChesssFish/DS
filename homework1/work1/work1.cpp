#include <iostream>
#include <fstream>
#include <ctime>
#include <Windows.h>
#include <map>
#define MAXLEN 10
#define PAUSE system("pause")
using namespace std;
map<char, int> ctoi;//将字符映射到整数，以便于自定义字符顺序

//用于比较字符串的顺序
//1：a 比 b “大”，排在后面
//0：a, b 为同一字符串
//-1: a 比 b “小”，排在前面
int cmp(char* a, char* b);
void swap(char * a, char* b);
//练习随机化快排
void string_sort(char **a, int low, int high);

//num:字符串个数
void print_strings(char **a, int num);

//判断输入是否有效（尚未完成）
bool valid();

void loadfile(char* filename);

char ** strings;
int strings_num;	
int main()
{
	/*-------------------------------------------------------
		此程序采用二维数组存储字符串						
		也可采用元素为字符串对象的数组（如使用string类）    
		也可采用链式存储，但是不便于排序                    
		也可采用树形结构存储（如字典树）                    
	-------------------------------------------------------*/
	srand(time(NULL));//为快排生成种子
	loadfile("sample.txt");
	int cnt = 0;
	for (char i = 'A'; i < 'Z'; i++)
		ctoi[i] = cnt++;
	for (char i = '0'; i < '9'; i++)
		ctoi[i] = cnt++;
	string_sort(strings, 0, strings_num - 1);

	cout << "The sorted string is:" << endl;
	print_strings(strings, strings_num);

	PAUSE;
	return 0;
}
int cmp(char* a, char* b)
{
	int i = 0;
	for (i = 0; a[i] != '\0'; i++)
	{
		if (ctoi[a[i]] > ctoi[b[i]])return 1;
		else if (ctoi[a[i]] < ctoi[b[i]])return -1;
	}
	//若a结束时b也结束，则相等
	if (ctoi[a[i]] == ctoi[b[i]])return 0;
	//若a结束时b未结束，则a<b
	else return -1;
}
void swap(char * a, char* b)
{
	char* temp = new char[MAXLEN];
	memcpy(temp, a, MAXLEN);
	memcpy(a, b, MAXLEN);
	memcpy(b, temp, MAXLEN);
	delete temp;
}
void string_sort(char** str, int low, int high)
{
	if (low >= high)return;

	//在有效范围内随机生成key
	int key = low + rand() % (high - low + 1);
	//临时存放key
	char * value = new char[MAXLEN];
	memcpy(value, str[key], MAXLEN);
	if (key != low)
		swap(str[low], str[key]);
	int i = low;
	int j = high;
	while (i < j)
	{
		while (i < j && cmp(str[j], value) >= 0)j--;
		memcpy(str[i], str[j], MAXLEN);
		while (i < j && cmp(str[i], value) <= 0)i++;
		memcpy(str[j], str[i], MAXLEN);
	}
	memcpy(str[i], value, MAXLEN);
	delete value;
	string_sort(str, low, i - 1);
	string_sort(str, i + 1, high);
}
void print_strings(char** str, int num)
{
	for (int i = 0; i < num; i++)
	{
		cout << str[i] << endl;
	}
	cout << endl;
}
void loadfile(char* filename)
{
	ifstream is(filename);
	is >> strings_num;
	strings = new char*[strings_num];
	for (int i = 0; i < strings_num; i++)
	{
		strings[i] = new char [MAXLEN];
		is >> strings[i];
	}
}