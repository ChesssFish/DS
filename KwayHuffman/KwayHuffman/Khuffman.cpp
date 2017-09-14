#include<iostream>
#include<fstream>
#include<vector>
#include<queue>
#include<string>
#include<map>
using namespace std;
class Node
{
public:
	Node(char v = 0, int f = 0) :val(v), fqc(f), isData(true) {};
	bool operator<(const Node& node) const;
	bool isData;
	char val;
	int fqc;
	vector<Node*> c;
};
bool Node::operator<(const Node& node) const
{
	//STL��priority_queueĬ��ʹ��С�ڣ���������
	//��С��������з��ش����߼�����Ĭ�ϲ�������¹���С����
	return fqc > node.fqc;
}
priority_queue<Node> p;
map<char, int> f;
// ����λ��: main
// ���ܣ���ָ�����ļ��ж�ȡ����
// ����1���ļ�·��
// ����ֵ������ͬ���ַ��� 
int ReadData(string file);

// ����λ��: main
// ����: �������ݽ���С����
void BuildHeap(void);

// ����λ��: main
// ����: �����е����ݺϲ���k���������
// ����1: �ַ����� n
// ����2: ������ k
// ����: k���������
Node* BuildHuffmanTree(int n, int k);

// ����λ��: BuildHuffmanTree
// ����: ����Nodeʵ����ָ��
// ����: Node���͵�ʵ��
// ����: Node���͵�ָ��
Node* MakePointer(const Node& n);

int main()
{
	int n, k;
	n = ReadData("in.txt");
	BuildHeap();
	cin >> k;
	Node* Huffman = BuildHuffmanTree(n, k);

	return 0;
}

int ReadData(string file)
{
	ifstream is;
	is.open(file);
	int n = 0;
	char chr;
	while (true)
	{
		is >> chr;
		if (f[chr] == 0)
		{
			n++;
		}
		if (is.good())
		{
			f[chr] ++;
		}
		else
		{
			break;
		}
	}
	return n;
}
void BuildHeap(void)
{
	map<char, int>::iterator i;
	for (i = f.begin(); i != f.end(); i++)
	{
		Node tmp((*i).first, (*i).second);
		p.push(tmp);
	}
}
Node* BuildHuffmanTree(int n, int k)
{
	int dummy_num = (n - 1) % (k - 1) == 0 ?
		0 : k - 1 - (n - 1) % (k - 1);
	Node dummy;
	dummy.isData = false;
	for (int i = 0; i < dummy_num; i++)
	{
		p.push(dummy);
	}
	int times = (n - 1 + dummy_num) / (k - 1);
	for (int t = 0; t < times; t++)
	{
		Node newNode;
		newNode.isData = false;
		for (int i = 0; i < k; i++)
		{
			newNode.fqc += p.top().fqc;
			newNode.c.push_back(MakePointer(p.top()));
			p.pop();
		}
		p.push(newNode);
	}
	return MakePointer(p.top());
}
Node* MakePointer(const Node& n)
{
	Node* newNode = new Node();
	newNode->isData = n.isData;
	newNode->fqc = n.fqc;
	newNode->val = n.val;
	newNode->c = n.c;
	return newNode;
}