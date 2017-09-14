#pragma once
#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;

//在单独的一行输出str
inline void Output(string str)
{
	cout << str << endl;
}
//输入一个数并检测是否在合法范围内
template<class T>void Input(
	T &obj,
	const T min = std::numeric_limits<T>::min(), 
	const T max = std::numeric_limits<T>::max())
{
	std::cin >> obj;
	while (cin.fail() || obj < min || obj > max)
	{
		Output("输入无效，请重新输入");
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cin >> obj;
	}
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
//打印一条确认信息并返回选择
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
		std::cout << "输入无效，请重新输入" << std::endl;
	}
}