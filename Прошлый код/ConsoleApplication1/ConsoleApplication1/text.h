#pragma once
#include <string>
#include <iostream>
#include <fstream>

class text
{
public:
	char * stroka;
	int length;
	text();
	text(const text &a);
	text( char * temp);
	text(std::string temp);
	~text();
	void clear();
	void add(text temp);
	void insert(int point, char *temp);
	void cut(int point, int size);
	void save(char * t);
	void load(char * t);
	void operator = ( text b)
	{
		if (length != 0)
		{
			delete[] stroka;
			length = 0;
		}
		length = b.length;
		stroka = new char[b.length];
		for (int i = 0; i < b.length; i++)
		{
			stroka[i] = b.stroka[i];
		}
	}
	
};


