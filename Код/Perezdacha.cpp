// Perezdacha.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Class.h"
#include <iostream>
#include <string>

using namespace std;


int main()
{
	setlocale(0, "");
	Class First, F2;
	First.in();
	First.out();
	First.save("text.txt");
	//F2.load("text.txt");
	//F2.out();
	system("pause");
    return 0;
}

