#include"number.h"
#include<algorithm>
#include<string>
using namespace std;

void Number::Print() {	//输出数字
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

void CatchInt(string s, int &i, int &a) {	//从字符串中读出一个整数放到x
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


Number::Number(string s, int &i) {	//用一个代表数字的字符串初始化数字对象
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\r')i++;
	if (s[i]<'0' || s[i]>'9') {
		this->integer = -1;
		return;
	}
	CatchInt(s, i, this->integer);
	this->denominator = 0;
	this->numerator = 0;
	if (i == s.length()) return;
	if (s[i]!= '\'') {
		if (s[i] == ' ' || s[i] == '\n' || s[i]=='\r') {	//初始化成功
			return;
		}
		else {	//初始化失败
			this->numerator = -1;
			return;
		}
	}
	i++;
	CatchInt(s, i, this->numerator);
	if (s[i] != '/') {	//初始化失败
		this->denominator = -1;
		return;
	}
	i++;
	CatchInt(s, i, this->denominator);
}

Number::Number(string str) {
	int i = 0;
	(*this) = Number(str, i);
}


string Number::ToString() {	//将储字转换成字符串
	char s[20];
	string str(itoa(this->integer, s, 10));
	if (this->denominator != 0) {
		str += '\'';
		str += itoa(this->numerator, s, 10);
		str += '/';
		str += itoa(this->denominator, s, 10);
	}
	return str;
}

int Gcd(int x, int y) {	//最大公因数
	if (y > x) swap(x, y);
	while (y) {
		x = x % y;
		swap(x, y);
	}
	return x;
}

void Number::ClarifyNu() {	//假分数化成带分数，调用前整数部分为正确数字
	this->integer += this->numerator / this->denominator;
	this->numerator %= this->denominator;
	if (this->numerator == 0) this->denominator = 0;
	else {
		int gcd = Gcd(this->denominator, this->numerator);
		this->denominator /= gcd;
		this->numerator /= gcd;
	}
}

Number Number::operator+(Number t) {
	Number ret;
	int gcd;
	ret.integer = this->integer + t.integer;
	if (this->denominator != 0 && t.denominator != 0) {
		ret.denominator = this->denominator * t.denominator;
		ret.numerator = this->numerator*t.denominator + t.numerator*this->denominator;
		ret.ClarifyNu();
	}
	else if (this->denominator != 0 || t.denominator != 0) {
		ret.denominator = this->denominator + t.denominator;
		ret.numerator = this->numerator + t.numerator;
	}
	else {
		ret.denominator = 0;
		ret.numerator = 0;
	}
	return ret;
}



Number Number::operator-(Number t) {
	Number ret;
	int gcd;
	ret.integer = this->integer - t.integer;
	if (this->denominator != 0 && t.denominator != 0) {
		ret.denominator = this->denominator * t.denominator;
		ret.numerator = this->numerator*t.denominator - t.numerator*this->denominator;
		if (ret.numerator == 0) {
			ret.denominator = 0;
		}
		else {
			if (ret.numerator < 0) {
				ret.integer--;
				ret.numerator += ret.denominator;
			}
			ret.ClarifyNu();
		}
	}
	else if (this->denominator != 0) {
		ret.denominator = this->denominator;
		ret.numerator = this->numerator;
	}
	else if (t.denominator != 0) {
		ret.integer--;
		ret.denominator = t.denominator;
		ret.numerator = ret.denominator - t.numerator;
	}
	else {
		ret.denominator = 0;
		ret.numerator = 0;
	}
	return ret;
}



Number Number::operator*(Number t) {
	Number ret(this->integer, this->numerator, this->denominator);
	if (ret.denominator == 0) ret.denominator = 1;
	if (t.denominator == 0) t.denominator = 1;
	ret.numerator = ret.denominator*ret.integer + ret.numerator;
	t.numerator = t.denominator*t.integer + t.numerator;
	if (ret.numerator == 0 || t.numerator == 0) return Number();
	ret.numerator *= t.numerator;
	ret.denominator *= t.denominator;
	ret.integer = 0;
	ret.ClarifyNu();
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