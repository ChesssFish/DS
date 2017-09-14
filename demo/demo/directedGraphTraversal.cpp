/*----------------------------------------------------------------
	�ļ�����directedGraphTraversal
	���ߣ�sis
	------------------------------------------------------------
	���ã���ʾ����ͼ�ı�������
	��������������һ������ͼ������֮
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

vector<bool> vis;//������飬��ǽڵ�ķ������
vector<vector<int>> map;//�ڽӾ���
int n;//������
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
	for (int i = 0; i < n; ++i)//��ʼ������
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
			map[i][j] = tmp;	//map[i][j] = 0,û·
		}
	}
	is.close();

	dfs(0);
	return 0;
}