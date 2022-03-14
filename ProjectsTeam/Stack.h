#pragma once
#include"DoublyLinkedList.h"
namespace DataStructure
{
	template<typename T>
	class Stack
	{
	private:
		LinkedList<T>* listStack;
	public:
		Stack() {
			listStack = new LinkedList<T>();
		}
		~Stack()
		{
			listStack->Clear();
		}

		void Push(T* data) {
			listStack->AddLast(*data);
		}

		T* Pop() {
			T tempData = listStack->Last()->data;
			listStack->RemoveLast();
			return &tempData;
		}
		T* Front()
		{
			return &listStack->Last()->data;
		}
		bool IsEmpty() {
			return listStack->Length() == 0;
		}

	};

}
