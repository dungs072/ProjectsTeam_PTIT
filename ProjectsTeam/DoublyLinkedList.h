#pragma once
#include<iostream>
#include"DoublyNode.h"
#include<string>
using std::string;
namespace DataStructure
{
	template<typename T>

	class DoublyLinkedList
	{
	private:
		DoublyNode<T>* first;
		DoublyNode<T>* last;
		int length;
		void InitialLinkedList(T value)
		{
			first = new DoublyNode<T>();
			first->data = value;
			first->prev = first->next = nullptr;
			last = first;
		}
		void InitialLinkedList(DoublyNode<T>* doublyNode)
		{
			first = doublyNode;
			first->prev = first->next = nullptr;
			last = first;
		}
		bool HasInLinkedList(DoublyNode<T>* doublyNode)
		{
			DoublyNode<T>* p = first;
			if (p == nullptr) { return false; }
			while (p != nullptr)
			{
				if (p == doublyNode)
				{
					return true;
				}
				p = p->next;
			}
			return false;
		}


	public:
		~DoublyLinkedList()
		{
			Clear();
		}
		DoublyLinkedList()
		{
			first = nullptr;
			last = first;
			length = 0;
		}

		DoublyNode<T>* First()
		{
			return first;
		}
		DoublyNode<T>* Last()
		{
			return last;
		}
		int Length()
		{
			return length;
		}
		void AddLast(T value)
		{
			if (first == last && first == nullptr)
			{
				InitialLinkedList(value);
			}
			else
			{
				DoublyNode<T>* t = new DoublyNode<T>();
				t->data = value;
				t->prev = last;
				t->next = nullptr;
				last->next = t;
				last = t;
			}
			length++;
		}
		void AddLast(DoublyNode<T>* DoublyNode)
		{
			if (HasInLinkedList(DoublyNode)) { return; }
			if (DoublyNode == nullptr) { return; }
			if (first == last && first == nullptr)
			{
				InitialLinkedList(DoublyNode);
			}
			else
			{
				DoublyNode->prev = last;
				DoublyNode->next = nullptr;
				last->next = DoublyNode;
				last = DoublyNode;
			}
			length++;
		}
		void AddFirst(T value)
		{

			if (first == last && last == nullptr)
			{
				InitialLinkedList(value);
			}
			else
			{
				DoublyNode<T>* t = new DoublyNode<T>();
				t->data = value;
				t->next = first;
				t->prev = nullptr;
				first->prev = t;
				first = t;
			}
			length++;
		}
		void AddFirst(DoublyNode<T>* DoublyNode)
		{
			if (HasInLinkedList(DoublyNode)) { return; }
			if (DoublyNode == nullptr) { return; }
			if (first == last && last == nullptr)
			{
				InitialLinkedList(DoublyNode);
			}
			else
			{
				DoublyNode->next = first;
				DoublyNode->prev = nullptr;
				first->prev = DoublyNode;
				first = DoublyNode;
			}
			length++;
		}
		void AddBefore(DoublyNode<T>* doublyNode, T value)
		{
			if (!HasInLinkedList(doublyNode)) { return; }
			if (doublyNode == first || doublyNode == nullptr)
			{
				AddFirst(value);
				return;
			}
			DoublyNode<T>* t = new DoublyNode<T>();
			t->data = value;
			t->next = doublyNode;
			t->prev = doublyNode->prev;
			if (doublyNode->prev) { doublyNode->prev->next = t; }
			doublyNode->prev = t;
			length++;
		}
		void AddBefore(DoublyNode<T>* doublyNode, DoublyNode<T>* doublyNodeValue)
		{
			if (HasInLinkedList(doublyNodeValue)) { return; }
			if (doublyNodeValue == nullptr) { return; }
			if (!HasInLinkedList(doublyNode)) { return; }
			if (doublyNode == first || doublyNode == nullptr)
			{
				AddFirst(doublyNodeValue);
				return;
			}
			doublyNodeValue->next = doublyNode;
			doublyNodeValue->prev = doublyNode->prev;
			if (doublyNode->prev) { doublyNode->prev->next = doublyNodeValue; }
			doublyNode->prev = doublyNodeValue;
			length++;
		}
		void AddAfter(DoublyNode<T>* doublyNode, T value)
		{
			if (!HasInLinkedList(doublyNode)) { return; }
			if (last == doublyNode || doublyNode == nullptr)
			{
				AddLast(value);
				return;
			}
			DoublyNode<T>* t = new DoublyNode<T>();
			t->data = value;
			t->next = doublyNode->next;
			t->prev = doublyNode;
			if (doublyNode->next) { doublyNode->next->prev = t; }
			doublyNode->next = t;
			length++;
		}
		void AddAfter(DoublyNode<T>* doublyNode, DoublyNode<T>* doublyNodeValue)
		{
			if (HasInLinkedList(doublyNodeValue)) { return; }
			if (doublyNodeValue == nullptr) { return; }
			if (!HasInLinkedList(doublyNode)) { return; }
			if (last == doublyNode || doublyNode == nullptr)
			{
				AddLast(doublyNodeValue);
				return;
			}
			doublyNodeValue->next = doublyNode->next;
			doublyNodeValue->prev = doublyNode;
			if (doublyNode->next) { doublyNode->next->prev = doublyNodeValue; }
			doublyNode->next = doublyNodeValue;
			length++;
		}
		void Clear()
		{
			length = 0;
			while (first != nullptr)
			{
				DoublyNode<T>* p = first;
				first = first->next;
				delete p;
				p = nullptr;
			}
			last = nullptr;
		}
		DoublyNode<T>* Find(T value)
		{
			DoublyNode<T>* p = first;
			while (p != nullptr)
			{
				if (p->data == value)
				{
					return p;
				}
				p = p->next;
			}
			return nullptr;
		}
		DoublyNode<T>* FindLast(T value)
		{
			DoublyNode<T>* p = first;
			DoublyNode<T>* result = nullptr;
			while (p != nullptr)
			{
				if (p->data == value)
				{
					result = p;
				}
				p = p->next;
			}
			return result;
		}
		void RemoveFirst()
		{
			if (first == nullptr) { return; }
			length--;
			if (first == last)
			{
				delete first;
				last = first = nullptr;
				return;
			}
			DoublyNode<T>* p = first;
			first = first->next;
			delete p;
			p = nullptr;
			first->prev = nullptr;
		}
		void RemoveLast()
		{
			if (last == nullptr) { return; }
			length--;
			if (last == first)
			{
				delete last;
				last = first = nullptr;
				return;
			}
			DoublyNode<T>* p = last;
			last = last->prev;
			delete p;
			p = nullptr;
			last->next = nullptr;
		}
		bool Remove(T value)
		{
			if (value == first->data)
			{
				RemoveFirst();
				return true;
			}
			DoublyNode<T>* p = first;
			while (p != nullptr)
			{
				if (p->data == value)
				{
					if (p == last)
					{
						RemoveLast();
						return true;
					}
					DoublyNode<T>* t = p;
					if (p->prev) { p->prev->next = p->next; }
					if (p->next) { p->next->prev = p->prev; }
					delete t;
					t = nullptr;
					length--;
					return true;
				}
				p = p->next;
			}
			return false;
		}
		void Remove(DoublyNode<T>* doublyNode)
		{
			if (doublyNode == nullptr) { return; }
			if (!HasInLinkedList(doublyNode)) { return; }
			if (doublyNode == first)
			{
				first = first->next;
				first->prev = nullptr;
				doublyNode->next = nullptr;
				doublyNode->prev = nullptr;
				length--;
				return;
			}
			DoublyNode<T>* p = first;
			while (p != nullptr)
			{
				if (p == doublyNode)
				{
					DoublyNode<T>* t = p;
					if (p->prev) { p->prev->next = p->next; }
					if (p->next) { p->next->prev = p->prev; }
					t->next = nullptr;
					t->prev = nullptr;
					length--;
					return;
				}
				p = p->next;
			}
		}
		bool Remove(string bookCode)
		{
			if (bookCode == first->data.GetBookCode())
			{
				RemoveFirst();
				return true;
			}
			DoublyNode<T>* p = first;
			while (p != nullptr)
			{
				if (p->data.GetBookCode() == bookCode)
				{
					if (p == last)
					{
						RemoveLast();
						return true;
					}
					DoublyNode<T>* t = p;
					if (p->prev) { p->prev->next = p->next; }
					if (p->next) { p->next->prev = p->prev; }
					delete t;
					t = nullptr;
					length--;
					return true;
				}
				p = p->next;
			}
			return false;
		}
		void Reverse()
		{
			if (first == nullptr) { return; }
			last = first;
			DoublyNode<T>* p = first;
			while (p != nullptr)
			{
				DoublyNode<T>* t = p->next;
				p->next = p->prev;
				p->prev = t;
				p = p->prev;
				if (p != nullptr && p->next == nullptr)
				{
					first = p;

				}
			}
		}
		bool Contains(T value)
		{
			if (first == nullptr) { return false; }
			DoublyNode<T>* p = first;
			while (p != nullptr)
			{
				if (value == p->data)
				{
					return true;
				}
				p = p->next;
			}
			return false;
		}
		bool Contains(DoublyNode<T>* doublyNode)
		{
			if (first == nullptr) { return false; }
			DoublyNode<T>* p = first;
			while (p != nullptr)
			{
				if (doublyNode == p)
				{
					return true;
				}
				p = p->next;
			}
			return false;
		}
		void Display()
		{
			DoublyNode<T>* p = first;
			if (p == nullptr)
			{
				std::cout << "Linked list is empty" << std::endl;
				return;
			}
			while (p != nullptr)
			{
				std::cout << p->data << std::endl;
				p = p->next;
			}
		}
		void AddOrder(T data)
		{
			
		}
	};
}


