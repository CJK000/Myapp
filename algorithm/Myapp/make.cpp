#include"make.h"
#include<vector>
#include<string>
#include<set>
#include<random>


bool Make::CheckExist(Expression exp) {
	return this->stringSet.find(exp.ToString()) != this->stringSet.end() ;
}

void Make::Insert(Expression exp) {
	this->stringSet.insert(exp.ToString());
}




vector<Expression> Make::RandPlus(int max_n, int symbol_n, int output) {
	vector<Expression> v;
	Number a(max_n);	//生成 b + c = a
	Number b;
	Number c;
	if (symbol_n == 1) {
		if (a.denominator == 0) {
			b = Number(max_n);
		}
		else {
			b = Number(max_n, this->max_number / a.denominator);
		}
		if (b > a) {
			swap(a, b);
		}
		c = a - b;
		v.push_back(Expression(b, '+', c, a));
		v.push_back(Expression(c, '+', b, a));
		return v;
	}
	else {
		vector<Expression> subExpression;
		while (a == Number(0, 0, 0))a = Number(max_n);
		subExpression = (this->*randMake[rand() % 4])(a.integer, symbol_n - 1, 0);
		for (Expression exp : subExpression) {
			c = a - exp.answer;
			v.push_back(Expression(exp, '+', c, a));
			v.push_back(Expression(c, '+', exp, a));
		}
	}
	if (output == 1) {
		if (this->CheckExist(v[0]) == false) {
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




vector<Expression> Make::RandMinus(int max_n, int symbol_n, int output) {
	vector<Expression> v;
	Number a(max_n);
	Number b, c;
	while (a <= Number(1, 0, 0))a = Number(max_n);
	if (symbol_n == 1) {
		if (a.denominator == 0)b = Number(max_n);
		else {
			b = Number(max_n, this->max_number / a.denominator);
		}
		if (b > a) {
			swap(b, a);
		}
		c = a - b;
		v.push_back(Expression(a, '-', b, c));
	}
	else {
		vector<Expression> subExpression;
		subExpression = (this->*randMake[rand() % 4])(a.integer, symbol_n - 1, 0);
		for (Expression exp : subExpression) {
			c = a - exp.answer;
			v.push_back(Expression(a, '-', exp, c));
		}
	}
	if (output == 1) {
		if (this->CheckExist(v[0]) == false) {
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





vector<Expression> Make::RandMul(int max_n, int symbol_n, int output) {
	Expression ret;
	vector<Expression> v;
	Number a(max_n);	//生成 b * c = a
	Number b;
	Number c;
	while (a == Number(0, 0, 0))a = Number(max_n,this->max_number);
	if (symbol_n == 1) {
		while(b==Number(0,0,0))b = Number(max_n, this->max_number / a.denominator);
		if (b > Number(1, 0, 0)) {
			swap(a, b);
		}
		c = a / b;
		v.push_back(Expression(b, '*', c, a));
	}
	else {
		vector<Expression> subExpression;
		subExpression = (this->*randMake[rand() % 4])(a.integer, symbol_n - 1, 0);
		if (subExpression[0].answer == Number(0, 0, 0)) {
			for (Expression x : subExpression) {
				x.AddParenthesis();
				v.push_back(Expression(x, '*', a, x.answer));
				v.push_back(Expression(a, '*', x, x.answer));
			}
		}
		else {
			for (Expression x : v) {
				c = a / x.answer;
				x.AddParenthesis();
				v.push_back(Expression(x, '*', c, a));
				v.push_back(Expression(c, '*', x, a));
			}
		}
	}
	if (output == 1) {
		if (this->CheckExist(v[0]) == false) {
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



vector<Expression> Make::RandDiv(int max_n, int symbol_n, int output) {
	vector<Expression> v;
	Number a(max_n,this->max_number);
	while (a == Number(0, 0, 0))a = Number(max_n,this->max_number);
	Number b, c;
	if (symbol_n == 1) {
		c = a / b;
		while (b == Number(0, 0, 0) || c.CheckNumber(this->max_number)==false) {
			b = Number(max_n,this->max_number);
			c = a / b;
		}
		v.push_back(Expression(a, '/', b, c));
	}
	else {
		vector<Expression> subExpression;
		subExpression = (this->*randMake[rand() % 4])(max_n, symbol_n - 1, 0);
		while (subExpression[0].answer == Number(0, 0, 0)||(a / subExpression[0].answer).CheckNumber(this->max_number) == false) {
			subExpression.clear();
			subExpression = (this->*randMake[rand() % 4])(max_n, symbol_n - 1, 0);
		}
		for (Expression x : subExpression) {
			x.AddParenthesis();
			v.push_back(Expression(a, '/', x, a / x.answer));
		}
	}
	if (output == 1) {
		if (this->CheckExist(v[0]) == false) {
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