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
//输入一个数并检测是否在合法范围内
template<class T>void input(
	T &obj,
	const T min = std::numeric_limits<T>::min(), 
	const T max = std::numeric_limits<T>::max())
{
	std::cin >> obj;
	while (cin.fail() || obj < min || obj > max)
	{
		error("输入无效，请重新输入");
		cin.clear();
		FLUSH_BUFFER;
		cin >> obj;
	}
	FLUSH_BUFFER;
}
//打印一条确认信息并返回选择
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
		error("输入无效，请重新输入");
	}
}