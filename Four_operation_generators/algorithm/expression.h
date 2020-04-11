#pragma once
#include"number.h"
using namespace std;

class Point {
	public:
		int type;//��ǵ�ǰ�ṹ���������壬 0 ��ʾ����, 1��ʾ����
		char symbol;//�����
		Number num;	//����
		Point(Number n);// ��һ�� Number �����ʼ����ǰ Point ����
		Point(char c);//��һ�����ų�ʼ����ǰ Point ����
};

//���ʽ�࣬�� Make ������Ϊ�������ͣ����಻������ʹ��
class Expression {
	public:
		vector<Point> question;	//��Ŀ
		Number answer;	//��
		bool valid;	//��ǰ��Ŀ�Ƿ�Ϊһ����Ч����Ŀ
		Expression() { };	//�޲ι��캯������ʼ��һ���յĶ���
		Expression(string str);	//����Ŀ�ַ�����ʼ�������������ȷ��
		string ToString();//����Ŀת�����ַ������������𰸣��𰸿�ֱ��ʹ�� Number ��� ToString ����ת��
		//������������Ϊ��ǰ��Ŀĩβ���¸���Ԫ��
		void Add(Number n);
		void Add(char c);
		void Add(Expression exp);
		//�������������ֱ�Ϊ����˳����ǰ�����в������ݣ�ǰ����Ϊ��Ŀ���ݣ����һ��Ϊ��
		Expression(Number num, char c, Number num2, Number ans);
		Expression(Number num, char c, Expression exp,Number ans);
		Expression(Expression exp, char c, Number num, Number ans);
		void AddParenthesis(void);	//�ڵ�ǰ��Ŀ�����ұ�Ե���һ������
		void clear();	//��ն���ǰ����
		bool CheckValid();	//�жϵ�ǰ��Ŀ�Ƿ�Ϸ�
		vector<Point> Nifix2Postfix();	//��׺ת��׺����׺���ʽ��vector��� 
		Number Calculate();	//���㵱ǰ��Ŀ�Ĵ�
};
