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
	int h;
	setlocale(0, "");
	Class First, F2, F3;
	//First.in();
	////F2.saveen("text1.txt");
	////F3.loadde("text1.txt");
	////F3.out();
	First.in();
	cout << "Vubery deystvie: " << endl
		<< "1. Proverka imeni i familii" << endl
		<< "2. Proverka pasporta" << endl;
	cin >> h;
	if (h == 1)
	{
	
		bool pr = true;
		for (int i = 0; i < First.FamilyName.length(); i++)
		{
			if (isalpha(First.FamilyName[i]) && isalpha(First.Name[i]))
			{
			}
			else
			{
				pr = false;
				cout << "Dannue vvedenu ne verno. Vvedite ih zanovo." << endl;
				break;
			}
		}
	}
	if (h == 2)
	{
		bool pr = true;
		if (First.Pasport.length() == 10) {
			for (int i = 0; i < 10; i++)
			{
				if (First.Pasport[i] <'0' || First.Pasport[i] >'9') {
					pr = false;
					break;
				}
			}
		}
		else
			pr = false;
		
	}

	First.out();
	First.save("text.txt"); // загружаем в файл
	F2.load("text.txt"); // загружаем из файла
	F2.change(F2.Name); // меняем имя в F2
	F2.out();
	system("pause");
    return 0;
}

