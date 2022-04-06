#pragma once
#include<iostream>
template<typename T>
class SinglyNode
{
public:
	T data;
	SinglyNode* next;
	SinglyNode()
	{
		next = nullptr;
	}
	~SinglyNode() 
	{
		next = nullptr;
	}
};

