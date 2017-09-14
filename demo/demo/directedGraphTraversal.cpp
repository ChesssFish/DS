/*----------------------------------------------------------------
	文件名：directedGraphTraversal
	作者：sis
	------------------------------------------------------------
	作用：演示有向图的遍历方法
	问题描述：输入一张有向图，遍历之
----------------------------------------------------------------*/
#include<iostream>
#include<fstream>
#include<vector>
using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::vector;

vector<bool> vis;//标记数组，标记节点的访问情况
vector<vector<int>> map;//邻接矩阵
int n;//顶点数
ifstream is;


void dfs(int cur)
{
	if (vis[cur])
	{
		return;
	}
	vis[cur] = true;
	cout << cur << endl;
	for (int i = 0; i < n; ++i)
	{
		if (map[cur][i] == 1 && !vis[i])
		{
			dfs(i);
		}
	}

}

int main()
{
	n = 4;

	map.resize(n);
	for (int i = 0; i < n; ++i)//初始化数组
	{
		vis.push_back(false);
		map[i].resize(n);
	}

	is.open("in.txt");
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			int tmp;
			is >> tmp;
			map[i][j] = tmp;	//map[i][j] = 0,没路
		}
	}
	is.close();

	dfs(0);
	return 0;
}