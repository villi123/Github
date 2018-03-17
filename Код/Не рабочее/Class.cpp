#include "stdafx.h"
#include "Class.h"
#include <iostream>
#include <string>
#include <fstream>
#include <openssl/conf.h> // �������, ��������� � ��������� ��������� OpenSSL
#include "../include/openssl/conf.h"
#include <openssl/evp.h> // ���� ����������������� �������
#include <openssl/err.h> // ���� ���������� ������ OpenSSL � �� �����������
#include <openssl/aes.h>

using namespace std;

Class::Class()
{
}


Class::~Class()
{
}


void Class::in() // ������ ����
{
	//setlocale(0, "");
	cout << "������� �������\n";
	cin >> FamilyName;
	cout << "������� ���\n";
	cin >> Name;
	cout << "������� 10-������� ����� ��������\n";
	cin >> Pasport;
}

void Class::out() // �����
{
	//setlocale(0, "");
	cout <<"�������: "<< FamilyName << endl;
	cout << "���: " << Name << endl;
	cout << "� ��������: " << Pasport << endl << endl;
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

void Class::save(char * t )// ��������� � ���� � ������ t
{
	fstream f_out;
	f_out.open(t/*���������� t - ��� ������ �����*/,
		std::fstream::out /*out - ������*/ | std::fstream::trunc/*��������� - �������� �����, ���� ��� ���*/ | std::fstream::binary/*������������� ����. ��������*/);
	f_out.write(" ", 1); // ��� ����� ������� ������������ � �����
	f_out.write(preobr(FamilyName), FamilyName.length());
	f_out.write(" ", 1); // ��� ����� ������� ������������ � �����
	f_out.write(preobr(Name), Name.length());
	f_out.write(" ", 1); // ��� ����� ������� ������������ � �����
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

void Class::saveen(char * t)// ��������� � ���� � ������ t
{
	fstream f_out;
	f_out.open(t/*���������� t - ��� ������ �����*/,
		std::fstream::out /*out - ������*/ | std::fstream::trunc/*��������� - �������� �����, ���� ��� ���*/ | std::fstream::binary/*������������� ����. ��������*/);
	f_out.write("", 1); // ��� ����� ������� ������������ � �����
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
	unsigned char *plaintext = preobr2(a);// �������� �����
	int plaintext_len = a.length(); // ����� ������
	unsigned char *key = (unsigned char *)"0123456789"; // ������ (����)
	unsigned char *iv = (unsigned char *)"0123456789012345";// ���������������� ������, �����������
	unsigned char cryptedtext[256]; // ������������� ���������

									  // 1. �������� ��������� �� �������������� ���������
									  // ��������� - ��� ������ � C++, ������ � ������, �������� ����������
	EVP_CIPHER_CTX *ctx; // structure

						 // 2. ��� ��������� �������� ������ ��������� �������� (�����, ����, ������ ������������� � �.�.)
	ctx = EVP_CIPHER_CTX_new(); // �������� ��������� � ����������� ������

								// 3. ��������� EVP_CIPHER_CTX ����������� �����������
	EVP_EncryptInit_ex(ctx, // ������ �� ������/���������, ���� ��������� ���������
		EVP_aes_256_cbc(), // ������ �� ��������� ���� AES 256 (������� � ����������)
		NULL,
		key, // ����/������/������
		iv); // ����������� (��������� ��������� ������)

			 // 4. ��� ������� ���������� - ������� EVP_EncryptUpdate
	int len;
	EVP_EncryptUpdate(ctx, // ������ � �����������
		cryptedtext, // ������� ��������: ������, ���� �������� ������������� ������
		&len, // �������� ��������: ����� ����������� �����
		plaintext, // ������� ��������: ��� ���������
		plaintext_len); // ������� �������� : ����� ������� ������
	int cryptedtext_len = len;

	// 5. ����������� �������� ����������
	// ����������, ���� ��������� ���� �������� ������� �� ���������
	EVP_EncryptFinal_ex(ctx, cryptedtext + len, &len);
	cryptedtext_len += len;

	// 6. �������� ���������
	EVP_CIPHER_CTX_free(ctx);
	/*
	// ����� ������������� ������
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
	unsigned char *cryptedtext = a;// �������� �����
	int cryptedtext_len = strlen((char *)cryptedtext); // ����� ������
	unsigned char *key = (unsigned char *)"0123456789"; // ������ (����)
	unsigned char *iv = (unsigned char *)"0123456789012345";// ���������������� ������, �����������
															//unsigned char [256] = plaintext; // ������������� ���������
	unsigned char decryptedtext[256] = {}; // �������������� ���������
									  // 2. ��� ��������� �������� ������ ��������� �������� (�����, ����, ������ ������������� � �.�.)
	ctx = EVP_CIPHER_CTX_new(); // �������� ��������� � ����������� ������

	EVP_DecryptInit_ex(ctx, // ������ �� ������/���������, ���� ��������� ���������
		EVP_aes_256_cbc(), // ������ �� ��������� ���� AES 256 (������� � ����������)
		NULL,
		key, // ����/������/������
		iv);// ����������� (��������� ��������� ������)
			// 4. ��� ������� ������������ - ������� EVP_DecryptUpdate
			//int len;
	int len = 0;
	EVP_DecryptUpdate(ctx,
		decryptedtext, // ������� �������� : ������, ���� �������� ��������������� ������
		&len, // �������� ��������: ����� ����������� �����
		cryptedtext,// ������� ��������: ��� ������������
		cryptedtext_len // ������� �������� : ����� ������� ������
	);
	int decryptedtext_len = len;
	/*
	// 5. ����������� �������� �������������
	// ����������, ���� ��������� ���� �������� ������� �� ���������
	EVP_EncryptFinal_ex(ctx, cryptedtext + len, &len);
	cryptedtext_len += len;
	*/
	EVP_DecryptFinal_ex(ctx, decryptedtext + len, &len);
	decryptedtext_len += len;

	// 6. �������� ���������
	EVP_CIPHER_CTX_free(ctx);

	// ����� ������������� ������
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

						 // 2. ��� ��������� �������� ������ ��������� �������� (�����, ����, ������ ������������� � �.�.)
	ctx = EVP_CIPHER_CTX_new(); // �������� ��������� � ����������� ������
	// �- ���������� �����
	// ������������ ����� ��� ��, �� ��������, � �����
	std::fstream f0, f_enctypted, f_decrypted;
	f0.open("f0.txt", std::fstream::in | std::fstream::binary); // ���� � ��������� �������

																// ���� ��� ������������� ������
	f_enctypted.open("f_enctypted.txt",
		std::fstream::out | std::fstream::trunc | std::fstream::binary);

	char buffer[256] = { 0 };
	char out_buf[256] = { 0 };

	ctx = EVP_CIPHER_CTX_new();
	EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv);
	len = 0;
	f0.read(buffer, 256);
	while (f0.gcount() > 0) // ����, ���� �� ����� ���-�� ����������� (���� ������ ��������� ������ > 0)
	{
		// ���������� ������
		EVP_EncryptUpdate(ctx, // ������ � �����������
			(unsigned char *)out_buf, // ������� ��������: ������, ���� �������� ������������� ������
			&len, // �������� ��������: ����� ����������� �����
			(unsigned char *)buffer, // ������� ��������: ��� ���������
			f0.gcount()); // ������� �������� : ����� ������� ������

						  // ����� ������������� ������ � ����
		f_enctypted.write(out_buf, len);

		// ���������� ��������� ������
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