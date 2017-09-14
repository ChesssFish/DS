#ifndef CHASE_APPLICATION_PRIORITY_QUEUE_H
#define CHASE_APPLICATION_PRIORITY_QUEUE_H
#include<vector>
#include<map>
template <class T>
class PriorityQueue
{
public:
	PriorityQueue();
	void Push(T item);
	T Pop();
	void DecreaseKey(T item);
	bool IsEmpty();
private:
	std::vector<T> heap;
	std::map<T, int> pos;
	void _PushUpdate(int p);
	int _MinChild(int p);
	int _Parent(int p);
	void _PopUpdate();
};
template<class T>
inline PriorityQueue<T>::PriorityQueue()
{
}

template<class T>
void PriorityQueue<T>::Push(T item)
{
	heap.push_back(item);
	pos[item] = heap.size() - 1;
	_PushUpdate(heap.size() - 1);
}

template<class T>
T PriorityQueue<T>::Pop()
{
	T tmp = heap[0];
	heap[0] = heap[heap.size() - 1];
	pos[heap[heap.size() - 1]] = 0;
	heap.pop_back();
	_PopUpdate();
	return tmp;
}

template<class T>
void PriorityQueue<T>::DecreaseKey(T item)
{
	heap[pos[item]] = item;
	_PushUpdate(pos[item]);
}

template<class T>
inline bool PriorityQueue<T>::IsEmpty()
{
	return heap.size() == 0;
}

template<class T>
void PriorityQueue<T>::_PushUpdate(int p)
{
	int ppar = _Parent(p);
	while (heap[ppar] > heap[p])
	{
		std::swap(heap[p] ,heap[(p - 1) >> 1]);
		std::swap(pos[heap[p]],pos[heap[(p - 1) >> 1]]);
		p = ppar;
		ppar = _Parent(p);
	}
}

template<class T>
int PriorityQueue<T>::_MinChild(int p)
{
	int pmin = p;
	if ((p << 1) + 1 < heap.size())
	{
		pmin = heap[p] > heap[(p << 1) + 1] ? (p << 1) + 1 : p;
		if ((p << 1) + 2 < heap.size())
			pmin = heap[(p << 1) + 2] > heap[pmin] ? pmin : (p << 1) + 2;
	}
	return pmin;
}

template<class T>
inline int PriorityQueue<T>::_Parent(int p)
{
	return (p - 1) >> 1 >= 0 ? (p - 1) >> 1 : p;
}

template<class T>
void PriorityQueue<T> ::_PopUpdate()
{
	int p = 0;
	int pmin = _MinChild(p);
	while (pmin != p)
	{
		std::swap(heap[p], heap[pmin]);
		std::swap(pos[heap[p]], pos[heap[pmin]]);
		p = pmin;
		pmin = _MinChild(p);
	}
}
#endif