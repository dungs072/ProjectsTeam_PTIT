#pragma once
#include"Queue.h"
#include"Stack.h"
#include"BSTNode.h"
#include"CardReader.h"
typedef unsigned long long ulong;
namespace DataStructure
{
	template<class T>
	class BSTree
	{
	private:
		BSTNode<T>* rootNode;
		int numberNodes = 0;
		BSTNode<T>* InPre(BSTNode<T>* p)
		{
			while (p != nullptr && p->rightNode != nullptr)
			{
				p = p->rightNode;
			}
			return p;
		}
		BSTNode<T>* InSucc(BSTNode<T>* p)
		{
			while (p != nullptr && p->leftNode != nullptr)
			{
				p = p->leftNode;
			}
			return p;
		}
		BSTNode<T>* Delete(BSTNode<T>* p, ulong key)
		{
			BSTNode<T>* q;
			if (p == nullptr) { return nullptr; }
			if (p->rightNode == nullptr && p->leftNode == nullptr)
			{
				if (p == rootNode)
				{
					rootNode = nullptr;
				}
				delete p;
				return nullptr;
			}
			if (key < p->data->GetCardCode())
			{
				p->leftNode = Delete(p->leftNode, key);
			}
			else if (key > p->data->GetCardCode())
			{
				p->rightNode = Delete(p->rightNode, key);
			}
			else
			{
				if (Height(p->leftNode) > Height(p->rightNode))
				{
					q = InPre(p->leftNode);
					p->data = q->data;
					p->leftNode = Delete(p->leftNode, q->data->GetCardCode());
				}
				else
				{
					q = InSucc(p->rightNode);
					p->data = q->data;
					p->rightNode = Delete(p->rightNode, q->data->GetCardCode());
				}
			}
			return p;
		}
		void Clear(BSTNode<T>*& root)
		{
			if (root == nullptr) {
				return;
			}
			if (root->leftNode) {
				Clear(root->leftNode);
			}
			if (root->rightNode) {
				Clear(root->rightNode);
			}
			delete root;
			root = nullptr;
		}

	public:
		BSTree()
		{
			rootNode = nullptr;
		}
		~BSTree()
		{
			Clear();
		}
		void Clear()
		{
			Clear(rootNode);
			numberNodes = 0;
			rootNode = nullptr;
		}
		void Add(T* data)
		{

			numberNodes++;
			if (rootNode == nullptr)
			{
				rootNode = new BSTNode<T>();
				rootNode->data = data;
				rootNode->rightNode = rootNode->leftNode = nullptr;
				return;
			}
			BSTNode<T>* p = rootNode;
			BSTNode<T>* r = nullptr;
			while (p != nullptr)
			{
				r = p;
				if (data->GetCardCode() < p->data->GetCardCode())
				{
					p = p->leftNode;
				}
				else if (data->GetCardCode() > p->data->GetCardCode())
				{
					p = p->rightNode;
				}
				else
				{
					std::cout << "duplicate data" << std::endl;
					return;
				}

			}
			p = new BSTNode<T>();
			p->data = data;
			p->rightNode = p->leftNode = nullptr;
			if (data->GetCardCode() < r->data->GetCardCode()) r->leftNode = p;
			else r->rightNode = p;

		}
		int Height(BSTNode<T>* mainNode)
		{
			if (mainNode == nullptr) { return 0; }
			int height = 0;
			//two pointers to temp used for count height in queue
			BSTNode<T>* temp = new BSTNode<T>();
			BSTNode<T>* pointedTemp = new BSTNode<T>();
			pointedTemp->rightNode = pointedTemp->leftNode = nullptr;
			temp->rightNode = pointedTemp;
			temp->leftNode = nullptr;
			Queue<BSTNode<T>>* queue = new Queue<BSTNode<T>>();
			queue->Enqueue(*mainNode);
			queue->Enqueue(*temp);
			while (!queue->IsEmpty())
			{
				BSTNode<T> node = queue->Dequeue();
				if (node.rightNode == pointedTemp)
				{
					height++;
				}
				if (node.rightNode != pointedTemp)
				{
					if (node.rightNode != nullptr)
					{
						queue->Enqueue(*node.rightNode);
					}
					if (node.leftNode != nullptr)
					{
						queue->Enqueue(*node.leftNode);
					}
				}
				else if (!queue->IsEmpty())
				{
					queue->Enqueue(*temp);
				}
			}
			delete temp, pointedTemp;
			delete queue;
			return height;
		}
		int Height()
		{
			return Height(rootNode) - 1;
		}
		bool Delete(ulong key)
		{
			if (Search(key) == nullptr) { return false; }
			numberNodes--;
			return Delete(rootNode, key) != nullptr;
		}

		BSTNode<T>* Search(ulong key)
		{
			return Search(rootNode, key);
		}
		BSTNode<T>* Search(BSTNode<T>* mainNode, ulong key)
		{
			if (mainNode == nullptr) { return nullptr; }
			while (mainNode != nullptr)
			{
				if (mainNode->data->GetCardCode() < key)
				{
					mainNode = mainNode->rightNode;
				}
				else if (mainNode->data->GetCardCode() > key)
				{
					mainNode = mainNode->leftNode;
				}
				else
				{
					return mainNode;
				}
			}
			return nullptr;
		}
		BSTNode<T>* RootNode() { return rootNode; }
		void InOrderTravelsal(BSTNode<T>* t)
		{
			if (t == nullptr) { return; }
			BSTNode<T> node;
			Stack<BSTNode<T>>* stack = new Stack<BSTNode<T>>();
			while (t != nullptr || !stack->IsEmpty())
			{
				if (t != nullptr)
				{
					stack->Push(*t);
					t = t->leftNode;
				}
				else
				{
					node = stack->Pop();
					t = &node;
					std::cout << t->data->GetCardCode() << " ";
					t = t->rightNode;
				}
			}
			delete stack;

		}
		void InOrderTravelsal()
		{
			InOrderTravelsal(rootNode);
		}
		T** ToSortArray()
		{
			T** arr = new T * [numberNodes];
			int index = 0;
			BSTNode<T>* t = rootNode;
			if (t == nullptr) { return nullptr; }
			BSTNode<T> node;
			Stack<BSTNode<T>>* stack = new Stack<BSTNode<T>>();
			while (t != nullptr || !stack->IsEmpty())
			{
				if (t != nullptr)
				{
					stack->Push(*t);
					t = t->leftNode;
				}
				else
				{
					node = stack->Pop();
					t = &node;
					//std::cout << t->data.GetCardCode() << " ";
					if (index < numberNodes)
					{
						arr[index] = (t->data);
						index++;
					}
					t = t->rightNode;
				}
			}
			delete stack;
			return arr;
		}
		T** ToSameTreeArray()
		{
			if (numberNodes == 0)
			{
				return nullptr;
			}
			T** arr = new T * [numberNodes];
			int index = 0;
			BSTNode<T>* t = rootNode;
			if (t == nullptr) { return nullptr; }
			BSTNode<T> node;
			Queue<BSTNode<T>>* queue = new Queue<BSTNode<T>>();
			queue->Enqueue(*t);
			while (!queue->IsEmpty())
			{
				node = queue->Dequeue();
				t = &node;
				if (index < numberNodes)
				{
					arr[index] = t->data;
					index++;
				}
				if (t->leftNode != nullptr)
				{
					queue->Enqueue(*(t->leftNode));
				}
				if (t->rightNode != nullptr)
				{
					queue->Enqueue(*(t->rightNode));
				}
			}
			delete queue;
			return arr;
		}
		bool IsDifferentNode(ulong key)
		{
			return Search(key) == nullptr;
		}
		int GetNumberNodes() { return numberNodes; }
	};
}
