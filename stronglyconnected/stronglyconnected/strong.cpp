#include"stronglyconnected.h"
#include<iostream>
G g;
int main()
{
	g.ReadGraph("in.txt");
	if (g.IsStrong())
	{
		std::cout << "good" << std::endl;
	}
	else
	{
		std::cout << "bad" << std::endl;
	}
	return 0;
}