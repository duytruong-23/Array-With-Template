#ifndef ARRAY_H
#define ARRAY_H

template<class type>
class Array
{
private:
	type* Items;
	int Size;
	int Num;
public:
	Array(const int & n, const int & Inc = 0);
	Array();
	bool fail();
	bool erase(const int& pos);
	bool erase(const int& start, const int& end);
	type* binSearch(const type& X, const int& start = 0, const int& end = Num-1);
	type* insert(const type& X, const int& pos);
	bool resize(const int& Inc);
	type& operator[] (const int& i);
	~Array();
};

template<class type>
Array<type>::Array(const int & n, const int & Inc)
{
	if (n <= 0 || Inc < 0) { return; }
	for (int i = n + Inc; i >= n; i--)
	{
		Items = new (std::nothrow) type[i];
		if (!fail())
		{
			Size = i;
			Num = n;
			return;
		}
	}
}

template<class type>
inline Array<type>::Array()
	: Items(nullptr), Size(0), Num(0)
{
}

template<class type>
bool Array<type>::fail()
{
	if (Items == nullptr) { return true; }
	return false;
}

template<class type>
Array<type>::~Array()
{
	if (fail()) { return; }
	delete[] Items;
	Items = nullptr;
	Num = 0;
	Size = 0;
}

template<class type>
bool Array<type>::erase(const int& pos)
{
	if (pos < 0) { return false; }
	for (int i = pos; i < Num - 2; i++)
	{
		Items[i] = Items[i + 1];
	}
	Num--;
	return true;
}

template<class type>
bool Array<type>::erase(const int& start, const int& end)
{
	if (start < 0 || end < 0 || end >= Num || end < start) { return false; }
	int n = end - start + 1;
	for (int i = start; i < Num - n; i++)
	{
		Items[i] = Items[i + n];
	}
	Num -= n;
	return true;
}

template<class type>
type* Array<type>::binSearch(const type& X, const int& start, const int& end)
{
	if (start < 0 || end < 0 || end >= Num || end < start) { return nullptr; }
	int left = start;
	int right = end;
	int mid = 0;
	type* p = nullptr;
	while (right >= left)
	{
		mid = (start + end) / 2;
		if (Items[mid] == X)
		{
			p = (Items + mid);
			return p;
		}
		else if (Items[mid] > X)
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
bool Array<type>::resize(const int& Inc)
{
	int n = Size + Inc;
	if (n < Num) { return false; }
	type* p = realloc(p, n*sizeof(type));
	if (p != nullptr)
	{
		Items = p;
		Num = (Num > 0) ? Size : n;
		Size = n;
		return true;
	}
	return false;
}

template<class type>
type& Array<type>::operator[](const int& i)
{
	return *(Items + i);
}

template<class type>
type* Array<type>::insert(const type& X, const int& pos)
{
	if (pos < 0 || pos > Num) { return nullptr; }
	if (Num >= Size)
	{
		int n = Num - Size + 1;
		if (!resize(n)) { return nullptr; }
	}

	for (int i = Num - 1; i > pos; i--)
	{
		Items[i] = Items[i - 1];
	}
	Items[pos] = X;
	Num++;
	return (Items + pos);
}

#endif