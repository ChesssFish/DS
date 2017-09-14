#include<iostream>
#include<fstream>
#include<string>
#include<ctime>
using namespace std;
#define START int a = clock();
#define END int b = clock();cout << "time = " << b - a <<endl;
ifstream is;
string target;
string patten;
int* match_pos;
void input(const string& filename, string& str);
void pre(const string& str);
int match(const string& tar, const string& pat);

void naive_match_alogrithm(const string tar, const string pat);
int main()
{
	int result = -1;
	input("target.txt", target);
	input("patten.txt", patten);

	START;
	pre(patten);
	result = match(target, patten);

	if (result == -1)
	{
		cout << "未匹配到模式串" << endl;
	}
	else
	{
		cout << "在目标串第 " << result << " - " <<
			result + patten.length() - 1 << "个字符匹配成功"<< endl;
	}
	delete[]match_pos;
	END;

	naive_match_alogrithm(target, patten);
	return 0;
}

void naive_match_alogrithm(const string tar, const string pat)
{
	START;
	int tlen = tar.length();
	int plen = pat.length();
	int j;
	for (int i = 0; i < tlen; i++)
	{
		for (j = 0; j < plen;j++)
		{
			int pos = i;
			if (tar[pos++] != pat[j])
				break;
		}
		if (j == plen)
		{
			cout << "成功" << endl;
			break;
		}
	}
	END;
}

void input(const string& filename, string& str)
{
	is.open(filename);
	is >> str;
	is.close();
}
void pre(const string& str)
{
	int end = str.length();
	match_pos = new int[end];
	match_pos[0] = -1;
	for (int i = 1; i < end; i++)
	{
		int j = match_pos[i - 1]; //前一个字符最后匹配的位置
		while (j != -1)
		{
			if (str[j + 1] == str[i])
			{
				j++;
				break;
			}
			else
			{
				j = match_pos[j];
			}
		}
		if (j == -1 && str[j + 1] == str[i])
		{
			j = 0;
		}
		match_pos[i] = j;
	}
}
int match(const string& tar, const string& pat)
{
	int end = tar.length();
	int pat_len = pat.length();
	int j = -1;
	for (int i = 0; i < end; i++)
	{
		while (tar[i] != pat[j + 1] && j != -1)
		{
			j = match_pos[j];
		}
		if (tar[i] == pat[j + 1])
		{
			j++;
		}
		if (j == pat_len - 1)
		{
			return i - pat_len + 1;
		}
	}
	return -1;
}