#include"biconnect.h"
G g;
int main()
{
	g.ReadGraph("in.txt");
	if (g.IsBioconnected())
	{
		std::cout << "good" << std::endl;
	}
	else
	{
		std::cout << "bad" << std::endl;
	}
	return 0;
}