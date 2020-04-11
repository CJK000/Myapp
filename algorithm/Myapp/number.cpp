#include"number.h"
#include<algorithm>
#include<string>
using namespace std;

void Number::Print() {	//�������
	printf("%d", this->integer);
	if (this->denominator) {
		printf("'%d/%d", this->numerator, this->denominator);
	}
}


bool Number::CheckNumber() {
	if (this->integer <= -1)return false;
	if (this->numerator <= -1)return false;
	if (this->denominator <= -1)return false;
	if (this->denominator != 0 && this->numerator >= this->denominator)return false;
	return true;
}

bool Number::CheckNumber(int max_n, int max_de) {
	if (this->CheckNumber() == false)return false;
	if (this->integer > max_n)return false;
	if (this->denominator > max_de)return false;
	return true;
}

Number::Number() {
	integer = 0;
	this->numerator = 0;
	this->denominator = 0;
}

Number::Number(int n) {
	integer = rand() % (n+1);
	if (integer == n) {
		this->denominator = 0;
		this->numerator = 0;
		return;
	}
	denominator = rand() % (n+1);
	if (denominator == 0) numerator = 0;
	else {
		numerator = rand() % denominator;
		this->ClarifyNu();
	}
	if (this->numerator == 0)this->denominator = 0;
}

Number::Number(int n, int max_de) {
	integer = rand() % (n + 1);
	if (integer == n) {
		denominator = 0;
		numerator = 0;
		return;
	}
	denominator = rand() % (max_de + 1);
	if (denominator == 0) numerator = 0;
	else numerator = rand() % denominator;
	if (this->numerator == 0) this->denominator = 0;
	else this->ClarifyNu();
}

Number::Number(int a, int b, int c) {
	integer = a;
	numerator = b;
	denominator = c;
}

void CatchInt(string s, int &i, int &a) {	//���ַ����ж���һ�������ŵ�x
	a = 0;
	for (; i < s.length(); i++) {
		if (s[i] >= '0' && s[i] <= '9') {
			a = a * 10 + s[i] - '0';
		}
		else {
			return;
		}
	}
}


Number::Number(string s, int &i) {	//��һ���������ֵ��ַ�����ʼ�����ֶ���
	this->denominator = 0;
	this->numerator = 0;
	this->integer = 0;
	while (i < s.length() && s[i] == ' ')i++;
	if (i==s.length() || s[i]<'0' || s[i]>'9') {
		this->integer = -1;
		return;
	}
	CatchInt(s, i, this->integer);
	if (i == s.length()) return;
	if (s[i]!= '\''&& s[i]!='/' && s[i]!=' ') this->numerator = -1;	//��ʼ��ʧ��
	else if (s[i] == '\'') {	//�����֧��ȡ����
		i++;
		if (s[i]<'0' || s[i]>'9') this->numerator = -1;	//���Ӹ�ʽ������ȡʧ��
		else{
			CatchInt(s, i, this->numerator);
			if (s[i] != '/') this->denominator = -1;	//��ʽ��ʽ������ʼ��ʧ��
			else {	//�����֧��ȡ��ĸ
				i++;
				if (s[i]<'0' || s[i]>'9') this->denominator = -1;	//��ĸ��ʽ������ȡʧ��
				else{
					CatchInt(s, i, this->denominator);
					if (i < s.length() && s[i] != ' ') this->denominator = -1;	//��ĸ��ʽ������ȡʧ��
				}
			}
		}
	}
	else if (s[i] == '/') {
		i++;
		if (i == s.length() || (s[i]<'0'&&s[i]>'9'))this->denominator = -1;
		else {
			swap(this->integer, this->numerator);
			CatchInt(s, i, this->denominator);
			if (i < s.length() && s[i] != ' ') this->denominator = -1;	//ʧ��
		}
	}
}

Number::Number(string str) {
	int i = 0;
	(*this) = Number(str, i);
}


string Number::ToString() {	//������ת�����ַ���
	char s[20];
	string str;
	if(this->integer!=0) str += itoa(this->integer, s, 10);
	if (this->denominator != 0) {
		if (this->integer != 0) str += '\'';
		str += itoa(this->numerator, s, 10);
		str += '/';
		str += itoa(this->denominator, s, 10);
	}
	else if (this->integer == 0)str += '0';
	return str;
}

int Gcd(int x, int y) {	//�������
	if (y > x) swap(x, y);
	while (y) {
		x = x % y;
		swap(x, y);
	}
	return x;
}

void Number::ClarifyNu() {	//�ٷ������ɴ�����������ǰ��������Ϊ��ȷ����
	if (this->denominator == 0)return;
	this->integer += this->numerator / this->denominator;
	this->numerator %= this->denominator;
	if (this->numerator == 0) this->denominator = 0;
	else {
		int gcd = Gcd(this->denominator, this->numerator);
		this->denominator /= gcd;
		this->numerator /= gcd;
	}
}

void Number::CommonDenominator(Number &y) {	//ͬ�֣�������������Ĭ��Ϊ 0����ĸ��Ϊ 0
	Number &x = *this;
	int gcd = Gcd(x.denominator, y.denominator);
	int xm, ym;
	xm = y.denominator / gcd;
	ym = x.denominator / gcd;
	x.numerator *= xm;
	x.denominator *= xm;
	y.numerator *= ym;
	y.denominator *= ym;
}



Number Number::operator+(Number t) {
	Number ret(this->integer, this->numerator, this->denominator);
	ret.integer += t.integer;
	if (ret.denominator == 0)ret.denominator = 1;
	if (t.denominator == 0)t.denominator = 1;
	ret.CommonDenominator(t);
	ret.numerator += t.numerator;
	ret.ClarifyNu();
	return ret;
}



Number Number::operator-(Number t) {
	Number ret(this->integer, this->numerator, this->denominator);
	ret.integer -= t.integer;
	if (ret.denominator == 0)ret.denominator = 1;
	if (t.denominator == 0)t.denominator = 1;
	ret.CommonDenominator(t);
	ret.numerator -= t.numerator;
	if (ret.numerator < 0) {
		ret.integer--;
		ret.numerator += ret.denominator;
	}
	ret.ClarifyNu();
	return ret;
}



Number Number::operator*(Number t) {
	Number x(this->integer, this->numerator, this->denominator);
	int gcd;

	//�����������
	Number ret(this->integer*t.integer, 0, 0);

	//Ԥ����
	if (x.denominator == 0)x.denominator = 1;
	if (t.denominator == 0)t.denominator = 1;

	//�����������������ֳ������������ķ�������
	gcd = Gcd(x.integer, t.denominator);
	ret = ret + Number(0, x.integer / gcd * t.numerator, t.denominator / gcd);

	//���������ķ������ֳ���������������������
	gcd = Gcd(x.denominator, t.integer);
	ret = ret + Number(0, t.integer / gcd * x.numerator, x.denominator / gcd);

	//���������ķ������ֳ������������ķ�������
	gcd = Gcd(x.numerator, t.denominator);
	x.numerator /= gcd;
	t.denominator /= gcd;
	gcd = Gcd(x.denominator, t.numerator);
	x.denominator /= gcd;
	t.numerator /= gcd;
	ret = ret + Number(0, x.numerator * t.numerator, x.denominator*t.denominator);

	return ret;

}


Number Number::operator/(Number t) {
	if (t == Number(0, 0, 0))return Number(-1, -1, -1);
	if (t.denominator == 0) t.denominator = 1;
	t.numerator = t.denominator*t.integer + t.numerator;
	t.integer = 0;
	swap(t.denominator, t.numerator);
	t.ClarifyNu();
	return this->operator*(t);
}


bool Number::operator<(Number t) {
	if (this->integer == t.integer) {
		if (this->denominator == 0) {
			return t.denominator > 0;
		}
		else if (t.denominator == 0) {
			return false;
		}
		else {
			return this->numerator*t.denominator < t.numerator*this->denominator;
		}
	}
	return this->integer < t.integer;
}

bool Number::operator<=(Number t) {
	return *this > t == false;
}

bool Number::operator>(Number t) {
	return t < *this;
}

bool Number::operator>=(Number t) {
	return *this < t == false;
}

bool Number::operator==(Number t) {
	return *this < t == false && t < *this == false;
}

bool Number::operator!=(Number t) {
	return (*this == t) == false;
}