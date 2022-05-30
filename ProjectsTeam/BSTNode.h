#pragma once
template<class T>
class BSTNode
{

public:
	BSTNode* leftNode;
	BSTNode* rightNode;
	T* data;
	~BSTNode() { }
	BSTNode(T* value)
	{
		data = value;
		leftNode = nullptr;
		rightNode = nullptr;
	}
	BSTNode() 
	{
		data = nullptr;
		leftNode = nullptr;
		rightNode = nullptr;
	}
};
