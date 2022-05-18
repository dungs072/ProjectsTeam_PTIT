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
		DoublyNode() 
		{
			prev = nullptr;
			next = nullptr;
		}
		DoublyNode(T value)
		{
			data = value;
			prev = nullptr;
			next = nullptr;
		}
		
		//I modified here
	};
}
