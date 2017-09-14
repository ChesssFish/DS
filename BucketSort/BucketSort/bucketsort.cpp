#include<iostream>
#include<fstream>
#include<bitset>
#include<ctime>
#define MAXN 1000000000
#define TESTN 500000000
using namespace std;
FILE* fp;
bitset<MAXN> bucket;
int main()
{
	uint32_t buf;
	uint32_t maxnum = 0;
	time_t start, end;

	//fp = fopen("in.dat", "wb");
	//for (int i = 0; i < TESTN; i++)
	//{
	//	buf = rand();
	//	fwrite(&buf, sizeof(i), 1, fp);
	//}
	//fclose(fp);
	//fp = fopen("in.dat", "rb");

	fp = fopen("in.dat", "rb");
	for (size_t i = 0; i < TESTN; i ++)
	{
		fread(&buf, sizeof(buf), 1, fp);
		bucket[buf] = true;
		if (buf > maxnum)
			maxnum = buf;
	}
	fclose(fp);

	start = clock();
	for (size_t i = 0; i < maxnum; i++)
	{
		if (bucket[i])
			;
		//fwrite(&i, sizeof(buf), 1, fp);
	}
	end = clock();

	cout << end - start;
	cin >> buf;
	return 0;
}