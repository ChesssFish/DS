#pragma once
#include<vector>
#include<string>
#include<fstream>
using namespace std;
class Node
{
public:
	Node() {};
private:
	int data;
	vector<Node*> next;
	friend class Btree2Forest;
};

class Btree2Forest
{
public:
	Btree2Forest() :state(Btree), _pre(NULL) { roots.push_back(NULL); }
	//���ܣ���������ת��Ϊɭ�ֵĽӿ����
	//����λ��: main
	void ToForest(void);
	//���ܣ���ɭ��ת��Ϊ�������Ľӿ����
	//����λ��: main
	void ToBtree(void);
	//���ܣ������������Ľӿ����
	//����λ��: main
	void BuildBtree(string file);
private:
	enum S
	{
		Btree,
		Forest
	};
	S state;
	vector<Node*> roots;
	Node* _pre;
	//���ܣ���������ת��Ϊ������
	//����1�������ڵ�
	//����λ�ã�ToBtree
	void _tobtree(Node* cur);

	//���ܣ���cur�ڵ�ת��Ϊһ���������ڵ�
	//����1����ת���Ľڵ�
	//����λ�ã�_tobtree
	void _delete(Node* cur);

	//���ܣ������ö�����ת��Ϊ��
	//����1�������ڵ�
	//����λ�ã�ToForest
	void _totree(Node* cur);

	//����:������ת��Ϊ�������У�
	//     �����ӵ��ҡ����ҡ�������...����������cur
	//����: �����ӵĽڵ�
	//����λ��: _totree
	void _link(Node* cur);

	//����:����ǰ���������н���������
	//����1:���ڵ�
	//����2:������ʼλ��
	//����3:��������λ�ã�����ĩ�ڵ㣩
	//����λ��: BuildTree
	void _buildtree(Node*& cur, int start, int end);

	//����: Ѱ��ǰ��������ĳ�ڵ������������е�λ��
	//����1: ǰ�������нڵ��λ��
	//����2: ��ҪѰ�ҵ���ʼλ��
	//����3: ��ҪѰ�ҵĽ���λ��
	//����λ��: _buildtree
	int _findkey(int cnt, int start, int end);
};