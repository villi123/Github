#include "stdafx.h"
#include "text.h"
#include <string>
#include <iostream>
#include <fstream>


text::text()
{
	stroka = new char[0];
	length = 0;
}
text::text(const text &a) // конструктор, принимающий на вход class text
{
	length = a.length;
	stroka = new char[length];
	for (int i = 0; i < length; i++) // переносим элементы из одного класса в другой
	{
		stroka[i] = a.stroka[i];
	}
}
void text::clear() 
{
	delete[] stroka;
	length = 0;
	//stroka = new char[0];
}
void text::add(text temp)
{
	text a;
	a.stroka = stroka;
	delete[] stroka;
	length += temp.length;
	stroka = new char[length];
	for (int i = 0; i < a.length; i++) 
	{
		stroka[i] = a.stroka[i];
	}
	for (int i = a.length, j = 0; i < length; i++, j++)
	{
		stroka[i] = temp.stroka[j];
	}
	
}

void text::insert(int point, char *temp)
{
	int ln = 0;
	for (int i = 0; temp[i] != 0; i++)
	{
		ln = i + 1;
	}
	text a;
	a.stroka = stroka;
	delete[] stroka;
	length += ln;
	stroka = new char[length];
	for (int i = 0; i < point; i++)
	{
		stroka[i] = a.stroka[i];
	}
	for (int i = point, j = 0; i < point + ln; i++, j++)
	{
		stroka[i] = temp[j];
	}
	for (int i = point + ln, j = point; i < length; i++,j++)
	{
		stroka[i] = a.stroka[j];
	}
}

void text::cut(int point, int size) {
	if (point < length)
	{
		if (point < 0)
		{
			point = 0;
		}
		text a;
		if (point + size < length)
		{
			a.stroka = new char[length - size];
			a.length = length - size;
			for (int i = 0, j = 0; i < length - size; i++, j++)
			{
				if (j == point)
					j = point + size;
				a.stroka[i] = stroka[j];
			}
		}
		else
		{
			a.stroka = new char[point];
			a.length = point;
			for (int i = 0; i < point; i++)
			{
				a.stroka[i] = stroka[i];
			}
		}
		delete[] stroka;
		stroka = new char[a.length];
		stroka = a.stroka;
	}
}

text::text(char *temp)
{
	for (int i = 0; temp[i] != 0; i++)
	{
		length = i+1;
	}
	stroka = new char[length];
	for(int i = 0; i < length; i++)
	{
		stroka[i] = temp[i];
	}
}
text::text(std::string temp)
{
	length = temp.length();
	stroka = new char[length];
	for (int i = 0; i < length; i++)
	{
		stroka[i] = temp[i];
	}
}

text::~text()
{
	//if (length != 0)
	//{
		//delete[] stroka;
	//}
}


void text::save(char * t)
{
	std::fstream f_out;
	f_out.open(t/*переменная t - имя нашего файла*/,
		std::fstream::out /*out - запись*/| std::fstream::trunc/*затирание - создание файла, если его нет*/ | std::fstream::binary/*использование спец. символов*/);
	f_out.write(stroka, length);
	f_out.close();
}
void text::load(char * t)
{
	if ( length > 0)
		delete[] stroka;
	std::fstream f_out;
	f_out.open(t, 
		std::fstream::in/*чтение из файла*/ | std::fstream::binary);
	char buf[1000];
	f_out.read(buf, 999);
	for (int i = 0; buf[i] !=-52; i++)
	{
		length = i+1;
	}
	
	stroka = new char[length];
	for (int i = 0; i < length; i++)
	{
		stroka[i] = buf[i];
	}
	f_out.close();
}