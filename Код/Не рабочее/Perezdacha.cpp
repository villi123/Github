// Perezdacha.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Class.h"
#include <iostream>
#include <string>
#include <openssl/conf.h> // функции, структуры и константы настройки OpenSSL
#include "../include/openssl/conf.h"
#include <openssl/evp.h> // сами криптографические функции
#include <openssl/err.h> // коды внутренних ошибок OpenSSL и их расшифровка
#include <openssl/aes.h>

using namespace std;


int main()
{
	setlocale(0, "");
	Class First, F2, F3;
	First.in();
	First.out();
	First.save("text.txt"); // загружаем в файл
	F2.load("text.txt"); // загружаем из файла
	F2.change(F2.Name); // меняем имя в F2
	F2.out();
	F2.saveen("text1.txt");
	F3.loadde("text1.txt");
	F3.out();
	system("pause");
    return 0;
}

