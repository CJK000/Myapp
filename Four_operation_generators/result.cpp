#include "result.h"
#include "ui_result.h"
#include<fstream>
#include<queue>
#include<string>
#include"QString"
#include<qdebug.h>
#include"./algorithm/make.h"
#include"widget.h"
#include<sstream>


result::result(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::result)
{//核对答案并输出到文件
    queue<int> correct,wrong;
    int number=1;//题目标号
    string answer,problem;
    ui->setupUi(this);
    ifstream in_problem("./Exercises.txt");
    ifstream in_answer("./Answers.txt");
    if(!in_answer.is_open()||!in_problem.is_open())
        return;
    while(getline(in_problem,problem)&&getline(in_answer,answer)){
        problem=getpoint_problem(problem);
        answer=getpoint_answer(answer);
        //
//        if(problem.size()==0||answer.size()==0){
//            wrong.push(number);
//            number++;
//            continue;
//        }
        if(!check_answer(problem,answer))
            wrong.push(number);
        else correct.push(number);
        number++;
    }
    ofstream fileout("./Grade.txt",ios::trunc);//如果之前有同名文件则覆盖
    fileout.close();
    string filename="./Grade.txt";
    ofstream out(filename);
    if(out.is_open()){
        out<<"Correct: "<<correct.size()<<"(";
        if(!correct.empty()){
            out<<correct.front();
            correct.pop();
        }
        while(!correct.empty()){
            out<<","<<correct.front();
            correct.pop();
        }
        out<<")"<<endl;
        out<<"Wrong: "<<wrong.size()<<"(";
        if(!wrong.empty()){
            out<<wrong.front();
            wrong.pop();
        }
        while(!wrong.empty()){
            out<<","<<wrong.front();
            wrong.pop();
        }
        out<<")"<<endl;
    }
    //从文件读答案输出到gui
    string result;
    ifstream fin("./Grade.txt",ios::in);
    stringstream buf;
    buf<<fin.rdbuf();
    result=buf.str();
    QString str_result = QString::fromStdString(result);
    ui->textBrowser->setText(str_result);

}

result::~result()
{
    delete ui;
}

void result::on_pushButton_clicked()
{
    this->hide();
    Widget *W=new Widget;
    W->show();
}
