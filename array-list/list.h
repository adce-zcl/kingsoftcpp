#pragma once
#include <stdlib.h>
#include <iostream>
namespace ks
{
	template<typename T>
	struct  Node
	{
		T data;
		struct Node* next;
		struct Node* pre;
		Node() :data(0), next(nullptr), pre(nullptr) {}
		Node(T num) :data(num), next(nullptr), pre(nullptr) {}
	};

	template<typename T>
	class List
	{
	private:
		struct Node<T>* head = nullptr;
		struct Node<T>* tail = head;
		int length = 0;

	public:
		List() :head(nullptr),tail(nullptr), length(0) {}

		void push(T data);
		void insert(int index, T data);
		T find(int index);
		void remove(int index);
		void popAll();
		void printInfo();
	};
}

template<typename T>
void ks::List<T>::push(T data)
{
	Node<T>* node = new Node<T>(data);
	if (this->head != nullptr)
	{
		this->tail->next = node;
		node->pre = this->tail;
		this->tail = node;
	}
	else
	{
		this->head = node;
		this->tail = head;
	}
	this->length++;
	return;
}

template<typename T>
void ks::List<T>::insert(int index, T data)
{
	if (index < 0 || index >= this->length + 1)
	{
		return;
	}
	Node<T>* node = new Node<T>(data);
	if (index == 0)
	{
		if (this->head == nullptr)
		{
			this->head = node;
		}
		else
		{
			node->next = this->head;
			this->head->pre = node;
			head = node;
		}
	}
	else if (index == this->length)
	{
		this->tail->next = node;
		node->pre = this->tail;
		this->tail = node;
	}
	else
	{
		Node<T>* temp = this->head;
		int i = 0;
		while (i < index && temp->next != nullptr)
		{
			temp = temp->next;
			++i;
		}
		node->next = temp;
		node->pre = temp->pre;
		temp->pre = node;
		node->pre->next = node;
	}
	this->length++;
	return;
}

template<typename T>
T ks::List<T>::find(int index)
{
	if (index < 0 || index > this->length)
	{
		return INT_MAX;
	}
	int i = 0;
	Node<T>* temp = this->head;
	while (i < index && temp->next != nullptr)
	{
		temp = temp->next;
		++i;
	}
	return temp->data;
}

template<typename T>
void ks::List<T>::remove(int index)
{
	if (index < 0 || index >= this->length)
	{
		return;
	}
	if (index == 0)
	{
		Node<T>* temp = this->head->next;
		temp->pre = nullptr;
		delete this->head;
		this->head = temp;
	}
	else if (index == this->length - 1)
	{
		Node<T>* temp = this->tail;
		this->tail = this->tail->pre;
	}
	else
	{
		int i = 0;
		Node<T>* temp = this->head;
		while (i < index && temp->next != nullptr)
		{
			temp = temp->next;
			++i;
		}
		temp->pre->next = temp->next;
		temp->next->pre = temp->pre;
		delete temp;
	}

	this->length--;
	return;
}

template<typename T>
void ks::List<T>::popAll()
{
	int i = 0;
	Node<T>* temp = this->head;
	while (i < this->length && this->head != nullptr)
	{
		this->head = temp->next;
		delete temp;
		temp = this->head;
	}
	this->length = 0;
	return;
}

template<typename T>
void ks::List<T>::printInfo()
{
	int i = 0;
	Node<T>* temp = this->head;
	while (i < this->length && temp != nullptr)
	{
		std::cout << temp->data << " ";
		temp = temp->next;
		i++;
	}
	std::cout << std::endl;
	return;
}


