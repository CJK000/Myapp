#include "form2.h"
#include "ui_form2.h"
#include "widget.h"
#include <QFileDialog>
#include<string.h>
#include<fstream>
#include"success_ui.h"
#include"./algorithm/make.h"
#include"result.h"
using namespace std;

Form2::Form2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form2)
{
    ui->setupUi(this);
    ui->lineEdit->setPlaceholderText(tr("请输入导入题目文件"));
}

Form2::~Form2()
{
    delete ui;
}

void Form2::on_pushButton_clicked()
{
    QString filename =QFileDialog::getOpenFileName(this,tr("请选择导入题目文件"),"./",tr("文本文件(*txt)"));
    ui->lineEdit->setText(filename);
}

void Form2::on_pushButton_2_clicked()
{
    QString filename=ui->lineEdit->text();
    if(filename.isEmpty()){
        return;
    }
    string filename_std=filename.toStdString();
    ofstream fileout("./setting.txt",ios::trunc);//如果之前有同名文件则覆盖
    fileout.close();
    ofstream out("./setting.txt");
    if(out.is_open()){
        out <<filename_std;
        out.close();
    }

    if(!ui->label_6->text().isEmpty())return;

    success_ui *W = new success_ui;
    W->show();
    ui->label_6->setNum(1);
    string buffer;
    ifstream in(filename_std);
    if(in.is_open()){
        getline(in,buffer);
        buffer=getpoint_problem(buffer);
        if(buffer.size()==0)ui->label_7->setText(tr("读取失败"));
        QString str = QString::fromStdString(buffer);
        ui->label_7->setText(str);
    }

}

void Form2::on_pushButton_4_clicked()
{
    Widget *W=new Widget;
    W->show();
    this->hide();
}

void Form2::on_pushButton_3_clicked()
{
    static int count=2;
    int number;
    if(ui->label_6->text().isEmpty())return;

    ifstream address("./setting.txt");
    if(!address.is_open())return;
    string temp;
    getline(address,temp);
    address.close();

    ofstream out("./Answers.txt",ios::app);
    string answer;
    static string buffer;
    static ifstream in(temp);
    if(!in.is_open())return;
    if(in.eof()){
        if(out.is_open()){
            answer=ui->lineEdit_2->text().toStdString();
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
        answer=ui->lineEdit_2->text().toStdString();
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
    answer=ui->lineEdit_2->text().toStdString();
    number=count-2;
    if(out.is_open()){
        out<<number<<".";
        out<<answer<<endl;
        out.close();
    }
    ui->lineEdit_2->clear();
    getline(in,buffer);
}
