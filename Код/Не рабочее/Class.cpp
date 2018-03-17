#include "stdafx.h"
#include "Class.h"
#include <iostream>
#include <string>
#include <fstream>
#include <openssl/conf.h> // функции, структуры и константы настройки OpenSSL
#include "../include/openssl/conf.h"
#include <openssl/evp.h> // сами криптографические функции
#include <openssl/err.h> // коды внутренних ошибок OpenSSL и их расшифровка
#include <openssl/aes.h>

using namespace std;

Class::Class()
{
}


Class::~Class()
{
}


void Class::in() // первый ввод
{
	//setlocale(0, "");
	cout << "Введите Фамилию\n";
	cin >> FamilyName;
	cout << "Введите Имя\n";
	cin >> Name;
	cout << "Введите 10-значный номер паспорта\n";
	cin >> Pasport;
}

void Class::out() // вывод
{
	//setlocale(0, "");
	cout <<"Фамилия: "<< FamilyName << endl;
	cout << "Имя: " << Name << endl;
	cout << "№ паспорта: " << Pasport << endl << endl;
}

const char * Class::preobr( string str) 
{
	//setlocale(0, "");
	char buf[1000];
	for (int i = 0; i < str.length(); i++)
	{
		buf[i] = str[i];
	}
	buf[str.length()] = ' ';
	return buf;
}
unsigned char * Class::preobr2(string str)
{
	//setlocale(0, "");
	unsigned char buf[1000];
	for (int i = 0; i < str.length(); i++)
	{
		buf[i] = str[i];
	}
	buf[str.length()] = ' ';
	return buf;
}

void Class::save(char * t )// сохранить в файл с именем t
{
	fstream f_out;
	f_out.open(t/*переменная t - имя нашего файла*/,
		std::fstream::out /*out - запись*/ | std::fstream::trunc/*затирание - создание файла, если его нет*/ | std::fstream::binary/*использование спец. символов*/);
	f_out.write(" ", 1); // без этого неверно отображается в файле
	f_out.write(preobr(FamilyName), FamilyName.length());
	f_out.write(" ", 1); // без этого неверно отображается в файле
	f_out.write(preobr(Name), Name.length());
	f_out.write(" ", 1); // без этого неверно отображается в файле
	f_out.write(preobr(Pasport), Pasport.length());
	f_out.write("\n", 1);
	f_out.close();
}

void Class::load(char * t)
{
	std::fstream f_out;
	f_out.open(t,
		std::fstream::in | std::fstream::binary);

	char buf[1000];
	f_out.read(buf, 999);
	//string bufstr;
	char str1[1000] = {};
	char str2[1000] = {};
	char str3[1000] = {};
	int length = 0;
	int i = 1;
	for (int j = 0; i < 999 && buf[i] != NULL && buf[i] != ' ';j++, i++)
	{	
		str1[j] = buf[i];
	}
	FamilyName = str1;
	i++;
	for (int j = 0; i < 999 && buf[i] != NULL && buf[i] != ' '; j++, i++)
	{
		str2[j] = buf[i];
	}
	Name = str2;
	i++;
	for (int j = 0; i < 999 && buf[i] != NULL && buf[i] != ' '; j++, i++)
	{
		str3[j] = buf[i];
	}
	 Pasport = str3;

	f_out.close();
}

void Class::saveen(char * t)// сохранить в файл с именем t
{
	fstream f_out;
	f_out.open(t/*переменная t - имя нашего файла*/,
		std::fstream::out /*out - запись*/ | std::fstream::trunc/*затирание - создание файла, если его нет*/ | std::fstream::binary/*использование спец. символов*/);
	f_out.write("", 1); // без этого неверно отображается в файле
	f_out.write(encrypt(FamilyName), FamilyName.length());
	f_out.write(" ", 1);
	f_out.write(encrypt(Name), Name.length());
	f_out.write(" ", 1);
	f_out.write(encrypt(Pasport), Pasport.length() );
	f_out.write(" ", 1);
	f_out.write("\n", 1);
	f_out.close();
}

void Class::loadde(char * t)
{
	std::fstream f_out;
	f_out.open(t,
		std::fstream::in | std::fstream::binary);
	
	char buf[1000] = {};
	unsigned char buf1[1000] = {};
	unsigned char buf2[1000] = {};
	unsigned char buf3[1000] = {};
	f_out.read(buf, 999);
	//char buf[1000];
	//char * buf = decrypt((unsigned char*)buf2);
	//string bufstr;
	
	int length = 0;
	int i = 1;
	for (int j = 0; i < 999 && buf[i] != NULL && buf[i] != ' '; j++, i++)
	{
		buf1[j] = (unsigned char)buf[i];
	}
	i++;
	for (int j = 0; i < 999 && buf[i] != NULL && buf[i] != ' '; j++, i++)
	{
		buf2[j] = (unsigned char)buf[i];
	}
	i++;
	for (int j = 0; i < 999 && buf[i] != NULL && buf[i] != ' '; j++, i++)
	{
		buf3[j] = (unsigned char)buf[i];
	}
	char * str1 = decrypt(buf1);
	char * str2 = decrypt(buf2);
	char * str3 = decrypt(buf3);
	for (int k = 0; buf1[k]; k++)
	{
		cout << buf1[k];
	}
	cout << endl;
	for (int k = 0; str1[k]; k++)
	{
		cout << str1[k];
	}
	cout << endl;
	FamilyName = str1;
	Name = str2;
	Pasport = str3;
	f_out.close();
}


void Class::change(string & str)
{
	cin >> str;
}



char * Class::encrypt(string a)
{
	char buf[1000] = {};
	unsigned char *plaintext = preobr2(a);// исходный текст
	int plaintext_len = a.length(); // длина текста
	unsigned char *key = (unsigned char *)"0123456789"; // пароль (ключ)
	unsigned char *iv = (unsigned char *)"0123456789012345";// инициализирующий вектор, рандомайзер
	unsigned char cryptedtext[256]; // зашифрованный результат

									  // 1. Создаётся указатель на несуществующую структуру
									  // структура - тип данных в C++, близка к КЛАССУ, различия минимальны
	EVP_CIPHER_CTX *ctx; // structure

						 // 2. Для указателя создаётся пустая структура настроек (метод, ключ, вектор инициализации и т.д.)
	ctx = EVP_CIPHER_CTX_new(); // создание структуры с настройками метода

								// 3. Структура EVP_CIPHER_CTX заполняется настройками
	EVP_EncryptInit_ex(ctx, // ссылка на объект/структуру, куда заносятся параметры
		EVP_aes_256_cbc(), // ссылка на шифрующее ядро AES 256 (функцию с алгоритмом)
		NULL,
		key, // ключ/пароль/секрет
		iv); // рандомайзер (случайный начальный вектор)

			 // 4. САМ ПРОЦЕСС ШИФРОВАНИЯ - ФУКНЦИЯ EVP_EncryptUpdate
	int len;
	EVP_EncryptUpdate(ctx, // объект с настройками
		cryptedtext, // входной параметр: ссылка, куда помещать зашифрованные данные
		&len, // выходной параметр: длина полученного шифра
		plaintext, // входной параметр: что шифровать
		plaintext_len); // входной параметр : длина входных данных
	int cryptedtext_len = len;

	// 5. Финализация процесса шифрования
	// необходима, если последний блок заполнен данными не полностью
	EVP_EncryptFinal_ex(ctx, cryptedtext + len, &len);
	cryptedtext_len += len;

	// 6. Удаление структуры
	EVP_CIPHER_CTX_free(ctx);
	/*
	// вывод зашифрованных данных
	for (int i = 0; i < cryptedtext_len; i++)
	{
		std::cout << std::hex << cryptedtext[i];
		if ((i + 1) % 32 == 0) std::cout << std::endl;
	}
	std::cout << std::endl;
	*/
	return (char*)(cryptedtext);
}


char * Class::decrypt(unsigned char * a)
{
	EVP_CIPHER_CTX *ctx;
	ctx = EVP_CIPHER_CTX_new();
	char buf[256] = {};
	unsigned char *cryptedtext = a;// исходный текст
	int cryptedtext_len = strlen((char *)cryptedtext); // длина текста
	unsigned char *key = (unsigned char *)"0123456789"; // пароль (ключ)
	unsigned char *iv = (unsigned char *)"0123456789012345";// инициализирующий вектор, рандомайзер
															//unsigned char [256] = plaintext; // зашифрованный результат
	unsigned char decryptedtext[256] = {}; // расшифрованный результат
									  // 2. Для указателя создаётся пустая структура настроек (метод, ключ, вектор инициализации и т.д.)
	ctx = EVP_CIPHER_CTX_new(); // создание структуры с настройками метода

	EVP_DecryptInit_ex(ctx, // ссылка на объект/структуру, куда заносятся параметры
		EVP_aes_256_cbc(), // ссылка на шифрующее ядро AES 256 (функцию с алгоритмом)
		NULL,
		key, // ключ/пароль/секрет
		iv);// рандомайзер (случайный начальный вектор)
			// 4. САМ ПРОЦЕСС РАШИФРОВАНИЯ - ФУКНЦИЯ EVP_DecryptUpdate
			//int len;
	int len = 0;
	EVP_DecryptUpdate(ctx,
		decryptedtext, // входной параметр : ссылка, куда помещать расашифрованные данные
		&len, // выходной параметр: длина полученного шифра
		cryptedtext,// входной параметр: что расшифровать
		cryptedtext_len // входной параметр : длина входных данных
	);
	int decryptedtext_len = len;
	/*
	// 5. Финализация процесса расшифрования
	// необходима, если последний блок заполнен данными не полностью
	EVP_EncryptFinal_ex(ctx, cryptedtext + len, &len);
	cryptedtext_len += len;
	*/
	EVP_DecryptFinal_ex(ctx, decryptedtext + len, &len);
	decryptedtext_len += len;

	// 6. Удаление структуры
	EVP_CIPHER_CTX_free(ctx);

	// вывод зашифрованных данных
	for (int i = 0; i < decryptedtext_len; i++)
	{
		std::cout << std::hex << decryptedtext[i];
		if ((i + 1) % 32 == 0) std::cout << std::endl;
	}
	std::cout << std::endl;
	return (char*)(decryptedtext);
}

/*
void Class::saveencrypt(char * t)
{
	EVP_CIPHER_CTX *ctx; // structure

						 // 2. Для указателя создаётся пустая структура настроек (метод, ключ, вектор инициализации и т.д.)
	ctx = EVP_CIPHER_CTX_new(); // создание структуры с настройками метода
	// —- шифрование файла
	// производится точно так же, но порциями, в цикле
	std::fstream f0, f_enctypted, f_decrypted;
	f0.open("f0.txt", std::fstream::in | std::fstream::binary); // файл с исходными данными

																// файл для зашифрованных данных
	f_enctypted.open("f_enctypted.txt",
		std::fstream::out | std::fstream::trunc | std::fstream::binary);

	char buffer[256] = { 0 };
	char out_buf[256] = { 0 };

	ctx = EVP_CIPHER_CTX_new();
	EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv);
	len = 0;
	f0.read(buffer, 256);
	while (f0.gcount() > 0) // цикл, пока из файла что-то считывается (пока размер считанной порции > 0)
	{
		// шифрование порции
		EVP_EncryptUpdate(ctx, // объект с настройками
			(unsigned char *)out_buf, // входной параметр: ссылка, куда помещать зашифрованные данные
			&len, // выходной параметр: длина полученного шифра
			(unsigned char *)buffer, // входной параметр: что шифровать
			f0.gcount()); // входной параметр : длина входных данных

						  // вывод зашифрованной порции в файл
		f_enctypted.write(out_buf, len);

		// считывание следующей порции
		f0.read(buffer, 256);
	}
	EVP_EncryptFinal_ex(ctx, (unsigned char *)out_buf, &len);
	f_enctypted.write(out_buf, len);
	f_enctypted.close();
	f0.close();
	EVP_CIPHER_CTX_free(ctx);

}

void Class::loaddecrypt(char * t)
{

}
*/