#pragma once
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
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
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cin >> obj;
	}
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
//��ӡһ��ȷ����Ϣ������ѡ��
bool confirm(char* hint)
{
	std::cout << hint;
	char op;
	while (true)
	{
		cin >> op;
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		if (op == 'y' || op == 'Y')
			return true;
		if (op == 'n' || op == 'N')
			return false;
		std::cout << "������Ч������������" << std::endl;
	}
}