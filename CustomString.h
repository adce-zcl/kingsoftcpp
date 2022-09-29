#pragma once
namespace KS
{
	class string
	{
	private:
		char* str;
		int length;

	public:
		string();
		string(const char* other);
		string(const string& other);
		string(const string&& other);
		string& operator=(const string& other);
		string& operator=(const string&& other);
		string& operator=(const char* other);
		bool operator==(const string& other);
		void append(const char* other);
		void append(const string& other);
		int len();
		string sub(int start, int end);
		int find(const char* str);
		string* split(const char* str);
		~string();
	};
}



