#pragma once
#include"number.h"
#include"expression.h"
#include<vector>
#include<string>
#include<set>
#include<random>
#include<time.h>
using namespace std;

class Make {
	public:
		int max_number;	//最大数字
		int problemNum;	//生成题目的个数
		set<string> stringSet;	//将生成的题目和所有等价的题目插入此，用于查重
		vector<Expression> exp;
		typedef vector<Expression>(Make::*Function_ptr)(int, int, int);
		const Function_ptr randMake[4] = {&Make::RandPlus, &Make::RandMinus, &Make::RandMul, &Make::RandDiv };
		Make(int n, int problemNum) {
			this->max_number = n;
			this->problemNum = problemNum;
			stringSet.clear();
			srand(time(0));
		}
		//max_n 为数字的最大值
		//symbol_n 为生成题目的符号数
		//output=1表示本次调用为第一次调用，需要返回输出
		//返回值中为一个题目和它的等价题目
		//如果返回的vector为空，则本次生成题目失败
		vector<Expression> RandPlus(int max_n, int symbol_n, int output);
		vector<Expression> RandMinus(int max_n, int symbol_n, int output);
		vector<Expression> RandMul(int max_n, int symbol_n, int output);
		vector<Expression> RandDiv(int max_n, int symbol_n, int output);
		bool CheckExist(Expression exp);	//检查此题目是否已生成
		void Insert(Expression exp);	//将一个题目插入到 stringSet中
};


string Ex2String(Number a, char c, Number b);

void MakeProblem();