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
	First.save("text.txt"); // загружаем в файл
	F2.load("text.txt"); // загружаем из файла
	F2.change(F2.Name); // меняем имя в F2
	F2.out();

	system("pause");
    return 0;
}

