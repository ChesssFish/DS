#pragma once
#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;

//�ڵ�����һ�����str
inline void Output(string str)
{
	cout << str << endl;
}
//����һ����������Ƿ��ںϷ���Χ��
template<class T>void Input(
	T &obj,
	const T min = std::numeric_limits<T>::min(), 
	const T max = std::numeric_limits<T>::max())
{
	std::cin >> obj;
	while (cin.fail() || obj < min || obj > max)
	{
		Output("������Ч������������");
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cin >> obj;
	}
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
//��ӡһ��ȷ����Ϣ������ѡ��
bool Confirm(string hint)
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