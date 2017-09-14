#include<vector>
#include"rbt.h"
#include<fstream>
#include<iostream>
#include<string>
#include<ctime>
rbt* t;
int main()
{
	t = new rbt;
	std::ifstream is;
	std::string f = "random.txt";
	is.open(f);
	int i;
	std::vector<int> a;
	while (is >> i)
	{
		a.push_back(i);
	}
	std::cout << clock() << std::endl;
	for (auto i : a)
	{
		t->Insert(i);
	}
	std::cout << clock() << std::endl;
	for (auto i : a)
	{
		t->Delete(i);
	}
	std::cout << clock() << std::endl;
	//std::vector<int> a = { 41, 38, 31, 12, 19, 8 };
	//for (auto i : a)
	//{
	//	t->Insert(i);
	//}
	//std::vector<int> b = { 8,12,19,31,38,41 };
	//for (auto i : b)
	//{
	//	t->Delete(i);
	//}
	//t->Delete(41);
	return 0;
}