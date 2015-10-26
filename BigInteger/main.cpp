#include "BigInteger.h"
#include<iostream>
#include<fstream>

#define _CRTDBG_MAP_ALLOC

#include <stdlib.h>
#include <crtdbg.h>
#include<windows.h>
#pragma comment(lib,"winmm.lib")

void read_from_file(char *&a,char*&b,int &digits_a,int &digits_b,char &oper)
{
	int max_length;
	FILE* read;
	//long offet;
	read=fopen("data.txt","r");
	if(read!=NULL)
	{
	fseek(read,0,SEEK_END);
	max_length=ftell(read)-2*2;
	//cout<<max_length<<endl;
	char *operator_buffer=new char[3];
	a=new char[max_length];
	b=new char[max_length];
	memset(a,'0',max_length);
	memset(b,'0',max_length);
	rewind(read);
	if(fgets(operator_buffer,3,read)!=NULL)
	{
		oper=operator_buffer[0];
	}
	char *gets_status;
	gets_status=fgets(a,max_length,read);
	digits_a=strlen(a)-1;
	a[digits_a]='0';
	gets_status=fgets(b,max_length,read);
	//solve 2 situations:whether there is a \n before EOF,also we can say whether the last line is nothing
	//for example:3numbers
	//\n :  strlen=3,no \0 str[3]=0
	//no \n:  strlen=4,has \0  str[3]=\0 str[4]=0
	if(b[strlen(b)-1]-'0'==-38)
	{
		digits_b=strlen(b)-1;
		b[digits_b]='0';b[digits_b+1]='0';
	}
	else
	{
		digits_b=strlen(b);
		b[digits_b]='0';
	}
	fclose(read);
	delete[]operator_buffer;
	}
}

int main()
{
	////test_code,initialize here
	//int digit1 =6000;
	//int digit2 = 10;
	//char *a = new char[digit1];
	//char *b = new char[digit2];
	//a[0] = '9'; b[0] = '9';	for (int i = 1; i < digit1; ++i)a[i] = rand() % 10 + '0';for (int i = 1; i < digit2; ++i)b[i]=rand() % 10+'0';
	//char operator_;
	//cin >> operator_;

	//real code ,read from file
	char operator_;
	char *a;
	char *b;
	int digits_a;
	int digits_b;
	read_from_file(a,b,digits_a,digits_b,operator_);


	BigInteger Ba = BigInteger(a, digits_a);
	BigInteger Bb = BigInteger(b, digits_b);
	BigInteger Bc;
	BigInteger remainder;
	DWORD t1, t2;
	Ba.Print_result();
	Bb.Print_result();
	t1 = timeGetTime();

	switch (operator_)
	{
		case '+':
			Bc = Ba.add(Bb,0);
			Bc.Print_result();
			break;
		case '-':
			Bc = Ba.minus(Bb);
			Bc.Print_result();
			break;
		case '*':
			Bc = Ba.multi_byfft(Bb);
			//Bc = Ba.multiply_external(Bb);
			//Bc.Print_result();
			break;
		case '/':
			Bc = Ba.divide(Bb, remainder);
			remainder.Clear();
			break;
		default:
			cout << "operator input error!" << endl;
			return 0;
	}
	t2 = timeGetTime();
	cout << endl <<"time:"<< (t2 - t1)*1.0 <<"ms"<< endl;
//	Ba.Clear();
	Bb.Clear();
	//Bc.Clear();
	//_CrtDumpMemoryLeaks();
	return 0;




}
