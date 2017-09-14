#pragma once
#include <iostream>

void error(const char* str)
{
	std::cout << str << std::endl;
}
void input(int &obj, int min, int max)
{
	std::cin >> obj;
	while (std::cin.fail() || obj < min || obj > max)
	{
		error("������Ч������������");
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin >> obj;
	}
}
