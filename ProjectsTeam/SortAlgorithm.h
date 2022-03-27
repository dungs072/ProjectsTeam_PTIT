#pragma once
#include<iostream>
#include<functional>
template<class T>
class SortAlgorithm
{
public:
	SortAlgorithm(){}
	void Swap(T* t1, T* t2)
	{
		T temp = *t1;
		*t1 = *t2;
		*t2 = temp;
	}
	int partition(T** arr,int l, int h)
	{
		T* pivot = arr[l];
		int i = l;
		int j = h;
		do
		{
			do { i++; if (i == j) { break; } } while (Compare(arr[i], pivot) < 1);
			do { j--; } while (Compare(arr[j], pivot) == 1);
			if (i < j) { Swap(arr[i], arr[j]); }
		} while (i < j);
		Swap(arr[l], arr[j]);
		return j;
	}
	void QuickSort(T**arr,int l, int h)
	{
		int j = 0;
		if (l < h)
		{
			j = partition(arr,l, h);
			QuickSort(arr,l, j);
			QuickSort(arr,j + 1, h);
		}
	}
	std::function<int(T*, T*)>Compare = 0;
};

