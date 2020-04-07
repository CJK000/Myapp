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
	int t = 0;//���������ֻ����ǰ���ʽ����
	while (i < length) {
		while (i < length && s[i] == ' ')i++;
		if (i == length) break;	//��ʼ���ɹ�
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
				if (i < length) {	//�������
					this->question.clear();
					this->valid = false;
					return;
				}
				else {
					return;	//��ʼ���ɹ�
				}
			}
			default:
				break;
			}
		}
		if (t == this->question.size()) {	//����ʧ��
			this->question.clear();
			this->valid = false;
			return;
		}
		t++;
	}
	this->Calculate();	//ֱ�Ӽ������
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


vector<Point> Expression::Nifix2Postfix() {	//��׺ת��׺����׺���ʽ�� vector ����
	vector<Point> postfix_expression;	//��׺���ʽ�����ڷ���
	stack<Point> symbol_stack;	//�����ջ
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
						if (symbol_stack.empty() == true) {	//�������ƥ�䲻��������
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
//					cout << "û�����ܰ��ҵĴ����ܵ�����\n";
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


Number Expression::Calculate() {	//�����׺���ʽ
	if (this->CheckValid() == false) {	//���벻�Ϸ�
		this->valid = false;
		return Number(-1, 0, 0);
	}
	vector<Point> postfix_expression = this->Nifix2Postfix();
	stack<Number> cal_stack;
	if (postfix_expression.size() == 0) {	//�������
		this->valid = false;
		return Number(-1, 0, 0);
	}
	for (Point x : postfix_expression) {
		if (x.type == 1) {
			cal_stack.push(x.num);
		}
		else {
			Number elem;	//��ǰ������
			Number elem1;	//�������
			Number elem2;	//�Ҳ�����
			if (cal_stack.empty() == true) {	//�������
				this->valid = false;
				return Number(-1, 0, 0);
			}
			else {
				elem2 = cal_stack.top();	//��ȡ�Ҳ�����
				cal_stack.pop();
			}
			if (cal_stack.empty() == true) {	//�������
				this->valid = false;
				return Number(-1, 0, 0);
			}
			else {
				elem1 = cal_stack.top();	//��ȡ�������
				cal_stack.pop();
			}
			switch (x.symbol)									//���� 
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
