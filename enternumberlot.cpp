#include "enternumberlot.h"
#include "ui_enternumberlot.h"

EnterNumberLot::EnterNumberLot(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::EnterNumberLot)
{
    ui->setupUi(this);
    this->setWindowTitle("Enter number lot");
}

EnterNumberLot::~EnterNumberLot()
{
    delete ui;
}

void EnterNumberLot::on_pushButton_clicked()
{
    this->setVisible(false);
}
