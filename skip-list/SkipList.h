#pragma once
#include <cstdlib>
#include <random>
#include <ctime>
#include <iostream>
#define MAX_LEVEL 4	// 0 - 3
namespace KS
{
	struct SkipListNode
	{
		int data;
		struct SkipListNode* next[MAX_LEVEL];
		SkipListNode(int data_)
		{
			this->data = data_;
			for(int i = 0; i < MAX_LEVEL; ++i)
			{
				this->next[i] = nullptr;
			}
			return;
		}
	};

	class Skiplist 
	{
	private: 
		struct SkipListNode* head;

	public:
		Skiplist() 
		{
			this->head = new SkipListNode(INT_MIN);
			return;
		}

		bool search(int target) 
		{
			SkipListNode* curentNode = this->head;
			for(int i = MAX_LEVEL - 1; i >= 0; --i)
			{
				while (curentNode->next[i] != nullptr && curentNode->next[i]->data < target)
				{
					curentNode = curentNode->next[i];
				}
			}
			if (curentNode->next[0] != nullptr && curentNode->next[0]->data == target)
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		void add(int num) 
		{
			SkipListNode* nodes[MAX_LEVEL];
			SkipListNode* curentNode = this->head;
			for(int i = MAX_LEVEL - 1; i >= 0; --i)	// find pre node every level.
			{
				while(curentNode->next[i] != nullptr && curentNode->next[i]->data < num)
				{
					curentNode = curentNode->next[i];
				}
				nodes[i] = curentNode;
			}
			SkipListNode* newNode = new SkipListNode(num);
			// c++11 random
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<> dis(0,2);
			for(int i = 0; i < MAX_LEVEL; ++i)	// dynamic update index, p == 1/2.
			{
				newNode->next[i] = nodes[i]->next[i];
				nodes[i]->next[i] = newNode;
				if(dis(gen) == 0)
				{
					break;
				}
			}
		}

		bool erase(int num) 
		{
			SkipListNode* nodes[MAX_LEVEL];
			SkipListNode* curentNode = this->head;
			for(int i = MAX_LEVEL - 1; i >= 0; --i)	// find pre node every level.
			{
				while(curentNode->next[i] != nullptr && curentNode->next[i]->data < num)
				{
					curentNode = curentNode->next[i];
				}
				nodes[i] = curentNode;
			}
			if(nodes[0]->next[0] == nullptr || nodes[0]->next[0]->data != num)
			{
				return false;
			}
			SkipListNode* targetNode = nodes[0]->next[0];
			for(int i = 0; i < MAX_LEVEL; ++i)
			{
				if (nodes[i]->next[i] != nullptr && nodes[i]->next[i]->data == targetNode->data)
				{
					nodes[i]->next[i] = nodes[i]->next[i]->next[i];
				}
			}
			delete targetNode;
			return true;
		}
	};
}


