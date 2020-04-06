#pragma once
#include"number.h"
using namespace std;

class Point {
	public:
		int type;	// 0 ��ʾ����, 1��ʾ����
		char symbol;	//�����
		Number num;		//����
		Point(Number n);
		Point(char c);
};

class Expression {
	public:
		vector<Point> question;	//��Ŀ
		Number answer;	//��
		bool valid;	//��ǰ��Ŀ�Ƿ�Ϊһ����Ч����Ŀ
		Expression() { };	//�޲ι��캯������ʼ��һ���յĶ���
		Expression(string str);	//����Ŀ�ַ�����ʼ�������������ȷ��
		string ToString();
		//��ǰ���ʽĩβ���¸���Ԫ��
		void Add(Number n);
		void Add(char c);
		void Add(Expression exp);
		Expression(Number num, char c, Number num2, Number ans);
		Expression(Number num, char c, Expression exp,Number ans);
		Expression(Expression exp, char c, Number num, Number ans);
		void AddParenthesis(void);	//���һ������
		void clear();	//��ն���ǰ����
		bool CheckValid();	//�жϵ�ǰ��Ŀ�Ƿ�Ϸ�
		vector<Point> Nifix2Postfix();	//��׺ת��׺����׺���ʽ��vector��� 
		Number Calculate();	//���㵱ǰ��Ŀ�Ĵ�	//
};
