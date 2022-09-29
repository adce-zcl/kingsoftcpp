#pragma once
#include <cstdlib>
#include <string.h>
#include <iostream>
namespace ks
{
	template<typename T>
	class Array
	{
	private:
#define EXPAND_NUM 5	// expand amount every time.
#define REDUCE_NUM 6	// reduce amount every time.
		T* arr;
		int size = 0;
		int length = 0;

		void expand();	// auto expand
		void reduce();	// auto reduce

	public:
		Array(const Array& _other) = delete;
		Array(const Array&& _other) = delete;
		Array& operator=(const Array& _other) = delete;
		Array& operator=(const Array&& _other) = delete;

		Array() :arr(nullptr), size(0), length(0) {}

		void reserve(int size);
		void push(T data);
		void insert(int index, T data);
		void remove(int index);
		T pop();
		void clear();
		int findindex(int index);
		void printinfo();
		~Array();
	};
};


template<typename T>
void ks::Array<T>::expand()
{
	if (this->size == this->length)
	{
		// expand
		T* temp = (T*)malloc(sizeof(T) * (this->size + EXPAND_NUM));
		if (temp == nullptr)
		{
			return;
		}
		for (int i = 0; i < this->length; ++i)
		{
			temp[i] = this->arr[i];
		}
		free(this->arr);
		this->arr = temp;
		this->size = size + EXPAND_NUM;
	}
}

template<typename T>
void ks::Array<T>::reduce()
{
	if (this->size - REDUCE_NUM > this->length)
	{
		T* temp = (T*)malloc(sizeof(T) * (this->length + 1));
		if (temp == nullptr)
		{
			return;
		}
		for (int i = 0; i < this->length; ++i)
		{
			temp[i] = this->arr[i];
		}
		free(this->arr);
		this->arr = temp;
		this->size = this->length + 1;
	}
}

template<typename T>
void ks::Array<T>::reserve(int size)
{
	if (this->size == size)
	{
		return;
	}
	int index = size >= this->length ? this->length : size;
	T* temp = (T*)malloc(sizeof(T) * size);
	if (temp == nullptr)
	{
		return;
	}
	for (int i = 0; i < index; ++i)
	{
		temp[i] = this->arr[i];
	}
	free(this->arr);
	this->arr = temp;
	this->size = size;
	if (index == size)
	{
		this->length = size;
	}
	return;
}

template<typename T>
void ks::Array<T>::push(T data)
{
	expand();
	this->arr[this->length++] = data;
	return;
}

template<typename T>
void ks::Array<T>::insert(int index, T data)
{
	if (index < 0 || index > this->length)
	{
		return;
	}
	expand();
	for (int i = this->length - 1; i > index; --i)
	{
		this->arr[i + 1] = this->arr[i];
	}
	this->arr[index + 1] = data;
	this->length++;
	return;
}


template<typename T>
void ks::Array<T>::remove(int index)
{
	if (index < 0 || index >= this->length)
	{
		return;
	}

	for (int i = index + 1; i < this->length; ++i)
	{
		this->arr[i - 1] = this->arr[i];
	}
	this->length--;
	reduce();
	return;
}

template<typename T>
T ks::Array<T>::pop()
{
	if (this->length == 0)
	{
		return INT_MAX;
	}
	T temp = this->arr[this->length - 1];

	this->length--;
	reduce();
	return temp;
}

template<typename T>
void ks::Array<T>::clear()
{
	free(this->arr);
	this->arr = nullptr;
	this->length = 0;
	this->size = 0;
	return;
}


template<typename T>
int ks::Array<T>::findindex(int index)
{
	if (index < 0 || index >= this->length)
	{
		return INT_MAX;
	}
	return this->arr[index];
}

template<typename T>
void ks::Array<T>::printinfo()
{
	for (int i = 0; i < this->length; ++i)
	{
		std::cout << this->arr[i] << " ";
	}
	std::cout << std::endl;
}

template<typename T>
ks::Array<T>::~Array()
{
	if (this->arr != nullptr)
	{
		free(this->arr);
	}
	return;
}

