#include<fstream>
#include<list>
#include<iostream>
#include<vector>
#include<string>
#include<ctime>
using namespace std;
vector<list<uint16_t>> table;
const int length = (1 << 16);

bool search(uint16_t ip_seg, uint16_t ip_add);
void f(int x)
{
	if (x == 0)
		return;
	x--;
	f(x);
}
//#define GENERATE_RANDOM
int main()
{
	f(2000000);
	return 0;
	string file = "ip.txt";
#ifdef GENERATE_RANDOM
	ofstream os(file);
	srand(time(0));
	for (size_t i = 0; i < 30000000; i++)
	{
		os << rand() % 256 << ' ';
		os << rand() % 256 << ' ';
		os << rand() % 256 << ' ';
		os << rand() % 256 << endl;
	}
	os.close();
	return 0;
#endif
	/*
	ifstream is(file);
	uint16_t a1, a2, a3, a4;
	cout << clock() << endl;
	table.resize(length);
	while (is >> a1 >> a2 >> a3 >> a4)
	{
		uint16_t ip_seg = ((a1 << 8) + a2);
		uint16_t ip_add = ((a3 << 8) + a4);
		if (!search(ip_seg, ip_add))
		{
			table[ip_seg].push_back(ip_add);
		}
	}
	cout << clock() << endl;
	while (cin >> a1 >> a2 >> a3 >> a4)
	{
		uint16_t ip_seg = ((a1 << 8) + a2);
		uint16_t ip_add = ((a3 << 8) + a4);
		search(ip_seg, ip_add) ?
			(cout << "Found" << endl) : 
			(cout << "Not Found" << endl);
	}
	*/
	return 0;
}
bool search(uint16_t seg, uint16_t add)
{
	for (const auto i : table[seg])
		if (i == add)
			return true;
	return false;
}