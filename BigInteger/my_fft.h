#ifndef COMPLEX_H
#define COMPLEX_H
#include "complex.h"
#include<cmath>
#include<iostream>
using namespace std;
#define PI 3.1415926535897932384
complex compute_w(int &n, int &k)
{
	double exp_;
	exp_ = (2 * PI*k) / n;
	complex res;
	res.initial(cos(exp_), sin(exp_));
	return res;
}
void FFT(complex * &y, int y_length, complex * &Fy)
{
	if (y_length == 1)
	{
		Fy = y;
		return;
	}
	else
	{
		int length = y_length / 2;
		complex* z1 = new complex[length];
		complex* z2 = new complex[length];
		for (int i = 0; i < length; ++i)
		{
			z1[i] = y[2 * i];
			z2[i] = y[2 * i + 1];
		}
		complex *fz1 = new complex;
		complex *fz2 = new complex;
		FFT(z1, length, fz1);
		FFT(z2, length, fz2);
		complex *res = new complex[y_length];
		complex w;
		for (int i = 0; i < length; ++i)
		{
			int i_ = 0 - i;
			w = compute_w(y_length, i_);
			complex tmp = w.multiply(fz2[i]);
			res[i] = fz1[i].add(tmp);
			res[i + length] = fz1[i].minus(tmp);
		}
		delete[]z1; z1 = NULL;
		delete[]z2; z2 = NULL;
		if (length != 1)
		{
			delete[]fz1; fz1 = NULL;
			delete[]fz2; fz2 = NULL;
		}
		Fy = res;
		return;
	}
}
void IFFT(complex * &fy, int fy_length, complex *&y)
{
	if (fy_length == 1)
	{
		y = fy;
		return;
	}
	else
	{
		int length = fy_length / 2;
		complex* fz1 = new complex[length];
		complex* fz2 = new complex[length];
		for (int i = 0; i < length; ++i)
		{
			fz1[i] = fy[2 * i];
			fz2[i] = fy[2 * i + 1];
		}
		complex *z1 = new complex;
		complex *z2 = new complex;
		IFFT(fz1, length, z1);
		IFFT(fz2, length, z2);
		complex *res = new complex[fy_length];
		complex w;
		for (int i = 0; i < length; ++i)
		{
			w = compute_w(fy_length, i);
			complex tmp = w.multiply(z2[i]);
			res[i] = (z1[i].add(tmp)).num_multi(0.5);
			res[i + length] = (z1[i].minus(tmp)).num_multi(0.5);
		}
		if (length != 1)
		{
			delete[]z1; z1 = NULL;
			delete[]z2; z2 = NULL;
		}
		delete[]fz1; fz1 = NULL;
		delete[]fz2; fz2 = NULL;
		y = res;
		return;
	}
}

//int main()
//{
//	int digits = 8;
//	complex *y = new complex[digits];
//	//	y[0].initial(1, 2);
//	//y[1].initial(3, 4);
//	//complex ttest = y[0].multiply(y[1]);
//	for (int i = 0; i < digits; ++i)
//	{
//		y[i].initial(i + 1, 0);
//		y[i].print_result();
//	}
//
//	complex *Fy = new complex;
//	complex *y_ = new complex;
//	FFT(y, digits, Fy);
//	cout << "endof fft" << endl;
//	for (int i = 0; i < digits; ++i)
//	{
//		Fy[i].print_result();
//	}
//	IFFT(Fy, digits, y_);
//	printf("\n");
//	for (int i = 0; i < digits; ++i)
//	{
//		y_[i].print_result();
//	}
//	return 0;
//}

#endif