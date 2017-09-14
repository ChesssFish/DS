#pragma once
#include<vector>
using std::vector;
template<class ProtoData>
class Pqueue
{
public:
	Pqueue();
//	~Pqueue();
	Pqueue* Push(ProtoData d);
	ProtoData Pop();
private:
	class Data
	{
	public:
		Data() {}
		Data(const ProtoData& d);
		bool operator<(const Data& d);
		bool operator>(const Data& d);
		Data& operator=(const Data& d);
		ProtoData data;
		unsigned order;
		static unsigned next_order;
	};
	vector<Data> q;
	void update(int pos);
	void swap(Data& a, Data& b);
};

/*-----------------------------------------------
				Pqueue::Data实现
-----------------------------------------------*/
template<class ProtoData>
Pqueue<ProtoData>::Data::Data(const ProtoData& d)
{
	data = d;
	order = Data::next_order++;
}
/*

*/
template<class ProtoData>
bool Pqueue<ProtoData>::Data::operator<(const Data& d)
{
	if (data > d.data)
		return false;
	else if (data == d.data && order >= d.order)
		return false;
	return true;
}

template<class ProtoData>
bool Pqueue<ProtoData>::Data::operator>(const Data& d)
{
	if (data < d.data)
		return false;
	else if (data == d.data && order <= d.order)
		return false;
	return true;
}

template<class ProtoData>
typename Pqueue<ProtoData>::Data& Pqueue<ProtoData>::Data::operator=(const Data& d)
{
	data = d.data;
	order = d.order;
	return *this;
}
/*----------------------------------------------
				Pqueue实现
----------------------------------------------*/

template<class ProtoData>
Pqueue<ProtoData>::Pqueue()
{
	;
}
/*template<class ProtoData>
Pqueue<Data>::~Pqueue()
{
}*/
template<class ProtoData>
Pqueue<ProtoData>* Pqueue<ProtoData>::Push(ProtoData d)
{
	q.push_back(d);
	update(q.size() - 1);
	return this;
}
template<class ProtoData>
ProtoData Pqueue<ProtoData>::Pop()
{
	int last = q.size() - 1;
	ProtoData ret = q[0].data;
	q[0] = q[last];
	q.pop_back();
	update(0);
	return ret;
}
template<class ProtoData>
void Pqueue<ProtoData>::update(int pos)
{
	int end = q.size();
	int swappos;
	if (pos == 0)
	{
		while (pos < end)
		{
			swappos = pos;
			if (pos * 2 + 1 < end)
			{
				swappos = pos * 2 + 1;
			}
			if (pos * 2 + 2 < end)
			{
				swappos =  q[pos * 2 + 1] < q[pos * 2 + 2] ? 
					pos * 2 + 1 : pos * 2 + 2;
			}
			if (q[pos] > q[swappos])
			{
				swap(q[pos], q[swappos]);
				pos = swappos;
			}
			else
				break;
		}
	}
	else
	{
		while (pos != 0)
		{
			if (q[pos] < q[(pos - 1) / 2])
			{
				swap(q[pos], q[(pos - 1) / 2]);
				pos = (pos - 1) / 2;
			}
			else break;
		}
	}
}
template<class ProtoData>
void Pqueue<ProtoData>::swap(Data& a, Data& b)
{
	Data tmp;
	tmp = a;
	a = b;
	b = tmp;
}