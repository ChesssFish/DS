#pragma once
class RBT_node
{
	typedef int keyType;
	typedef bool COLOR;
	static const COLOR RED = false;
	static const COLOR BLACK = true;
	friend class rbt;
public:
	RBT_node(keyType k);
	~RBT_node();

private:
	keyType key;
	RBT_node* p = nullptr;
	RBT_node* lc = nullptr;
	RBT_node* rc = nullptr;
	COLOR color = BLACK;
};

RBT_node::RBT_node(keyType k) :
	key(k)
{
}

RBT_node::~RBT_node()
{

}

class rbt
{
public:
	rbt();
	~rbt();
	rbt* Insert(const RBT_node::keyType& k);
	rbt* Delete(const RBT_node::keyType& k);
	RBT_node* Search(const RBT_node::keyType& k);
private:
	static RBT_node* nil; //哨兵
	RBT_node* root;
	void _l_rotate(RBT_node* node);
	void _r_rotate(RBT_node* node);
	void _insert_fix_up(RBT_node* x);
	void _delete_fix_up(RBT_node* x);
	void _transplant(RBT_node* u, RBT_node* v);//用节点v替换节点u
	RBT_node* _find_min(RBT_node* u);//寻找节点u为根的树中的最小元素
};

rbt::rbt() :
	root(nil)
{

}

rbt::~rbt()
{
	nil = nullptr;
	delete root;
}
RBT_node* rbt::nil = new RBT_node(-1);

RBT_node* rbt::Search(const RBT_node::keyType& k)
{
	RBT_node* cur = root;
	while (cur != nil)
	{
		if (k == cur->key)
		{
			return cur;
		}
		else if (k < cur->key)
		{
			cur = cur->lc;
		}
		else
		{
			cur = cur->rc;
		}
	}
	return nil;
}

rbt* rbt::Insert(const RBT_node::keyType& k)
{
	RBT_node* newNode = new RBT_node(k);
	RBT_node* pre = nil;
	RBT_node* cur = root;
	while (cur != nil)
	{
		pre = cur;
		if (newNode->key < cur->key)
		{
			cur = cur->lc;
		}
		else
		{
			cur = cur->rc;
		}
	}
	newNode->p = pre;
	if (pre == nil)
	{
		root = newNode;
	}
	else if (newNode->key < pre->key)
	{
		pre->lc = newNode;
	}
	else
	{
		pre->rc = newNode;
	}
	newNode->lc = nil;
	newNode->rc = nil;
	newNode->color = RBT_node::RED;
	_insert_fix_up(newNode);
	return this;
}

void rbt::_l_rotate(RBT_node* x)
{
	RBT_node* r = x->rc;
	x->rc = r->lc;
	if (r->lc != nil)
	{
		r->lc->p = x;
	}
	r->p = x->p;
	if (x->p == nil)
	{
		root = r;
	}
	else if (x == x->p->lc)
	{
		x->p->lc = r;
	}
	else
	{
		x->p->rc = r;
	}
	r->lc = x;
	x->p = r;
}

void rbt::_r_rotate(RBT_node* x)
{
	RBT_node* l = x->lc;
	x->lc = l->rc;
	if (l->rc != nil)
	{
		l->rc->p = x;
	}
	l->p = x->p;
	if (x->p == nil)
	{
		root = l;
	}
	else if (x == x->p->lc)
	{
		x->p->lc = l;
	}
	else
	{
		x->p->rc = l;
	}
	l->rc = x;
	x->p = l;
}

void rbt::_insert_fix_up(RBT_node* x)
{
	RBT_node* uncle;
	while (x->p->color == RBT_node::RED)
	{
		if (x->p == x->p->p->lc)
		{
			uncle = x->p->p->rc;
			if (uncle->color == RBT_node::RED)
			{
				x->p->color = RBT_node::BLACK;
				uncle->color = RBT_node::BLACK;
				x->p->p->color = RBT_node::RED;
				x = x->p->p;
			}
			else
			{
				if (x == x->p->rc)
				{
					x = x->p;
					_l_rotate(x);
				}
				x->p->color = RBT_node::BLACK;
				x->p->p->color = RBT_node::RED;
				_r_rotate(x->p->p);
			}
		}
		else
		{
			uncle = x->p->p->lc;
			if (uncle->color == RBT_node::RED)
			{
				x->p->color = RBT_node::BLACK;
				uncle->color = RBT_node::BLACK;
				x->p->p->color = RBT_node::RED;
				x = x->p->p;
			}
			else
			{
				if (x == x->p->lc)
				{
					x = x->p;
					_r_rotate(x);
				}
				x->p->color = RBT_node::BLACK;
				x->p->p->color = RBT_node::RED;
				_l_rotate(x->p->p);
			}
		}
	}
	root->color = RBT_node::BLACK;
}

rbt* rbt::Delete(const RBT_node::keyType& k)
{
	RBT_node* x = Search(k);//要删除的节点
	if (x == nil)
	{
		return this;
	}
	RBT_node* y = x;//用来代替x的节点
	RBT_node* black_plus;//继承y节点黑色属性的节点
	RBT_node::COLOR y_original_color = x->color;

	if (x->lc == nil)
	{
		black_plus = x->rc;
		_transplant(x, x->rc);
	}
	else if (x->rc == nil)
	{
		black_plus = x->lc;
		_transplant(x, x->lc);
	}
	else
	{
		y = _find_min(x->rc);
		y_original_color = y->color;
		black_plus = y->rc;
		if (y->p == x)
		{
			black_plus->p = y;
		}
		else
		{
			_transplant(y, y->rc);
			y->rc = x->rc;
			x->rc->p = y;
		}
		_transplant(x, y);
		y->lc = x->lc;
		x->lc->p = y;
		y->color = x->color;//将x替代节点的颜色置为x的颜色，
							//这么做的结果是就关键字而言删除了x,
							//而就颜色而言删除了y
	}
	if (y_original_color == RBT_node::BLACK)
	{
		_delete_fix_up(black_plus);
	}
	delete x;
	return this;
}
void rbt::_transplant(RBT_node* u, RBT_node* v)
{
	if (u->p == nil)
	{
		root = v;
	}
	else if (u == u->p->lc)
	{
		u->p->lc = v;
	}
	else
	{
		u->p->rc = v;
	}
	v->p = u->p;
}

RBT_node* rbt::_find_min(RBT_node* x)
{
	while (x->lc != nil)
	{
		x = x->lc;
	}
	return x;
}

void rbt::_delete_fix_up(RBT_node* x)
{
	RBT_node* brother;
	while (x != root && x->color == RBT_node::BLACK)
	{
		if (x == x->p->lc)
		{
			brother = x->p->rc;
			if (brother->color == RBT_node::RED)
			{
				//case 1:将x的兄弟变为 brother->lc,转化为case 2,3,4
				brother->color = RBT_node::BLACK;
				x->p->color = RBT_node::RED;
				_l_rotate(x->p);
				brother = x->p->rc;
			}
			if(brother->lc->color == RBT_node::BLACK
			   && brother->rc->color == RBT_node::BLACK)
			{
				//case 2:黑色上浮一层
				brother->color = RBT_node::RED;
				x = x->p;
				continue;
			}
			else if(brother->rc->color == RBT_node::BLACK)
			{
				//case 3:被转化为case 4
				brother->lc->color = RBT_node::BLACK;
				brother->color = RBT_node::RED;
				_r_rotate(brother);
				brother = x->p->rc;
			}
			//case 4:
			brother->color = x->p->color;
			x->p->color = RBT_node::BLACK;
			brother->rc->color = RBT_node::BLACK;
			_l_rotate(x->p);
			x = root;//结束循环;
		}
		else
		{
			brother = x->p->lc;
			if (brother->color == RBT_node::RED)
			{
				brother->color = RBT_node::BLACK;
				x->p->color = RBT_node::RED;
				_r_rotate(x->p);
				brother = x->p->lc;
			}

			if (brother->lc->color == RBT_node::BLACK
				&& brother->rc->color == RBT_node::BLACK)
			{
				brother->color = RBT_node::RED;
				x = x->p;
				continue;
			}
			else if (brother->lc->color == RBT_node::BLACK)
			{
				brother->color = RBT_node::RED;
				brother->rc->color = RBT_node::BLACK;
				_l_rotate(brother);
				brother = x->p->lc;
			}
			brother->color = x->p->color;
			x->p->color = RBT_node::BLACK;
			brother->lc->color = RBT_node::BLACK;
			_r_rotate(x->p);
			x = root;
		}
	}
	x->color = RBT_node::BLACK;
}