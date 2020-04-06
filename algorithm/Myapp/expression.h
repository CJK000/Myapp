#pragma once
#include"number.h"
using namespace std;

class Point {
	public:
		int type;	// 0 表示符号, 1表示数字
		char symbol;	//运算符
		Number num;		//数字
		Point(Number n);
		Point(char c);
};

class Expression {
	public:
		vector<Point> question;	//题目
		Number answer;	//答案
		bool valid;	//当前题目是否为一个有效的题目
		Expression() { };	//无参构造函数，初始化一个空的对象
		Expression(string str);	//用题目字符串初始化，并计算出正确答案
		string ToString();
		//向当前表达式末尾以下各类元素
		void Add(Number n);
		void Add(char c);
		void Add(Expression exp);
		Expression(Number num, char c, Number num2, Number ans);
		Expression(Number num, char c, Expression exp,Number ans);
		Expression(Expression exp, char c, Number num, Number ans);
		void AddParenthesis(void);	//添加一对括号
		void clear();	//清空对象当前内容
		bool CheckValid();	//判断当前题目是否合法
		vector<Point> Nifix2Postfix();	//中缀转后缀，后缀表达式用vector存放 
		Number Calculate();	//计算当前题目的答案	//
};
