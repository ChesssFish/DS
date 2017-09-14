#include <fstream>
#include <iostream>
#include <time.h>
using namespace std;

//生成maxn个字符串
void GenerateSample1(int maxn);
//生成maxn个随机实数
void GenerateSample2(int maxn);
//生成maxn个顶点的比赛图
void GenerateSample3(int maxn);

int a;
class A
{
public:
	A() { cin >> a; }
	~A() {};
};
int main(int argc, char* argv[])
{
	A b;
	if (cin.fail())
		cout << "fail";

	exit(0);

	if (argc < 3)
	{
		cout << "用法: SampleGenerator.exe <样本号> <样本大小>" << endl;
		return 0;
	}
	srand(time(NULL));
	switch (argv[1][0])
	{
	case'1':
		GenerateSample1(atoi(argv[2]));
		cout << "Completed" << endl;
		break;
	case'2':
		GenerateSample2(atoi(argv[2]));
		cout << "Completed" << endl;
		break;
	case'3':
		GenerateSample3(atoi(argv[2]));
		cout << "Completed" << endl;
		break;
	default:
		cout << "用法: SampleGenerator.exe <样本号> <样本大小>" << endl;
		return 0;
	}
	return 0;
}
void GenerateSample1(int maxn)
{
	char charactorSet[] = { '0','1','2','3','4','5','6','7','8','9' };
}
void GenerateSample2(int maxn)
{
	ofstream os("sample2.txt");
	const double IP = 1e4;
	os << maxn << endl;
	for (int i = 0; i < maxn; i++)
		os << (double)rand() / (double)rand() * IP << endl;
	os.close();
}
void GenerateSample3(int maxn)
{
	ofstream os("sample3.txt");
	os << maxn << endl;
	for (int i = 0; i < maxn; i++)
		for (int j = 0; j <= i; j++)
		{
			if (i == j)
				os << i << " " << j << " " << 0 << endl;
			else
				os << i << " " << j << " " << rand() % 2 << endl;
		}
	os.close();
}