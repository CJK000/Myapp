#include "success_ui.h"
#include "ui_success_ui.h"

success_ui::success_ui(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::success_ui)
{
    ui->setupUi(this);
}

success_ui::~success_ui()
{
    delete ui;
}
