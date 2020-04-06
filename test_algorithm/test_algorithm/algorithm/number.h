#pragma once
#include<random>
#include<time.h>
using namespace std;

class Number {
public:
	int integer;	//整数部分
	int numerator;	//分子
	int denominator;	//分母
	Number();	//初始化全为 0
	Number(int n);	//随机生成数字不大于 n 的 Number 对象
	Number(int n, int max_de);	//随机生成数值不大于 n，分母不大于 max_de
	Number(int a, int b, int c);	// a 为整数部分，b 为分子，c 为分母
	Number(string str, int &i);	//将字符串 str 从第 i 位开始获取一个Number对象
	Number(string str);	//从字符串头开始获得一个数字
	string ToString();	//把当前的Number对象转换成 string ，可用于输出或其他处理
	void ClarifyNu();	//假分数化成带分数，调用前整数部分为正确数字
	bool CheckNumber();	//检查当前 Number 对象是否为一个合法的数字，可用于判断其他运算返回的结果是否合法
	bool CheckNumber(int max_n, int max_de);	//检查当前 Number 对象是否为一个合法的数字，可用于判断其他运算返回的结果是否合法
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
	void Print();	//用于测试

};



void CatchInt(string s, int &i, int &a);	//从字符串中读出一个整数