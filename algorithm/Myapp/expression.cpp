#include"expression.h"
#include<vector>
#include<stack>
#include<iostream>

Point::Point(Number n) {
	num = n;
	type = 1;
}
Point::Point(char c) {
	symbol = c;
	type = 0;
}


Expression::Expression(string s) {
	int i = 0;
	int length = s.length();
	int t = 0;//插入新数字或符号前表达式长度
	while (i < length) {
		while (i < length && s[i] == ' ')i++;
		if (i == length) break;	//初始化成功
		if (s[i] >= '0'&&s[i] <= '9') {
			this->Add(Number(s, i));
		}
		else {
			switch (s[i])
			{
			case '+':
			case '-':
			case '*':
			case '/':
			case '(':
			case ')': {
				this->Add(s[i]);
				i++;
				break;
			}
			case '=': {
				i++;
				while (i < length && (s[i] == ' '))i++;
				if (i < length) {	//输入出错
					this->question.clear();
					this->valid = false;
					return;
				}
				else {
					return;	//初始化成功
				}
			}
			default:
				break;
			}
		}
		if (t == this->question.size()) {	//插入失败
			this->question.clear();
			this->valid = false;
			return;
		}
		t++;
	}
	this->Calculate();	//直接计算出答案
}





string Expression::ToString() {
	string s;
	for (Point x : this->question) {
		if (x.type == 1) {
			s += x.num.ToString();
			s += ' ';
		}
		else {
			s += x.symbol;
			s += ' ';
		}
	}
	return s;
}


void Expression::Add(Number n) {
	if (n.CheckNumber() == false) return;
	this->question.push_back(Point(n));
}


void Expression::Add(char c){
	this->question.push_back(Point(c));
}
void Expression::clear() {
	this->question.clear();
}


void Expression::Add(Expression exp) {
	this->question.insert(this->question.end(), exp.question.begin(), exp.question.end());
}

Expression::Expression(Number num, char c, Number num2, Number ans) {
	this->Add(num);
	this->Add(c);
	this->Add(num2);
	this->answer = ans;
}


Expression::Expression(Number num, char c, Expression exp, Number ans) {
	this->Add(num);
	this->Add(c);
	this->Add(exp);
	this->answer = ans;
}



Expression::Expression(Expression exp, char c, Number num, Number ans) {
	this->Add(exp);
	this->Add(c);
	this->Add(num);
	this->answer = ans;
}

void Expression::AddParenthesis(void) {
	this->question.insert(this->question.begin(), Point('('));
	this->question.push_back(Point(')'));
}


bool Expression::CheckValid() {
	int cnt = 0;
	int length = this->question.size();
	if (length == 0) {
		return this->valid = false;
	}
	if (this->question[0].type == 0 && this->question[0].symbol != '(') {
		return this->valid = false;
	}
	if (this->question[length -1].type == 0 && this->question[length - 1].symbol != ')') {
		return this->valid = false;
	}
	if (length == 2) return this->valid = false;
	for (int i = 1; i < length - 1; i++) {
		if (this->question[i].type == 1) {
			if (this->question[i - 1].type == 1 || this->question[i + 1].type == 1) {
				return this->valid = false;
			}
		}
		else {
			char c, c1, c2;
			c = this->question[i].symbol;
			switch (c)
			{
			case '+':
			case '-':
			case '*':
			case '/': {
				if (this->question[i - 1].type == 0) {
					c1 = this->question[i - 1].symbol;
					if (c1 != '(' && c1 != ')') {
						return this->valid = false;
					}
				}
				if (this->question[i + 1].type == 0) {
					c2 = this->question[i + 1].symbol;
					if (c2 != '(' && c2 != ')') {
						return this->valid = false;
					}
				}
				break;
			}
			case '(': {
				if (this->question[i - 1].type == 1) {
					return this->valid = false;
				}
				else if (this->question[i - 1].symbol == ')') {
					return this->valid = false;
				}
				if (this->question[i + 1].type == 0) {
					if (this->question[i + 1].symbol != '(') {
						return this->valid = false;
					}
				}
				break;
			}
			case ')': {
				if (this->question[i + 1].type == 1) {
					return this->valid = false;
				}
				else if (this->question[i + 1].symbol == '(') {
					return this->valid = false;
				}
				if (this->question[i - 1].type == 0) {
					if (this->question[i - 1].symbol != ')') {
						return this->valid = false;
					}
				}
				break;
			}
			default:
				return this->valid = false;
			}
		}
	}
	for (int i = 0; i < length; i++) {
		if (this->question[i].type == 0) {
			if (this->question[i].symbol == '(') {
				cnt++;
			}
			if (this->question[i].symbol == ')') {
				cnt--;
				if (cnt < 0) {
					return this->valid = false;
				}
			}
		}
	}
	if (cnt > 0) {
		return this->valid = false;
	}
	return true;
}


vector<Point> Expression::Nifix2Postfix() {	//中缀转后缀，后缀表达式用 vector 返回
	vector<Point> postfix_expression;	//后缀表达式，用于返回
	stack<Point> symbol_stack;	//运算符栈
	for (Point x : this->question) {
		if (x.type == 1) {
			postfix_expression.push_back(x);
		}
		else {
			switch (x.symbol)
			{
				case '(': {
					symbol_stack.push(x);
					break;
				}
				case ')': {
					while (true) {
						if (symbol_stack.empty() == true) {	//输入出错，匹配不到左括号
							postfix_expression.clear();
							return postfix_expression;
						}
						if (symbol_stack.top().symbol == '(') {
							symbol_stack.pop();
							break;
						}
						postfix_expression.push_back(symbol_stack.top());
						symbol_stack.pop();
					}
					break;
				}
				case '*':
				case '/': {
					while (symbol_stack.empty() == false) {
						char c = symbol_stack.top().symbol;
						if (c == '*' || c == '/') {
							postfix_expression.push_back(symbol_stack.top());
							symbol_stack.pop();
						}
						else {
							break;
						}
					}
					symbol_stack.push(x);
					break;
				}
				case '+':
				case '-': {
					while (symbol_stack.empty() == false && symbol_stack.top().symbol != '(') {
						postfix_expression.push_back(symbol_stack.top());
						symbol_stack.pop();
					}
					symbol_stack.push(x);
					break;
				}
				default: {
//					cout << "没有人能把我的代码跑到这里\n";
					break;
				}
			}
		}
	}
	while (symbol_stack.empty() == false) {
		postfix_expression.push_back(symbol_stack.top());
		symbol_stack.pop();
	}
	return postfix_expression;
}


Number Expression::Calculate() {	//计算后缀表达式
	if (this->CheckValid() == false) {	//输入不合法
		this->valid = false;
		return Number(-1, 0, 0);
	}
	vector<Point> postfix_expression = this->Nifix2Postfix();
	stack<Number> cal_stack;
	if (postfix_expression.size() == 0) {	//输入出错
		this->valid = false;
		return Number(-1, 0, 0);
	}
	for (Point x : postfix_expression) {
		if (x.type == 1) {
			cal_stack.push(x.num);
		}
		else {
			Number elem;	//当前计算结果
			Number elem1;	//左操作数
			Number elem2;	//右操作数
			if (cal_stack.empty() == true) {	//输入出错
				this->valid = false;
				return Number(-1, 0, 0);
			}
			else {
				elem2 = cal_stack.top();	//获取右操作数
				cal_stack.pop();
			}
			if (cal_stack.empty() == true) {	//输入出错
				this->valid = false;
				return Number(-1, 0, 0);
			}
			else {
				elem1 = cal_stack.top();	//获取左操作数
				cal_stack.pop();
			}
			switch (x.symbol)									//计算 
			{
				case '+': elem = elem1 + elem2; break;
				case '-': elem = elem1 - elem2; break;
				case '*': elem = elem1 * elem2; break;
				case '/': elem = elem1 / elem2; break;
			}
			cal_stack.push(elem);
		}
	}
	if (cal_stack.size() != 1) {
		this->valid = false;
		return Number(-1, 0, 0);
	}
	return this->answer = cal_stack.top();
}
