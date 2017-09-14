/*---------------------------------------
	�ļ�����huffman.cpp
	�����ı��ļ��ľ�̬����������
---------------------------------------*/
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#define MAXN 2000
using namespace std;
ifstream is;
ofstream os;
map<char, int>c;//���ַ�ӳ�䵽���������ڴ���
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
int code_len;//�����ܳ���
void init();
//��ȡ���ݣ������ļ����ַ�����
int read_data(string filename);
//����huffman��
void create_huffman(int len);
void selectMin(huf_node* huf_tree, int len, int& p1, int& p2);
//��ȡÿ���ַ��ı��룬���ַ�����ʽ����
void get_encoding(int len);
//���ļ����룬��������Ķ������ļ�
void encode(string filename);
//�Ա����Ķ������ļ����룬����ı��ļ�
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
	cout << "��ȡ����..." + filename << endl;
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
	cout << "������������..." << endl;
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
	cout << "������ַ��ı���..." << endl;
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
	cout << "����...";
	is.open(filename);
	os.open(filename+"en",ios::binary);
	char chr;
	int buf = 0;
	int ilen;//���ÿ������ĳ���
	int count = 0;//����λ�����������
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
	cout << "�����ļ�" << filename + "en" << endl;
}
void decode(int len, string filename)
{
	cout << "����...";
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
		if (cur.lchild == -1)//cur��Ҷ�ڵ�
		{
			os << cur.chr;
			cur = huf_tree[2 * len - 2];
		}
	}
	cout << "�����ļ�" << "de_" + filename << endl << "���" << endl;
	return;
}