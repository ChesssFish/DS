#include<iostream>
#include<fstream>
#include<vector>
std::vector<std::vector<int>> a;
std::vector<std::vector<int>> ans;
const int INF = 0xffffff;
int n;
void Init(std::vector<std::vector<int>>& v);
void Floyd(void)
{
	for (int k = 0; k < n; k++)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (ans[i][j] > ans[i][k] + ans[k][j])
					ans[i][j] = ans[i][k] + ans[k][j];
			}
		}
	}
}
int main()
{
	std::ifstream is;
	is.open("in.txt");
	is >> n;
	Init(a);
	int u, v, w;
	while (is >> u >> v >> w)
	{
		a[u][v] = w;
	}
	ans = a;
	Floyd();
	return 0;

}
void Init(std::vector<std::vector<int>>& v)
{
	v.resize(n, std::vector<int>());
	for (int i = 0; i < n; i++)
	{
		v[i].resize(n, INF);
		v[i][i] = 0;
	}
}