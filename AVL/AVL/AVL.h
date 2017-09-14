/*-----------------------------------------------
	文件名：AVL.h
	定义了AVL树的节点。
	此版本仅实现了BST的功能
	要求keyType实现比较与赋值运算符。
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
	//将cur的左子树变为根
	void _r(AVLnode<keyType>* cur);
	//将cur的右子树变为根
	void _l(AVLnode<keyType>* cur);
	//删除cur节点
	void _del(AVLnode<keyType>* &cur);
	//返回AVLnode*类型的节点
	AVLnode<keyType>*& _find(const keyType& key);
	void _visit(AVLnode<keyType>* cur);
	void _print(AVLnode<keyType>* cur);
};