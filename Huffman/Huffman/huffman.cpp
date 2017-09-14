/*---------------------------------------
	文件名：huffman.cpp
	用于文本文件的静态哈夫曼编码
---------------------------------------*/
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#define MAXN 2000
using namespace std;
ifstream is;
ofstream os;
map<char, int>c;//将字符映射到整数，便于处理
string* encoding;
class huf_node
{
public:
	huf_node();
	char chr;
	int weight;
	int parent;
	int lchild;
	int rchild;
	bool operator==(huf_node& n) 
	{ 
		return (
			chr == n.chr
		&& weight == n.weight
		&& parent == n.parent 
		&& lchild == n.lchild 
		&& rchild == n.rchild); 
	}
};
huf_node::huf_node()
{
	chr = 0;
	weight = 0;
	parent = -1;
	lchild = -1;
	rchild = -1;
}
huf_node* huf_tree;
int code_len;//编码总长度
void init();
//读取数据，返回文件中字符个数
int read_data(string filename);
//建立huffman树
void create_huffman(int len);
void selectMin(huf_node* huf_tree, int len, int& p1, int& p2);
//获取每个字符的编码，以字符串形式保存
void get_encoding(int len);
//对文件编码，输出编码后的二进制文件
void encode(string filename);
//对编码后的二进制文件解码，输出文本文件
void decode(int len, string filename);
int main(int argc, char** argv)
{
	int n = 0;
	init();
	n = read_data(argv[1]);
	create_huffman(n);
	get_encoding(n);
	encode(argv[1]);
	decode(n, argv[1]);
	return 0;
}
void init()
{
	huf_tree = new huf_node[MAXN * 2 - 1];
	code_len = 0;
}
int read_data(string filename)
{
	cout << "读取数据..." + filename << endl;
	is.open(filename);
	char chr;
	int n = 0;
	while (true)
	{
		chr = is.get();
		if (is.fail())
		{
			break;
		}
		if (c.find(chr) == c.end())
		{
			c[chr] = n++;
		}
		huf_tree[c[chr]].chr = chr;
		huf_tree[c[chr]].weight++;
	}
	is.close();
	return n;
}
void selectMin(huf_node* huf_tree, int len, int& p1, int& p2)
{
	int m1 = numeric_limits<int>::max();
	int m2 = numeric_limits<int>::max();
	for (int i = 0; i < len; i++)
	{
		if (m1 <= m2 )
		{
			if (huf_tree[i].weight < m2 && huf_tree[i].parent == -1)
			{
				m2 = huf_tree[i].weight;
				p2 = i;
			}
		}
		else 
		{
			if (huf_tree[i].weight < m1 && huf_tree[i].parent == -1)
			{
				m1 = huf_tree[i].weight;
				p1 = i;
			}
		}
	}
}
void create_huffman(int len)
{
	cout << "建立哈夫曼树..." << endl;
	int p1, p2;
	int maxlen = len * 2 - 1;
	for (int i = len; i < maxlen;i++)
	{
		selectMin(huf_tree, i, p1, p2);
		huf_tree[p1].parent = i;
		huf_tree[p2].parent = i;
		huf_tree[i].lchild = p1;
		huf_tree[i].rchild = p2;
		huf_tree[i].weight = huf_tree[p1].weight + huf_tree[p2].weight;
	}
}
void get_encoding(int len)
{
	cout << "计算各字符的编码..." << endl;
	encoding = new string[len];
	huf_node cur;
	int ilen;
	for (int i = 0; i < len; i++)
	{
		ilen = 0;
		cur = huf_tree[i];
		while (cur.parent != -1)
		{
			if (huf_tree[huf_tree[cur.parent].lchild] == cur)
			{
				encoding[i] += '0';
			}
			else
			{
				encoding[i] += '1';
			}
			cur = huf_tree[cur.parent];
		}
		for (int k = 0, j = encoding[i].length() - 1;k < j;k++, j--)
		{
			swap(encoding[i][k], encoding[i][j]);
		}
	}
}
void encode(string filename)
{
	cout << "编码...";
	is.open(filename);
	os.open(filename+"en",ios::binary);
	char chr;
	int buf = 0;
	int ilen;//存放每个编码的长度
	int count = 0;//计算位数，便于输出
	while (true)
	{
		chr = is.get();
		if (is.fail())
		{
			break;
		}
		ilen = encoding[c[chr]].length();
		code_len += ilen;
		for (int i = 0;i < ilen; i++)
		{
			count++;
			if (encoding[c[chr]][i] == '0')
			{
				buf = (buf << 1) & 0xFFFFFFFE;
			}
			else
			{
				buf = (buf << 1) | 1;
			}
			if (count % (8*sizeof(buf)) == 0)
				os.write((char*)&buf, sizeof(buf));
		}
	}
	buf = buf << ((8 * sizeof(buf)) - (count % (8 * sizeof(buf))));
	os.write((char*)&buf, sizeof(buf));
	is.close();
	os.close();
	cout << "存入文件" << filename + "en" << endl;
}
void decode(int len, string filename)
{
	cout << "解码...";
	is.open(filename+"en", ios::binary);
	os.open("de_" + filename);
	int buf;
	int count = 0;
	huf_node cur = huf_tree[2 * len - 2];
	while (true)
	{
		if (count % (8 * sizeof(buf)) == 0)
		{
			is.read((char*)&buf, sizeof(buf));
			if (is.fail())
			{
				break;
			}
		}
		if ((buf & 0x80000000) == 0)
		{
			cur = huf_tree[cur.lchild];
		}
		else
		{
			cur = huf_tree[cur.rchild];
		}
		buf = buf << 1;
		count++;
		if (count > code_len)break;
		if (cur.lchild == -1)//cur是叶节点
		{
			os << cur.chr;
			cur = huf_tree[2 * len - 2];
		}
	}
	cout << "存入文件" << "de_" + filename << endl << "完成" << endl;
	return;
}