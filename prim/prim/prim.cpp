#include"prim.h"
G g;
int main()
{
	g.ReadGraph("in.txt");
	std::cout << g.Prim();
	return 0;
}