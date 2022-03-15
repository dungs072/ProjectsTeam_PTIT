#pragma once
#include<iostream>
namespace DataStructure
{
	template<typename T>
	class Node
	{
	public:
		Node* prev;
		Node* next;
		T data;
		Node(T value)
		{
			data = value;
			prev = nullptr;
			next = nullptr;
		}
		Node() {}
	};
}
