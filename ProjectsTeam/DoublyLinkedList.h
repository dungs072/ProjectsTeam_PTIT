#pragma once
#include<iostream>
#include"Node.h"
#include<string>
namespace DataStructure
{
	template<typename T>

	class DoublyLinkedList
	{
	private:
		Node<T>* first;
		Node<T>* last;
		int length;
		void InitialLinkedList(T value)
		{
			first = new Node<T>();
			first->data = value;
			first->prev = first->next = nullptr;
			last = first;
		}
		void InitialLinkedList(Node<T>* node)
		{
			first = node;
			first->prev = first->next = nullptr;
			last = first;
		}
		bool HasInLinkedList(Node<T>* node)
		{
			Node<T>* p = first;
			if (p == nullptr) { return false; }
			while (p != nullptr)
			{
				if (p == node)
				{
					return true;
				}
				p = p->next;
			}
			return false;
		}

		~DoublyLinkedList()
		{
			Clear();
		}
	public:
		DoublyLinkedList()
		{
			first = nullptr;
			last = first;
			length = 0;
		}

		Node<T>* First()
		{
			return first;
		}
		Node<T>* Last()
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
				Node<T>* t = new Node<T>();
				t->data = value;
				t->prev = last;
				t->next = nullptr;
				last->next = t;
				last = t;
			}
			length++;
		}
		void AddLast(Node<T>* node)
		{
			if (HasInLinkedList(node)) { return; }
			if (node == nullptr) { return; }
			if (first == last && first == nullptr)
			{
				InitialLinkedList(node);
			}
			else
			{
				node->prev = last;
				node->next = nullptr;
				last->next = node;
				last = node;
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
				Node<T>* t = new Node<T>();
				t->data = value;
				t->next = first;
				t->prev = nullptr;
				first->prev = t;
				first = t;
			}
			length++;
		}
		void AddFirst(Node<T>* node)
		{
			if (HasInLinkedList(node)) { return; }
			if (node == nullptr) { return; }
			if (first == last && last == nullptr)
			{
				InitialLinkedList(node);
			}
			else
			{
				node->next = first;
				node->prev = nullptr;
				first->prev = node;
				first = node;
			}
			length++;
		}
		void AddBefore(Node<T>* node, T value)
		{
			if (!HasInLinkedList(node)) { return; }
			if (node == first || node == nullptr)
			{
				AddFirst(value);
				return;
			}
			Node<T>* t = new Node<T>();
			t->data = value;
			t->next = node;
			t->prev = node->prev;
			if (node->prev) { node->prev->next = t; }
			node->prev = t;
			length++;
		}
		void AddBefore(Node<T>* node, Node<T>* nodeValue)
		{
			if (HasInLinkedList(nodeValue)) { return; }
			if (nodeValue == nullptr) { return; }
			if (!HasInLinkedList(node)) { return; }
			if (node == first || node == nullptr)
			{
				AddFirst(nodeValue);
				return;
			}
			nodeValue->next = node;
			nodeValue->prev = node->prev;
			if (node->prev) { node->prev->next = nodeValue; }
			node->prev = nodeValue;
			length++;
		}
		void AddAfter(Node<T>* node, T value)
		{
			if (!HasInLinkedList(node)) { return; }
			if (last == node || node == nullptr)
			{
				AddLast(value);
				return;
			}
			Node<T>* t = new Node<T>();
			t->data = value;
			t->next = node->next;
			t->prev = node;
			if (node->next) { node->next->prev = t; }
			node->next = t;
			length++;
		}
		void AddAfter(Node<T>* node, Node<T>* nodeValue)
		{
			if (HasInLinkedList(nodeValue)) { return; }
			if (nodeValue == nullptr) { return; }
			if (!HasInLinkedList(node)) { return; }
			if (last == node || node == nullptr)
			{
				AddLast(nodeValue);
				return;
			}
			nodeValue->next = node->next;
			nodeValue->prev = node;
			if (node->next) { node->next->prev = nodeValue; }
			node->next = nodeValue;
			length++;
		}
		void Clear()
		{
			length = 0;
			while (first != nullptr)
			{
				Node<T>* p = first;
				first = first->next;
				delete p;
				p = nullptr;
			}
			last = nullptr;
		}
		Node<T>* Find(T value)
		{
			Node<T>* p = first;
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
		Node<T>* FindLast(T value)
		{
			Node<T>* p = first;
			Node<T>* result = nullptr;
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
			Node<T>* p = first;
			first = first->next;
			delete p;
			p = nullptr;
			length--;
			if (first == nullptr) { return; }
			first->prev = nullptr;
		}
		void RemoveLast()
		{
			if (last == nullptr) { return; }
			Node<T>* p = last;
			last = last->prev;
			delete p;
			p = nullptr;
			length--;
			if (last == nullptr) { return; }
			last->next = nullptr;
		}
		bool Remove(T value)
		{
			if (value == first->data)
			{
				RemoveFirst();
				return true;
			}
			Node<T>* p = first;
			while (p != nullptr)
			{
				if (p->data == value)
				{
					if (p == last)
					{
						RemoveLast();
						return true;
					}
					Node<T>* t = p;
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
		void Remove(Node<T>* node)
		{
			if (node == nullptr) { return; }
			if (!HasInLinkedList(node)) { return; }
			if (node == first)
			{
				first = first->next;
				first->prev = nullptr;
				node->next = nullptr;
				node->prev = nullptr;
				length--;
				return;
			}
			Node<T>* p = first;
			while (p != nullptr)
			{
				if (p == node)
				{
					Node<T>* t = p;
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
		void Reverse()
		{
			if (first == nullptr) { return; }
			last = first;
			Node<T>* p = first;
			while (p != nullptr)
			{
				Node<T>* t = p->next;
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
			Node<T>* p = first;
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
		bool Contains(Node<T>* node)
		{
			if (first == nullptr) { return false; }
			Node<T>* p = first;
			while (p != nullptr)
			{
				if (node == p)
				{
					return true;
				}
				p = p->next;
			}
			return false;
		}
		void Display()
		{
			Node<T>* p = first;
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
	};
}


