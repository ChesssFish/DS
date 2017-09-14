#include"Priorityqueue.h"
template<class ProtoData>
unsigned Pqueue<ProtoData>::Data::next_order = 0;
class node
{
public:
	node() {};
	node(int v, int p) { val = v; priority = p; }
	int val;
	int priority;
	bool operator<(const node& n);
	bool operator>(const node& n);
	bool operator==(const node& n);
};
bool node::operator<(const node& n)
{
	if (priority > n.priority)
		return false;
	else if (priority == n.priority && val >= n.val)
		return false;
	return true;
}
bool node::operator>(const node& n)
{
	if (priority < n.priority)
		return false;
	else if (priority == n.priority && val <= n.val)
		return false;
	return true;
}
bool node::operator==(const node& n)
{
	if (priority == n.priority &&
		val == n.val)
		return true;
	return false;
}
int main()
{
	Pqueue<node>* a;
	a = new Pqueue<node>();
	node n1(1, 0), n2(10, 3), n3(80, 2);
	a->Push(n1);
	a->Push(n3);
	a->Push(n2);
	node result = a->Pop();
	return 0;
}
