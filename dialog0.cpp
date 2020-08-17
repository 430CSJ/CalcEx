#include "dialog0.h"
#include "ui_dialog0.h"

Dialog0::Dialog0(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog0)
{
    ui->setupUi(this);
}

Dialog0::~Dialog0()
{
    delete ui;
}
