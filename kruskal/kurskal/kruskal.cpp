#include"kruskal.h"
G g;
int main()
{
	g.ReadGraph("in.txt");
	std::vector<Edge> a = g.Kruskal();
	return 0;
}