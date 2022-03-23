#pragma once
#include<iostream>
using std::string;
namespace DataStructure
{
	template<class T>
	class LinearList {
	private:
		int currentLength;
		int maxLength;
		T** list;
	public:
		LinearList(int maxLength)
		{
			this->maxLength = maxLength;
			list = new T * [maxLength];
			currentLength = 0;
		}
		LinearList()
		{
			maxLength = 100;
			currentLength = 0;
			list = new T * [maxLength];
		}
		~LinearList()
		{
			Clear();
		}
		int Length()
		{
			return currentLength;
		}
		void AddLast(T* data)
		{
			if (IsFull()) { return; }
			if (list == nullptr)
			{
				list = new T * [maxLength];
			}
			list[currentLength++] = data;
		}
		void Delete(T* data)
		{
			int pos = 0;
			if (!HasInList(data, pos)) { return; }
			delete data;
			data = nullptr;
			if (pos == -1) { return; }
			for (int i = pos; i < currentLength-1; i++)
			{
				list[i] = list[i + 1];
			}
			list[currentLength - 1] = nullptr;
			currentLength--;
		}
		void Delete(int pos)
		{
			if (pos<0 || pos>currentLength) { return; }
			delete list[pos];
			list[pos] = nullptr;
			for (int i = pos; i < currentLength-1; i++)
			{
				list[i] = list[i + 1];
			}
			list[currentLength - 1] = nullptr;
			currentLength--;
		}
		void Delete(string ISBN)
		{
			int pos = 0;
			if (!HasInList(ISBN, pos)) { return; }
			if (pos == -1) { return; }
			T* temp = list[pos];
			delete temp;
			temp = nullptr;
			for (int i = pos; i < currentLength-1; i++)
			{
				list[i] = list[i + 1];
			}
			list[currentLength-1] = nullptr;
			currentLength--;
		}
		T* Search(int pos)
		{
			if (pos<0 || pos>currentLength-1) { return nullptr; }
			return list[pos];
		}
		T* GetData(int pos)
		{
			return Search(pos);
		}
		bool HasInList(string ISBN, int& pos)
		{
			for (int i = 0; i < currentLength; i++)
			{
				if (list[i]->GetISBN() == ISBN)
				{
					pos = i;
					return true;
				}
			}
			pos = -1;
			return false;
		}
		bool HasInList(T* data, int& pos)
		{
			for (int i = 0; i < currentLength; i++)
			{
				if (list[i]->GetISBN() == data->GetISBN())
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
			return currentLength == maxLength;
		}
		bool IsEmpty()
		{
			return currentLength == 0;
		}
		void Clear()
		{
			for (int i = 0; i < currentLength; i++)
			{
				delete list[i];
				list[i] = nullptr;
			}
			delete list;
			list = nullptr;
			currentLength = 0;
		}
		T** ToArray()
		{
			return list;
		}
		int MaxLength()
		{
			return maxLength;
		}
	};

}

