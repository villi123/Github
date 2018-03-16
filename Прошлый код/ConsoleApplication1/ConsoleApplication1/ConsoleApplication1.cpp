
#include "stdafx.h"
#include "text.h"
#include <iostream>
#include <string>
#define cout std::cout

text operator + (text a, text b)
{
	a.add(b);
	return a;
}
std::ostream & operator << (std::ostream &os, text a)
{
	for (int i = 0; i < a.length; i++)
	{
		os << a.stroka[i];
		//cout << a.stroka[i];
	}
	return os;
}


int main()
{
	std::string p;
	std::cin >> p;
	text a = "string";
	text b = a;
	b.clear();
	//b = a;
	a = p;
	cout << a;
	
	a.save("f_out.txt");
	text c;
	c.load("f_out.txt");
	int l = c.stroka[8];
	cout << "\n" << c;
	system("pause");
    return 0;
}

