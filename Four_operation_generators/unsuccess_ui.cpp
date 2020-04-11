#include "unsuccess_ui.h"
#include "ui_unsuccess_ui.h"

unsuccess_ui::unsuccess_ui(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::unsuccess_ui)
{
    ui->setupUi(this);
}

unsuccess_ui::~unsuccess_ui()
{
    delete ui;
}
