#include "testexcel.h"
#include "ui_testexcel.h"

TestExcel::TestExcel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestExcel)
{
    ui->setupUi(this);
    excel = new ExcelConfig(ui->tableWidget);
    excel->OpenFile("C:\\Users\\i.tabachnik\\Desktop\\EXE\\Config.xlsx");
}

TestExcel::~TestExcel()
{
    delete excel;
    delete ui;
}

void TestExcel::on_pushButton_clicked()
{
    excel->ExtractOpenShortTabel();
}

void TestExcel::on_pushButton_2_clicked()
{
    excel->ExtractOptionsFPGA();
}
