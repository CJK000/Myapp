#include "form3.h"
#include "ui_form3.h"
#include"widget.h"
#include"./algorithm/make.h"
#include"success_ui.h"
#include"unsuccess_ui.h"
#include<fstream>
#include<string>
#include"QString"
#include"result.h"
using namespace std;

Form3::Form3(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form3)
{
    ui->setupUi(this);
}

Form3::~Form3()
{
    delete ui;
}

void Form3::on_pushButton_2_clicked()
{
    this->hide();
    Widget *W=new Widget;
    W->show();
}

void Form3::on_pushButton_3_clicked()
{
    if(!ui->label_6->text().isEmpty())return;
    int problem_number= ui->spinBox->text().toInt();
    int max_number=ui->spinBox_2->text().toInt();
    if(!build_problem(max_number,problem_number)){
        unsuccess_ui *w=new unsuccess_ui;
        w->show();
    }
    else{
        success_ui *W = new success_ui;
        W->show();
    }
    ui->label_6->setNum(1);
    string buffer;
    ifstream in("./Exercises.txt");
    if(in.is_open()){
        getline(in,buffer);
        buffer=getpoint_problem(buffer);
        if(buffer.size()==0)ui->label_7->setText(tr("读取失败"));
        QString str = QString::fromStdString(buffer);
        ui->label_7->setText(str);
    }
}

void Form3::on_pushButton_clicked()
{
    static int count=2;
    int number;
    if(ui->label_6->text().isEmpty())return;
    ofstream out("./Answers.txt",ios::app);
    string answer;
    static string buffer;
    static ifstream in("./Exercises.txt");
    if(!in.is_open())return;
    if(in.eof()){
        if(out.is_open()){
            answer=ui->lineEdit->text().toStdString();
            number=count-1;
            out<<number<<".";
            out<<answer<<endl;
            out.close();
        }
        this->hide();
        result *W=new result;
        W->show();
        return;
    }
    ui->label_6->clear();
    ui->label_6->setNum(count);
    if(count==2){
        getline(in,buffer);//舍弃掉第一行
        getline(in,buffer);
        ofstream fileout("./Answers.txt",ios::trunc);//如果之前有同名文件则覆盖
        fileout.close();
        answer=ui->lineEdit->text().toStdString();
        if(out.is_open()){
            out<<1<<".";
            out<<answer<<endl;
            out.close();
        }
    }
    count++;
    buffer=getpoint_problem(buffer);
    if(buffer.size()==0)ui->label_7->setText(tr("读取失败"));
    QString str = QString::fromStdString(buffer);
    ui->label_7->setText(str);
    answer=ui->lineEdit->text().toStdString();
    number=count-2;
    if(out.is_open()){
        out<<number<<".";
        out<<answer<<endl;
        out.close();
    }
    ui->lineEdit->clear();
    getline(in,buffer);
}
