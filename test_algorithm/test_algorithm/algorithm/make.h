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
private:
    int max_number;	//�������
    int problem_number;
    bool CheckNumber();
    set<string> stringSet;	//�����ɵ���Ŀ�����еȼ۵���Ŀ����ˣ����ڲ���
    typedef vector<Expression> (Make::*Function_ptr)(int, int, int, int);
    //����ָ������ randMake[4] ���ĸ�Ԫ��Ϊ���������Ŀ�ĺ���ָ�룬�����������ʱʹ��
    const Function_ptr randMake[4] = {&Make::RandPlus, &Make::RandMinus, &Make::RandMul, &Make::RandDiv };
    bool CheckExist(Expression exp);	//������Ŀ�Ƿ�������
    void Insert(Expression exp);	//��һ����Ŀ���뵽 stringSet��

    //�����ĸ�����Ϊ���������Ŀ����
    //max_n Ϊ��Ŀ�������������ֵ����ֵ�����ɵ�����ʽ�ӵĴ𰸲��ܴ��� max_n
    //max_de Ϊ��Ŀ�з�ĸ�����ֵ
    //symbol_n Ϊ������Ŀ�ķ�����
    //��symbol > 1���ں������������������Ŀ�ĺ�������Ϊ���ε��õ��Ӳ���
    //symbol = 1������Ϊ���һ�ε��ã�ֱ���������� Number ����Ļ������㣬Ȼ�󷵻�
    //output=1 ��ʾ���ε���Ϊ��һ�ε��ã���Ҫ�������
    //output=0 ��ʾ���ε���Ϊ���ݹ���ã�ֻ�践�ظ���һ������ʹ�ã������ж����ɵ���Ŀ�Ƿ���� stringSet ��
    //����ֵ��Ϊһ����Ŀ�����ĵȼ���Ŀ����������һ��
    //������ص�vectorΪ�գ��򱾴�������Ŀʧ��
    vector<Expression> RandPlus(int max_n, int max_de, int symbol_n, int output);
    vector<Expression> RandMinus(int max_n, int max_de, int symbol_n, int output);
    vector<Expression> RandMul(int max_n, int max_de, int symbol_n, int output);
    vector<Expression> RandDiv(int max_n, int max_de, int symbol_n, int output);

public:
    Make(int n, int m);
    Expression MakeProblem(void);	//�������������ã�����һ��������������������3������ȷ��Ŀ
};


bool check_answer(string problem,string answer);
bool build_problem(int max_number,int problem_number);
string getpoint_problem(string s);
string getpoint_answer(string s);
