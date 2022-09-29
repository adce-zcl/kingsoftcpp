#pragma once
#include <functional>
#include <stack>
namespace KS
{
	struct Node
	{
		void* data = nullptr;
		struct Node* next = nullptr;
	};

	class StackInfo
	{
	private:
		Node* head = nullptr;

	public:
		StackInfo() :head(nullptr) {}

		template<typename T>
		void push(const T& data)
		{
			Node* node = (Node*)malloc(sizeof(Node));
			node->data = malloc(sizeof(data));
			node->next = nullptr;
			memcpy(node->data, &data, sizeof(data));
			if (head == nullptr)
			{
				head = node;
			}
			else
			{
				node->next = head;
				head = node;
			}
			return;
		}

		template<typename T>
		void pop(T& data)
		{
			if (head == nullptr)
			{
				return;
			}
			data = *((T*)(head->data));
			Node* node = head;
			head = head->next;
			if (node->data != nullptr)
			{
				free(node->data);
			}
			free(node);
			return;
		}

		~StackInfo()
		{
			while (head != nullptr)
			{
				Node* temp = head;
				head = head->next;
				if (temp->data != nullptr)
				{
					free(temp->data);
				}
				free(temp);
			}
			return;
		}
	};
}