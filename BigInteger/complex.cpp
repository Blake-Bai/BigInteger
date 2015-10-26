#ifndef COMPLEX_H
#define COMPLEX_H
#include "complex.h"
complex::complex()
{
}
void complex::initial(double real_, double im_)
{
	real = real_;
	im = im_;
}

complex::~complex()
{
}

complex complex::add(complex a)
{
	complex res;
	res.real = real + a.real;
	res.im = im + a.im;
	return res;
}
complex complex::minus(complex a)
{
	complex res;
	res.real = real - a.real;
	res.im = im - a.im;
	return res;
}
complex complex::num_multi(double s)
{
	complex res;
	res.real = real*s;
	res.im = im*s;
	return res;
}
complex complex::multiply(complex a)
{
	complex res;
	res.real = real*a.real - im*a.im;
	res.im = im*a.real + real*a.im;
	return res;
}
void complex::print_result()
{
	printf("%f + %f i\n", real, im);
}

#endif