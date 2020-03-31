#pragma once
#include<random>
#include<time.h>
using namespace std;

class Number {
public:
	int integer;	//��������
	int numerator;	//����
	int denominator;	//��ĸ
	Number() {
		integer = 0;
		this->numerator = 0;
		this->denominator = 0;
	}
	Number(int n) {
		integer = rand() % n;
		denominator = rand() % n;
		if (denominator == 0) numerator = 0;
		else numerator = rand() % denominator;
	}
	Number(int a, int b, int c) {
		integer = a;
		numerator = b;
		denominator = c;
	}
	string ToString();
	void ClarifyNu();
	Number operator+(Number t);
	Number operator-(Number t);
	Number operator*(Number t);
	Number operator/(Number t);
	bool operator>(Number t);
	bool operator<(Number t);
	bool operator==(Number t);
	void Print();

};