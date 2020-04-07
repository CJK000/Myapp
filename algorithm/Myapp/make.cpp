#include"make.h"
#include<vector>
#include<string>
#include<set>
#include<random>



Expression Make::MakeProblem(void) {
	vector<Expression> v;	//接收生成题目的返回值
	int t = 0;
	while (v.size() == 0) {
		if (t == 30) {
			return Expression();	//生成题目失败，整数最大值太小，无法生成指定数量题目。
		}
		v = (this->*this->randMake[rand() % 4])(this->max_number, this->max_number, rand() % 3 + 1, 1);
	}
	return v[rand() % v.size()];
}









bool Make::CheckExist(Expression exp) {
	return this->stringSet.find(exp.ToString()) != this->stringSet.end() ;
}

void Make::Insert(Expression exp) {
	this->stringSet.insert(exp.ToString());
}




vector<Expression> Make::RandPlus(int max_n, int max_de, int symbol_n, int output) {
	vector<Expression> v;
	Number a(max_n, max_de);	//生成 b + c = a
	Number b;
	Number c;
	if (symbol_n == 1) {
		if (a.denominator == 0) {
			b = Number(max_n, max_de);
		}
		else {
			b = Number(max_n, max_de / a.denominator);
		}
		if (b > a) {
			swap(a, b);
		}
		c = a - b;
		if (c.CheckNumber(max_n, max_de) == true) {
			v.push_back(Expression(b, '+', c, a));
			v.push_back(Expression(c, '+', b, a));
		}
	}
	else {
		vector<Expression> subExpression;
		if (max_n == 0)return v;
		while (a == Number(0, 0, 0))a = Number(max_n, max_de);
		if (a.denominator == 0) subExpression = (this->*randMake[rand() % 4])(a.integer, max_de, symbol_n - 1, 0);
		else subExpression = (this->*randMake[rand() % 4])(a.integer, max_de / a.denominator, symbol_n - 1, 0);
		if (subExpression.size() > 0) {
			for (Expression exp : subExpression) {
				c = a - exp.answer;
				if (c.CheckNumber(max_n, max_de) == true) {
					v.push_back(Expression(exp, '+', c, a));
					v.push_back(Expression(c, '+', exp, a));
				}
			}
		}
	}
	if (output == 1) {
		if (v.size() > 0 && this->CheckExist(v[0]) == false) {
			for (Expression e : v) {
				this->Insert(e);
			}
		}
		else {
			v.clear();
		}
	}
	return v;
}




vector<Expression> Make::RandMinus(int max_n, int max_de, int symbol_n, int output) {
	vector<Expression> v;
	Number a(max_n, max_de);	//生成 a - b = c
	Number b, c;
	if (max_n <= 1)return v;
	while (a <= Number(1, 0, 0))a = Number(max_n, max_de);
	if (symbol_n == 1) {
		if (a.denominator == 0)b = Number(max_n, max_de);
		else {
			b = Number(max_n, max_de / a.denominator);
		}
		if (b > a) {
			swap(b, a);
		}
		c = a - b;
		if (c.CheckNumber(max_n, max_de) == true) {
			v.push_back(Expression(a, '-', b, c));
		}
	}
	else {
		vector<Expression> subExpression;
		if (a.denominator == 0) subExpression = (this->*randMake[rand() % 4])(a.integer, max_de, symbol_n - 1, 0);
		else subExpression = (this->*randMake[rand() % 4])(a.integer, max_de / a.denominator, symbol_n - 1, 0);
		if (subExpression.size() > 0) {
			for (Expression exp : subExpression) {
				c = a - exp.answer;
				if (c.CheckNumber(max_n, max_de)) {
					exp.AddParenthesis();
					v.push_back(Expression(a, '-', exp, c));
				}
			}
		}
	}
	if (output == 1) {
		if (v.size() > 0 && this->CheckExist(v[0]) == false) {
			for (Expression e : v) {
				this->Insert(e);
			}
		}
		else {
			v.clear();
		}
	}
	return v;
}





vector<Expression> Make::RandMul(int max_n, int max_de, int symbol_n, int output) {
	Expression ret;
	vector<Expression> v;
	Number a(max_n, max_de);	//生成 b * c = a
	Number b;
	Number c;
	if (max_n == 0) return v;	//输入太小，难以生成题目，直接退出
	while (a == Number(0, 0, 0))a = Number(max_n, max_de);
	if (symbol_n == 1) {
		int t = 0;
		while (b == Number(0, 0, 0)) {
			if (t == 3)return v;	//防止死循环
			t++;
			if (a.denominator == 0) b = Number(max_n, max_de);
			else b = Number(max_n, max_de / a.denominator);
		}
		if (b == Number(0, 0, 0)) return v;
		c = a / b;
		if (c.CheckNumber(max_n, max_de) == true) {
			v.push_back(Expression(b, '*', c, a));
			v.push_back(Expression(c, '*', b, a));
		}
	}
	else {
		vector<Expression> subExpression;
		if (a.denominator == 0) subExpression = (this->*randMake[rand() % 4])(a.integer, max_de, symbol_n - 1, 0);
		else subExpression = (this->*randMake[rand() % 4])(a.integer, max_de / a.denominator, symbol_n - 1, 0);
		if (subExpression.size() > 0) {
			if (subExpression[0].answer == Number(0, 0, 0)) {
				for (Expression x : subExpression) {
					x.AddParenthesis();
					v.push_back(Expression(x, '*', a, x.answer));
					v.push_back(Expression(a, '*', x, x.answer));
				}
			}
			else {
				for (Expression x : subExpression) {
					c = a / x.answer;
					if (c.CheckNumber(max_n, max_de) == true) {
						x.AddParenthesis();
						v.push_back(Expression(x, '*', c, a));
						v.push_back(Expression(c, '*', x, a));
					}
				}
			}
		}
	}
	if (output == 1) {
		if (v.size() > 0 && this->CheckExist(v[0]) == false) {
			for (Expression e : v) {
				this->Insert(e);
			}
		}
		else {
			v.clear();
		}
	}
	return v;
}


//生成 a / b = c
vector<Expression> Make::RandDiv(int max_n, int max_de, int symbol_n, int output) {
	vector<Expression> v;
	if (max_n == 0) return v;
	Number a(max_n, max_de);
	while (a == Number(0, 0, 0))a = Number(max_n, max_de);
	Number b, c;
	if (symbol_n == 1) {
		int t = 0;
		while (b == Number(0, 0, 0) || c.CheckNumber(max_n, max_de) == false) {
			if (t == 3) return v;	//防止死循环
			t++;
			b = Number(max_n, max_de);
			c = a / b;
		}
		v.push_back(Expression(a, '/', b, c));
	}
	else {
		vector<Expression> subExpression;
		subExpression = (this->*randMake[rand() % 4])(max_n, max_de, symbol_n - 1, 0);
		if (subExpression.size() > 0) {
			int t = 0;
			while (subExpression[0].answer == Number(0, 0, 0) || (a / subExpression[0].answer).CheckNumber(max_n, max_de) == false) {
				subExpression.clear();
				if (t++ == 3)break;	//三次都生成失败则退出，避免死循环
				subExpression = (this->*randMake[rand() % 4])(max_n, max_de, symbol_n - 1, 0);
				if (subExpression.size() == 0)break;
			}
			if (subExpression.size() > 0) {
				for (Expression x : subExpression) {
					c = a / x.answer;
					if (c.CheckNumber() == true) {
						x.AddParenthesis();
						v.push_back(Expression(a, '/', x, c));
					}
				}
			}
		}
	}
	if (output == 1) {
		if (v.size() > 0 && this->CheckExist(v[0]) == false) {
			for (Expression e : v) {
				this->Insert(e);
			}
		}
		else {
			v.clear();
		}
	}
	return v;

}