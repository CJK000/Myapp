#include "form2.h"
#include "ui_form2.h"
#include "widget.h"
#include <QFileDialog>

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
    QString filename =QFileDialog::getOpenFileName(this,tr("请选择导入题目文件"),"C:",tr("文本文件(*txt)"));
    ui->lineEdit->setText(filename);
}

void Form2::on_pushButton_2_clicked()
{
    QString filename=ui->lineEdit->text();
    if(filename.isEmpty()){
        return;
    }
}

void Form2::on_pushButton_4_clicked()
{
    Widget *W=new Widget;
    W->show();
}
