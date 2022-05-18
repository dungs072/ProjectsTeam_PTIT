#pragma once
#include<iostream>
#include"SinglyNode.h"
using std::string;
namespace DataStructure
{
	template<typename T>
	class SinglyLinkedList
	{
	private:
		SinglyNode<T>* firstSinglyNode;
		SinglyNode<T>* lastSinglyNode;
		int lengthList;
		SinglyNode<T>* CreateSinglyNode(T data)
		{
			SinglyNode<T>* p = new SinglyNode<T>();
			p->data = data;
			p->next = nullptr;
			return p;
		}
		void SetListnullptr()
		{
			firstSinglyNode = nullptr;
			lastSinglyNode = nullptr;
		}
	public:
		SinglyLinkedList<T>()
		{
			firstSinglyNode = nullptr;
			lastSinglyNode = nullptr;
			lengthList = 0;
		}
		~SinglyLinkedList<T>()
		{
			Clear();
		}
		void Add(T newData)
		{
			if (firstSinglyNode == nullptr && lastSinglyNode == nullptr)
			{
				firstSinglyNode = CreateSinglyNode(newData);
				lastSinglyNode = new SinglyNode<T>();
				lastSinglyNode = firstSinglyNode;
				lengthList++;
			}
			else
			{
				SinglyNode<T>* tempSinglyNode = CreateSinglyNode(newData);
				lastSinglyNode->next = tempSinglyNode;
				lastSinglyNode = tempSinglyNode;
				lengthList++;
			}
		}
		void Insert(T newData, T previousData)
		{
			if (firstSinglyNode == nullptr) { return; }
			SinglyNode<T>* temp = CreateSinglyNode(newData);
			SinglyNode<T>* p = FindSinglyNode(previousData);
			if (p == nullptr) { return; }//cannot insert
			temp->next = p->next;
			p->next = temp;
			if (p == lastSinglyNode)
			{
				lastSinglyNode = temp;
			}
			lengthList++;
		}
		void Insert(T newData, SinglyNode<T>* previousSinglyNode)
		{
			//check whether previousSinglyNode is in SinglyLinkedList or not
			if (firstSinglyNode == nullptr || !Contains(previousSinglyNode)) { return; }
			SinglyNode<T>* temp = CreateSinglyNode(newData);
			temp->next = previousSinglyNode->next;
			previousSinglyNode->next = temp;
			if (previousSinglyNode == lastSinglyNode)
			{
				lastSinglyNode = temp;
			}
			lengthList++;
		}
		void InsertFirstList(T newData)
		{
			SinglyNode<T>* temp = CreateSinglyNode(newData);
			lengthList++;
			if (firstSinglyNode == nullptr)
			{
				lastSinglyNode = firstSinglyNode = temp;
				return;
			}
			temp->next = firstSinglyNode;
			firstSinglyNode = temp;

		}
		void Remove(T dataDelete)
		{
			if (firstSinglyNode == nullptr) { return; }
			SinglyNode<T>* p = firstSinglyNode;

			if (dataDelete == firstSinglyNode->data) {
				if (firstSinglyNode->next != nullptr) {
					firstSinglyNode = firstSinglyNode->next;
				}
				else {
					SetListnullptr();
				}
				delete p;
				p = nullptr;
				lengthList--;
				return;
			}

			p = FindSinglyNode(dataDelete);
			if (p == nullptr) { return; }// not have data in linked List
			SinglyNode<T>* prevSinglyNode = FindPreviousSinglyNode(p);
			prevSinglyNode->next = p->next;
			if (p == lastSinglyNode)
			{
				lastSinglyNode = prevSinglyNode;
			}
			p->next = nullptr;
			delete p;
			p = nullptr;
			lengthList--;
		}
		void Remove(SinglyNode<T>* prevNode, SinglyNode<T>* curNode)
		{
			//just use in methods in case curNode and prevNode have in SinglyLinkedList;
			if (curNode == nullptr)
			{
				return;
			}
			if (prevNode == nullptr)
			{
				RemoveFirst();
				
			}
			else if (curNode == lastSinglyNode)
			{
				RemoveLast();
			}
			else
			{
				prevNode->next = curNode->next;
				curNode->next = nullptr;
				delete curNode;
				lengthList--;
			}
		}
		void RemoveFirst()
		{
			if (firstSinglyNode == nullptr) { return; }
			lengthList--;
			if (firstSinglyNode == lastSinglyNode) {
				SetListnullptr();
				return;
			}
			SinglyNode<T>* p = firstSinglyNode;
			firstSinglyNode = firstSinglyNode->next;
			delete p;
			p = nullptr;

		}
		void RemoveLast()
		{
			if (lastSinglyNode == nullptr) { return; }
			lengthList--;
			if (firstSinglyNode == lastSinglyNode) {
				SetListnullptr();
				return;
			}
			SinglyNode<T>* p = lastSinglyNode;
			lastSinglyNode = FindPreviousSinglyNode(lastSinglyNode);
			lastSinglyNode->next = nullptr;
			delete p;
			p = nullptr;

		}
		SinglyNode<T>* FindPreviousSinglyNode(T data)
		{
			if (firstSinglyNode == nullptr) { return nullptr; }
			if (data == firstSinglyNode->data)
			{
				return nullptr;
			}
			SinglyNode<T>* p = firstSinglyNode;
			while (p->next != nullptr)
			{
				if (p->next->data == data)
				{
					return p;
				}
				p = p->next;
			}
			return nullptr;
		}
		SinglyNode<T>* FindPreviousSinglyNode(SinglyNode<T>* singlyNode)
		{
			if (firstSinglyNode == nullptr) { return nullptr; }
			if (singlyNode == firstSinglyNode) { return nullptr; }
			SinglyNode<T>* p = firstSinglyNode;
			while (p->next != nullptr)
			{
				if (p->next == singlyNode)
				{
					return p;
				}
				p = p->next;
			}
			return nullptr;
		}
		void DisplaySinglyNode()
		{
			if (firstSinglyNode == nullptr) {
				std::cout << "list is nullptr" << std::endl;
				return;
			}
			SinglyNode<T>* p = firstSinglyNode;
			while (p != nullptr)
			{
				std::cout << p->data << std::endl;
				p = p->next;
			}
		}
		void Reverse()
		{
			if (firstSinglyNode == nullptr) { return; }
			SinglyNode<T>* p = firstSinglyNode;
			SinglyNode<T>* q = nullptr;
			SinglyNode<T>* r = nullptr;
			while (p != nullptr)
			{
				r = q;
				q = p;
				p = p->next;
				q->next = r;
			}
			firstSinglyNode = q;
		}
		bool Contains(T data)
		{
			SinglyNode<T>* p = FindSinglyNode(data);
			return p != nullptr ? true : false;
		}
		bool Contains(SinglyNode<T>* singlyNode)
		{
			SinglyNode<T>* p = FindSinglyNode(singlyNode);
			return p != nullptr ? true : false;
		}
		SinglyNode<T>* FindSinglyNode(T data)
		{
			if (firstSinglyNode == nullptr) { return nullptr; }
			SinglyNode<T>* p = firstSinglyNode;
			while (p != nullptr)
			{
				if (p->data == data)
				{
					return p;
				}
				p = p->next;
			}
			return nullptr;
		}
		SinglyNode<T>* FindSinglyNode(SinglyNode<T>* singlyNode)
		{
			if (firstSinglyNode == nullptr) { return nullptr; }
			SinglyNode<T>* p = firstSinglyNode;
			while (p != nullptr)
			{
				if (p == singlyNode)
				{
					return p;
				}
				p = p->next;
			}
			return nullptr;
		}
		int Length()
		{
			return lengthList;
		}
		void Clear()
		{
			if (firstSinglyNode == nullptr) { return; }
			SinglyNode<T>* p = firstSinglyNode;
			while (p != nullptr)
			{
				firstSinglyNode = firstSinglyNode->next;
				
				if (p == lastSinglyNode)
				{
					SetListnullptr();
				}
				delete p;
				p = firstSinglyNode;
				lengthList--;
			}
		}
		SinglyNode<T>* First()
		{
			return firstSinglyNode;
		}
		SinglyNode<T>* Last()
		{
			return lastSinglyNode;
		}
		bool IsEmptyList()
		{
			return lengthList == 0;
		}
	};




}
