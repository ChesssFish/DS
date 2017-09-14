#include"acAutomation.h"
using std::vector;
using std::string;
using std::cin;
using std::cout;
using std::ifstream;
using std::ofstream;
AC* ac;
ifstream is;
ofstream os;
auto input()-> vector<string>
{
	int num;
	string str;
	vector<string> words;

	is.open("in.txt");
	is >> num;
	for (int i = 0; i < num; ++i)
	{
		is >> str;
		words.push_back(str);
	}
	is.close();
	return words;
}

int main()
{
	ac = new AC;
	ac->build(input());

	vector<int> ans;

	string str;
	while (true)
	{
		cin >> str;
		ans = ac->query(str);
		for (auto i : ans)
		{
			cout << i << " ";
		}
		cout << std::endl;
	}
	return 0;
}