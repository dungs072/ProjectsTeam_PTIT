#pragma once
#include"DoublyLinkedList.h"
namespace DataStructure
{
	template<class T>
	class Queue
	{
	private:
		DoublyLinkedList<T>* listQueue;
	public:
		Queue()
		{
			listQueue = new DoublyLinkedList<T>();
		}
		~Queue()
		{
			listQueue->Clear();
		}
		void Enqueue(T data)
		{
			listQueue->AddLast(data);
		}
		T Dequeue()
		{
			T data = (listQueue->First()->data);
			listQueue->RemoveFirst();
			return data;
		}
		bool IsEmpty()
		{
			return listQueue->Length() == 0;
		}
	};
}


