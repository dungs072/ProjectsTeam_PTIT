#pragma once
#include<iostream>
#include"SinglyNode.h"
template<typename T>
class SinglyLinkedList
{
private:
	Node<T>* firstNode;
	Node<T>* lastNode;
	int lengthList;
	Node<T>* CreateNode(T data)
	{
		Node<T>* p = new Node<T>();
		p->data = data;
		p->next = nullptr;
		return p;
	}
	void SetListnullptr()
	{
		firstNode = nullptr;
		lastNode = nullptr;
	}
public:
	SinglyLinkedList<T>()
	{
		firstNode = nullptr;
		lastNode = nullptr;
		lengthList = 0;
	}
	~SinglyLinkedList<T>()
	{
		Clear();
	}
	void Add(T newData)
	{
		if (firstNode == nullptr && lastNode == nullptr)
		{
			firstNode = CreateNode(newData);
			lastNode = new Node<T>();
			lastNode = firstNode;
			lengthList++;
		}
		else
		{
			Node<T>* tempNode = CreateNode(newData);
			lastNode->next = tempNode;
			lastNode = tempNode;
			lengthList++;
		}
	}
	void Insert(T newData, T previousData)
	{
		if (firstNode == nullptr) { return; }
		Node<T>* temp = CreateNode(newData);
		Node<T>* p = FindNode(previousData);
		if (p == nullptr) { return; }//cannot insert
		temp->next = p->next;
		p->next = temp;
		if (p == lastNode)
		{
			lastNode = temp;
		}
		lengthList++;
	}
	void Insert(T newData, Node<T>* previousNode)
	{
		//check whether previousNode is in SinglyLinkedList or not
		if (firstNode == nullptr || !Contains(previousNode)) { return; }
		Node<T>* temp = CreateNode(newData);
		temp->next = previousNode->next;
		previousNode->next = temp;
		if (previousNode == lastNode)
		{
			lastNode = temp;
		}
		lengthList++;
	}
	void InsertFirstList(T newData)
	{
		Node<T>* temp = CreateNode(newData);
		lengthList++;
		if (firstNode == nullptr)
		{
			lastNode = firstNode = temp;
			return;
		}
		temp->next = firstNode;
		firstNode = temp;

	}
	void Remove(T dataDelete)
	{
		if (firstNode == nullptr) { return; }
		Node<T>* p = firstNode;

		if (dataDelete == firstNode->data) {
			if (firstNode->next != nullptr) {
				firstNode = firstNode->next;
			}
			else {
				SetListnullptr();
			}
			delete p;
			p = nullptr;
			lengthList--;
			return;
		}

		p = FindNode(dataDelete);
		if (p == nullptr) { return; }// not have data in linked List
		Node<T>* prevNode = FindPreviousNode(p);
		prevNode->next = p->next;
		if (p == lastNode)
		{
			lastNode = prevNode;
		}
		p->next = nullptr;
		delete p;
		p = nullptr;
		lengthList--;
		return;
	}
	void RemoveFirst()
	{
		if (firstNode == nullptr) { return; }
		lengthList--;
		if (firstNode == lastNode) {
			SetListnullptr();
			return;
		}
		Node<T>* p = firstNode;
		firstNode = firstNode->next;
		delete p;
		p = nullptr;

	}
	void RemoveLast()
	{
		if (lastNode == nullptr) { return; }
		lengthList--;
		if (firstNode == lastNode) {
			SetListnullptr();
			return;
		}
		Node<T>* p = lastNode;
		lastNode = FindPreviousNode(lastNode);
		lastNode->next = nullptr;
		delete p;
		p = nullptr;

	}
	Node<T>* FindPreviousNode(T data)
	{
		if (firstNode == nullptr) { return nullptr; }
		if (data == firstNode->data)
		{
			return nullptr;
		}
		Node<T>* p = firstNode;
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
	Node<T>* FindPreviousNode(Node<T>* node)
	{
		if (firstNode == nullptr) { return nullptr; }
		if (node == firstNode) { return nullptr; }
		Node<T>* p = firstNode;
		while (p->next != nullptr)
		{
			if (p->next == node)
			{
				return p;
			}
			p = p->next;
		}
		return nullptr;
	}
	void DisplayNode()
	{
		if (firstNode == nullptr) {
			std::cout << "list is nullptr" << std::endl;
			return;
		}
		Node<T>* p = firstNode;
		while (p != nullptr)
		{
			std::cout << p->data << std::endl;
			p = p->next;
		}
	}
	void Reverse()
	{
		if (firstNode == nullptr) { return; }
		Node<T>* p = firstNode;
		Node<T>* q = nullptr;
		Node<T>* r = nullptr;
		while (p != nullptr)
		{
			r = q;
			q = p;
			p = p->next;
			q->next = r;
		}
		firstNode = q;
	}
	bool Contains(T data)
	{
		Node<T>* p = FindNode(data);
		return p != nullptr ? true : false;
	}
	bool Contains(Node<T>* node)
	{
		Node<T>* p = FindNode(node);
		return p != nullptr ? true : false;
	}
	Node<T>* FindNode(T data)
	{
		if (firstNode == nullptr) { return nullptr; }
		Node<T>* p = firstNode;
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
	Node<T>* FindNode(Node<T>* node)
	{
		if (firstNode == nullptr) { return nullptr; }
		Node<T>* p = firstNode;
		while (p != nullptr)
		{
			if (p == node)
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
		if (firstNode == nullptr) { return; }
		Node<T>* p = firstNode;
		while (p != nullptr)
		{
			firstNode = firstNode->next;
			p->next = nullptr;
			delete p;
			if (p == lastNode)
			{
				SetListnullptr();
			}
			p = nullptr;
			p = firstNode;
			lengthList--;
		}
	}
	Node<T>* First()
	{
		return firstNode;
	}
	Node<T>* Last()
	{
		return lastNode;
	}
	bool IsEmptyList()
	{
		return lengthList == 0;
	}
};



