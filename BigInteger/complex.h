#include<stdio.h>
class complex
{
public:
	complex();
	~complex();
	void initial(double real_, double im_);
public:
	complex add(complex b);
	complex minus(complex b);
	complex multiply(complex b);
	complex num_multi(double s);

	void update_Real(double real_)
	{
		real = real_;
	}
	void update_im(double im_)
	{
		im = im_;
	}
	void print_result();
private:
	double real;
	double im;
};
