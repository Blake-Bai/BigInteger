#include "BigInteger.h"
#include "my_fft.h"

BigInteger::BigInteger()
{
}
BigInteger::BigInteger(char *a, int &digits_)
{
	start_id = 0;
	digits = digits_;
	data = a;
}

BigInteger::~BigInteger()
{
}
void BigInteger::Clear()
{
	if (data != NULL)
	{
		delete[]data;
		data = NULL;
	}
}
void BigInteger::Print_result()
{
	if (digits - start_id > 0)
	{
		for (int i = start_id; i < digits; ++i)cout << data[i] - '0';
	}
	else
	{
		cout << "0";
	}
	cout << endl;
}
BigInteger BigInteger::add(BigInteger a,int multi_maxlength)
{
	BigInteger res;
	int id1 = this->digits;
	int this_length = id1 - start_id;
	int id2 = a.digits;
	int a_length = id2 - a.start_id;
	char *d1 = this->data;
	char *d2 = a.data;
	res.digits = ((this_length > a_length) ? this_length : a_length )+1;
	if (multi_maxlength == 0)
	{
		res.data = new char[res.digits];
	}
	else
	{
		res.data = new char[multi_maxlength];
		memset(res.data, '0', multi_maxlength);
	}
	char *sum_ = res.data + res.digits - 1;
	--id1; --id2;
	int addition = 0;
	int digit_sum = 0;
	int sum = 0;
	while (id1 >= start_id && id2 >= a.start_id)
	{
		sum = (d1[id1] - '0') + (d2[id2] - '0') + addition;
		addition = sum / 10;
		digit_sum = sum % 10;
		*sum_ = digit_sum + '0';
		--sum_;
		--id1;
		--id2;
	}
	if (id1 ==  start_id-1&& id2 == a.start_id-1)
	{
		if (addition != 0)
		{
			*sum_ = addition + '0';
			--sum_;
		}
	}
	else if (id1 == start_id-1)
	{
		diff_digits_sumoper(&a, sum_,  id2, addition);
	}
	else
	{
		diff_digits_sumoper(this, sum_,  id1, addition);
	}
	res.start_id = (sum_ - res.data) +1;
	//cout << "add" << endl;
	//res.Print_result();
	return res;
}
BigInteger BigInteger::minus(BigInteger a)
{
	BigInteger res;
	int id1 = this->digits;
	int big_startid = this->start_id;
	int id2 = a.digits;
	char *d1 = this->data;
	char *d2 = a.data;
	res.digits = id1 - this->start_id;
	res.data = new char[res.digits];
	char *dif_ = res.data + res.digits - 1;
	--id1; --id2;
	int addition = 0;
	int digit_dif = 0;
	int dif = 0;

	while (id1 >=big_startid  && id2 >=0 )
	{
		dif = (d1[id1] - '0') - (d2[id2] - '0') + addition;
		if (dif < 0)
		{
			addition = -1;
			digit_dif = dif + 10;
		}
		else
		{
			addition = 0;
			digit_dif = dif;
		}
		*dif_ = digit_dif + '0';
		--dif_;
		--id1;
		--id2;
	}
	//test
	if (id1 == big_startid-1 && id2 == -1)
	{
		if (addition != 0)cout << "id1id2-1 error" << endl;
	}
	//test
	if (id1 == big_startid-1 && id2!=-1)cout << "id1-1 error" << endl;
	//we only have id2==-1 because a is always the smaller one
	if(id1!=big_startid-1 && id2==-1)diff_digits_minusoper(this, dif_, id1, addition);
	++dif_;
	res.start_id = dif_ - res.data;
	//if ((*dif_ - '0' )== 0 &&res.start_id<res.digits-1)++res.start_id;
	while (int(res.data[res.start_id] - '0') == 0)
	{
		res.start_id++;
	}
	//cout << "minus" << endl;
	//res.Print_result();
	return res;
}
void BigInteger::diff_digits_sumoper(BigInteger *a, char *&sum_, int &id, int &addition)
{
	int sum = 0;
	int digit_sum = 0;
	int a_startid = a->start_id;
	while (id >= a_startid)
	{
		if (addition == 0)
		{
			while (id >= a_startid)
			{
				*sum_ = a->data[id];
				--sum_;
				--id;
			}
			break;
		}
		else
		{
			sum = (a->data[id] - '0') + addition;
			addition = sum / 10;
			digit_sum = sum % 10;
			*sum_= digit_sum + '0';
			--sum_;
			--id;
		}
	}
	if (addition != 0 && id==a_startid-1)
	{
		*sum_ = addition + '0';
		--sum_;
	}
}
void BigInteger::diff_digits_minusoper(BigInteger *a, char *&dif_, int &id, int &addition)
{
	int dif = 0;
	int digit_dif = 0;
	while (id >= a->start_id)
	{
		if (addition == 0)
		{
			while (id >=a->start_id)
			{
				*dif_= a->data[id];
				--dif_;
				--id;
			}
			break;
		}
		else
		{
			dif = (a->data[id] - '0') + addition;
			if (dif < 0)
			{
				addition = -1;
				digit_dif = dif + 10;
			}
			else
			{
				addition = 0;
				digit_dif = dif;
			}
			*dif_= digit_dif + '0';
			--dif_;
			--id;
		}
	}
}

//multiply
BigInteger BigInteger::extract_part(int from_id, int to_id)
//left close right open
{
	BigInteger res;
	res.data = data;
	res.start_id = start_id + from_id;
	res.digits = start_id + to_id;
	return res;
}
BigInteger BigInteger::multiply_nto1(char b,int max_length)
{
	int b_integer = b - '0';
	BigInteger res;
	if (b_integer == 0)
	{
		res.start_id = 0;
		res.digits = 1;
		res.data = new char[max_length];
		memset(res.data, '0', max_length);
		return res;
	}
	else
	{

		res.digits = this->digits - this->start_id + 1;
		res.data = new char[max_length];
		memset(res.data, '0', max_length);
		res.start_id = 0;
		int addition = 0;
		char *res_ = res.data;
		char *thisdata = this->data;
		int endid = this->digits - 1;
		int startid = this->start_id;
		int multiply_res = 0;
		int multiply_digit = 0;
		int res_data_id = res.digits - 1;
		for (int i = endid; i >= startid; --i)
		{
			multiply_res = (thisdata[i] - '0')*b_integer + addition;
			addition = multiply_res / 10;
			multiply_digit = multiply_res % 10;
			res_[res_data_id] = multiply_digit + '0';
			--res_data_id;
		}
		if (addition == 0)
		{
			res.start_id = 1;
		}
		else
		{
			res_[0] = addition + '0';
		}
		return res;
	}
}
void BigInteger::directly_multiply(BigInteger a,BigInteger &res)
{
	int length, a_length;
	length = digits - start_id;
	a_length = a.digits - a.start_id;
	int num = 0;
	int a_num = 0;
	char *data = new char[length];
	char *a_data = new char[a_length];
	
	for (int i = 0; i < length; ++i)data[i] = data[start_id + i];
	for (int i = 0; i < a_length; ++i)a_data[i] = a.data[a.start_id + i];
	num = atoi(data);
	a_num = atoi(a_data);
	int c = num*a_num;
	delete[]data;
	delete[]a_data;
	res.digits = length + a_length + 1;
	res.data = new char[res.digits];
	memset(res.data, '-1', res.digits);
	itoa(c, res.data,10);
	for (int i = 0; i < res.digits; ++i)
	{
		if (res.data[i] == '-1')
		{
			res.digits = i-1;
			break;
		}
	}
	res.start_id = 0;
}
BigInteger BigInteger::multiply_external(BigInteger a)
{
	int max_length = digits - start_id + a.digits - a.start_id + 1;
	//max_length *= 10000;
	return multiply(a, max_length);
}
BigInteger BigInteger::multiply(BigInteger a,int max_length)
{
	BigInteger res;

	int this_length = this->digits - this->start_id;
	int a_length = a.digits - a.start_id;
	//if (this_length < 5 && a_length < 5)
	//	//than we can compute the 2 numbers directly
	//{
	//	printf("directly*\n");
	//	this->Print_result();
	//	a.Print_result();
	//	BigInteger res;
	//	directly_multiply(a,res);
	//	res.Print_result();
	//}
	if (this_length == 1)
	{
		res = a.multiply_nto1(this->data[this->start_id],max_length);
	}
	else if (a_length == 1)
	{
		res = this->multiply_nto1(a.data[a.start_id],max_length);
	}
	else
	{
		BigInteger a1 = a.extract_part(0, a_length / 2);
		int a1_length = a1.digits - a1.start_id;
		//	printf("a1:"); a1.Print_result();
		BigInteger a0 = a.extract_part(a1_length, a_length);
		//	printf("a0:"); a0.Print_result();
		int a0_length = a0.digits - a0.start_id;
		BigInteger b1 = this->extract_part(0, this_length / 2);
	//		printf("b1:"); b1.Print_result();
		int b1_length = b1.digits - b1.start_id;
		BigInteger b0 = this->extract_part(b1_length, this_length);
		//	printf("b0:"); b0.Print_result();
		int b0_length = b0.digits - b0.start_id;
		BigInteger res_1, res_2, res_3;
		//res_1.start_id = 0; res_2.start_id = 0; res_3.start_id = 0;
		//for initial version:res_1.digits = 0; res_2.digits = 0; res_3.digits = 0;
		BigInteger res1 = a1.multiply(b1,max_length);
		//printf("res1\n"); res1.Print_result();
		BigInteger res2 = a1.multiply(b0,max_length);
	//	printf("res2\n"); res2.Print_result();
		BigInteger res3 = a0.multiply(b1,max_length);
		//printf("res3\n"); res3.Print_result();
		BigInteger res4 = a0.multiply(b0,max_length);
		//printf("res4\n"); res4.Print_result();
		div_offsetzero(res1, &res_1, a0_length + b0_length);
		if (a0_length + b0_length + res1.digits  > max_length)cout << "too long" << endl;
		//	printf("res_1\n"); res_1.Print_result();
		div_offsetzero(res2, &res_2, a0_length);
		if (a0_length  + res2.digits  > max_length)cout << "too long" << endl;
			//printf("res_2\n"); res_2.Print_result();
		div_offsetzero(res3, &res_3, b0_length);
		if (b0_length + res3.digits > max_length)cout << "too long" << endl;
			//printf("res_3\n"); res_3.Print_result();
//			printf("res_4\n"); res4.Print_result();

		BigInteger sum1, sum2;
		sum1 = res_1.add(res_2,max_length);
				//sum1.Print_result();
		sum2 = sum1.add(res_3,max_length);
				//sum2.Print_result();
		res = sum2.add(res4,max_length);
		//res.Print_result();
		//res_1.Clear();
		//res_2.Clear();
		//res_3.Clear();
		res1.Clear();
		res2.Clear();
		res3.Clear();
		res4.Clear();
		sum1.Clear();
		sum2.Clear();
	}
	return res;
}

//using fft
BigInteger BigInteger::multi_byfft(BigInteger a)
{
	//initial a1,a2,fft fomulation
	int length1 = this->digits - this->start_id;
	int length2 = a.digits - a.start_id;
	int digits_ = int(log(length1 + length2-1) / log(2)) + 1;
	printf("%d\n", digits_);
	int length = pow(2, digits_);
	complex *a1 = new complex[length];
	complex *a2 = new complex[length];
	int a1_id = length;
	int a2_id = a1_id;
	for (int i = digits - 1; i >= start_id; --i)
	{
		--a1_id;
		a1[a1_id].initial(data[i]-'0',0);
	}
	for (int i = a.digits - 1; i >= a.start_id; --i)
	{
		--a2_id;
		a2[a2_id].initial(a.data[i] - '0',0);
	}
	--a1_id; --a2_id;
	for (a1_id; a1_id >= 0; --a1_id)
	{
		a1[a1_id].initial(0, 0);
	}
	for (a2_id; a2_id >= 0; --a2_id)
	{
		a2[a2_id].initial(0, 0);
	}

	////test
	//for (int i = 0; i < length; ++i)
	//{
	//	a1[i].print_result();
	//	
	//}
	//printf("\n");
	//for (int i = 0; i < length; ++i)
	//{
	//	a2[i].print_result();

	//}
	complex *fa1=new complex;
	complex *fa2=new complex;
	FFT(a1, length, fa1);
	FFT(a2, length, fa2);
	if (a1){ delete[]a1; a1 = NULL; }
	if (a2)
	{
		delete[]a2; 
		a2 = NULL;
	}
	for (int i = 0; i < length; ++i)
	{
		fa1[i]=fa1[i].multiply(fa2[i]);
	}
	delete[]fa2; 
	fa2 = NULL;
	complex *res_ = new complex;
	IFFT(fa1, length, res_);
	for (int i = 0; i < length; ++i)
	{
		res_[i].print_result();
	}
	BigInteger res;
	return res;

}
BigInteger BigInteger::divide(BigInteger a,BigInteger &remainder)
{
	BigInteger res;
	BigInteger denominator;
	denominator.digits = 0;
	denominator.start_id = 0;
	int a_length = a.digits - a.start_id;
	//expand a to possiable biggest digits
	char *a_data = new char[digits-start_id];
	memset(a_data, '0', digits-start_id);
	for (int i = 0; i <a_length; ++i)
	{
		a_data[i] = a.data[start_id + i];
	}
	
	a.data = a_data;

	remainder.digits = this->digits;
	remainder.data = this->data;
	remainder.start_id = this->start_id;
	if (this->compare(a) >= 0)
	{
		int *nzeros = new int[this->digits];
		int *quotients = new int[this->digits];
		int id = 0;
		while (remainder.compare(a) >= 0)
		{
			int noffset = remainder.digits - remainder.start_id - a.digits;
			if (noffset > 0)
			{
				div_offsetzero(a, &denominator, noffset);
				if (remainder.compare(denominator) >= 0)
				{
					nzeros[id] = noffset;
				}
				else
				{
					--noffset;
					--denominator.digits;
					nzeros[id] = noffset;
				}
			}
			else
			{
				denominator.digits = a.digits;
				denominator.data = a.data;
				nzeros[id] = noffset;
			}
			infer_quotient(remainder, denominator, quotients[id]);
			++id;
		}
		//sum
		int digits = nzeros[0] + 1;
		res.digits = digits;
		res.start_id = 0;
		res.data = new char[res.digits];
		memset(res.data, '0', res.digits);
		for (int i = 0; i < id; ++i)
		{
			res.data[digits - 1 - nzeros[i]] = quotients[i] + '0';
		}

		delete[]nzeros;
		delete[]quotients;
	}
	else
	{
		//result is 0
		res.start_id = 0; 
		res.digits = 0;
		res.data = new char[1];
	}
	printf("shang\n");
	res.Print_result();
	printf("remainder\n");
	remainder.Print_result();
	
	return res;
}
void BigInteger::div_offsetzero(BigInteger small,BigInteger *denominator, int nzero)
{
	int small_digits = small.digits;
	int small_startid = small.start_id;
	if (small.data[small_startid] == '0')
	{
		nzero = 0;
		//if (small_digits - small_startid != 1)printf("div_offzeroerror!\n");
	}
	denominator->start_id = small.start_id;
	denominator->data = small.data;
	if (*(denominator->data+small.digits + 1) != '0')cout << "offseterror" << endl;
	denominator->digits = small.digits + nzero;

}
void BigInteger::multi_offsetzero(BigInteger small, BigInteger *big, int nzero)
{
	//if (denominator->digits > 0)
	//{
	//	delete []denominator->data;
//	}
	int small_digits = small.digits;
	int small_startid = small.start_id;
	big->start_id = 0;
	big->digits = small_digits-small_startid + nzero;
	big->data = new char[big->digits];
	memset(big->data, '0', big->digits);
	for (int i = small_startid; i <small_digits ; ++i)
	{
		big->data[i-small_startid] = small.data[i];
	}
}
void BigInteger::infer_quotient(BigInteger &remainder,BigInteger b, int &quotient)
{
	quotient = 0;
	char *pre_data = NULL;
	while (remainder.compare(b) >=0)
	{
		pre_data = remainder.data;
		remainder = remainder.minus(b);
		if (pre_data != NULL)
		{
			delete[]pre_data;
			pre_data = NULL;
		}
		quotient++;
	}
}
int BigInteger::compare( BigInteger b)
{
	int ndigitsa = this->digits - this->start_id;
	int ndigitsb = b.digits - b.start_id;
	if (ndigitsa>ndigitsb)
	{
		return 1;
	}
	else if (ndigitsa<ndigitsb)
	{
		return -1;
	}
	else
	{
		int i = this->start_id;
		int j = b.start_id;
		while (i < this->digits&&j<b.digits)
		{
			int diff = (this->data[i] - '0') - (b.data[j] - '0');
			if (diff>0)return 1;
			else if (diff < 0)return -1;
			++i; 
			++j;
		}
		return 0;
	}
}