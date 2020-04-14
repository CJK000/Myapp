#include"make.h"
#include<fstream>
#include<string>
#include<vector>
#include<string>
#include<set>
#include<random>
#include<qstring.h>
#include<qdebug.h>

using namespace std;

Make::Make(int n, int m) {
    this->max_number = n-1;
    this->problem_number = m;
    this->AVLroot = NULL;
//	stringSet.clear();
    srand(time(0));
}

bool Make::CheckNumber() {
    if (this->max_number < 0)return false;
    else if (this->problem_number <= 0)return false;
    else if (this->max_number == 0) if (this->problem_number > 1)return false;
    else if (this->max_number == 1) if (this->problem_number > 40)return false;
    else if (this->max_number == 2) if (this->problem_number > 500)return false;
    else if (this->max_number == 3) if (this->problem_number > 10000)return false;
    else if (this->max_number == 4) if (this->problem_number > 50000)return false;
    else if (this->max_number < 10) if(this->problem_number > 1000000)return false;
    else if (this->max_number < 100) if (this->problem_number > 10000000)return false;
    else if (this->problem_number > 30000000)return false;
    return true;
}


Expression Make::MakeProblem(void) {
//	if (this->CheckNumber() == false)return Expression();
    vector<Expression> v;	//����������Ŀ�ķ���ֵ
    while (v.size() == 0) {
        v = (this->*this->randMake[rand() % 4])(this->max_number, this->max_number, rand() % 3 + 1, 1);
        if (this->max_number > 1289) {	//������ִ��� 1289 ʱ���ܻ����ɴ������Ŀ���ж�һ����Ŀ�Ƿ���ȷ
            if (v.size() > 0) {
                int n_ret;	//���ص� n ��ʽ��
                n_ret = rand() % v.size();
                if (Expression(v[n_ret].ToString()).answer == v[n_ret].answer) {	//��Ŀ��Ч
                    return v[n_ret];
                }
                else {	//��Ŀ�д�
                    v.clear();
                }
            }

        }
    }
    return v[rand() % v.size()];
}




/*
bool Make::CheckExist(Expression exp) {
    return this->stringSet.find(exp.ToString()) != this->stringSet.end() ;
}

void Make::Insert(Expression exp) {
    this->stringSet.insert(exp.ToString());
}
*/



//���� b + c = a
vector<Expression> Make::RandPlus(int max_n, int max_de, int symbol_n, int output) {
    vector<Expression> v;
    Number a(max_n, max_de);
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
//		if (v.size() > 0 && this->trie.Insert(v[0].ToString()) == true) {
        if (v.size() > 0 && insertAVL(this->AVLroot, v[0].ToString()+v[0].answer.ToString()) == true) {
            for (Expression e : v) {
//				this->trie.Insert(e.ToString());
                insertAVL(this->AVLroot, e.ToString()+e.answer.ToString());
            }
        }
        else {
            v.clear();
        }
    }
    return v;
}



//���� a - b = c
vector<Expression> Make::RandMinus(int max_n, int max_de, int symbol_n, int output) {
    vector<Expression> v;
    Number a(max_n, max_de);
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
//		if (v.size() > 0 && this->trie.Insert(v[0].ToString()) == true) {
        if (v.size() > 0 && insertAVL(this->AVLroot, v[0].ToString() + v[0].answer.ToString()) == true) {
            for (Expression e : v) {
//				this->trie.Insert(e.ToString());
                insertAVL(this->AVLroot, e.ToString() + e.answer.ToString());
            }
        }
        else {
            v.clear();
        }
    }
    return v;
}




//���� b * c = a
vector<Expression> Make::RandMul(int max_n, int max_de, int symbol_n, int output) {
    Expression ret;
    vector<Expression> v;
    Number a(max_n, max_de);
    Number b;
    Number c;
    if (max_n == 0) return v;	//����̫С������������Ŀ��ֱ���˳�
    while (a == Number(0, 0, 0))a = Number(max_n, max_de);
    if (symbol_n == 1) {
        int t = 0;
        while (b == Number(0, 0, 0)) {
            if (t == 3)return v;	//��ֹ��ѭ��
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
//		if (v.size() > 0 && this->trie.Insert(v[0].ToString()) == true) {
        if (v.size() > 0 && insertAVL(this->AVLroot, v[0].ToString() + v[0].answer.ToString()) == true) {
            for (Expression e : v) {
//				this->trie.Insert(e.ToString());
                insertAVL(this->AVLroot, e.ToString() + e.answer.ToString());
            }
        }
        else {
            v.clear();
        }
    }
    return v;
}


//���� a / b = c
vector<Expression> Make::RandDiv(int max_n, int max_de, int symbol_n, int output) {
    vector<Expression> v;
    if (max_n == 0) return v;
    Number a(max_n, max_de);
    while (a == Number(0, 0, 0))a = Number(max_n, max_de);
    Number b, c;
    if (symbol_n == 1) {
        int t = 0;
        while (b == Number(0, 0, 0) || c.CheckNumber(max_n, max_de) == false) {
            if (t == 3) return v;	//��ֹ��ѭ��
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
                if (t++ == 3)break;	//���ζ�����ʧ�����˳���������ѭ��
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
//		if (v.size() > 0 && this->trie.Insert(v[0].ToString()) == true) {
        if (v.size() > 0 && insertAVL(this->AVLroot, v[0].ToString() + v[0].answer.ToString()) == true) {
            for (Expression e : v) {
//				this->trie.Insert(e.ToString());
                insertAVL(this->AVLroot, e.ToString() + e.answer.ToString());
            }
        }
        else {
            v.clear();
        }
    }
    return v;

}
bool check_answer(string problem,string answer){
    Number user_answer(answer);	//���û��Ĵ�ת���� Number ����
    Number cal_answer;	//�洢��������������ȷ��
    QString str = QString::fromStdString(problem);
    cal_answer = Expression(problem).answer;
    //���ַ�����ʼ��Expression����ʱ����ɼ�����ȷ��
    //����ȷ�𰸸�ֵ�� cal_answer

    if (cal_answer.CheckNumber() == false) {	//��Ŀ��ʽ�д�
        return false;
    }
    else {
        if (user_answer.CheckNumber() == false) {	//�û��𰸸�ʽ�д�
            return false;
        }
        else {
            if (cal_answer == user_answer) {
                //����ȷ
                return true;
            }
            else {
                //�𰸴���
                return false;	//�������ת��Ϊ�ַ����������Ӧλ��
            }
        }
      }
}

bool build_problem(int max_number,int problem_number){
    Make m(max_number,problem_number);	//��ʼ��һ�� Make �࣬����Ϊ�������
    if(m.CheckNumber()==false)return false;
        Expression problem;	//���ڽ��շ��ص���Ŀ
        int cnt = 0;	//��������������������Ŀ������
        string filename1 = "./Exercises.txt";
        string filename2 = "./Answers.txt";
        ofstream out_1(filename1);
        ofstream out_2(filename2);
        if (out_1.is_open()&&out_2.is_open()) {
            while (cnt < problem_number) {
                problem = m.MakeProblem();	//����һ������Ҫ�����Ŀ
                if (problem.question.size() > 0) {	//����ֵ��������Ŀ��������Ŀ�ɹ�
                    out_1 << cnt + 1 << ".";
                    out_2 << cnt + 1 << ".";
                    out_1 << problem.ToString() << endl;
                    out_2 << problem.answer.ToString() << endl;
                    cnt++;	//��������һ
                }
                else {
                    //������Ŀʧ�ܣ��������ֵ̫С���޷�����ָ��������Ŀ��
                    return false;
                }
            }
        }
        return true;
}

string getpoint_problem(string s) {//�����Ŀ������Ĳ���
    int start_pos=0,end_pos=0;
    int i;
    for (i = 0; i < (int)s.size(); i++) {
        if (s[i] == '.')
            start_pos=i;
        if(s[i]=='=')
            end_pos=i;
    }
    if (start_pos==0)return "";//�Ҳ�����ŷָ��
    if (s[start_pos - 1] >= '0' && s[start_pos - 1] <= '9') {
        return s.substr(start_pos+1, end_pos-1);
    }
    else return "";
}
string getpoint_answer(string s){
    int start_pos=0;
    int i;
    for (i = 0; i < (int)s.size(); i++) {
        if (s[i] == '.')
            start_pos=i;
    }
    if (start_pos==0)return "";//�Ҳ�����ŷָ��
    if (s[start_pos - 1] >= '0' && s[start_pos - 1] <= '9') {
        return s.substr(start_pos+1, s.size());
    }
    else return "";
}

