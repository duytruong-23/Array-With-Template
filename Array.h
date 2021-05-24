#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>

using namespace std;

template<class type>
class Array
{
private:
	type* item;
	int size;
	int num;
public:
	Array(int n, int Inc = 0);
	bool fail();
	bool erase(int pos);
	bool erase(int start, int end);
	type* binSearch(type X, int start = 0, int end = num - 1);
	type* insert(type X, int pos);
	bool resize(int Inc);
	~Array();
};

template<class type>
Array<type>::Array(int n, int Inc)
{
	if (n <= 0 || Inc < 0) { return; }
	for (int i = n + Inc; i >= n; i--)
	{
		item = new (nothrow) type[i];
		if (!fail())
		{
			size = i;
			num = n;
			return;
		}
	}
}

template<class type>
bool Array<type>::fail()
{
	if (item == nullptr) { return true; }
	return false;
}

template<class type>
Array<type>::~Array()
{
	if (fail()) { return; }
	delete[] item;
	item = nullptr;
	num = 0;
	size = 0;
}

template<class type>
bool Array<type>::erase(int pos)
{
	if (pos < 0) { return false; }
	for (int i = pos; i < num - 2; i++)
	{
		item[i] = item[i + 1];
	}
	num--;
	return true;
}

template<class type>
bool Array<type>::erase(int start, int end)
{
	if (start < 0 || end < 0 || end >= num || end < start) { return false; }
	int n = end - start + 1;
	for (int i = start; i < num - n; i++)
	{
		item[i] = item[i + n];
	}
	num -= n;
	return true;
}

template<class type>
type* Array<type>::binSearch(type X, int start, int end)
{
	if (start < 0 || end < 0 || end >= num || end < start) { return nullptr; }
	int left = start;
	int right = end;
	int mid = 0;
	type* p = nullptr;
	while (right >= left)
	{
		mid = (start + end) / 2;
		if (item[mid] == X)
		{
			p = (item + mid);
			return p;
		}
		else if (item[mid] > X)
		{
			right = mid - 1;
		}
		else
		{
			left = mid + 1;
		}
	}
	return nullptr;
}

template<class type>
bool Array<type>::resize(int Inc)
{
	int n = size + Inc;
	if (n < num) { return false; }
	type* p = realloc(p, n*sizeof(type));
	if (p != nullptr)
	{
		item = p;
		size = n;
		return true;
	}
	return false;
}

template<class type>
type* Array<type>::insert(type X, int pos)
{
	if (pos < 0 || pos > num) { return nullptr; }
	if (num >= size)
	{
		int n = num - size + 1;
		if (!resize(n)) { return nullptr; }
	}

	for (int i = num - 1; i > pos; i--)
	{
		item[i] = itme[i - 1];
	}
	item[pos] = X;
	num++;
	return (item + pos);
}

#endif