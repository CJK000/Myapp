#pragma once
#include<random>
#include<time.h>
using namespace std;

class Number {
public:
	int integer;	//��������
	int numerator;	//����
	int denominator;	//��ĸ
	Number();	//��ʼ��ȫΪ 0
	Number(int n);	//����������ֲ����� n �� Number ����
	Number(int n, int max_de);	//���������ֵ������ n����ĸ������ max_de
	Number(int a, int b, int c);	// a Ϊ�������֣�b Ϊ���ӣ�c Ϊ��ĸ
	Number(string str, int &i);	//���ַ��� str �ӵ� i λ��ʼ��ȡһ��Number����
	Number(string str);	//���ַ���ͷ��ʼ���һ������
	string ToString();	//�ѵ�ǰ��Number����ת���� string ���������������������
	void ClarifyNu();	//�ٷ������ɴ�����������ǰ��������Ϊ��ȷ����
	bool CheckNumber();	//��鵱ǰ Number �����Ƿ�Ϊһ���Ϸ������֣��������ж��������㷵�صĽ���Ƿ�Ϸ�
	bool CheckNumber(int max_n, int max_de);	//��鵱ǰ Number �����Ƿ�Ϊһ���Ϸ������֣��������ж��������㷵�صĽ���Ƿ�Ϸ�
	Number operator+(Number t);
	Number operator-(Number t);
	Number operator*(Number t);
	Number operator/(Number t);
	bool operator>(Number t);
	bool operator>=(Number t);
	bool operator<(Number t);
	bool operator<=(Number t);
	bool operator==(Number t);
	bool operator!=(Number t);
	void Print();	//���ڲ���

};



void CatchInt(string s, int &i, int &a);	//���ַ����ж���һ������