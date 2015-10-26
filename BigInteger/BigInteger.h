#pragma once
#include<iostream>
#include<vector>
using namespace std;
using std::vector;
class BigInteger
{
public:
	BigInteger();
	~BigInteger();
	BigInteger(char *a, int &digits);
	void Clear();
	void Print_result();   
	BigInteger add(BigInteger a,int multi_maxlength);
	BigInteger minus(BigInteger a);

	void directly_multiply(BigInteger a, BigInteger &res);
	BigInteger multiply_external(BigInteger a);
	BigInteger multiply(BigInteger a,int maxlength);
	BigInteger multiply_nto1(char b,int max_length);

	BigInteger BigInteger::multi_byfft(BigInteger a);

	BigInteger divide(BigInteger a,BigInteger &remainder);

	int compare( BigInteger b);   //1 for bigger 0 for equal -1 for smaller
	void diff_digits_sumoper(BigInteger *a, char * &sum_, int &id, int &addition);
	void diff_digits_minusoper(BigInteger *a, char *&dif_, int &id, int &addition);

	//multiply
	BigInteger BigInteger::extract_part(int from_id, int to_id);

	void infer_quotient(BigInteger &remainder,BigInteger b, int &quotient);
	void BigInteger::div_offsetzero(BigInteger small, BigInteger *denominator, int nzero);
	void BigInteger::multi_offsetzero(BigInteger small, BigInteger *big, int nzero);
		//a>b && a<b*10
private:
	char *data;
	int start_id;
	int digits;
};

