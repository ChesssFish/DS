#include<iostream>
#include<vector>
#include<fstream>
#include<ctime>
#include<algorithm>
#include<random>
using namespace std;
#define CUTOFF 50
#define MAXN 130000000
FILE* fp;
default_random_engine generator;
uniform_int_distribution<int> distribution(1, 1000000000);

template<typename T>
void SelectionSort(vector<T>& v, int low, int high)
{
	T min = numeric_limits<T>::max();
	int pos = 0;
	for (int j = low; j <= high;++j)
	{
		min = numeric_limits<T>::max();
		for (int i = j; i <= high; ++i)
		{
			if (v[i] < min)
			{
				min = v[i];
				pos = i;
			}
		}
		swap(v[pos], v[j]);
	}
}

template<typename T>
inline int SelectPivot(vector<T>& v, int low, int high)
{
	return low + distribution(generator) % (high - low);
}

template<typename T>
inline int Partition(vector<T>& v, int low, int high)
{
	//cout << low << " " << high << endl;
	int pos = SelectPivot(v, low, high);
	if (pos == -1) return -1;

	T key = v[pos];
	int i = low, j = high;
	swap(v[pos], v[i]);

	while (i < j)
	{
		while (i < j && v[j] >= key) --j;
		while (i < j && v[i] <= key) ++i;
		swap(v[i], v[j]);
	}
	v[i] = key;
	return (i == low) ? pos : i;
}

template<typename T>
void QuickSort(vector<T>& v, int low, int high)
{
	if (low >= high)return;
	if (high - low < CUTOFF)
	{
		SelectionSort(v, low, high);
	}
	else
	{
		while (low < high)
		{
			int m = Partition(v, low, high);
			if (m == -1)return;
			QuickSort(v, low, m - 1);
			low = m + 1;
		}
	}
}
template<typename T>
void Read(vector<T>& v)
{
	fp = fopen("in.dat", "rb");
	for (size_t i = 0; i < MAXN; ++i)
	{
		int buf;
		fread(&buf, sizeof(buf), 1, fp);
		v.push_back(buf);
	}
	fclose(fp);
}
int main()
{
	time_t start;
	time_t end;
	vector<int> a;
	//fp = fopen("in.dat", "wb");
	//for (size_t i = 0; i < 500000000; i++)
	//{
	//	uint32_t buf;
	//	buf = distribution(generator);
	//	fwrite(static_cast<void*>(&buf), sizeof(buf), 1, fp);
	//}
	//fclose(fp);
	start = clock();
	Read(a);
	end = clock();
	cout << end - start << endl;

	ofstream os;
	os.open("res.txt");
	start = clock();
	QuickSort(a, 0, a.size() - 1);
	end = clock();
	os << end - start << endl;
	os.close();

	os.open("data.txt");
	os << a.size() << endl;
	for (int i = 0; i < 1000; i++)
	{
		os << a[i] << endl;
	}
	os.close();
	/*start = clock();
	sort(a.begin(), a.end());
	end = clock();
	cout << end - start << endl;*/
	return 0;
}