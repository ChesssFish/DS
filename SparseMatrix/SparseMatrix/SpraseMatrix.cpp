#include<iostream>
#include<fstream>
#include"valid.h"
class SPMatrix;
class Triple
{
public:
	Triple(int xi = 0, int xj = 0, int xv = 0) :i(xi), j(xj), val(xv) {};
	Triple& operator=(const Triple& t);
	bool operator<(const Triple& t);
	bool operator==(const Triple& t);
	bool operator>(const Triple& t);
	Triple reverse();
private:
	int i, j;
	int val;
	friend class SPMatrix;
};
class SPMatrix
{
public:
	SPMatrix(int row, int col, int n);
	SPMatrix* Set(const Triple& t, const int pos);
	SPMatrix* Reverse();
private:
	int row, col, num;
	Triple* data;
};
/*-------------------------------------------------------------

-------------------------------------------------------------*/
SPMatrix::SPMatrix(int r, int c, int n)
{
	row = r;
	col = c;
	num = n;
	data = new Triple[n];
};
SPMatrix* SPMatrix::Set(const Triple& t, const int pos)
{
	data[pos] = t;
	return this;
}
SPMatrix* SPMatrix::Reverse()
{
	int* seg = new int[col];
	memset(seg, 0, col*sizeof(int));
	int* offset = new int[col];
	memset(seg, 0, col*sizeof(int));
	Triple* newData = new Triple[num];
	offset[0] = 0;
	for (int i = 0; i < num; i++)
	{
		seg[data[i].j]++;
	}
	for (int i = 1; i < col; i++)
	{
		offset[i] = offset[i - 1] + seg[i - 1];
	}
	memset(seg, 0, col*sizeof(int));
	for (int i = 0; i < num; i++)
	{
		newData[offset[data[i].j] + seg[data[i].j]] = data[i].reverse();
		++seg[data[i].j];
	}
	delete[]seg;
	delete[]offset;
	delete[]data;
	data = newData;
	col = col + row;
	row = col - row;
	col = col - row;
	return this;
}
/*-----------------------------------------------------------

-----------------------------------------------------------*/
Triple& Triple::operator=(const Triple& t)
{
	i = t.i;
	j = t.j;
	val = t.val;
	return *this;
}
bool Triple::operator<(const Triple& t)
{
	if (i < t.i)
	{
		return true;
	}
	else if (i == t.i && j < t.j)
	{
		return true;
	}
	return false;
}
bool Triple::operator==(const Triple& t)
{
	if (i == t.i && j == t.j)
	{
		return true;
	}
	return false;
}
bool Triple::operator>(const Triple& t)
{
	if (i > t.i)
	{
		return true;
	}
	else if (i == t.i && j > t.j)
	{
		return true;
	}
	return false;
}
Triple Triple::reverse()
{
	Triple tmp(j, i, val);
	return tmp;
}
/*-----------------------------------------------------------

-----------------------------------------------------------*/
SPMatrix* matrix;
std::ifstream is;
int main()
{
	int row = 0, col = 0, num = 0;
#ifdef CONSOLE
	cout << "请输入矩阵行数" << endl;
	input(row, 1);
	cout << "请输入矩阵列数" << endl;
	input(col, 1);
	cout << "请输入非零元素个数" << endl;
	input(num, 1);
#else
	is.open("data.txt");
	is >> row >> col >> num;
#endif
	matrix = new SPMatrix(row, col, num);

	int i = 0, j = 0, v = 0;
#ifdef CONSOLE
	cout << "请输入非零元素所在行、列以及值" << endl;
#endif
	for (int k = 0; k < num; k++)
	{
#ifdef CONSOLE
		cin >> i >> j >> v;
		while (i < 0 || j < 0 || v == 0 || cin.fail())
		{
			error("输入有误，请重新输入");
			FLUSH_BUFFER;
			cin.clear();
			cin >> i >> j >> v;
		}
#else
		is >> i >> j >> v;
#endif
		Triple tmp(i,j,v);
		matrix->Set(tmp, k);
	}
#ifndef CONSOLE
	is.close();
#endif
	matrix->Reverse();
	return 0;
}