#ifndef COMPLEX_OPER_H
#define COMPLEX_OPER_H
#include "complex_oper.h"
#include<cmath>
#define PI 3.141592653
complex compute_w(int &n,int &k)
{
	complex res;
	double exp_ = 2 * PI*k / n;
	res.real = cos(exp_);
	res.im = sin(exp_);
	return res;
}
void FFT(complex *y,)

#endif