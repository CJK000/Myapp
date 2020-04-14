#pragma once
#include"number.h"
#include"expression.h"
#include"trie.h"
#include"avl.h"
#include<vector>
#include<string>
#include<set>
#include<unordered_set>
#include<random>
#include<time.h>
using namespace std;

class Make {
private:
	int max_number;	//最大数字
	int problem_number;	//要求生成题目的数量
	unordered_set<long long> Set;
	Trie trie;
	AVL *AVLroot;
	typedef vector<Expression> (Make::*Function_ptr)(int, int, int, int);
	//函数指针数组 randMake[4] 的四个元素为随机生成题目的函数指针，方便随机调用时使用
	const Function_ptr randMake[4] = {&Make::RandPlus, &Make::RandMinus, &Make::RandMul, &Make::RandDiv };

	//以下四个函数为随机生成题目函数
	//max_n 为题目中数字整数部分的最大值，生成的数字式子的答案不能大于 max_n
	//max_de 为题目中分母的最大值
	//symbol_n 为生成题目的符号数
	//若symbol > 1，在函数中随机调用生成题目的函数，作为本次调用的子部份
	//symbol = 1，本次为最后一次调用，直接生成两个 Number 对象的基本运算，然后返回
	//output=1 表示本次调用为第一次调用，需要返回输出
	//output=0 表示本次调用为被递归调用，只需返回给上一级调用使用，无需判断生成的题目是否存在 stringSet 中
	//返回值中为一个题目和它的等价题目，可随机输出一个
	//如果返回的vector为空，则本次生成题目失败
	vector<Expression> RandPlus(int max_n, int max_de, int symbol_n, int output);
	vector<Expression> RandMinus(int max_n, int max_de, int symbol_n, int output);
	vector<Expression> RandMul(int max_n, int max_de, int symbol_n, int output);
	vector<Expression> RandDiv(int max_n, int max_de, int symbol_n, int output);

public:
	Make(int n, int m);
	bool CheckNumber();	//检查参数 r 和 n 是否合法
	Expression MakeProblem(void);	//供给主函数调用，返回一个随机生成运算符不超过3个的正确题目
};
