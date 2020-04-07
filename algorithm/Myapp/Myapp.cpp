// Myapp.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include"number.h"
#include"expression.h"
#include"make.h"
#include <iostream>
using namespace std;


int main()
{
	Make m(100, 2);
	vector<Expression> v;
/*
	for (int i = 0; i < 10000; i++) {
		v = (m.*m.randMake[rand() % 4])(m.max_number, m.max_number, rand() % 3 + 1, 1);
		if (v.size() > 0) {
			if (Expression(v[0].ToString()).Calculate() == v[0].answer) {
				cout << "true\n";
			}
			else {
				cout << v[0].ToString() << endl;
				cout << Expression(v[0].ToString()).Calculate().ToString() << endl;
				cout << v[0].answer.ToString() << endl;
				cout << "false\n";
			}
		}
	}
*/

	for (int i = 0; i < 10000; i++) {
		v = m.RandPlus(m.max_number, m.max_number, 1, 1);
		if (v.size() > 0)cout << v[0].ToString() << " = " << v[0].answer.ToString() << endl;
		v = m.RandMinus(m.max_number, m.max_number, 1, 1);
		if (v.size() > 0)cout << v[0].ToString() << " = " << v[0].answer.ToString() << endl;
		v = m.RandMul(m.max_number, m.max_number, 1, 1);
		if (v.size() > 0)cout << v[0].ToString() << " = " << v[0].answer.ToString() << endl;
		v = m.RandDiv(m.max_number, m.max_number, 1, 1);
		if (v.size() > 0)cout << v[0].ToString() << " = " << v[0].answer.ToString() << endl;
	}

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
