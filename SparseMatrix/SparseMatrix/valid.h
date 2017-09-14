#pragma once
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#define FLUSH_BUFFER cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
void error(const char* str)
{
	cout << str << endl;
}
//����һ����������Ƿ��ںϷ���Χ��
template<class T>void input(
	T &obj,
	const T min = std::numeric_limits<T>::min(), 
	const T max = std::numeric_limits<T>::max())
{
	std::cin >> obj;
	while (cin.fail() || obj < min || obj > max)
	{
		error("������Ч������������");
		cin.clear();
		FLUSH_BUFFER;
		cin >> obj;
	}
	FLUSH_BUFFER;
}
//��ӡһ��ȷ����Ϣ������ѡ��
bool confirm(char* hint)
{
	std::cout << hint;
	char op;
	while (true)
	{
		cin >> op;
		FLUSH_BUFFER;
		if (op == 'y' || op == 'Y')
			return true;
		if (op == 'n' || op == 'N')
			return false;
		error("������Ч������������");
	}
}