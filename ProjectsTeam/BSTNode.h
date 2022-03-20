#pragma once
template<class T>
class BSTNode
{

public:
	BSTNode* leftNode;
	BSTNode* rightNode;
	T* data;
	BSTNode(T* value)
	{
		data = value;
		leftNode = nullptr;
		rightNode = nullptr;
	}
	BSTNode() {}
};
