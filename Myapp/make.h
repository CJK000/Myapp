#pragma once
#include"number.h"
#include<vector>
#include<string>
#include<set>
#include<random>
#include<time.h>
using namespace std;

class Point {
	bool type;
	char symbol;
	Number num;
};

class Make {
	public:
		int n;	//最大数字
		int problemNum;	//生成题目的个数
		set<string> stringSet;
		Make(int n, int problemNum) {
			this->n = n;
			this->problemNum = problemNum;
			stringSet.clear();
			srand(time(0));
		}
		Number Calculate(vector<Point>expression);
		string MakePlus();
		string MakeMinus();
		string MakeMul();
		string MkaeDiv();
		string MakeThree();
		bool CheckIn(string str);
		void RandMake();
		void OrderMake();
};

void MakeProblem();