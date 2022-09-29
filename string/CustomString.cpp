#include "CustomString.h"
#include <string.h>
#include <cstdlib>
using namespace KS;

string::string()
{
	this->str = nullptr;
	this->length = 0;
	return;
}

string::string(const char* other)
{
	int i = 0;
	while (other[i] != '\0') 
	{
		++i;
	}
	if (i == 0)
	{
		this->length = 0;
		this->str = nullptr;
		return;
	}
	this->length = i;
	this->str = (char*)malloc(sizeof(char) * (i + 1));
	if (this->str == nullptr)
	{
		return;
	}
	memcpy(this->str, other, i + 1);
	return;
}

string::string(const string& other)
{
	if (other.length == 0)
	{
		this->length = 0;
		this->str = nullptr;
		return;
	}
	this->length = other.length;
	this->str = (char*)malloc(sizeof(char) * (other.length + 1));
	if (this->str == nullptr)
	{
		return;
	}
	memcpy(this->str, other.str, other.length + 1);
}

string::string(const string&& other)
{
	if (other.length == 0)
	{
		this->length = 0;
		this->str = nullptr;
		return;
	}
	this->length = other.length;
	this->str = (char*)malloc(sizeof(char) * (other.length + 1));
	if (this->str == nullptr)
	{
		return;
	}
	memcpy(this->str, other.str, other.length + 1);
}

string& string::operator=(const string& other)
{
	this->str = (char*)malloc(sizeof(char) * other.length);
	if (this->str == nullptr)
	{
		this->length = 0;
		return *this;
	}
	memcpy(this->str, other.str, other.length + 1);
	this->length = other.length;
	return *this;
}

string& string::operator=(const string&& other)
{
	this->str = (char*)malloc(sizeof(char) * other.length);
	if (this->str == nullptr)
	{
		this->length = 0;
		return *this;
	}
	memcpy(this->str, other.str, other.length + 1);
	this->length = other.length;
	return *this;
}

string& string::operator=(const char* other)
{
	int i = 0;
	while (other[i] != '\0')
	{
		++i;
	}
	if (i == 0)
	{
		this->length = 0;
		this->str = nullptr;
		return *this;
	}
	this->length = i;
	this->str = (char*)malloc(sizeof(char) * (i + 1));
	if (this->str == nullptr)
	{
		return *this;
	}
	memcpy(this->str, other, i + 1);
	return *this;
}

bool string::operator==(const string& other)
{
	if (this->length != other.length)
	{
		return false;
	}
	for (int i = 0; i < this->length; i++)
	{
		if (this->str[i] != other.str[i])
		{
			return false;
		}
	}
	return true;
}

void string::append(const char* other)
{
	int i = 0;
	while (other[i] != '\0')
	{
		++i;
	}
	if (i == 0)
	{
		return;
	}
	char* tempStr = (char*)malloc(sizeof(char) * (this->length + 1 + i));
	if (tempStr == nullptr)
	{
		return;
	}
	memcpy(tempStr, this->str, sizeof(char) * this->length);
	memcpy(&tempStr[this->length + 1], other, i + 1);
	this->length += i;
	delete this->str;
	this->str = tempStr;
	return;
}

void string::append(const string& other)
{
	this->append(other.str);
	return;
}

int string::len()
{
	return this->length;
}

string string::sub(int start, int end)
{
	if (start < 0 || end > this->length + 1)
	{
		return string();
	}
	char* tempStr = (char*)malloc(sizeof(char) * (end - start + 1));
	if (tempStr == nullptr)
	{
		return string();
	}
	memcpy(tempStr, &this->str[start], start - end);
	tempStr[start - end] = '\0';
	
	return string(tempStr);
}

int string::find(const char* other)
{
	for (int i = 0; i < this->length; i++)
	{
		int j = 0;
		int k = i;
		while (other[j] != '\0' && (this->str[k] == other[j]))
		{
			k++;
			j++;
		}
		if (other[j] == '\0')
		{
			return i;
		}
	}
	return -1;
}

string* string::split(const char* other)
{
	int num = 0;
	for (int i = 0; i < this->length; i++)
	{
		int j = 0;
		int k = i;
		while (other[j] != '\0' && (this->str[k] == other[j]))
		{
			k++;
			j++;
		}
		if (other[j] == '\0')
		{
			i = k - 1;
			num++;
		}
	}

	string* value = (string*)malloc(sizeof(string) * num);
	int index = 0;
	num = 0;
	for (int i = 0; i < this->length; i++)
	{
		int j = 0;
		int k = i;
		while (other[j] != '\0' && (this->str[k] == other[j]))
		{
			k++;
			j++;
		}
		if (other[j] == '\0')
		{
			i = k - 1;
			char* temp = (char*)malloc(sizeof(char) * (i - index + 1));
			if (temp == nullptr)
			{
				return nullptr;
			}
			memcpy(temp, &this->str[index], sizeof(char) * (i - index));
			temp[i - index] = '\0';
			int length = i - index;
			value[num].length = length;
			value[num].str = temp;
			num++;
			index = k;
		}
	}
	return value;
}

string::~string()
{
	if (this->str != nullptr)
	{
		delete this->str;
	}
	return;
}
