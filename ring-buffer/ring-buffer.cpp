#include "ring-buffer.h"
#include <iostream>
void KS::RingBuffer::expand()
{
	if (this->dataLength < this->bufferSize)
	{
		return;
	}
	int* newBuffer = new int[this->bufferSize * 2];
	int newSize = this->bufferSize * 2;
	for (int i = this->dataStart, j = this->dataStart; i < this->dataStart + this->dataLength; ++i, ++j)
	{
		i &= (this->bufferSize - 1);
		newBuffer[j] = this->buffer[i];
	}
	delete[] this->buffer;
	this->buffer = newBuffer;
	this->bufferSize = newSize;
	return;
}

void KS::RingBuffer::reduce()
{
	if (this->dataLength != this->bufferSize / 2 - 1)	// reserve one space
	{
		return;
	}
	int* newBuffer = new int[this->dataLength + 1];
	int newSize = this->dataLength + 1;
	for (int i = this->dataStart, j = 0; i < this->dataStart + this->dataLength; ++i, ++j)
	{
		i &= (this->bufferSize - 1);
		newBuffer[j] = this->buffer[i];
	}
	this->dataStart = 0;
	delete[] this->buffer;
	this->buffer = newBuffer;
	this->bufferSize = newSize;
	return;
}

KS::RingBuffer::RingBuffer()
{
	this->bufferSize = 4;	// Power of 2 expansion, the initial value is 4
	this->buffer = new int[this->bufferSize];
	this->dataLength = 0;
	this->dataStart = 0;
	return;
}

void KS::RingBuffer::push(int data)
{
	expand();
	this->buffer[(this->dataStart + this->dataLength) & (this->bufferSize - 1)] = data;
	this->dataLength++;
	return;
}

int KS::RingBuffer::pop()
{
	int temp = this->buffer[this->dataStart];
	this->dataStart++;
	this->dataStart %= this->bufferSize;
	this->dataLength--;
	reduce();
	return temp;
}

void KS::RingBuffer::printInfo()
{
	for (int i = this->dataStart; i < this->dataStart + this->dataLength; ++i)
	{
		i &= this->bufferSize - 1;
		std::cout << this->buffer[i] << " ";
	}
	std::cout << std::endl;
	return;
}



KS::RingBuffer::~RingBuffer()
{
	if (this->buffer != nullptr)
	{
		delete[] buffer;
	}
	return;
}
