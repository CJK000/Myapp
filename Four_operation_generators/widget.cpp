#include "widget.h"
#include "ui_widget.h"
#include "form.h"
#include "form1.h"
#include"form2.h"
#include"form3.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle(QString("四则运算生成器"));
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()//转到操作手册
{
    Form *W = new Form;
    W->show();
}

void Widget::on_pushButton_2_clicked()//转到关于我们
{
    Form1 *W = new Form1;
    W->show();
}

void Widget::on_pushButton_3_clicked()//转到题目生成
{
    this->hide();
    Form3*W=new Form3;
    W->show();
}

void Widget::on_pushButton_4_clicked()//转到自定义模式
{
   this->hide();
   Form2*W=new Form2;
   W->show();
}
