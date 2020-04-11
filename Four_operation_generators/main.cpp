#include "widget.h"
#include<string.h>
#include<qdebug.h>
#include"./algorithm/make.h"
#include <QApplication>
#include <QStyleFactory>
#include <iostream>
#include<queue>
#include<fstream>
using namespace std;
#define maxlen_filename 100

struct Topt
{
    bool n=false,r=false,e=false, a=false;//选择参数
    char filename1[maxlen_filename];
    char filename2[maxlen_filename];
    int num_n, num_r;
}opt;
char temp[maxlen_filename];

void Choose(int argc, char* argv[]) {//参数选择
    for (int i = 0; i < argc - 1; i++) {
        if (strcmp(argv[i], "-n") == 0) {
            opt.n = true;
            strcpy(temp, argv[i+1]);
            opt.num_n = atoi(temp);
        }
        if (strcmp(argv[i], "-r") == 0) {
            opt.r = true;
            strcpy(temp, argv[i + 1]);
            opt.num_r = atoi(temp);
        }
        if (strcmp(argv[i], "-e") == 0) {
            opt.e = true;
            strcpy(opt.filename1, argv[i + 1]);
        }
        if (strcmp(argv[i], "-a") == 0) {
            opt.a = true;
            strcpy(opt.filename2, argv[i + 1]);
        }

    }
}



int main(int argc, char *argv[])
{
    Choose(argc, argv);
        if (opt.r==false&&opt.n==true) {
            qDebug() << "-r 参数不能缺少" << endl;
            return -1;
        }
        if (opt.n == false && opt.r == true)
            if (!build_problem(opt.num_r, 10)) {
                qDebug() << "生成失败" << endl;
                return -1;
            }
            else return 0;
        if(opt.n == true && opt.r == true)
            if (!build_problem(opt.num_r, opt.num_n)) {
                qDebug() << "生成失败" << endl;
                return -1;
            }
            else return 0;

        if (opt.a == true && opt.e == true) {
            queue<int> correct, wrong;
            int number = 1;//题目标号
            string answer, problem;
            ifstream in_problem(opt.filename1);
            ifstream in_answer(opt.filename2);
            if (!in_answer.is_open() || !in_problem.is_open())
                return -1;
            while (getline(in_problem, problem) && getline(in_answer, answer)) {
                problem = getpoint_problem(problem);
                answer = getpoint_answer(answer);
                //
        //        if(problem.size()==0||answer.size()==0){
        //            wrong.push(number);
        //            number++;
        //            continue;
        //        }
                if (!check_answer(problem, answer))
                    wrong.push(number);
                else correct.push(number);
                number++;
            }
            ofstream fileout("./Grade.txt", ios::trunc);//如果之前有同名文件则覆盖
            fileout.close();
            string filename = "./Grade.txt";
            ofstream out(filename);
            if (out.is_open()) {
                out << "Correct: " << correct.size() << "(";
                if (!correct.empty()) {
                    out << correct.front();
                    correct.pop();
                }
                while (!correct.empty()) {
                    out << "," << correct.front();
                    correct.pop();
                }
                out << ")" << endl;
                out << "Wrong: " << wrong.size() << "(";
                if (!wrong.empty()) {
                    out << wrong.front();
                    wrong.pop();
                }
                while (!wrong.empty()) {
                    out << "," << wrong.front();
                    wrong.pop();
                }
                out << ")" << endl;
                return 0;
            }
        }
    QApplication a(argc, argv);
    QApplication::setStyle(QStyleFactory::create("Fusion"));
    Widget w;
    w.show();
    return a.exec();
}
