﻿// Myapp.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include"number.h"
#include"expression.h"
#include"make.h"
#include <iostream>
#define PROBLEM_NUMBER 100	//需要生成的题目数量
using namespace std;


int main()
{

//	cout << (Number(18, 0, 0) / Number(18, 1, 2)).ToString() << endl;

//	if (Number(5, 0, 0).CheckNumber(3, 10) == true) {
//		cout << "true\n";
//	}
//	else {
//		cout << "false\n";
//	}

//	cout << (Number(0, 1, 1283) / Number(1289, 1, 1291)).ToString() << endl;

//	cout << Expression("1'2235/6638 * 7010'188/285 =").answer.ToString();




/*
	Make *m;
	Expression e;
	int cnt = 0;
	int maxn = 50000;
	while(1) {
		m = new Make(maxn);
		cout << maxn << endl;
		while (1) {
			e = m->MakeProblem();
			if (e.question.size() > 0) {
				if (Expression(e.ToString()).Calculate() != e.answer) {
					maxn--;
					string s = e.ToString();
					cout << s << endl;
					cout << Expression(s).answer.ToString() << endl;
					cout << e.answer.ToString() << endl;
					cout << "false\n\n";
					delete m;
					break;
				}
			}
		}
	}
*/






	Make m(129000007);
	Expression e;
	int cnt = 0;
	while(1) {
		e = m.MakeProblem();
		if (e.question.size() > 0) {
			if (Expression(e.ToString()).Calculate() == e.answer) {
				cnt++;
				if (cnt % 1000 == 0) {
					cout << cnt << " " << "true\n";
//					return 0;
				}
			}
			else {
				string s = e.ToString();
				cout << s << endl;
				cout << Expression(s).answer.ToString() << endl;
				cout << e.answer.ToString() << endl;
				cout << "false\n";
			}
		}
	}



/*
	for (int i = 0; i < 10000000; i++) {
		v = m.RandPlus(m.max_number, m.max_number, 3, 1);
		if (v.size() > 0)cout << v[0].ToString() << " = " << v[0].answer.ToString() << endl;
		v = m.RandMinus(m.max_number, m.max_number, 2, 1);
		if (v.size() > 0)cout << v[0].ToString() << " = " << v[0].answer.ToString() << endl;
		v = m.RandMul(m.max_number, m.max_number, 2, 1);
		if (v.size() > 0)cout << v[0].ToString() << " = " << v[0].answer.ToString() << endl;
		v = m.RandDiv(m.max_number, m.max_number, 2, 1);
		if (v.size() > 0)cout << v[0].ToString() << " = " << v[0].answer.ToString() << endl;
	}
*/




















//比对答案操作
/*
	string problem;	//从题目文件中直接读一行到这里
	string answer;	//从答案文件中直接读一行到这里
	Number user_answer(answer);	//将用户的答案转换成 Number 对象
	Number cal_answer;	//存储程序计算出来的正确答案

	cal_answer = Expression(problem).answer;
	//用字符串初始化Expression对象时已完成计算正确答案
	//将正确答案赋值给 cal_answer

	if (cal_answer.CheckNumber() == false) {	//题目格式有错
		//做对应处理
	}
	else {
		if (user_answer.CheckNumber() == false) {	//用户答案格式有错
			//做对应处理
		}
		else {
			if (cal_answer == user_answer) {
				//答案正确
				cout << user_answer.ToString();		//将正确答案转化为字符串输出到对应位置
			}
			else {
				//答案错误
				cout << user_answer.ToString();		//将错误答案转化为字符串输出到对应位置
			}
		}
	}
*/

//生成题目操作
/*
	Make m(10);	//初始化一个 Make 类，参数为最大数字
	Expression problem;	//用于接收返回的题目
	int cnt = 0;	//计数器，计算已生成题目的数量
	while (cnt < PROBLEM_NUMBER) {
		problem = m.MakeProblem();	//生成一个符合要求的题目
		if (problem.question.size() > 0) {	//返回值里面有题目，生成题目成功

			cnt++;	//计数器加一

			cout << problem.ToString();	//将题目转换成字符串输出
			cout << problem.answer.ToString() << endl;	//将本题的答案转换成字符串输出

			//将本处的 cout 换成输出到文件或 UI 界面即可
		}
		else {
			//生成题目失败，整数最大值太小，无法生成指定数量题目。
			break;
		}
	}
*/

}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
