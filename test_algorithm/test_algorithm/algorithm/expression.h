#pragma once
#include"number.h"
using namespace std;

class Point {
	public:
		int type;//标记当前结构体代表的意义， 0 表示符号, 1表示数字
		char symbol;//运算符
		Number num;	//数字
		Point(Number n);// 用一个 Number 对象初始化当前 Point 对象
		Point(char c);//用一个符号初始化当前 Point 对象
};

//表达式类，在 Make 类中作为参数类型，本类不被单独使用
class Expression {
	public:
		vector<Point> question;	//题目
		Number answer;	//答案
		bool valid;	//当前题目是否为一个有效的题目
		Expression() { };	//无参构造函数，初始化一个空的对象
		Expression(string str);	//用题目字符串初始化，并计算出正确答案
		string ToString();//将题目转换成字符串，不包括答案，答案可直接使用 Number 类的 ToString 函数转换
		//以下三个函数为向当前题目末尾以下各类元素
		void Add(Number n);
		void Add(char c);
		void Add(Expression exp);
		//以下三个函数分别为，按顺序向当前对象中插入内容，前三个为题目内容，最后一个为答案
		Expression(Number num, char c, Number num2, Number ans);
		Expression(Number num, char c, Expression exp,Number ans);
		Expression(Expression exp, char c, Number num, Number ans);
		void AddParenthesis(void);	//在当前题目的左右边缘添加一对括号
		void clear();	//清空对象当前内容
		bool CheckValid();	//判断当前题目是否合法
		vector<Point> Nifix2Postfix();	//中缀转后缀，后缀表达式用vector存放 
		Number Calculate();	//计算当前题目的答案
};
