/*-----------------------------------------------
	�ļ�����AVL.h
	������AVL���Ľڵ㡣
	�˰汾��ʵ����BST�Ĺ���
	Ҫ��keyTypeʵ�ֱȽ��븳ֵ�������
-----------------------------------------------*/

#pragma once
template<typename keyType = int>class AVL;
template<typename keyType = int>
class AVLnode
{
public:
	AVLnode();
	AVLnode(const keyType& key);
	~AVLnode();
	AVLnode& operator=(AVLnode& node);
	bool operator==(AVLnode& node);
	bool operator<(AVLnode& node);
	bool operator>(AVLnode& node);
	bool operator<=(AVLnode& node);
private:
	int mHeight;
	keyType mKey;
	AVLnode* pParent;
	AVLnode* pLchild;
	AVLnode* pRchild;
	void _calcHeight();
	friend class AVL<keyType>;
};
template<typename keyType>
class AVL
{
public:
	AVL();
	~AVL();
	void clear(void);
	void ins(keyType rec);
	void del(const keyType& del);
	bool find(const keyType& key);
	void getInOrder();
	keyType* mInOrder;
	int mlen;
private:
	AVLnode<keyType>* root;
	int mCount;
	//��cur����������Ϊ��
	void _r(AVLnode<keyType>* cur);
	//��cur����������Ϊ��
	void _l(AVLnode<keyType>* cur);
	//ɾ��cur�ڵ�
	void _del(AVLnode<keyType>* &cur);
	//����AVLnode*���͵Ľڵ�
	AVLnode<keyType>*& _find(const keyType& key);
	void _visit(AVLnode<keyType>* cur);
	void _print(AVLnode<keyType>* cur);
};