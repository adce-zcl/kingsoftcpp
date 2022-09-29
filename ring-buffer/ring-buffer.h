#pragma once
namespace KS
{
	class RingBuffer
	{
	private:
		int dataStart = 0;	// read point
		int dataLength = 0;		// data length
		int bufferSize = 0;	// buffer size
		int* buffer = nullptr;

		void expand();	// auto expand buffer
		void reduce();	// auto reduce buffer


	public:

		RingBuffer();
		void push(int data);
		int pop();
		void printInfo();
		~RingBuffer();
	};
}


