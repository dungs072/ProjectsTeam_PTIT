#pragma once
#include<iostream>
namespace DataStructure
{
	template<class T>
	class LinearList
	{
	private:
		int currentPointer;
		int maxLength;
		T** list;
	public:
		LinearList(int maxLength)
		{
			list = new T * [maxLength];
			currentPointer = 0;
		}
		LinearList()
		{
			maxLength = 100;
			currentPointer = 0;
			list = new T * [maxLength];
		}
		~LinearList()
		{
			Clear();
		}
		int Length()
		{
			return currentPointer;
		}
		void AddLast(T* data)
		{
			if (IsFull()) { return; }
			list[currentPointer++] = data;
		}
		void Delete(T* data)
		{
			int pos = 0;
			if (!HasInList(data, pos)) { return; }
			delete data;
			data = nullptr;
			if (pos == -1) { return; }
			for (int i = pos; i < currentPointer; i++)
			{
				list[i] = list[i + 1];
			}
			currentPointer--;
		}
		void Delete(int pos)
		{
			if (pos<0 || pos>currentPointer) { return; }
			delete list[pos];
			list[pos] = nullptr;
			for (int i = pos; i <= currentPointer; i++)
			{
				list[i] = list[i + 1];
			}
			currentPointer--;
		}
		T* Search(int pos)
		{
			if (pos<0 || pos>currentPointer) { return nullptr; }
			return list[pos];
		}
		T* GetData(int pos)
		{
			return Search(pos);
		}
		bool HasInList(T* data, int& pos)
		{
			for (int i = 0; i <= currentPointer; i++)
			{
				if (list[i] == data)
				{
					pos = i;
					return true;
				}
			}
			pos = -1;
			return false;
		}
		bool IsFull()
		{
			return currentPointer == maxLength - 1;
		}
		bool IsEmpty()
		{
			return currentPointer == -1;
		}
		void Clear()
		{
			delete list;
			list = nullptr;
		}
		void Display()
		{

		}
		T** ToArray()
		{
			return list;
		}
	};

}

