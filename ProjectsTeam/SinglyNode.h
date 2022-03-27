#pragma once
#include<iostream>
template<typename T>
class SinglyNode
{
public:
	T data;
	SinglyNode* next;
	SinglyNode() {};
	~SinglyNode()
	{
		delete next;
		next = nullptr;
	}
};

