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
		int max_number;	//�������
		int problemNum;	//������Ŀ�ĸ���
		set<string> stringSet;	//�����ɵ���Ŀ�����еȼ۵���Ŀ����ˣ����ڲ���
		vector<Expression> exp;
		typedef vector<Expression>(Make::*Function_ptr)(int, int, int);
		const Function_ptr randMake[4] = {&Make::RandPlus, &Make::RandMinus, &Make::RandMul, &Make::RandDiv };
		Make(int n, int problemNum) {
			this->max_number = n;
			this->problemNum = problemNum;
			stringSet.clear();
			srand(time(0));
		}
		//max_n Ϊ���ֵ����ֵ
		//symbol_n Ϊ������Ŀ�ķ�����
		//output=1��ʾ���ε���Ϊ��һ�ε��ã���Ҫ�������
		//����ֵ��Ϊһ����Ŀ�����ĵȼ���Ŀ
		//������ص�vectorΪ�գ��򱾴�������Ŀʧ��
		vector<Expression> RandPlus(int max_n, int symbol_n, int output);
		vector<Expression> RandMinus(int max_n, int symbol_n, int output);
		vector<Expression> RandMul(int max_n, int symbol_n, int output);
		vector<Expression> RandDiv(int max_n, int symbol_n, int output);
		bool CheckExist(Expression exp);	//������Ŀ�Ƿ�������
		void Insert(Expression exp);	//��һ����Ŀ���뵽 stringSet��
};


string Ex2String(Number a, char c, Number b);

void MakeProblem();