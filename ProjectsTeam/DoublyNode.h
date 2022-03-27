#pragma once
#include<iostream>
namespace DataStructure
{
	template<class T>
	class DoublyNode
	{
	public:
		DoublyNode* prev;
		DoublyNode* next;
		T data;
		DoublyNode(T value)
		{
			data = value;
			prev = nullptr;
			next = nullptr;
		}
		DoublyNode() {}
		~DoublyNode()
		{
			delete prev;
			delete next;
			prev = nullptr;
			next = nullptr;
		}
	};
}
