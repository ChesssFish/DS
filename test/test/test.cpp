#include<vector>
#include<iostream>
#include<string>
#include<list>
#include<cstdarg>
#include<regex>
#define max [](int x,int y){return x > y ? x : y;}
//#define max(a,b) (a > b ? a : b)
using namespace std;


bool vis[3] = { false,false,false };
void a(int x)
{
	if (vis[x])
	{
		return;
	}
	vis[x] = true;
	for (int i = 0; i < 3; i++)
	{
		cout << i << endl;
		a(i);
	}
}

class Game
{
public:
	Game() { cout << "Game.const" << endl; }
	static int rule;
};
class BorderGame :public Game
{
public:
	BorderGame() { cout << "Border.const" << endl; }
};
class Chess :public BorderGame
{
public:
	Chess() { cout << "Chess.const" << endl; }
};

template<typename _Ty>
class A
{
public:
	A() {};
	~A() {};
	std::list<_Ty> list1;
private:
};

class InClassInit
{
public:
	InClassInit(int x = 3) :a(x) {}
	///*InClassInit& operator,(const InClassInit& rhs)
	//{
	//	a += rhs.a;
	//	return *this;
	//*/}
private:
	int a = 3;
};
struct Data
{
	int a;
	char b;
};
vector<int> listreturn(void)
{
	return{ 1,2,3,4,5,6,7 };
}
template<typename _Ty>
vector<_Ty> lr(_Ty a1, _Ty a2, ...)
{

}
auto trailing(int x)
{
	return [x](double y, double z)->int {return (double)x + y*z;};
}
auto pf(int) ->int(*)(int*, int);

int f(int, int);
vector<decltype(f)*> vpf;

int __stdcall g(int x, ...)
{
	va_list argp;
	va_start(argp, x);
	int para;
	//while (true)
	{
		para = va_arg(argp, int);
		cout << para << endl;
	}
	return 0;
}
bool cmp(const string& a, const string& b);
auto p(int a)
{
	return [a](int b) {return [a, b](int c) {return a + b + c;};};
}

class Del
{
public:
	Del(int a) :m_a(a) {};
	Del(const Del&) = delete;
	Del& operator=(const Del&) = delete;
	void operator()(int x)
	{
		;
	}
	~Del() = default;
	int m_a;
};

int main()
{
	/*-------------------------------------------------------------
	智能指针
	-------------------------------------------------------------*/
	//typedef shared_ptr<int> pint;
	//typedef shared_ptr<string> pstr;

	//int y = 0xABABABAB;
	//string str = "sisi";

	//pint p1 = make_shared<int>(y);
	//pstr p2 = make_shared<string>(str);

	//pint p3(p1);
	//pstr p4(p2);
	//pstr p5(p4);

	//

	//int x1 = p1.use_count();
	//int x2 = p5.use_count();
	//int x = p(1)(2)(3);
	/*-----------------------------------------------------
	阻止拷贝与复制
	-----------------------------------------------------*/
	//Del d1(5,"si");
	//Del d2(9, "AlMH");
	//Del d3(d2);
	//d2 = d3;

	//Del d(1);
	//d(0);
	//Del dd(2);
	//dd(0);
	//int x = 1;
	//[x](int &a) {a += 1;return [x, a](int &b) {b = x + a*b;};}(++x)(++x);
	/*--------------------------------------------
	右值引用
	--------------------------------------------*/
	//int i = 0;
	//int &  r = i;
	//int && rr = i;//左值
	//int &  r2 = 9;//右值
	//int && rr2 = 9;
	/*vector<char> a = { 'd','a','b','a','c','d','i','e','f','s','g','h','u','i','j','k','k','l','i','m','n' };
	for (int k = 0; k < 50; ++k)
	{
	for (int i = 0; i < a.size(); ++i)
	{
	cout << char((a[i] + k - 'a') % 26 + 'a');
	}
	cout << endl;
	}*/
	const regex pat("host: ([\\S ]+)\r\n");
	match_results<string::const_iterator> result;

//	while (true)
	char test[5000] = {'0',':','\r','\n',
		'h','o','s','t',':',' ', 'w','w','w','.','b','a','i','d','u','.','c','o','m',':','4','3','3','\r','\n',
		'2','2','a','b',':','.','\r','\n' };
	string str = test;
	std::regex_search(str, result, pat);
	if (result.size()) {
		cout << result[1] << endl;
		//for (auto i = 0; i <result.size(); ++i){
		//	cout << result[i] << endl;
		//}
	}
	return 0;
}