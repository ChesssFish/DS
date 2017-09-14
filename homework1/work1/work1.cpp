#include <iostream>
#include <fstream>
#include <ctime>
#include <Windows.h>
#include <map>
#define MAXLEN 10
#define PAUSE system("pause")
using namespace std;
map<char, int> ctoi;//���ַ�ӳ�䵽�������Ա����Զ����ַ�˳��

//���ڱȽ��ַ�����˳��
//1��a �� b ���󡱣����ں���
//0��a, b Ϊͬһ�ַ���
//-1: a �� b ��С��������ǰ��
int cmp(char* a, char* b);
void swap(char * a, char* b);
//��ϰ���������
void string_sort(char **a, int low, int high);

//num:�ַ�������
void print_strings(char **a, int num);

//�ж������Ƿ���Ч����δ��ɣ�
bool valid();

void loadfile(char* filename);

char ** strings;
int strings_num;	
int main()
{
	/*-------------------------------------------------------
		�˳�����ö�ά����洢�ַ���						
		Ҳ�ɲ���Ԫ��Ϊ�ַ�����������飨��ʹ��string�ࣩ    
		Ҳ�ɲ�����ʽ�洢�����ǲ���������                    
		Ҳ�ɲ������νṹ�洢�����ֵ�����                    
	-------------------------------------------------------*/
	srand(time(NULL));//Ϊ������������
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
	//��a����ʱbҲ�����������
	if (ctoi[a[i]] == ctoi[b[i]])return 0;
	//��a����ʱbδ��������a<b
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

	//����Ч��Χ���������key
	int key = low + rand() % (high - low + 1);
	//��ʱ���key
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